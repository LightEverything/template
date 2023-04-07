#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int inf=0x3f3f3f3f,N=5e3+5,M=1e5+5;
int head[N],ver[M],Next[M],edge[M],now[N],cost[M],dist[N],vis[N];
int n,m,s,t,tot,maxflow,ret;

void add(int x,int y,int w,int c)
{
	ver[++tot]=y; Next[tot]=head[x]; head[x]=tot; edge[tot]=w; cost[tot]=c;
	ver[++tot]=x; Next[tot]=head[y]; head[y]=tot; edge[tot]=0; cost[tot]=-c;
}

bool spfa()
{
	memset(dist,0x3f,sizeof(dist));
	queue<int> q; q.push(s);
	dist[s]=0; vis[s]=1;
	now[s]=head[s];
	while(!q.empty()){
		int x=q.front(); q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(edge[i]&&dist[y]>dist[x]+cost[i]){
				dist[y]=dist[x]+cost[i];
				now[y]=head[y];
				if(!vis[y]) q.push(y),vis[y]=1;
			}
		}
	}
	return dist[t]!=inf;
}

int dinic(int x,int flow)
{
	if(x==t) return flow;
	vis[x]=1; 
	int rest=flow,k;
	for(int i=now[x];i&&rest;i=Next[i]){
		int y=ver[i];
		now[x]=i;
		if(!vis[y]&&edge[i]&&dist[y]==dist[x]+cost[i]){
			k=dinic(y,min(rest,edge[i]));
			if(k){
				ret+=k*cost[i];
				edge[i]-=k;
				edge[i^1]+=k;
				rest-=k;
			}
		}
	}
	vis[x]=0;
	return flow-rest;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m>>s>>t;
	tot=1; maxflow=0; ret=0;
	for(int i=1;i<=m;i++){
		int u,v,w,c;
		cin>>u>>v>>w>>c;
		add(u,v,w,c);
	}
	int flow=0;
	maxflow=0; ret=0;
	while(spfa()){
		while(flow=dinic(s,inf)) maxflow+=flow;
	}
	cout<<maxflow<<" "<<ret<<endl;
	return 0;
}