#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LENGTH 60
#define INPUT_LIMIT 82
#define PI 3.14159265
#define HELP "The calculator can do compound mathematic calculations.\n\
Here are some instructions it can recognize:\n\
1) plus: + expression: a+b calculate the sum of a+b.\n\
2) minus: - expression: a-b calculate the difference between a-b.\n\
3) multiply: * expression: a*b calculate the product of a*b.\n\
4) devision: / expression: a/b calculate the quotient of a/b\n\
5) sin: s() expression: s(x) calculate the sine of angle x.\n\
6) cos: c() expression: c(x) calculate the cosine of angle x.\n\
7) tan: t() expressiom: t(x) calculate the tangent of angle x.\n\
8) arcsin: S() expression: S(x) get the angle of arcsine x.\n\
9) arccos: C() expression: C(x) get the angle of arccosine x.\n\
10) arctan: T() expression: T(x) get the angle of arctangent x.\n\
11) power: ^ expression: a^b calculate the a power to b.\n\
12) parentheses: ( ) expresion: (a+b)*c calculate a+b first then *c.\n\
"

//函数 
_Bool safeInput(void);
_Bool analyseInput(void);
_Bool getRange(int *startopr, int *endopr, int *startnum, int *endnum);
void printHelp(void);
void calRange(void);
int Calculate(void);


//变量 
float number[MAX_LENGTH];
char operators[MAX_LENGTH];
char input[100];
int length1=0;//记录操作符数组中元素的个数
int length2=0;//记录数字数组中元素的个数
int rangenum[2];//数字计算范围 
int rangeopr[2];//符号计算范围 
_Bool safe=0;

