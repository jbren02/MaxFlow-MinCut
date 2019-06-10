//Dinic算法
//BFS求层次图，DFS求增广路径中的最小残余容量
//时间复杂度 O(n^2*m)
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
	int n, m, s, t;//定点数，边数，源点，汇点
	vector<edge> edges;
	vector<int> f[Maxn];
	bool vis[Maxn];//访问标记
	int d[Maxn];
	int cur[Maxn];
	//---------------------------------------------------------------------------------
	//添加边，起点、到点、容量、流量
	void AddEdge(int from, int to, int cap)
	{
		edges.push_back({ from, to, cap, 0 });
		edges.push_back({ to, from, 0, 0 });
		m = edges.size();//边数
		f[from].push_back(m - 2);//f[x]中存储了由节点x出发的边的编号，f[x].size()是从节点x出发的边的条数
		f[to].push_back(m - 1);
	}
	//---------------------------------------------------------------------------------
	//广度优先算法求增广路径及分层
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
				if (!vis[e.to] && e.flow < e.cap) //只考虑残留网络中的弧 
				{
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;//层次图
					q.push(e.to);
				}
			}
		}
		return vis[t];//能否到汇点，不能就结束 
	}

	//---------------------------------------------------------------------------------
	int DFS(int x, int a)//x为当前节点，a为当前最小残量 
	{
		if (x == t || a == 0) return a;
		int flow = 0, r;

		for (int& i = cur[x]; i < f[x].size(); i++)
		{
			edge& e = edges[f[x][i]];
			if (d[x] + 1 == d[e.to] && (r = DFS(e.to, min(a, e.cap - e.flow))) > 0)
			{
				e.flow += r;
				edges[f[x][i] ^ 1].flow -= r;//按位异或运算，得到其反向边
				flow += r;//累加流量 
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
