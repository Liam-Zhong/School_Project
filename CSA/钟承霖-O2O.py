#%% md
# 特征工程
#%%
from datetime import date
from datetime import datetime
import numpy as np
import pandas as pd
from sklearn.model_selection import StratifiedKFold
from sklearn.metrics import roc_auc_score
from sklearn.preprocessing import MinMaxScaler
from xgboost import XGBClassifier
import warnings

warnings.filterwarnings("ignore")
datapath = './data/'
featurepath = './feature/'
fd_seperator = ':'
#%% md
## 工具函数
#%%
#计算折扣率，将满减和折扣统一
def get_discount_rate(s):
    s = str(s)
    if s == 'null':
        return -1
    s = s.split(fd_seperator)
    if len(s) == 1:
        return float(s[0])
    else:
        return round((1.0 - float(s[1]) / float(s[0])), 3)

#获取是否满减
def get_if_fd(s):
    return int(fd_seperator in s)

#获取满减的条件
def get_full_value(s):
    if fd_seperator in s:
        return int(s.split(fd_seperator)[0])
    return np.nan

#获取满减的优惠
def get_reduction_value(s):
    if pd.isna(s) or s == 'null':
        return np.nan
    parts = s.split(fd_seperator)
    if len(parts) == 1:
        return np.nan
    return int(parts[1])

def get_day_gap(s):
    """Get the day gap between received date and used date."""
    received_date, used_date = s.split(fd_seperator)
    if 'null' in s:
        return -1
    received_date = datetime.strptime(received_date, '%Y%m%d')
    used_date = datetime.strptime(used_date, '%Y%m%d')
    return (used_date - received_date).days

#获取Label，输入内容为Date:Date_received
def get_label(s):
    s = s.split(fd_seperator)
    if s[0] == 'null':
        return 0
    if s[1] == 'null':
        return -1
    elif (date(int(s[0][0:4]), int(s[0][4:6]), int(s[0][6:8])) -
          date(int(s[1][0:4]), int(s[1][4:6]), int(s[1][6:8]))).days <= 15:
        return 1
    else:
        return 0

#增加折扣相关特征
def add_discount(df):
    df['if_fd'] = df['discount_rate'].apply(get_if_fd)
    df['full_value'] = df['discount_rate'].apply(get_full_value)
    df['reduction_value'] = df['discount_rate'].apply(get_reduction_value)
    df['discount_rate'] = df['discount_rate'].apply(get_discount_rate)
    df.distance = df.distance.replace('null', np.nan)
    return df

#计算日期间隔
def add_day_gap(df):
    df['day_gap'] = df['date'].astype(
        'str') + ':' + df['date_received'].astype('str')
    df['day_gap'] = df['day_gap'].apply(get_day_gap)
    return df

#获取label
def add_label(df):
    df['label'] = df['date'].astype('str') + ':' + df['date_received'].astype(
        'str')
    df['label'] = df['label'].apply(get_label)
    return df

def is_firstlastone(x):
    if x == 0:
        return 1
    elif x > 0:
        return 0
    else:
        #return -1
        return np.nan

def get_day_gap_before(x):
    dates = x.split('-')[-1].split(':')
    date_received = int(x.split('-')[0])
    gaps = [date_received - int(d) for d in dates if date_received > int(d)]
    return min(gaps) if gaps else -1

def get_day_gap_after(x):
    dates = x.split('-')[-1].split(':')
    date_received = int(x.split('-')[0])
    gaps = [int(d) - date_received for d in dates if int(d) > date_received]
    return min(gaps) if gaps else -1

def add_agg_feature_names(df, df_group, group_cols, value_col, agg_ops,
                          col_names):
    df_group[value_col] = df_group[value_col].astype('float')
    df_agg = pd.DataFrame(
        df_group.groupby(group_cols)[value_col].agg(agg_ops)).reset_index()
    df_agg.columns = group_cols + col_names
    df = df.merge(df_agg, on=group_cols, how="left")
    return df

