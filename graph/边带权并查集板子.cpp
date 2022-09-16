//边带权并查集的板子

const int MS=10010;//size of array
struct _edge{
    int u,v,w;
    bool operator<(const _edge & t) const
    {
        return w<t.w;
    }
}edge[MS];

int fa[MS],sz[MS];

int findf(int u){
    return u==fa[u]?u:fa[u]=findf(fa[u]);
}

bool uni(int u,int v)
{
    u=findf(u),v=findf(v);
    if(u!=v){                       //它这个合并是带查询是否在同一个集合里的功能的
        if(sz[u]<sz[v])swap(u,v);
        fa[v]=u;sz[u]+=sz[v];
        return 1;
    }
    return 0;
}

int main()
{
    int n,m;//number of vertex,edge
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
    for(int i=0;i<m;i++)cin>>edge[i].u>>edge[i].v>>edge[i].w;
    sort(edge,edge+m);
    int ans=0;//total weight
    for(int i=0;i<m;i++)
    {
        int u=edge[i].u,v=edge[i].v,w=edge[i].w;
        if(uni(u,v))ans+=w;
    }
    printf("%d\n",ans);
}   