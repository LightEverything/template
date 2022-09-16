#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back
#define endl "\n"

const int inf=1<<29,N=50010,M=300010;
int head[N],ver[M],edge[M],Next[M],d[N],now[M];
int n,m,s,t,tot,maxflow;

void add(int x,int y,int w)
{
	ver[++tot]=y; Next[tot]=head[x]; head[x]=tot; edge[tot]=w;
	ver[++tot]=x; Next[tot]=head[y]; head[y]=tot; edge[tot]=0;
}

bool bfs()
{
	memset(d,0,sizeof(d));
	queue<int> q;
	q.push(s); d[s]=1;
	now[s]=head[s];
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(edge[i]&&!d[y]){
				q.push(y);
				now[y]=head[y];
				d[y]=d[x]+1;
				if(y==t) return 1;
			}
		}
	}
	return 0;
}

int dinic(int x,int flow)
{
	if(x==t) return flow;
	int rest=flow,k;
	for(int i=now[x];i&&rest;i=Next[i]){
		now[x]=i;
		int y=ver[i];
		if(edge[i]&&d[y]==d[x]+1){
			k=dinic(y,min(rest,edge[i]));
			if(!k) d[y]=0;
			edge[i]-=k;
			edge[i^1]+=k;
			rest-=k;
		}
	}
	return flow-rest;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	cin>>s>>t;
	tot=1;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
	}
	int flow=0;
	while(bfs()){
		while(flow=dinic(s,inf)) maxflow+=flow;
	}	
	cout<<maxflow<<endl;
	return 0;
}