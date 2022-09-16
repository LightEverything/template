#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=100005;
int head[N],ver[N*2],Next[N*2];
int dfn[N],low[N],n,m,tot,num;
int bridge[N*2];

void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x,int in_edge)
{
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]){
				bridge[i]=1;
				bridge[i^1]=1;
			}
		}else {
			if(i!=(in_edge^1)){
				low[x]=min(low[x],low[y]);
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	tot=1;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i,0);
	}
	for(int i=2;i<=tot;i+=2){
		if(bridge[i]) cout<<ver[i]<<" "<<ver[i^1]<<endl;
	}
	return 0;
}