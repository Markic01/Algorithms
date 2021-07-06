#include <bits/stdc++.h>
using namespace std;

#define MEM_ERR "Not enough memory!"
#define pb push_back

int n,m;
vector<int> c;

void error(string s){
	cout<<s<<'\n';
	exit(EXIT_FAILURE);
}

int** allocate_matrix(int n,int m){
	int** x=(int**)malloc(n*sizeof(*x));
	if(x==NULL)
		error(MEM_ERR);
	for(int i=0;i<n;i++){
		x[i]=(int*)malloc(m*sizeof(**x));
		if(x[i]==NULL){
			for(int j=i-1;j>=0;j--){
				free(x[i]);
				x[i]=NULL;
			}
			free(x);
			x=NULL;
			error(MEM_ERR);
		}
	}
	return x;
}

void path(int i,int j,int** prev){
    if(prev[i][j]==-1){
        c.pb(i);
        while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
        c.pb(j);
        while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
        return;
    }
    c.pb(i);
    while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
    path(i,prev[i][j],prev);
    path(prev[i][j],j,prev);
    c.pb(j);
    while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
}

int main(){
	int n,m;
    cin>>n>>m;
    int **x,**d,**prev;
    x=allocate_matrix(n,n);
    d=allocate_matrix(n,n);
    prev=allocate_matrix(n,n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            x[i][j]=0,d[i][j]=INT_MAX;
    int a,b,t;
    for(int i=0;i<m;i++){
        cin>>a>>b>>t;
        a--;
        b--;
        x[a][b]=d[a][b]=t;
        prev[a][b]=-1;
        prev[b][a]=-1;
        x[b][a]=d[b][a]=t;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n&&j!=i;k++)
                if(d[i][j]+d[j][k]<d[i][k]&&j!=k&&i!=k)
                    d[i][k]=d[i][j]+d[j][k],prev[i][k]=j;
    int u,v;
    cin>>u>>v;
    path(u,v,prev);
    for(int i=0;i<(int)c.size();i++)
        cout<<c[i]<<" ";
}
