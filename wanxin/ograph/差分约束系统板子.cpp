#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int inf=0x3f3f3f3f,N=7000,M=100000;
int head[N],ver[M],Next[M],edge[M],vis[N],cnt[N],dist[N];
int n,m,tot;

void add(int x,int y,int w)
{
	ver[++tot]=y; Next[tot]=head[x]; head[x]=tot; edge[tot]=w;
}

bool spfa(int s)
{
	memset(dist,0x3f,sizeof(dist));
	memset(cnt,0,sizeof(cnt));
	queue<int> q; q.push(s);
	vis[s]=1; dist[s]=0; cnt[s]++;
	while(!q.empty()){
		int x=q.front(); q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(dist[y]>dist[x]+edge[i]){
				dist[y]=dist[x]+edge[i];
				cnt[y]++;
				if(cnt[y]>=n+1) return false;   //这里是n+1,因为多加了一个超级源点
				if(!vis[y]) q.push(y),vis[y]=1;
			}
		}
	}
	return true;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		add(0,i,0);
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(v,u,w);
	}
	if(!spfa(0)) {
		cout<<"NO"<<endl;
		return 0;
	}
	int mins=inf;
	for(int i=1;i<=n;i++) mins=min(mins,dist[i]);
	for(int i=1;i<=n;i++){
		cout<<dist[i]-mins<<" ";
	}
	return 0;
}