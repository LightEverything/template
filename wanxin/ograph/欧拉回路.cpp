#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=55;
const int M=1005;
int deg[N],vis[N];
int g[N][N];
int n,m;

void dfs(int x )
{
	for(int i=1;i<=n;i++){
		if(g[x][i]){
			g[x][i]--; g[i][x]--;
			//cout<<x<<" "<<i<<endl;
			dfs(i);
			cout<<i<<" "<<x<<endl;
		}
	}
}

void dfs_2(int x,int fa)
{
	vis[x]=1;
	for(int i;i<=n;i++){
		if(i!=fa&&!vis[i]&&g[x][i]){
			dfs_2(i,x);
		}
	}
}

void init()
{
	memset(deg,0,sizeof(deg));
	memset(g,0,sizeof(g));
	memset(vis,0,sizeof(vis));
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t,kase=0;
	cin>>t;
	while(t--){
		kase++;
		n=50;
		cin>>m;
		init();
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			deg[u]++; deg[v]++;
			g[u][v]++; g[v][u]++;
		}
		int flag=1;
		for(int i=1;i<=n;i++){
			if(deg[i]&&deg[i]%2==1){
			//if(deg[i]&1){
				flag=0;
				break;
			}
		}
		int f;
		for(int i=1;i<=n;i++){
			if(deg[i]) {
				f=i;
				break;
			}
		}
		if(flag){
			dfs_2(f,0);
			for(int i=1;i<=n;i++){
				if(deg[i]&&vis[i]==0){
					flag=0;
					break;
				}
			}
		}
		cout<<"Case #"<<kase<<endl;
		if(flag){
			dfs(f);
		}else {
			cout<<"some beads may be lost"<<endl;
		}
		if(t!=0) cout<<endl;
	}
	return 0;
}