# 统计特征处理函数
def add_agg_feature(df, df_group, group_cols, value_col, agg_ops, keyword):
    col_names = []
    for op in agg_ops:
        col_names.append(keyword + '_' + value_col + '_' + op)
    df = add_agg_feature_names(df, df_group, group_cols, value_col, agg_ops,
                               col_names)
    return df

# 因为count特征很多，开发了这个专门提取count特征的函数
def add_count_new_feature(df, df_group, group_cols, new_feature_name):
    df_group[new_feature_name] = 1
    df_group = df_group.groupby(group_cols).agg('sum').reset_index()
    df = df.merge(df_group, on=group_cols, how="left")
    return df
#%% md
## 特征群生成
#%%
def get_merchant_feature(feature):
    merchant = feature[['merchant_id', 'coupon_id', 'distance', 'date_received', 'date']].copy()

    merchant_ids = merchant['merchant_id'].unique()
    merchant_feature = pd.DataFrame({'merchant_id': merchant_ids})

    # 计算每个商户的交易总次数
    total_sales = merchant[merchant['date'].notna()].groupby('merchant_id').size().rename('total_sales')
    merchant_feature = merchant_feature.merge(total_sales, on='merchant_id', how='left')

    # 计算每个商户销售中使用了优惠券的交易次数
    sales_use_coupon = merchant[(merchant['date'].notna()) & (merchant['coupon_id'].notna())].groupby(
        'merchant_id').size().rename('sales_use_coupon')
    merchant_feature = merchant_feature.merge(sales_use_coupon, on='merchant_id', how='left')

    # 计算每个商户发放的优惠券总数
    total_coupon = merchant[merchant['coupon_id'].notna()].groupby('merchant_id').size().rename('total_coupon')
    merchant_feature = merchant_feature.merge(total_coupon, on='merchant_id', how='left')

    # 统计每个商户含有优惠券交易中的距离特征
    distance_data = \
        merchant[(merchant['date'].notna()) & (merchant['coupon_id'].notna()) & (merchant['distance'].notna())][
            ['merchant_id', 'distance']]
    distance_data = distance_data[distance_data['distance'] != 'null']  # 过滤掉无效的'null'值
    distance_data['distance'] = distance_data['distance'].astype(float)  # 将distance列转换为浮点数
    distance_stats = distance_data.groupby('merchant_id')['distance'].agg(['min', 'max', 'mean', 'median'])
    distance_stats.columns = ['merchant_distance_' + col for col in distance_stats.columns]
    merchant_feature = merchant_feature.merge(distance_stats, on='merchant_id', how='left')

    # 填充NaN值
    merchant_feature = merchant_feature.fillna({'sales_use_coupon': 0, 'total_coupon': 0})

    # 计算商户发放优惠券的使用率和使用优惠券的交易占比
    merchant_feature['merchant_coupon_transfer_rate'] = merchant_feature['sales_use_coupon'] / merchant_feature[
        'total_coupon']
    merchant_feature['coupon_rate'] = merchant_feature['sales_use_coupon'] / merchant_feature['total_sales']

    return merchant_feature


