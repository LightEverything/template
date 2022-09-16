#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

int v;
vector<int> ve[350];
int color[340];

bool dfs(int cur,int c)
{
	color[cur]=c;
	for(auto a : ve[cur]){
		if(color[a]){
			if(color[a]==c) return false;
		}else {
			if(!dfs(a,-c)) return false;
		}
	}
	return true;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	while(cin>>v&&v!=0){
		for(int i=1;i<=v;i++){
			ve[i].clear();
		}
		while(1){
			int u,v;
			cin>>u>>v;
			if(u+v==0) break;
			ve[u].pb(v);
			ve[v].pb(u);
		}
		memset(color,0,sizeof(color));
		int ok=1;
		for(int i=1;i<=v;i++){
			if(color[i]==0){
				if(!dfs(i,1)) {
					ok=0;
					break;
				}
			}
		}
		if(ok) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}