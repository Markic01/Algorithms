#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int n,m,disc[100000],low[100000],parent[100000];
static int k,tim,pos[100000],r[100000];
vector<int> x[100000];
int dfs(int i,int p){
    parent[i]=p;
    disc[i]=low[i]=tim++;
    pos[i]=1;
    int children=0;
    for(int j=0;j<x[i].size();j++)
        if(!pos[x[i][j]]){
            dfs(x[i][j],i);
            children++;
            low[i]=min(low[i],low[x[i][j]]);
            if(parent[i]==-1&&children>1)
                r[i]=1;
            if(parent[i]!=-1&&low[x[i][j]]>=disc[i])
                r[i]=1;
        }
        else
            low[i]=min(low[i],disc[x[i][j]]);
}
int main(){
    cin>>n>>m;
    int a,b;
    for(int i(0);i<m;i++){
        cin>>a>>b;
        x[a].pb(b);
        x[b].pb(a);
    }
    dfs(0,-1);
    for(int i=0;i<n;i++)
        if(r[i])
            cout<<i<<" ";
    cout<<endl;
    for(int i(0);i<n;i++)
        cout<<disc[i]<<" ";
    cout<<endl;
    for(int i(0);i<n;i++)
        cout<<low[i]<<" ";
}
