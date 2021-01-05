#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define N 100000
int n,m,disc[N],low[N],parent[N];
static int k,tim,visited[N],art_point[N];
vector<int> x[N];
int dfs(int i,int p){
    parent[i]=p;
    disc[i]=low[i]=tim++;
    visited[i]=1;
    int children=0;
    for(int j=0;j<x[i].size();j++)
        if(!visited[x[i][j]]){
            dfs(x[i][j],i);
            children++;
            low[i]=min(low[i],low[x[i][j]]);
            if(parent[i]==-1&&children>1)
                art_point[i]=1;
            if(parent[i]!=-1&&low[x[i][j]]>=disc[i])
                art_point[i]=1;
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
    cout<<"Articulation points are: ";
    for(int i=0;i<n;i++)
        if(art_point[i])
            cout<<i<<" ";
    cout<<'\n';
    for(int i(0);i<n;i++)
        cout<<disc[i]<<" ";
    cout<<'\n';
    for(int i(0);i<n;i++)
        cout<<low[i]<<" ";
}
