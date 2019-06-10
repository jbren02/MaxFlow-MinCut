//ѹ���ر���㷨Push-Relabel�㷨
#include<iostream>
#include<limits>
#include<iomanip>
#include<algorithm>//min()����
using namespace std;

struct Point{
	char ch;//�ڵ��ʶ 
	int e;//�����
	int h;//�߶� 
};
Point point[6];
int graph[6][6] = {
		{ 0, 16, 13, 0, 0, 0 },
		{ 0, 0, 10, 12, 0, 0 },
		{ 0, 4, 0, 0, 14, 0 },
		{ 0, 0, 9, 0, 0, 20 },
		{ 0, 0, 0, 7, 0, 4 },
		{ 0, 0, 0, 0, 0, 0 } };
int Push_Relabel(int s, int t, int n); //����Ϊ ���  �˵�  �ڵ��� 

int main(){
	int  n = 6;
	point[0].ch = 's';  point[0].e = 0; point[0].h = 0;
	point[1].ch = 'u';  point[1].e = 0; point[1].h = 0;
	point[2].ch = 'v';  point[2].e = 0; point[2].h = 0;
	point[3].ch = 'a';  point[3].e = 0; point[3].h = 0;
	point[4].ch = 'b';  point[4].e = 0; point[4].h = 0;
	point[5].ch = 't';  point[5].e = 0; point[5].h = 0;
	cout << "ԭʼ����ͼ�ڽӾ���" << endl;
	for (int i = 0; i <= 5; i++){
		for (int j = 0; j <= 5; j++){
			cout << setw(6) << graph[i][j] << " ";
		}
		cout << endl;
	}
	cout << "max_flow=" << Push_Relabel(0, n - 1, n) << endl;

	cout << "�����ʱ����ͼ����" << endl;
	for (int i = 0; i <= 5; i++){
		for (int j = 0; j <= 5; j++){
			cout << setw(6) << graph[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

int Push_Relabel(int s, int t, int n)
{
	int  max_flow;

	point[s].h = n;  //��ʼ��߶���Ϊn ���
	//��ʼ������Դ��Ŀ�� ����ȥ ����ʣ��ͼ 
	for (int u = 1; u <= t; u++) {
		if (graph[s][u] > 0) {
			point[u].e = graph[s][u];
			point[s].e -= graph[s][u];
			graph[u][s] = graph[s][u];
			graph[s][u] = 0;
		}
	}


	while (1) {
		int finishflag = 1;
		for (int u = s + 1; u < t; u++) {  //�������ڵ�s���ڵ�t����Ľڵ� 
			if (point[u].e > 0) {  //���ֿ��������0�Ľڵ� u  ����push 
				finishflag = 0;
				int relabel = 1;   //�ȼ���ڵ�u��Ҫrelabel  ��߸߶�h 

				for (int v = s; v <= t && point[u].e > 0; v++) {   //������push�Ķ���   
					if (graph[u][v] > 0 && point[u].h >point[v].h) {  //���ֽڵ�v 
						relabel = 0;  //����u����Ҫrelabel
						int bottleneck = min(graph[u][v], point[u].e);
						point[u].e -= bottleneck; //u�ڵ��������� 
						point[v].e += bottleneck; //v�ڵ���������
						graph[u][v] -= bottleneck;//��������ߵ�ʣ������
						graph[v][u] += bottleneck;//���·���ߵ�ʣ������
					}
				}
				if (relabel == 1) {  //û�п���push�Ķ���,u�ڵ���Ҫrelabel ��߸߶�
					point[u].h += 1;
				}
			}
		}

		if (finishflag == 1) { // ��Դ��ͻ����,ÿ�������e[i]��Ϊ0 
			max_flow = 0;
			for (int u = s; u <= t; u++) {
				if (graph[t][u] > 0) {
					max_flow += graph[t][u];
				}
			}
			//cout<<"max_flow="<<max_flow<<endl;
			break;
		}
	}
	return max_flow;
}