def get_user_feature(feature):
    user = feature[[
        'user_id', 'merchant_id', 'coupon_id', 'discount_rate', 'distance',
        'date_received', 'date'
    ]].copy()

    user = user.drop_duplicates()

    def safe_to_int(series):
        return pd.to_numeric(series, errors='coerce').fillna(0).astype(int)

    def replace_null_with(series, value):
        return series.replace('null', value).fillna(value)

    # 每个用户交易的商户数
    t1 = user.loc[replace_null_with(user['date'], np.nan).notna(), ['user_id', 'merchant_id']]
    t1 = t1.drop_duplicates()
    user_feature = add_count_new_feature(user[['user_id']].drop_duplicates(), t1[['user_id']], 'user_id',
                                         'count_merchant')

    # 统计和商户距离的最大值、最小值、平均值、中位值
    t2 = user.loc[(replace_null_with(user['date'], np.nan).notna()) &
                  (replace_null_with(user['coupon_id'], np.nan).notna()) &
                  (replace_null_with(user['distance'], np.nan).notna()),
    ['user_id', 'distance']]
    t2['distance'] = safe_to_int(t2['distance'])
    user_feature = add_agg_feature(user_feature, t2, ['user_id'], 'distance', ['min', 'max', 'mean', 'median'], 'user')

    # 每个用户使用优惠券消费的次数
    t7 = user.loc[(replace_null_with(user['date'], np.nan).notna()) &
                  (replace_null_with(user['coupon_id'], np.nan).notna()),
    ['user_id']]
    user_feature = add_count_new_feature(user_feature, t7, 'user_id', 'buy_use_coupon')

    # 每个用户消费的总次数
    t8 = user.loc[replace_null_with(user['date'], np.nan).notna(), ['user_id']]
    user_feature = add_count_new_feature(user_feature, t8, 'user_id', 'buy_total')

    # 每个用户收到优惠券的总数
    t9 = user.loc[replace_null_with(user['coupon_id'], np.nan).notna(), ['user_id']]
    user_feature = add_count_new_feature(user_feature, t9, 'user_id', 'coupon_received')

    # 用户从收到优惠券到用券消费的时间间隔
    t10 = user.loc[(replace_null_with(user['date_received'], np.nan).notna()) &
                   (replace_null_with(user['date'], np.nan).notna()),
    ['user_id', 'date_received', 'date']]
    t10 = add_day_gap(t10)
    user_feature = add_agg_feature(user_feature, t10[['user_id', 'day_gap']], ['user_id'], 'day_gap',
                                   ['min', 'max', 'mean', 'median'], 'user')
    user_feature[['count_merchant', 'buy_use_coupon', 'buy_total', 'coupon_received']] = user_feature[
        ['count_merchant', 'buy_use_coupon', 'buy_total', 'coupon_received']].fillna(0)
    user_feature['buy_use_coupon_rate'] = user_feature['buy_use_coupon'] / user_feature['buy_total']
    user_feature['user_coupon_transfer_rate'] = user_feature['buy_use_coupon'] / user_feature['coupon_received']

    return user_feature


def get_user_merchant_feature(feature):
    t = feature[['user_id', 'merchant_id']].drop_duplicates()
    t0 = feature.loc[feature.date.notnull(), ['user_id', 'merchant_id']]
    user_merchant = add_count_new_feature(t.copy(), t0, ['user_id', 'merchant_id'], 'user_merchant_buy_total')
    t1 = feature.loc[feature.coupon_id.notnull(), ['user_id', 'merchant_id']]
    user_merchant = add_count_new_feature(user_merchant, t1, ['user_id', 'merchant_id'], 'user_merchant_received')
    t2 = feature.loc[feature.date.notnull() & feature.date_received.notnull(), ['user_id', 'merchant_id']]
    user_merchant = add_count_new_feature(user_merchant, t2, ['user_id', 'merchant_id'], 'user_merchant_buy_use_coupon')
    t3 = feature[['user_id', 'merchant_id']]
    user_merchant = add_count_new_feature(user_merchant, t3, ['user_id', 'merchant_id'], 'user_merchant_any')
    t4 = feature.loc[feature.date.notnull() & feature.coupon_id.isnull(), ['user_id', 'merchant_id']]
    user_merchant = add_count_new_feature(user_merchant, t4, ['user_id', 'merchant_id'], 'user_merchant_buy_common')
    user_merchant['user_merchant_buy_use_coupon'].fillna(0, inplace=True)
    user_merchant['user_merchant_buy_common'].fillna(0, inplace=True)
    user_merchant['user_merchant_coupon_transfer_rate'] = (
            user_merchant['user_merchant_buy_use_coupon'].astype(float) /
            user_merchant['user_merchant_received'].astype(float)
    ).fillna(0)
    user_merchant['user_merchant_coupon_buy_rate'] = (
            user_merchant['user_merchant_buy_use_coupon'].astype(float) /
            user_merchant['user_merchant_buy_total'].astype(float)
    ).fillna(0)
    user_merchant['user_merchant_rate'] = (
            user_merchant['user_merchant_buy_total'].astype(float) /
            user_merchant['user_merchant_any'].astype(float)
    ).fillna(0)
    user_merchant['user_merchant_common_buy_rate'] = (
            user_merchant['user_merchant_buy_common'].astype(float) /
            user_merchant['user_merchant_buy_total'].astype(float)
    ).fillna(0)
    return user_merchant


