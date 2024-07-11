#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstring>
#define MaxInt 32767
#define MVNum 100//最大顶点数
/* 注意是有向图，用邻接矩阵
*/
int D[MVNum];//起点开始到各个点的距离
int S[MVNum];//是否访问过
int Path[MVNum];
using namespace std;
typedef struct
{
	char vexs[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
int Locate(AMGraph& G, char s)//返回编号
{
	for (int i = 1; i <= G.vexnum; i++)
	{
		if (G.vexs[i] == s)
			return i;
	}
}
void Creat(AMGraph& G)
{
	for (int i = 1; i <= G.vexnum; i++)
	{
		cin >> G.vexs[i];
	}
	for (int i = 0; i <= G.arcnum; i++)
		for (int j = 0; j <= G.arcnum; j++)
		{
			G.arcs[i][j] = MaxInt;
		}
	for (int i = 0; i < G.arcnum; i++)
	{
		char a, b;
		int c;
		cin >> a >> b >> c;
		int h, t;
		h = Locate(G, a);
		t = Locate(G, b);
		G.arcs[h][t] = c;//有向图
	}
}
void Dijkstra(AMGraph& G, int v0)
{
	int n = G.vexnum;
	int v;
	for (v = 1; v <= n; v++)
	{
		S[v] = 0;
		D[v] = G.arcs[v0][v];
		if (D[v] < MaxInt)
			Path[v] = v0;
		else
			Path[v] = -1;
	}
	S[v0] = 1;
	D[v0] = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int min = MaxInt;
		int v = 1;
		for (int w = 1; w <= n; w++)
		{
			if (S[w] != 1 && D[w] <= min)
			{
				v = w;
				min = D[w];
			}
		}
		S[v] = 1;
		for (int w = 1; w <= n; w++)
		{
			if (S[w] != 1 && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];
				Path[w] = v;
			}
		}
	}
}
void Print(AMGraph& G, int s, int e)
{
	int r[MVNum];//记录路径的编号
	r[0] = e;
	int i = 1;
	while (Path[r[i - 1]] != -1)
	{
		r[i] = Path[r[i - 1]];
		i++;
	}
	for (int j = i - 1; j > 0; j--)
		cout << G.vexs[r[j]] << " ";
	cout << G.vexs[r[0]] << endl;
}
int main(void)
{
	int n, m;
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0)
			break;
		AMGraph G;
		G.vexnum = n;
		G.arcnum = m;
		Creat(G);
		char start, end;
		cin >> start >> end;
		int s, e;
		s = Locate(G, start);
		e = Locate(G, end);
		Dijkstra(G, s);
		cout << D[e] << endl;
		Print(G, s, e);
	}
	return 0;
}
