#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=1000;
const int M=10000;
int match[N],vis[N],cnt,n;
vector<int> ve[N];

bool dfs(int u)
{
	for(auto v: ve[u]){
		if(vis[v]==cnt) continue;
		vis[v]=cnt;
		if(!match[v]||dfs(match[v])){	
			match[v]=u;
			return true;
		}
	}
	return false;
}

int solve()
{
	int ans=0;
	for(int i=1;i<=n;i++){
		cnt=i;
		if(dfs(i)) ans++;
	}
	return ans;
}

void init()
{
	memset(match,0,sizeof(match));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<=n;i++) ve[i].clear();
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	return 0;
}