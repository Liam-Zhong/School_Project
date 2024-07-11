#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#define MAXNUM 255

int num[26] = { 0 };
char saveLetter[26] = { '0' };
int countNum[26] = { 0 };
char codeTemp[MAXNUM] = { '0' };

//���������Ĵ洢��ʾ
typedef struct HTNode {
	int weight;//����Ȩֵ
	int parent, lchild, rchild;//����˫�ס����ӡ��Һ��ӵ��±�
	char data;
}HTNode, * HuffmanTree;

int Frequent(char s[], int& n) {
	int len = strlen(s);
	int num[26] = { 0 };

	memset(num, 0, sizeof(num));//ȫ��Ϊ0
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
	int min = MAXNUM;//��Сֵ
	int lmin = MAXNUM;//��Сֵ
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
* ���������ĸ��ڵ�洢��HuffmanTree����Ķ�̬����������У�Ϊ��ʵ�ַ��㣬
* �����0�ŵ�Ԫ��ʹ�ã���1�ŵ�Ԫ��ʼʹ�ã���������Ĵ�СΪ2n
* ��Ҷ�ӽ�㼯�д洢��ǰ�沿��1~n��λ�ã��������n-1��λ�ô洢�����Ҷ�ӽ��
*/
void CreateHuffmanTree(HuffmanTree& HT, int n) {//�����������HT
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	//cout << m << endl;
	HT = new HTNode[m + 1];//0�ŵ�Ԫδ�ã�������Ҫ��̬����m+1����Ԫ��HT[m]��ʾ�����
	for (int i = 1; i < m; i++) {
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].data = saveLetter[i - 1];//��ĸ
	}
	for (int i = 1; i <= n; i++) {
		//cin >> HT[i].weight;//����ǰn����Ԫ��Ҷ�ӽ���Ȩֵ
		HT[i].weight = countNum[i - 1];
	}
	int s1 = 0, s2 = 0;
	//��ʼ�����������濪ʼ������������
	for (int i = n + 1; i <= m; i++) {
		Select(HT, i - 1, s1, s2);
		//��HT[k]��1<=k<=i-1)��ѡ��������˫����Ϊ0��Ȩֵ��С�Ľ�㣬
		//������������HT�е����s1��s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		//�õ��½��i,��ɭ����ɾ��s1,s2,��s1��s2��˫������0��Ϊi
		HT[i].lchild = s1;
		HT[i].rchild = s2;//s1,s2�ֱ���Ϊi�����Һ���
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i��ȨֵΪ���Һ���Ȩֵ֮��
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
	//��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢�ڱ����HC��
	HC = new char* [n + 1];//����洢n���ַ�����ı����ռ�
	char* cd;
	cd = new char[n];//������ʱ���ÿ���ַ�����Ķ�̬����ռ�
	cd[n - 1] = '\0';//���������
	int start = 0, c, f = 0;
	for (int i = 1; i <= n; i++) {//����ַ������������
		start = n - 1;//start��ʼʱָ����󣬼����������λ��
		c = i;
		f = HT[i].parent;//fָ����c��˫�׽��
		while (f != 0) {//��Ҷ�ӽ�㿪ʼ���ϻ��ݣ�ֱ�������
			start--;//����һ��start��ǰָ��һ��λ��
			if (HT[f].lchild == c)
				cd[start] = '0';//���c��f�����ӣ������ɴ���0
			else
				cd[start] = '1';//���c��f���Һ��ӣ������ɴ���1
			c = f; f = HT[f].parent;//�������ϻ���
		}
		HC[i] = new char[n - start];//Ϊ��i���ַ�������޿ռ�
		strcpy(HC[i], &cd[start]);//����õı������ʱ�ռ�cd���Ƶ�HC�ĵ�ǰ����
	}
	delete[] cd;//�ͷ���ʱ�ռ�
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
	while (codeTemp[j] != '\0') {//codeTemp���ݴ�01���봮
		if (codeTemp[j] == '0') {
			i = HT[i].lchild;//����
		}
		else if (codeTemp[j] == '1') {
			i = HT[i].rchild;//�Һ���
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
		memset(codeTemp, 0, sizeof codeTemp);//�������
	}

}