#提取穿越特征
def get_leakage_feature(dataset):
    t = dataset[['user_id']].copy()
    t['this_month_user_receive_all_coupon_count'] = 1
    t = t.groupby('user_id').agg('sum').reset_index()

    t1 = dataset[['user_id', 'coupon_id']].copy()
    t1['this_month_user_receive_same_coupn_count'] = 1
    t1 = t1.groupby(['user_id', 'coupon_id']).agg('sum').reset_index()

    t2 = dataset[['user_id', 'coupon_id', 'date_received']].copy()
    t2.date_received = t2.date_received.astype('str')
    #如果出现相同的用户接收相同的优惠券在接收时间上用‘：’连接上第n次接受优惠券的时间
    t2 = t2.groupby([
        'user_id', 'coupon_id'
    ])['date_received'].agg(lambda x: ':'.join(x)).reset_index()
    #将接收时间的一组按着':'分开，这样就可以计算接受了优惠券的数量,apply是合并
    t2['receive_number'] = t2.date_received.apply(lambda s: len(s.split(':')))
    t2 = t2[t2.receive_number > 1]
    #最大接受的日期
    t2['max_date_received'] = t2.date_received.apply(
        lambda s: max([int(d) for d in s.split(':')]))
    #最小的接收日期
    t2['min_date_received'] = t2.date_received.apply(
        lambda s: min([int(d) for d in s.split(':')]))
    t2 = t2[['user_id', 'coupon_id', 'max_date_received', 'min_date_received']]

    t3 = dataset[['user_id', 'coupon_id', 'date_received']]
    t3 = pd.merge(t3, t2, on=['user_id', 'coupon_id'], how='left')
    #这个优惠券最近接受时间
    t3['this_month_user_receive_same_coupon_lastone'] = t3.max_date_received - t3.date_received.astype(
        int)
    #这个优惠券最远接受时间
    t3['this_month_user_receive_same_coupon_firstone'] = t3.date_received.astype(
        int) - t3.min_date_received

    t3.this_month_user_receive_same_coupon_lastone = t3.this_month_user_receive_same_coupon_lastone.apply(
        is_firstlastone)
    t3.this_month_user_receive_same_coupon_firstone = t3.this_month_user_receive_same_coupon_firstone.apply(
        is_firstlastone)
    t3 = t3[[
        'user_id', 'coupon_id', 'date_received',
        'this_month_user_receive_same_coupon_lastone',
        'this_month_user_receive_same_coupon_firstone'
    ]]

    #提取第四个特征,一个用户所接收到的所有优惠券的数量
    t4 = dataset[['user_id', 'date_received']].copy()
    t4['this_day_receive_all_coupon_count'] = 1
    t4 = t4.groupby(['user_id', 'date_received']).agg('sum').reset_index()

    #提取第五个特征,一个用户不同时间所接收到不同优惠券的数量
    t5 = dataset[['user_id', 'coupon_id', 'date_received']].copy()
    t5['this_day_user_receive_same_coupon_count'] = 1
    t5 = t5.groupby(['user_id', 'coupon_id',
                     'date_received']).agg('sum').reset_index()

    #一个用户不同优惠券的接受时间
    t6 = dataset[['user_id', 'coupon_id', 'date_received']].copy()
    t6.date_received = t6.date_received.astype('str')
    t6 = t6.groupby([
        'user_id', 'coupon_id'
    ])['date_received'].agg(lambda x: ':'.join(x)).reset_index()
    t6.rename(columns={'date_received': 'dates'}, inplace=True)

    t7 = dataset[['user_id', 'coupon_id', 'date_received']]
    t7 = pd.merge(t7, t6, on=['user_id', 'coupon_id'], how='left')
    t7['date_received_date'] = t7.date_received.astype('str') + '-' + t7.dates
    t7['day_gap_before'] = t7.date_received_date.apply(get_day_gap_before)
    t7['day_gap_after'] = t7.date_received_date.apply(get_day_gap_after)
    t7 = t7[[
        'user_id', 'coupon_id', 'date_received', 'day_gap_before',
        'day_gap_after'
    ]]

    other_feature = pd.merge(t1, t, on='user_id')
    other_feature = pd.merge(other_feature, t3, on=['user_id', 'coupon_id'])
    other_feature = pd.merge(other_feature,
                             t4,
                             on=['user_id', 'date_received'])
    other_feature = pd.merge(other_feature,
                             t5,
                             on=['user_id', 'coupon_id', 'date_received'])
    other_feature = pd.merge(other_feature,
                             t7,
                             on=['user_id', 'coupon_id', 'date_received'])
    return other_feature

