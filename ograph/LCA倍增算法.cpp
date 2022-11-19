#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define mem(a,x) memset(a,x,sizeof(a));
typedef long long ll;
const int N=1005;
const int M=10005;
int f[N][20],d[N],dist[N];
int head[N],ver[M],edge[M],Next[M];
int n,m,tot,t;

void add(int x,int y,int z)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	edge[tot]=z;
}

void bfs()		//预处理
{
	queue<int> q;
	q.push(1); d[1]=1;
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(d[y]) continue;
			d[y]=d[x]+1;
			dist[y]=dist[x]+edge[i];
			f[y][0]=x;
			for(int j=1;j<=t;j++){
				f[y][j]=f[f[y][j-1]][j-1];
			}
			q.push(y);
		}
	}
}

int lca(int x,int y)
{
	//回答一个询问
	if(d[x]>d[y]) swap(x,y); //要求y比x深
	for(int i=t;i>=0;i--){
		if(d[f[y][i]]>=d[x]) y=f[y][i];
	}
	//此时y与x的深度相同
	if(x==y) return x;
	for(int i=t;i>=0;i--){
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}

void init()
{
	mem(f,0);
	mem(d,0);
	mem(dist,0);
	mem(head,0);
	tot=1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int kase;
	cin>>kase;
	while(kase--){
		cin>>n>>m;
		t=(int)(log(n)/log(2))+1;
		init();
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			add(u,v,w);
			add(v,u,w);
		}
		bfs();
		//回答问题
		int q;
		cin>>q;
		for(int i=1;i<=q;i++){
			int x,y;
			cin>>x>>y;
			cout<<(dist[x]+dist[y]-2*dist[lca(x,y)])<<endl;
		}
	}
	return 0;
}