#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define mem(a,x) memset(a,x,sizeof(a));

const int N=1005;
const int M=10010;
int head[N],ver[N],edge[N],Next[N];
int v[N],dist[N];
int n,m,tot,ans;

void add(int x,int y,int w)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	edge[tot]=w;
}

void dp(int x)
{
	v[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(v[y]) continue;
		dp(y);
		ans=max(ans,dist[x]+dist[y]+edge[i]);
		dist[x]=max(dist[x],dist[y]+edge[i]);
	}
}

void init()
{
	mem(head,0);
	mem(v,0);
	mem(dist,0);
	tot=1;
	ans=INT_MIN;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int kase;
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
		dp(1);
		cout<<ans<<endl;
	}
	return 0;
}
