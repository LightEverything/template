// LCA
const int maxn = 2e5 + 5;
int up[maxn][23], maxx[maxn][23];
int deep[maxn], dis[maxn];
int cnt, head[maxn];
int n, m, q;
struct node {  //  存树
    int to, next, w;
}e[maxn<<1];
void init() {
    Fill(head,-1); Fill(dis,0);
    Fill(up,0);  Fill(deep,0);
    cnt = 0;  Fill(maxx, -1);
}
void add(int u, int v, int w) {
    e[cnt] = node{v, head[u], w};
    head[u] = cnt++;
}

void dfs(int u,int fa,int d) {
    deep[u] = d + 1;
    for(int i = 1 ; i < 20 ; i ++) {
        up[u][i] = up[up[u][i-1]][i-1];
        maxx[u][i] = max(maxx[up[u][i-1]][i-1], maxx[u][i-1]);
    }
    for(int i = head[u] ; ~i ; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        dis[to] = dis[u] + e[i].w;
        up[to][0] = u;
        maxx[to][0] = e[i].w;
        dfs(to, u, d+1);
    }
}

int LCA_BZ(int u,int v) {
    int mx = 0;
    if(deep[u] < deep[v]) swap(u,v);
    int k = deep[u] - deep[v];
    for(int i = 0 ; i < 20 ; i ++) {
        if((1<<i) & k) {
            mx = max(mx, maxx[u][i]);
            u = up[u][i];
        }
    }
    if(u != v) {
        for(int i = 19 ; i >= 0 ; i --) {
            if(up[u][i] != up[v][i]) {
                mx = max(mx, max(maxx[u][i], maxx[v][i]));
                u = up[u][i];
                v = up[v][i];
            }
        }
        mx = max(mx, max(maxx[u][0], maxx[v][0]));
        u = up[u][0];
    }
    return mx;
    //return u;
}