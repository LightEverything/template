#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

int n;
map<char,int> m;
int g[30][30];
int dout[30];
int ok;
char ans[30];
char a[30];

void toposort(int cur)
{
	if(cur==n){
		for(int i=0;i<n-1;i++){
			cout<<ans[i]<<" ";
		}
		cout<<ans[n-1];
		cout<<endl;
		ok=1;
		return ;
	}else {
		for(int i=0;i<n;i++){
			if(dout[i]==0){
				dout[i]--;
				for(int j=0;j<n;j++){
					if(g[i][j]) dout[j]--;
				}
				ans[cur]=a[i];
				toposort(cur+1);
				dout[i]++;
				for(int j=0;j<n;j++){
					if(g[i][j]) dout[j]++;
				}
			}
		}
	}
}



int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t;
	string str;
	cin>>t;
	cin.get();
	while(t--){
		ok=0;
		n=0;
		m.clear();
		memset(g,0,sizeof(g));
		memset(dout,0,sizeof(dout));
		string str;
		getline(cin,str);
		getline(cin,str);
		char ch;
		for(int i=0;i<str.size();i++){
			if(isalpha(str[i])){
				a[n++]=str[i];
			}
		}
		sort(a,a+n);
		for(int i=0;i<n;i++) m[a[i]]=i;
		getline(cin,str);
		for(int i=0;i<str.size();i++){
			if(str[i]=='<'){
				char ch1,ch2;
				ch1=str[i-1];
				ch2=str[i+1];
				g[m[ch1]][m[ch2]]=1;
				dout[m[ch2]]++;
			}
		}

		toposort(0);
		if(!ok) cout<<"NO"<<endl;
		if(t!=0) cout<<endl;
 	}	
	return 0;
}