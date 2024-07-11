#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 10005

void CreateGraph(int n, int m);
int BFSTraverse(int i);

int G[MAXVEX][MAXVEX], Nv, Ne;
int visited[MAXVEX];

int main()
{
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && (n || m))
	{
		CreateGraph(n, m);
		for (int i = 1; i <= Nv; i++)
		{
			int count = BFSTraverse(i);
			double b = 100.0 * count / Nv;
			printf("%d: %.2f%%\n", i, b);
		}
	}

	return 0;
}

void CreateGraph(int n, int m)
{
	//���ڽӾ����ʾͼ
	int i, j;
	int v1, v2;
	Nv = n;
	Ne = m;
	for (i = 0; i <= Nv; i++)
	{
		for (j = 0; j <= Nv; j++)
		{
			G[i][j] = 0;  //��ʼ��
		}
	}
	for (i = 0; i < Ne; i++)  //ע�������Ƕ����
	{
		scanf("%d %d", &v1, &v2);
		G[v1][v2] = 1;
		G[v2][v1] = G[v1][v2];  //����ͼ�Գ�
	}
}

int BFSTraverse(int i)
{
	int q[MAXVEX] = { 0 }; //�������ʾ����
	int rear = -1, front = -1;
	int j;
	int temp;
	int cnt;

	int level;   //��ǰ������ڵĲ���
	int last;      //�ò�����һ�����
	int tail;    //���һ��������еĽ��

	for (j = 0; j <= Nv; j++)
	{
		visited[j] = 0;
	}

	visited[i] = 1;
	cnt = 1;
	level = 0;   //����㲻���ڲ�����
	last = i;
	q[++rear] = i;  //���
	while (front < rear)    //�ж϶����Ƿ�Ϊ��
	{
		temp = q[++front];  //����

		for (j = 1; j <= Nv; j++)
		{
			if (G[temp][j] && !visited[j])
			{
				visited[j] = 1;
				q[++rear] = j;
				cnt++;
				tail = j;
			}
		}
		if (temp == last)
		{
			level++;
			last = tail;
		}
		if (level == 6)
		{
			break;
		}
	}

	return cnt;
}

