#include <iostream>
#include <vector>
#define MAX_N 100

using namespace std;

typedef struct {
	int n;
	vector <int> adj[MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
	pG->n = n;
}

/* Do thi vo huong
void add_edge(Graph *pG, int u, int v) {
	if (u != v) {
		pG->adj[u].push_back(v);
		pG->adj[v].push_back(u);
	}
	else pG->adj[u].push_back(v);
}
*/

//Do thi co huong
void add_edge(Graph *pG, int u, int v) {
	pG->adj[u].push_back(v);
}


int adjacent(Graph *pG, int u, int v) {
	int j;
	for (j = 1; j <= pG->adj[u].size(); j++)
		if (pG->adj[u][j - 1] == v)
			return 1;
	return 0;
}

//Do thi co huong
int indegree(Graph *pG, int x) {
	int i,j, indeg_v = 0;
	for(i = 1; i <= pG->n; i++){
		for (j = 1; j <= pG->adj[i].size(); j++)
			if (pG->adj[i][j - 1] == x)
				indeg_v++;
	}
	return indeg_v;
}

int outdegree(Graph *pG, int x) {
	return pG->adj[x].size();
}

int degree(Graph *pG, int x){
	return indegree(pG,x) + outdegree(pG,x);
}

/*
//Do thi vo huong
int indegree(Graph *pG, int x) {
	int i,j, indeg_v = 0;
	for(i = 1; i <= pG->n; i++){
		for (j = 1; j <= pG->adj[i].size(); j++)
			if (pG->adj[i][j - 1] == x)
				indeg_v++;
	}
	return indeg_v;
}

int outdegree(Graph *pG, int x) {
	return pG->adj[x].size();
}

int degree(Graph *pG, int x){
	return pG->adj[x].size();
}
*/

int main(){
	int n,m;
	cin >> n >> m;
	Graph G;
	init_graph(&G, n);
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		add_edge(&G, u, v);
	}
	
	for (int i = 1; i <= n; i++) {
		cout << i << ": ";
		for (int x: G.adj[i]) cout << x << " ";
		cout << endl;
	}
	for (int i = 1; i <= n; i++)
		cout << "degree(" << i << ") = " << degree(&G, i) << endl;
	for (int i = 1; i <= n; i++)
		cout << "deg_in(" << i << ") = " << indegree(&G, i) << endl;
	for (int i = 1; i <= n; i++)
		cout << "deg_out(" << i << ") = " << outdegree(&G, i) << endl;
	return 0;
}