int main() {
    char userInput[10];
    while(1) {
        printf("Enter 's' to begin calculation, or enter '-h' to get the help menu.\nEnter 'q' to exit.\n>> ");
        scanf("%s", userInput);
        if(strcmp(userInput, "s") == 0) {
            Calculate();
        } else if(strcmp(userInput, "-h") == 0) {
            printHelp();
        } else if(strcmp(userInput, "q") == 0) {
            printf("Exiting program...\n");
            break;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
    return 0;
}

int Calculate(void){
    int n=0;
    //初始化数组 
    for(n=0;n<INPUT_LIMIT;n++){
        if(n<MAX_LENGTH){
            number[n]=0;
            operators[n]='\0';
        }
        input[n]='\0';
    }
    fgets(input,INPUT_LIMIT,stdin);
    while(input[0]!='q'){
        if(safeInput())
            return 1;
        analyseInput();
        while(operators[0]!='\0'){//计算 
            if(!getRange(&rangeopr[0],&rangeopr[1],&rangenum[0],&rangenum[1])){
                rangeopr[0]=0;
                rangeopr[1]=length1-1;
                rangenum[0]=0;
                rangenum[1]=length2-1;
            }
            calRange();
        }
        printf("%f\n",number[0]);
        for(n=0;n<INPUT_LIMIT;n++){//重置 
            if(n<MAX_LENGTH){
                number[n]=0;
                operators[n]='\0';
            }
            input[n]='\0';
        }
        fgets(input,INPUT_LIMIT,stdin);
    }
 }

_Bool safeInput(void){//防止不合法输入 
    int n=0;//字符索引 
    unsigned long pos=0;//小数和操作符 
    unsigned long i=0;
    while(input[n]!='\n'){
        if(((input[n]<40)||(input[n]>57)||(input[n]==','))&&(input[n]!='^')){
            if(((input[n]=='s')||(input[n]=='c')||(input[n]=='t')||(input[n]=='S')
                ||(input[n]=='C')||(input[n]=='T'))&&(input[n+1]!='(')){
                printf("Function operators should followed by brackets!(s(x)/(c(x)...)\n");
                return 1;
            }
            if((input[n]!='s')&&(input[n]!='c')&&(input[n]!='t')&&(input[n]!='S')&&(input[n]!='C')
               &&(input[n]!='T')){
                printf("Detected unexpected character: %c\n",input[n]);
                return 1;
            }
        }
        n++;
    }
    n=0;
	//计算负数 
    while(input[n]!='\n'){
        if(input[n]=='-'){
            if(((input[n-1]>=40)&&(input[n-1]<=47)&&(input[n-1]!=')'))||(n==0)||(input[n-1]=='^')){
                for(i=strlen(input)+1;i>=n+2;i--)
                    input[i]=input[i-2];
                input[n]='(';
                input[n+1]='0';
                for(i=n+3;i<=strlen(input)+1;i++){
                    if((input[i]!='.')&&(input[i]<'0')){
                        pos=i;
                        break;
                    }
                }
                for(i=strlen(input)+1;i>=pos+1;i--)
                    input[i]=input[i-1];
                input[pos]=')';
            }
        }
        n++;
    }
    return 0;
}

_Bool analyseInput(void){//分开操作符和数字 
    int m=0;//操作符数 
    int m2=0;//数字 
    int i=0;
    int n=0;
    int length=0;
    float multiple=0;//转换成浮点数 
    while(input[n]!='\n'){
    // 找操作符 
        if(((input[n]>=40)&&(input[n]<=47)&&(input[n]!=','))||(input[n]=='^')
           ||(input[n]=='s')||(input[n]=='c')||(input[n]=='t')||(input[n]=='S')
           ||(input[n]=='C')||(input[n]=='T'))
		   {
            operators[m]=input[n];
            m++;
            length1++;
            if(m>=MAX_LENGTH)
                return 1;
            n++;
        }
    // 数字 
        if((input[n]>='0')&&(input[n]<='9')){
            length2++;
            multiple=1;
            while((input[n]>='0')&&(input[n]<='9')){ 
                length++;
                n++;
            }
            n-=length;
    // 转换成浮点数 
            for(;length>0;length--){
                for(i=1;i<length;i++)
                    multiple*=10;
                number[m2]+=(input[n]-'0')*multiple;
                n++;
                multiple=1;
            }
            length=0;
    //找 . 
            if(input[n]=='.'){
                n++;
                multiple=0.1;
                while((input[n]>='0')&&(input[n]<='9')){
                    number[m2]+=(input[n]-'0')*multiple;
                    multiple*=0.1;
                    n++;
                }
            }
            m2++;
        }
    }
    return 0;
}

_Bool getRange(int *startopr, int *endopr, int *startnum, int *endnum){//先算 
    //() 
    int index=0;
    int n=0;
    int function=0;//三角函数 
    _Bool brackets=0;//用于判断是否存在左右括号
    
    while(operators[index]!=')'){
        if(operators[index]=='('){
            *startopr=index;
            brackets=1;
        }
        if(index+1<length1)
            index++;
        else
            break;

    }
    *endopr=index;
    //除了（都对应一个数 
    for(index=0;index<=(*startopr);index++){
        if((operators[index]!='(')&&(operators[index]!='s')
           &&(operators[index]!='c')&&(operators[index]!='t')
           &&(operators[index]!='S')&&(operators[index]!='C')&&(operators[index]!='T'))
            n++;
    }
    for(index=(*startopr);index<=(*endopr);index++){
    if((operators[index]=='s')||(operators[index]=='c')||(operators[index]=='t')
       ||(operators[index]=='S')||(operators[index]=='C')||(operators[index]=='T'))
        function++;
    }
    *startnum=n;
    *endnum=(*startnum)+(*endopr)-(*startopr)-1-function;
    return brackets;
}

void calRange(void){//算 
    
    int i=0;
    int j=0;
    int l1=rangeopr[1]-rangeopr[0]+1;//操作符长度 
    int l2=rangenum[1]-rangenum[0]+1;//数字长度 
    char bufopr[l1];//临时操作符 
    float bufnum[l2];//数字 
    
    for(i=rangenum[0];i<=rangenum[1];i++){
        bufnum[j]=number[i];
        j++;
    }
    j=0;
    for(i=rangeopr[0];(i<length1)&&(i<MAX_LENGTH);i++){
        if(i<=rangeopr[1]){
            bufopr[j]=operators[i];
            j++;
        }
        operators[i]=operators[i+l1];
        operators[i+l1]='\0';
    }
    
    if(bufopr[0]=='('){//去括号 
        for(i=0;i<l1;i++){
            if(bufopr[i+1]!=')'){
                bufopr[i]=bufopr[i+1];
                bufopr[i+1]='\0';
            }
            else{
                bufopr[i]='\0';
                bufopr[i+1]='\0';
                break;
            }
        }
        l1-=2;
    }
    for(i=0;i<l1;i++){
        if((bufopr[i]=='s')||(bufopr[i]=='c')||(bufopr[i]=='t')||(bufopr[i]=='S')
           ||(bufopr[i]=='C')||(bufopr[i]=='T')){
            if(bufopr[i]=='s')
                number[rangenum[0]]=sin(bufnum[i]*PI/180);
            else if(bufopr[i]=='c')
                number[rangenum[0]]=cos(bufnum[i]*PI/180);
            else if(bufopr[i]=='t')
                number[rangenum[0]]=tan(bufnum[i]*PI/180);
            else if(bufopr[i]=='S')
                number[rangenum[0]]=(asin(bufnum[i]))*180/PI;
            else if(bufopr[i]=='C')
                number[rangenum[0]]=(acos(bufnum[i]))*180/PI;
            else if(bufopr[i]=='T')
                number[rangenum[0]]=(atan(bufnum[i]))*180/PI;
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            i=-1;
        }
    }
    for(i=0;i<l1;i++){//幂 
        if(bufopr[i]=='^'){
            number[rangenum[0]]=pow(bufnum[i],bufnum[i+1]);
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            for(j=i+1;j<l2;j++){
                if(j+1<l2){
                    bufnum[j]=bufnum[j+1];
                    bufnum[j+1]=0;
                }
            }
            i=-1;
        }
    }
    /* * / */
    for(i=0;i<l1;i++){
        if((bufopr[i]=='*')||(bufopr[i]=='/')){
            if(bufopr[i]=='*')
                number[rangenum[0]]=bufnum[i]*bufnum[i+1];
            else
                number[rangenum[0]]=bufnum[i]/bufnum[i+1];
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            for(j=i+1;j<l2;j++){
                if(j+1<l2){
                    bufnum[j]=bufnum[j+1];
                    bufnum[j+1]=0;
                }
            }
            i=-1;
        }
    }
    /* + -*/
    for(i=0;i<l1;i++){
        if((bufopr[i]=='+')||(bufopr[i]=='-')){
            if(bufopr[i]=='+')
                number[rangenum[0]]=bufnum[i]+bufnum[i+1];
            else
                number[rangenum[0]]=bufnum[i]-bufnum[i+1];
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            for(j=i+1;j<l2;j++){
                if(j+1<l2){
                    bufnum[j]=bufnum[j+1];
                    bufnum[j+1]=0;
                }
            }
            i=-1;
        }
    }
    if(l2>1){
        /* 把结果返回到number */
        for(i=rangenum[0]+1;(i<length2)&&(i<MAX_LENGTH);i++){
            number[i]=number[i+l2-1];
            number[i+l2-1]=0;
        }
        
        length1-=l1;
        length2-=l2-1;
    }
}

void printHelp(void){
    printf("%s",HELP);
    printf("Index:\n");
    printf("Max Input avaliable: %d\n",INPUT_LIMIT-2);
    printf("float number of PI: %f\n",PI);
}