#%% md
## 特征集成
#%%
def f(dataset, feature, if_train):
    result = add_discount(dataset)
    merchant_feature = get_merchant_feature(feature)
    result = result.merge(merchant_feature, on='merchant_id', how="left")
    user_feature = get_user_feature(feature)
    result = result.merge(user_feature, on='user_id', how="left")
    user_merchant = get_user_merchant_feature(feature)
    result = result.merge(user_merchant,
                          on=['user_id', 'merchant_id'],
                          how="left")

    leakage_feature = get_leakage_feature(dataset)
    result = result.merge(leakage_feature,
                          on=['user_id', 'coupon_id', 'date_received'],
                          how='left')

    result.drop_duplicates(inplace=True)
    if if_train:
        result = add_label(result)
    return result
#%% md
## 特征输出
#%%
#########################特征集成及输出#############################
#生成滑窗特征
def slide_feature_generate(feature_function):
    off_train = pd.read_csv(datapath + 'ccf_offline_stage1_train.csv',
                            header=0,
                            keep_default_na=False)
    off_train.columns = [
        'user_id', 'merchant_id', 'coupon_id', 'discount_rate', 'distance',
        'date_received', 'date'
    ]

    off_test = pd.read_csv(datapath + 'ccf_offline_stage1_test_revised.csv',
                           header=0,
                           keep_default_na=False)
    off_test.columns = [
        'user_id', 'merchant_id', 'coupon_id', 'discount_rate', 'distance',
        'date_received'
    ]

    #交叉训练集一：收到券的日期大于4月14日和小于5月14日
    dataset1 = off_train[(off_train.date_received >= '201604014')
                         & (off_train.date_received <= '20160514')]
    #交叉训练集一特征：线下数据中领券和用券日期大于1月1日和小于4月13日
    feature1 = off_train[(off_train.date >= '20160101') &
                         (off_train.date <= '20160413') |
                         ((off_train.date == 'null') &
                          (off_train.date_received >= '20160101') &
                          (off_train.date_received <= '20160413'))]

    #交叉训练集二：收到券的日期大于5月15日和小于6月15日
    dataset2 = off_train[(off_train.date_received >= '20160515')
                         & (off_train.date_received <= '20160615')]
    #交叉训练集二特征：线下数据中领券和用券日期大于2月1日和小于5月14日
    feature2 = off_train[(off_train.date >= '20160201') &
                         (off_train.date <= '20160514') |
                         ((off_train.date == 'null') &
                          (off_train.date_received >= '20160201') &
                          (off_train.date_received <= '20160514'))]

    #测试集
    dataset3 = off_test
    #测试集特征 :线下数据中领券和用券日期大于3月15日和小于6月30日的
    feature3 = off_train[((off_train.date >= '20160315') &
                          (off_train.date <= '20160630')) |
                         ((off_train.date == 'null') &
                          (off_train.date_received >= '20160315') &
                          (off_train.date_received <= '20160630'))]

    dftrain1 = feature_function(dataset1, feature1, True)
    dftrain2 = feature_function(dataset2, feature2, True)
    dftrain = pd.concat([dftrain1, dftrain2], axis=0)

    dftest = feature_function(dataset3, feature3, False)

    dftrain.drop(['date'], axis=1, inplace=True)
    dftrain.drop(['merchant_id'], axis=1, inplace=True)
    dftest.drop(['merchant_id'], axis=1, inplace=True)

    #输出特征
    print('输出特征')
    dftrain.to_csv(featurepath + 'train_s' + feature_function.__name__ +
                   '.csv',
                   index=False,
                   sep=',')
    dftest.to_csv(featurepath + 'test_s' + feature_function.__name__ + '.csv',
                  index=False,
                  sep=',')
