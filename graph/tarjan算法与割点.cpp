#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=100005;
int n,m;
int head[N],ver[2*N],Next[2*N];
int dfn[N],low[N],num,tot,root;
int cut[N];

void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	int cnt=0;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				cnt++;
				if(x!=root||cnt>1) cut[x]=1;
			}
		}else {
			low[x]=min(low[x],dfn[y]);
		}
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
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(dfn[i]) root=i,tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(cut[i]) cout<<i<<" ";
	}
	return 0;
}