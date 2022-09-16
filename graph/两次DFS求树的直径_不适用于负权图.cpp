#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back
#define endl "\n"
#define mem(a,x) memset(a,x,sizeof(a))
typedef long long ll;

const int N=1000;
const int M=10000;
int head[N],ver[M],Next[M],edge[M];
int dist[N];
int n,m,p,tot;

void add(int x,int y,int w)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	edge[tot]=w;
}

void dfs(int x, int fa) {
	for(int i=head[x];i;i=Next[i]){
  		int y=ver[i];
  		if(y==fa) continue;
  		dist[y]=dist[x]+edge[i];
  		if(dist[y]>dist[p]) p=y;
  		dfs(y,x);
    }
}

void init()
{
	mem(head,0);
	mem(dist,0);
	p=1;
	tot=1;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int kase=0;
	cin>>kase;
	while(kase--){
		cin>>n>>m;
		init();
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			add(u,v,w);
			add(v,u,w);
		}
		p=1;
		dfs(1,0);
		mem(dist,0); 
		dfs(p,0);
		cout<<dist[p]<<endl;
	}
	return 0;
}