#%%
#生成特征文件
slide_feature_generate(f)
#%% md
## 训练及结果输出
#%%
# 读取训练集和测试集
train_df = pd.read_csv(featurepath + 'train_sf.csv')
test_df = pd.read_csv(featurepath + 'test_sf.csv')
# 填充缺失值
train_df = train_df.fillna(0)
test_df = test_df.fillna(0)
# 特征列和目标列
id_cols = ['user_id', 'coupon_id', 'date_received']
target_col = 'label'
feature_cols = [col for col in train_df.columns if col not in id_cols + [target_col]]
# 归一化特征
scaler = MinMaxScaler()
train_df[feature_cols] = scaler.fit_transform(train_df[feature_cols])
test_df[feature_cols] = scaler.transform(test_df[feature_cols])
# XGBoost 参数
params = {
    'objective': 'binary:logistic',
    'eval_metric': 'auc',
    'n_estimators': 200,
    'max_depth': 5,
    'learning_rate': 0.05,
    'lambda': 1e-05,
    'alpha': 1e-05,
    'subsample': 0.9,
    'colsample_bytree': 0.6,
    'seed': 1024,
    'n_jobs': 12
}
# 5折交叉验证
n_splits = 5
kf = StratifiedKFold(n_splits=n_splits, shuffle=True, random_state=520)
cv_scores = []
test_preds = np.zeros(test_df.shape[0])

for fold, (train_idx, val_idx) in enumerate(kf.split(train_df[feature_cols], train_df[target_col])):
    print(f'Fold {fold + 1}')
    train_x, train_y = train_df[feature_cols].iloc[train_idx], train_df[target_col].iloc[train_idx]
    val_x, val_y = train_df[feature_cols].iloc[val_idx], train_df[target_col].iloc[val_idx]
    model = XGBClassifier(**params)
    model.fit(train_x, train_y, eval_set=[(val_x, val_y)], early_stopping_rounds=100, verbose=100)
    val_pred = model.predict_proba(val_x)[:, 1]
    cv_score = roc_auc_score(val_y, val_pred)
    cv_scores.append(cv_score)
    print(f'AUC = {cv_score:.4f}')
    test_preds += model.predict_proba(test_df[feature_cols])[:, 1] / n_splits
print(f'Mean AUC = {np.mean(cv_scores):.4f}')
test_df['Probability'] = test_preds
test_df[['user_id', 'coupon_id', 'date_received', 'Probability']].to_csv('submission.csv', index=False, header=False)