#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int x[10000][10000],n,m,d[10000][10000],pre[10000][10000];
vector<int> c;
void put(int i,int j){
    //cout<<i<<" "<<j<<endl;
    if(pre[i][j]==-1){
        c.pb(i);
        while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
        c.pb(j);
        while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
        return;
    }
    c.pb(i);
    while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
    put(i,pre[i][j]);
    put(pre[i][j],j);
    c.pb(j);
    while(c.size()>1&&c[c.size()-1]==c[c.size()-2])c.pop_back();
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            x[i][j]=0,d[i][j]=99;
    int a,b,t;
    for(int i=0;i<m;i++){
        cin>>a>>b>>t;
        a--;
        b--;
        x[a][b]=d[a][b]=t;
        pre[a][b]=-1;
        pre[b][a]=-1;
        x[b][a]=d[b][a]=t;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n&&j!=i;k++)
                if(d[i][j]+d[j][k]<d[i][k]&&j!=k&&i!=k)
                    d[i][k]=d[i][j]+d[j][k],pre[i][k]=j;
    int u,v;
    cin>>u>>v;
    put(u,v);
    for(int i=0;i<c.size();i++)
        cout<<c[i]<<" ";
}
