#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define mem(a,x) memset(a,x,sizeof(a));
#define pii pair<int,int>
const int INF=0x3f3f3f3f;
const int N=10000;
const int M=100000;
int head[N],ver[M],edge[M],Next[M];
int d[N],cnt[N],vis[N];
int n,m,tot=0;
queue<int> q;

void add(int x,int y,int w)
{
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
    edge[tot]=w;
}

bool spfa( int s )
{
  mem(d,0x3f);
  mem(vis,0);
  d[s]=0; vis[s]=1;
  q.push(s);
  while(!q.empty()){
    int x=q.front(); q.pop();
    vis[x]=0;
    for(int i=head[x];i;i=Next[i]){
      int y=ver[i],w=edge[i];
      if(d[y]>d[x]+w){
        d[y]=d[x]+w;
        cnt[y]=cnt[x]+1;    //记录最短路径经过的边数
        if(cnt[y]>=n) return false;     //经过了负环
        if(!vis[y]) q.push(y),vis[y]=1;
      }
    }
  }
  return true;
}