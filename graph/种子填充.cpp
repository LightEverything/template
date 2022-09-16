#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
int H,W,mk;
int c[2000][2100];
char D[6]={'W','A','K','J','S','D'};
void drawgragh( char ch,int i,int j)
{
	int a[4];
	int num;
	if(isdigit(ch)){
		num=ch-'0';
	}else {
		num=(ch-'a')+10;
	}
	for(int i=3;i>=0;i--){
		a[i]=num%2;
		num/=2;
	}
	for(int jj=(j-1)*4+1,cnt=0;cnt<=3;cnt++){
		c[i][jj+cnt]=a[cnt];
	}
}


void dfs1(int x,int y )   //扣背景的函数
{
	if(x<1||x>H||y<1||y>W) return ;			//超出边界
	if(c[x][y]) return ;  
	c[x][y]=-1;
	for(int dx=-1;dx<=1;dx++){
		for(int dy=-1;dy<=1;dy++){
			//if(dx!=0||dy!=0) dfs1(x+dx,y+dy);
			dfs1(x+dx,y+dy);
		}
	}

}

void dfs2(int x,int y)
{
	if(x<1||x>H||y<1||y>W) return ;			
	if(c[x][y]==-1)  return;
	if(c[x][y]==1){
		c[x][y]=-1;
		for(int dx=-1;dx<=1;dx++){
			for(int dy=-1;dy<=1;dy++){
				//if(dx!=0||dy!=0) dfs2(x+dx,y+dy);
				dfs2(x+dx,y+dy);
			}
		}
	}else {
		mk++;
		dfs1(x,y);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t=0;
	int h,w;
	while(cin>>h>>w&&h!=0){
		t++;
		H=h;
		W=w*4;
		priority_queue<char,vector<char>,greater<char> > pq;   //储存答案的优先队列
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				char ch; cin>>ch;
				drawgragh(ch,i,j);
			}
		}
		//摸着边界扣背景
		for(int i=1;i<=H;i++){
			dfs1(i,1); dfs1(i,W);
		}
		for(int i=1;i<=W;i++){
			dfs1(1,i); dfs1(H,i);
		}

		for(int i=1;i<=H;i++){
			for(int j=1;j<=W;j++){
				if(c[i][j]==1){
					mk=0;
					dfs2(i,j);
					pq.push(D[mk]);
				}
			}
		}
		cout<<"Case "<<t<<": ";
		while(!pq.empty()) {
			char c=pq.top();
			pq.pop();
			cout<<c;
		}
		cout<<endl;
	}
	return 0;
}
