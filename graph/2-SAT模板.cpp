#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=2500000;
const int M=3000000;
int n,m,fen;
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

bool solve()
{
	for(int i=1;i<=n*2;i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(c[i]==c[i+fen]) return false;
	}
	return  true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	fen=n;
	for(int k=1;k<=m;k++){
		int i,a,j,b;
		cin>>i>>a>>j>>b;
		if(a&&b){
			add(i+fen,j); add(j+fen,i);
		}else if(!a&&b){
			add(i,j); add(j+fen,i+fen);
		}else if(a&&!b){
			add(i+fen,j+fen); add(j,i);
		}else if(!a&&!b){
			add(i,j+fen); add(j,i+fen);
		}
	}
	if(solve()){
		cout<<"POSSIBLE"<<endl;
		for(int i=1;i<=n;i++){
			if(c[i]<c[i+fen]) cout<<"1"<<" ";
			else cout<<"0"<<" ";
		}
	}else {
		cout<<"IMPOSSIBLE";
	}	
	return 0;
}