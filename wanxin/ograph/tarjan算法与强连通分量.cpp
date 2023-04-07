#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=100000;
const int M=1000000;
int n,m;
int head[N],ver[M],Next[M];
int low[N],dfn[N],stacks[N],c[N],vis[N],tot,num,cnt,top;
vector<int> scc[N];

void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	stacks[++top]=x; vis[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(vis[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		cnt++;
		int y;
		do{
			y=stacks[top--];
			vis[y]=0; c[y]=cnt;
			scc[cnt].pb(y);
		}while(x!=y);
	}
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	tot=1;
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i);
	}
	return 0;
}