#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define pii pair<int,int>
#define mk(a,b) make_pair(a,b)
#define mem(a,x) memset(a,x,sizeof(a))
const int N=10010;
const int M=100010;
int head[N],ver[M],edge[M],Next[M];
int vis[N],d[N];
int n,m,tot;

priority_queue<pair<int,int>,vector<pair<int,int> >, greater<pair<int,int> > > q;

void add(int x,int y,int w)
{
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
    edge[tot]=w;
}

void dijkstra( int term)
{
    mem(d,0x3f);
    mem(vis,0);
    d[term]=0;
    q.push(mk(0,term));
    while(!q.empty()){
        int x=q.top().second;q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i;i=Next[i]){
            int y=ver[i],z=edge[i];
            if(d[y]>d[x]+z){
                d[y]=d[x]+z;
                q.push(mk(d[y],y));
            }
        }
    }
}
