//Dinic�㷨
//BFS����ͼ��DFS������·���е���С��������
//ʱ�临�Ӷ� O(n^2*m)
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int Maxn = 10000 + 10;
const int INF = 0x6fffffff >> 2;

struct edge{
	int from, to, cap, flow;
};

struct Dinic{
	int n, m, s, t;//��������������Դ�㣬���
	vector<edge> edges;
	vector<int> f[Maxn];
	bool vis[Maxn];//���ʱ��
	int d[Maxn];
	int cur[Maxn];
	//---------------------------------------------------------------------------------
	//��ӱߣ���㡢���㡢����������
	void AddEdge(int from, int to, int cap)
	{
		edges.push_back({ from, to, cap, 0 });
		edges.push_back({ to, from, 0, 0 });
		m = edges.size();//����
		f[from].push_back(m - 2);//f[x]�д洢���ɽڵ�x�����ıߵı�ţ�f[x].size()�Ǵӽڵ�x�����ıߵ�����
		f[to].push_back(m - 1);
	}
	//---------------------------------------------------------------------------------
	//��������㷨������·�����ֲ�
	bool BFS()
	{
		memset(vis, 0, sizeof(vis));
		queue<int> q;
		q.push(s);
		d[s] = 0;
		vis[s] = 1;
		while (!q.empty())
		{
			int x = q.front(); q.pop();
			for (int i = 0; i<f[x].size(); i++)
			{
				edge &e = edges[f[x][i]];
				//cout<<"to="<<e.to<<"from="<<e.from<<' '<<e.flow<<' '<<e.cap<<' '<<vis[e.to]<<endl;
				if (!vis[e.to] && e.flow < e.cap) //ֻ���ǲ��������еĻ� 
				{
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;//���ͼ
					q.push(e.to);
				}
			}
		}
		return vis[t];//�ܷ񵽻�㣬���ܾͽ��� 
	}

	//---------------------------------------------------------------------------------
	int DFS(int x, int a)//xΪ��ǰ�ڵ㣬aΪ��ǰ��С���� 
	{
		if (x == t || a == 0) return a;
		int flow = 0, r;

		for (int& i = cur[x]; i < f[x].size(); i++)
		{
			edge& e = edges[f[x][i]];
			if (d[x] + 1 == d[e.to] && (r = DFS(e.to, min(a, e.cap - e.flow))) > 0)
			{
				e.flow += r;
				edges[f[x][i] ^ 1].flow -= r;//��λ������㣬�õ��䷴���
				flow += r;//�ۼ����� 
				a -= r;
				if (a == 0) break;
			}
		}
		return flow;
	}

	//---------------------------------------------------------------------------------	
	int MaxFlow(int s, int t)
	{
		this->s = s; this->t = t;
		int flow = 0;
		while (BFS())
		{

			memset(cur, 0, sizeof(cur));
			flow += DFS(s, INF);
		}
		return flow;
	}
}G;

int main()
{
	int x, y, z;
	int s, t;
	scanf("%d", &G.n);
	while (1)
	{
		scanf("%d%d%d", &x, &y, &z);
		if (!(x | y | z)) break;
		G.AddEdge(x, y, z);
	}
	scanf("%d%d", &s, &t);
	printf("%d\n", G.MaxFlow(s, t));
	system("pause");
	return 0;
}
