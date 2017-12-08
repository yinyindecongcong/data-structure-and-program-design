#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//邻接矩阵实现图的常见算法，包括深/广度遍历，基于深/广度遍历的拓扑排序，最短路径，最小生成树
typedef vector<int> VI;
const int INT_MAX = 65535;
class matrix_graph{
public:
	//initialize
	matrix_graph():num_vertex(0), num_edge(0){}
	void init(){
		cout << "input the num_vertex and num_edge" << endl;
		cin >> num_vertex >> num_edge;
		VI V(num_vertex, INT_MAX);
		vector<VI> G1(num_vertex, V);
		for(int i = 0; i < num_vertex; i++) G1[i][i] = 0;
		G = G1;
		int i = num_edge, a, b, w;
		cout << "input edges" << endl;
		while(i--){
			cin >> a >> b >> w;
			G[a][b] = w;
			G[b][a] = w;
		}
	}
	int size(){ return num_vertex; }
	//DFS,BFS
	void DFS(){
		VI visit(num_vertex, 0);
		for(int i = 0; i < num_vertex; i++)
			if (visit[i] == 0) recursive_DFS(i, visit);
	}
	void BFS(int s = 0){
		VI visit(num_vertex, 0);
		queue<int> Q;
		for (int i = 0; i < num_vertex; i++)
			if (visit[(s + i) % num_vertex] == 0){
				Q.push((s + i) % num_vertex);
				visit[(s + i) % num_vertex] = 1;
				while(!Q.empty()){
					int k = Q.front();
					Q.pop();
					cout << k << ' ';
					for(int i = 0; i < num_vertex; i++)
						if (visit[i] == 0 && G[s][i] != INT_MAX) {
							Q.push(i);
							visit[i] = 1;
						}
				}
			}
	}
	//topological sort
	void depth_sort(VI & topological_order){
		topological_order.clear();
		VI visit(num_vertex, 0);
		for (int i = 0; i < num_vertex; i++)
			if (!visit[i]) recursive_depth_sort(i, visit, topological_order);
		for (auto a : topological_order) cout << a << ' ';
		cout << endl;
	}
	void breadth_sort(VI & topological_order){
		//初始化入度表
		topological_order.clear();
		VI in_arc(num_vertex, 0);
		for (int i = 0; i < num_vertex; i++)
			for (int j = 0; j < num_vertex; j++)
				in_arc[j] += (i != j && G[i][j] != INT_MAX);
		queue<int> Q; //存放入度为0的顶点
		for (int i = 0; i < num_vertex; i++) if (in_arc[i] == 0) Q.push(i);
		while(!Q.empty()){
			int k = Q.front();
			Q.pop();
			topological_order.push_back(k);
			//更新Q
			for(int i = 0; i < num_vertex; i++)
				if (G[k][i] != INT_MAX)
					if (--in_arc[i] == 0) Q.push(i);
		}
		for (auto a : topological_order) cout << a << ' ';
		cout << endl;
	}
	//最短路径
	//dijkstra
	void get_distance(int s, VI & dis){
		VI found(num_vertex, 0); //是否找到最短路径
		for (int i = 0; i < num_vertex; i++) dis[i] = G[s][i];
		dis[s] = 0;
		found[s] = 1;
		for (int i = 0; i < num_vertex - 1; i++){ //每次找到一个节点的最短路径，n - 1次即可
			int min = INT_MAX, v = s;
			for (int j = 0; j < num_vertex; j++)
				if (!found[j] && dis[j] < min){
					v = j;
					min = dis[j];
				}
			found[v] = 1;
			//更新dis
			for (int j = 0; j < num_vertex; j++)
				if (!found[j] && min + G[v][j] < dis[j])
					dis[j] = min + G[v][j];
		}
		for (auto a : dis) cout << a << ' ';
		cout << endl;
	}
	//floyd
	void get_distance2(vector<VI> & dis, int s = 0){
		for (int i = 0; i < num_vertex; i++)
			for (int j = 0; j < num_vertex; j++)
				dis[i][j] = G[i][j];
		for (int k = 0; k < num_vertex; k++)
			for (int i = 0; i < num_vertex; i++)
				for (int j = 0; j < num_vertex; j++)
					if (dis[i][j] > dis[i][k] + dis[k][j])
						dis[i][j] = dis[i][k] + dis[k][j];
		for (auto a : dis[s]) cout << a << ' ';
		cout << endl;
	}
	//PRIM
	void minimal_spanning(){ //最小生成树或连通分支
		VI found(num_vertex, 0); //是否加入生成树
		VI neighbor(num_vertex, 0); //起点
		VI len(num_vertex, 0); //当前到各点的长度
		found[0] = 1;
		for (int i = 0; i < num_vertex; i++) len[i] = G[0][i];
		for (int i = 0; i < num_vertex - 1; i++){
			int min = INT_MAX, v = 0;
			for (int j = 0; j < num_vertex; j++)
				if (!found[j] && len[j] < min) {
					v = j;
					min = len[j];
				}
			if (min < INT_MAX){
				found[v] = 1; //加入v
				//更新
				for(int j = 0; j < num_vertex; j++)
					if (!found[j] && G[v][j] < len[j]) {
						len[j] = G[v][j];
						neighbor[j] = v;
					}
			}
			else break; 
		}
		cout << "source of vertex -> " << endl;
		for (auto a : neighbor) cout << a << ' ';
		cout << endl;
		cout << "length of edges -> " << endl;
		for (auto a : len) cout << a << ' ';
		cout << endl;
	}
private:
	//auxiliary function
	void recursive_DFS(int s, VI &visit){
		visit[s] = 1;
		cout << s << ' '; //访问节点
		for(int i = 0; i < num_vertex; i++)
			if (visit[i] == 0 && G[s][i] != INT_MAX) recursive_DFS(i, visit);
	}
	void recursive_depth_sort(int s, VI & visit, VI & topological_order){
		visit[s] = 1;
		for(int i = 0; i < num_vertex; i++)
			if (!visit[i] && G[s][i] != INT_MAX) recursive_depth_sort(i, visit, topological_order);
		topological_order.insert(topological_order.begin(), s); //插在第一个位置，即在所有关联点之后
	}
private:
	vector <VI> G;
	int num_vertex, num_edge;

};
int main(){
	matrix_graph G;
	G.init();
	cout << "result of BFS -> " << endl;
	G.BFS();
	cout << endl;
	cout << "result of DFS -> " << endl;
	G.DFS();
	cout << endl << endl;

	VI topological_order;
	cout << "result of DFS_SORT -> " << endl;
	G.depth_sort(topological_order);
	cout << "result of BFS_SORT -> " << endl;
	G.breadth_sort(topological_order);

	VI dis(G.size(), 0);
	vector<VI> DIS(G.size(), dis);
	cout << "result of DIJKSTRA -> " << endl;
	G.get_distance(0, dis);
	cout << "result of FLOYD -> " << endl;
	G.get_distance2(DIS, 0);

	cout << "result of PRIM -> " << endl;
	G.minimal_spanning(); 
	return 0;
}