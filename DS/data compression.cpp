#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#define MAXNUM 255

int num[26] = { 0 };
char saveLetter[26] = { '0' };
int countNum[26] = { 0 };
char codeTemp[MAXNUM] = { '0' };

//哈夫曼树的存储表示
typedef struct HTNode {
	int weight;//结点的权值
	int parent, lchild, rchild;//结点的双亲、左孩子、右孩子的下标
	char data;
}HTNode, * HuffmanTree;

int Frequent(char s[], int& n) {
	int len = strlen(s);
	int num[26] = { 0 };

	memset(num, 0, sizeof(num));//全置为0
	int i = 0, j = 0;
	while (s[i] != '\0') {
		j = s[i] - 97;
		num[j]++;
		i++;
	}
	j = 0;
	for (i = 0; i < 26; i++) {
		if (num[i] != 0) {
			saveLetter[j] = char(i + 97);
			countNum[j] = num[i];
			j++;
		}
	}
	n = j;
	for (int k = 0; k < n; k++) {
		if (k == n - 1) {
			cout << saveLetter[k] << ":" << countNum[k] << endl;
		}
		else
		{
			cout << saveLetter[k] << ":" << countNum[k] << " ";
		}
	}
	return n;
}


void Select(HuffmanTree& HT, int Max, int& s1, int& s2) {
	int min = MAXNUM;//最小值
	int lmin = MAXNUM;//次小值
	for (int i = 1; i <= Max; i++) {
		if (HT[i].parent == 0) {
			if (HT[i].weight < min) {
				min = HT[i].weight;
				s1 = i;
			}
		}
	}
	for (int i = 1; i <= Max; i++) {
		if (HT[i].parent == 0) {
			if (HT[i].weight < lmin && i != s1) {
				lmin = HT[i].weight;
				s2 = i;
			}
		}
	}
}

/*
* 哈夫曼树的各节点存储在HuffmanTree定义的动态分配的数组中，为了实现方便，
* 数组的0号单元不使用，从1号单元开始使用，所以数组的大小为2n
* 将叶子结点集中存储在前面部分1~n个位置，而后面的n-1个位置存储其余非叶子结点
*/
void CreateHuffmanTree(HuffmanTree& HT, int n) {//构造哈夫曼树HT
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	//cout << m << endl;
	HT = new HTNode[m + 1];//0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点
	for (int i = 1; i < m; i++) {
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].data = saveLetter[i - 1];//字母
	}
	for (int i = 1; i <= n; i++) {
		//cin >> HT[i].weight;//输入前n个单元中叶子结点的权值
		HT[i].weight = countNum[i - 1];
	}
	int s1 = 0, s2 = 0;
	//初始化结束，下面开始创建哈夫曼树
	for (int i = n + 1; i <= m; i++) {
		Select(HT, i - 1, s1, s2);
		//在HT[k]（1<=k<=i-1)中选择两个其双亲域为0且权值最小的结点，
		//并返回它们在HT中的序号s1和s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		//得到新结点i,从森林中删除s1,s2,将s1和s2的双亲域由0改为i
		HT[i].lchild = s1;
		HT[i].rchild = s2;//s1,s2分别作为i的左右孩子
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i的权值为左右孩子权值之和
		if (i == m) {
			HT[i].parent = 0;
		}
	}
}

void ShowHT(HuffmanTree& HT, int n) {
	int m = 2 * n - 1;
	for (int i = 1; i <= m; i++) {
		cout << i;
		cout << " " << HT[i].weight;
		cout << " " << HT[i].parent;
		cout << " " << HT[i].lchild;
		cout << " " << HT[i].rchild << endl;
	}
}

typedef char** HuffmanTreeCode;

void CreateHuffmanCode(HuffmanTree HT, HuffmanTreeCode& HC, int n) {
	//从叶子到根逆向求每个字符的哈夫曼编码，存储在编码表HC中
	HC = new char* [n + 1];//分配存储n个字符编码的编码表空间
	char* cd;
	cd = new char[n];//分配临时存放每个字符编码的动态数组空间
	cd[n - 1] = '\0';//编码结束符
	int start = 0, c, f = 0;
	for (int i = 1; i <= n; i++) {//逐个字符求哈夫曼编码
		start = n - 1;//start开始时指向最后，即编码结束符位置
		c = i;
		f = HT[i].parent;//f指向结点c的双亲结点
		while (f != 0) {//从叶子结点开始向上回溯，直到根结点
			start--;//回溯一次start向前指向一个位置
			if (HT[f].lchild == c)
				cd[start] = '0';//结点c是f的左孩子，则生成代码0
			else
				cd[start] = '1';//结点c是f的右孩子，则生成代码1
			c = f; f = HT[f].parent;//继续向上回溯
		}
		HC[i] = new char[n - start];//为第i个字符编码分呸空间
		strcpy(HC[i], &cd[start]);//将求得的编码从临时空间cd复制到HC的当前行中
	}
	delete[] cd;//释放临时空间
}

void ShowCode(HuffmanTree& HT, HuffmanTreeCode& HC, int n, char str1[]) {
	for (int i = 0; str1[i] != '\0'; i++) {
		for (int j = 1; j <= n; j++) {
			if (str1[i] == saveLetter[j - 1]) {
				cout << HC[j];
				strcat_s(codeTemp, HC[j]);
			}
		}
	}
	cout << endl;
}

void CreateHuffmanReCode(HuffmanTree& HT, HuffmanTreeCode& HC, int n) {
	int i = 2 * n - 1;
	int j = 0;
	while (codeTemp[j] != '\0') {//codeTemp是暂存01编码串
		if (codeTemp[j] == '0') {
			i = HT[i].lchild;//左孩子
		}
		else if (codeTemp[j] == '1') {
			i = HT[i].rchild;//右孩子
		}
		if (HT[i].lchild == 0) {
			cout << HT[i].data;
			i = 2 * n - 1;
		}
		j++;
	}
	cout << endl;
}


void ShowHC(HuffmanTreeCode& HC, int n) {
	for (int i = 1; i <= n; i++) {
		if (i != n)
			cout << saveLetter[i - 1] << ":" << HC[i] << " ";
		else
			cout << saveLetter[i - 1] << ":" << HC[i] << endl;
	}
}

int main() {
	int n;
	char string[50] = { '0' };
	while (true) {
		cin >> string;
		if (string[0] == '0')
			break;
		n = Frequent(string, n);
		HuffmanTree ht;
		HuffmanTreeCode hc;
		CreateHuffmanTree(ht, n);
		CreateHuffmanCode(ht, hc, n);
		ShowHT(ht, n);
		ShowHC(hc, n);
		ShowCode(ht, hc, n, string);
		CreateHuffmanReCode(ht, hc, n);
		memset(codeTemp, 0, sizeof codeTemp);//清空数组
	}

}