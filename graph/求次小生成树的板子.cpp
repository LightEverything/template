#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
typedef long long ll;
const int  N=1e5+50;
const int  M=1e6;
const ll INF=2e18;
ll n,m,ecnt=-1,tot;
ll fa[N],head[N];
ll dep[N],anc[N][25];
ll ancmax[N][25],ancmin[N][25];
ll totans=INF,sum=0;
bool vis[M];
struct _edge
{
    ll u,v,w;
}edge[M];

struct mint_edge
{
    ll nxt,u,v,w;
}e[M];
bool cmp(_edge a,_edge b)
{
    return a.w<b.w;
}
void addline(ll u,ll v,ll w)
{
    e[++ecnt].nxt=head[u];
    e[ecnt].v=v;
    e[ecnt].u=u;
    e[ecnt].w=w;
    head[u]=ecnt;
}
ll Find(ll x)
{
    if(x==fa[x]) return x;
    return fa[x]=Find(fa[x]);
}
void dfs(ll x,ll fa)
{
    dep[x]=dep[fa]+1;
    anc[x][0]=fa;
    for(ll i=head[x];~i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==fa) continue;
    	ancmax[v][0]=e[i].w;
    	ancmin[v][0]=-INF;
		dfs(v,x);
    }
}
void cal()
{
	for(ll i=1;i<=18;++i)
	{
		for(ll x=1;x<=n;++x)
		{
			anc[x][i]=anc[anc[x][i-1]][i-1];
			ancmax[x][i]=max(ancmax[x][i-1],ancmax[anc[x][i-1]][i-1]);
			ancmin[x][i]=max(ancmin[x][i-1],ancmin[anc[x][i-1]][i-1]);
			if(ancmax[x][i-1]>ancmax[anc[x][i-1]][i-1]) ancmin[x][i]=max(ancmin[x][i],ancmax[anc[x][i-1]][i-1]);
			else if(ancmax[x][i-1]<ancmax[anc[x][i-1]][i-1]) ancmin[x][i]=max(ancmin[x][i],ancmax[x][i-1]);	
		}
	}
}
ll LCA(ll x,ll y)
{   
    if(dep[x]<dep[y]) swap(x,y);
    for(ll i=18;i>=0;--i)
    {
        if(dep[anc[x][i]]>=dep[y]) x=anc[x][i];        
    } 
    if(x==y) return x;
    for(ll i=18;i>=0;--i)
    {
    	if(anc[x][i]!=anc[y][i])
    	{
    		x=anc[x][i];
			y=anc[y][i];		
    	}
    }
    return anc[x][0];
}
ll getmax(ll x,ll fath,ll maxx)
{
	ll ans=-INF;
	for(ll i=18;i>=0;--i)
	{
		if(dep[anc[x][i]]>=dep[fath])
	    {
		// 	if(ancmax[x][i]!=maxx) ans=max(ans,ancmax[x][i]);     //严格次小生成树
		// 	else ans=max(ans,ancmin[x][i]);                       
            ans=max(ans,ancmax[x][i]);                            //求非严格次小生成树
			x=anc[x][i];
		}
	}
	return ans;
}
void init( void )
{
    memset(head,-1,sizeof(head));
    memset(anc,0,sizeof(anc));
    memset(ancmax,0,sizeof(ancmax));
    memset(ancmin,0,sizeof(ancmin));
    memset(vis,0,sizeof(vis));
    for(ll i=1;i<=n;++i) {
        fa[i]=i;
    }
    tot=0; ecnt=-1; totans=INF; sum=0;
}
void solve( void )
{
    cin>>n>>m;
    init();
    for(ll i=1;i<=m;++i)
    {
        ll x,y,z;
        cin>>x>>y>>z;
        edge[i].u=x;
        edge[i].v=y;
        edge[i].w=z;
    }
    sort(edge+1,edge+m+1,cmp);
    for(ll i=1;i<=m;++i)
    {
        ll x=Find(edge[i].u),y=Find(edge[i].v);
        if(x!=y)
        {
			fa[x]=y;
        	addline(edge[i].u,edge[i].v,edge[i].w);
        	addline(edge[i].v,edge[i].u,edge[i].w);
        	sum+=edge[i].w;
        	tot++;
        	vis[i]=true;
        	if(tot==n-1) break;
    	}
	}
	ancmin[1][0]=-INF;
    dfs(1,0);
    cal();
    totans=INF;
    for(ll i=1;i<=m;++i)
    {
    	if(!vis[i])
    	{
			ll x=edge[i].u,y=edge[i].v;
			ll fath=LCA(x,y);
			ll maxx=max(getmax(x,fath,edge[i].w),getmax(y,fath,edge[i].w));
            ll now=sum-maxx+edge[i].w;
            totans=min(totans,sum-maxx+edge[i].w);
    	}
	}
    if(totans==INF) cout<<sum<<" "<<sum<<endl;
    else cout<<sum<<" "<<totans<<endl;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}