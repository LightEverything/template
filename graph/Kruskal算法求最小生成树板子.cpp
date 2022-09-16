#include<bits/stdc++.h> 
using namespace std;
#define endl "\n"
#define pb emplace_back

int n,m;				//number of vertex,edge
const int N=1001; 		//图的点数
const int M=10010;     	//图的边数
struct _edge{
    int u,v,w;
    bool operator<(const _edge & t) const
    {
        return w<t.w;
    }
}edge[M];

int fa[N],sz[N];

int get(int x){
    return x==fa[x]?x:fa[x]=get(fa[x]);
}

bool merge(int x,int y)
{
    x=get(x),y=get(y);
    if(x!=y){                       //它这个合并是带查询是否在同一个集合里的功能的
        if(sz[x]<sz[y])swap(x,y);
        fa[y]=x;sz[x]+=sz[y];
        return 1;
    }
    return 0;
}

void init( void )
{
	for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;		//并查集初始化;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>edge[i].u>>edge[i].v>>edge[i].w;
    //按边权排序
    sort(edge+1,edge+1+m);
	//并查集初始化
    init();
    //求最小生成树
    int ans=0;
    for(int i=1;i<=m;i++){
    	int x=edge[i].u,y=edge[i].v,w=edge[i].w;
    	if(merge(x,y)) ans+=w;
    }
    cout<<ans<<endl;
}   