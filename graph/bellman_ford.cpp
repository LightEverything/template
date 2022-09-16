#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
const int inf=0x3f3f3f3f;
#define ll long long 

ll cube(ll x)
{
	return x*x*x;
}

ll d[501];
ll nd_cost[501];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int nd,u,v,edg,t=0,kase=0;
	while(cin>>nd){
		kase++;
		for(int i=1;i<=nd;i++) cin>>nd_cost[i];
		vector<pair<int,int> > vec;
		cin>>edg;
		for(int i=1;i<=edg;i++){ 
			cin>>u>>v;
			vec.pb(make_pair(u,v));
		}
		memset(d,0x3f,sizeof(d));
		d[1]=0;
		for(int i=1;i<=nd*2;i++){
			bool isbreak= true;
			for(int j=0;j<edg;j++){
				int u=vec[j].first,v=vec[j].second;
				int w=cube(nd_cost[v]-nd_cost[u]);
				if(d[u]+w<d[v]){
					isbreak=false;
					if(i>=nd) d[v]=-inf;
					else d[v]=d[u]+w;
				}
			}
			if(isbreak) break;
		}
		cout<<"Set #"<<kase<<endl;
		cin>>edg;
		while(edg--){
			int v;
			cin>>v;
			if(d[v]<3||d[v]>100000) cout<<"?"<<endl;
			else cout<<d[v]<<endl;
		}
	}
}