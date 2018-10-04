#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>

#define MAX 100100
#define TREE 400400
#define LOG 20

using namespace std;

struct vertex{
	int sz, lv, pos, pai;
	vector<int> nodes;
};

vertex grafo[MAX];
int arr[MAX], v = 1;
int anc[MAX][LOG];
int chains[MAX], head[MAX], tree[TREE], lazy[TREE];
int pos = 0, cs = 0;

void update(int node, int i, int j, int a, int b){
	int esq=node<<1, dir=esq+1, med=(i+j)/2;
	if(lazy[node] == v){
		tree[node] = v;
		if(i != j){
			lazy[esq] = lazy[dir] = v;
		}
		lazy[node] = 0;
	}
	if(i >= a && j <= b){
		tree[node] = v;
		if(i!=j)
			lazy[esq] = lazy[dir] = v;
		return;
	}
	if(i > b || j < a)
		return;
	update(esq, i, med, a, b);
	update(dir, med+1, j, a, b);
}

int query(int node, int i, int j, int a, int b){
	int esq=node<<1, dir=esq+1, med=(i+j)/2;

	if(lazy[node] == v){
		tree[node] = v;
		if(i!=j)
			lazy[esq] = lazy[dir] = v;
		lazy[node] = 0;
	}
	if(i>=a && j<=b){
		if(tree[node] == v)
			return j-i+1;
		if(i==j)
			return 0;
	}
	if(i > b || j < a)
		return 0;
	return query(esq, i, med, a, b) + query(dir, med+1, j, a, b);	
}

void dfs(int x, int prev, int l){
	grafo[x].lv = l;
	grafo[x].pai = prev;
	grafo[x].sz = 1;

	for(int i = 0; i < grafo[x].nodes.size(); i++){
		if(grafo[x].nodes[i] != prev){
			dfs(grafo[x].nodes[i], x, l+1);
			grafo[x].sz += grafo[grafo[x].nodes[i]].sz;
		}
	}
}

void hld(int x, int prev){
	if(head[cs] == -1)
		head[cs] = x;
	pos++;
	arr[pos] = x;
	chains[x] = cs;
	grafo[x].pos = pos;

	int i, sc = -1;
	for(i = 0; i < grafo[x].nodes.size(); i++){
		if(grafo[x].nodes[i] != prev){
			if(sc == -1 || grafo[sc].sz < grafo[grafo[x].nodes[i]].sz){
				sc = grafo[x].nodes[i];
			}
		}
	}

	if(sc != -1)
		hld(sc, x);
	for(i = 0; i < grafo[x].nodes.size(); i++){
		if(grafo[x].nodes[i] != prev && grafo[x].nodes[i] != sc){
			cs++;
			hld(grafo[x].nodes[i], x);
		}
	}
}

int LCA(int u, int v){
	if(grafo[u].lv < grafo[v].lv)
		swap(u, v);
	
	for(int i = LOG-1;i >= 0;i--)
		if(grafo[u].lv - (1<<i) >= grafo[v].lv)
			u = anc[u][i];
	if(u == v) return u;
	
	for(int i = LOG-1;i >= 0;i--)
		if(anc[u][i] != -1 && anc[u][i] != anc[v][i]){
			u = anc[u][i];
			v = anc[v][i];
	}
	return anc[u][0];
}

void setPath(int u, int v){
	int u_chain, v_chain = chains[v];

	while(true){
		u_chain = chains[u];
		if(u_chain == v_chain){
			if(u!=v){
				update(1, 1, pos, grafo[v].pos+1, grafo[u].pos);
			}
			return;
		}
		else{
			update(1, 1, pos, grafo[head[u_chain]].pos, grafo[u].pos);
			u = grafo[head[u_chain]].pai;
		}
	}
}

int runPath(int u, int v){
	int u_chain, v_chain = chains[v], ans = 0;

	while(true){
		u_chain = chains[u];
		if(u_chain == v_chain){
			if(u!=v){
				ans += query(1, 1, pos, grafo[v].pos+1, grafo[u].pos);
			}
			break;
		}
		else{
			ans += query(1, 1, pos, grafo[head[u_chain]].pos, grafo[u].pos);
			u = grafo[head[u_chain]].pai;
		}
	}
	return ans;
}

int main(){
	int N, Q, A, B, C, D, x, y, lca;
	scanf("%d %d", &N, &Q);
	lca = N;
	while(N>1){
		scanf("%d %d", &x, &y);
		grafo[x].nodes.push_back(y);
		grafo[y].nodes.push_back(x);
		N--;
	}
	N = lca;
	memset(head, -1, sizeof(head));
	dfs(1, -1, 0);
	hld(1, -1);
	memset(anc, -1, sizeof(anc));
	for(int i = 1; i <= N;i++) 
		anc[i][0] = grafo[i].pai;
	for(int j = 1;j < LOG;j++)
		for(int i = 1;i <= N;i++)
			if(anc[i][j-1] != -1)
				anc[i][j] = anc[anc[i][j-1]][j-1];
	while(Q--){
		scanf("%d %d %d %d", &A, &B, &C, &D);
		lca = LCA(A, B);
		setPath(A, lca), setPath(B, lca), update(1, 1, pos, grafo[lca].pos, grafo[lca].pos);
		lca = LCA(C, D);
		printf("%d\n", runPath(C, lca) + runPath(D, lca) + query(1, 1, pos, grafo[lca].pos, grafo[lca].pos));
		v++;
	}
	return 0;
}