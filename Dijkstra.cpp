#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int n,izv,m,l[100000],pre[100000];
vector<int> x[100000],y[100000];
int nadjimin(bool a[]){
    int mini=-1;
    for(int i=1;i<n;i++)
        if((mini==-1&&!a[i])||(!a[i]&&x[i]<x[mini]))
            mini=i;
    return mini;
}
int minDis(bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;

   for (int v = 0; v < n; v++)
     if (sptSet[v] == false && l[v] <= min)
         min = l[v], min_index = v;

   return min_index;
}
void dijkstra(){
    static bool a[100000];
    int u;
    pre[izv]=-1;
    for(int i=0;i<n;i++){
        u=minDis(a);
        if(u==-1)
            break;
        a[u]=1;
        for(int j=0;j<x[u].size();j++)
            if(l[u]+y[u][j]<l[x[u][j]]){
                l[x[u][j]]=l[u]+y[u][j];
                pre[x[u][j]]=u;
            }
    }
}
void put(int i){
    if(pre[i]==-1){
        cout<<i<<" "<<endl;
        return;
    }
    put(pre[i]);
    cout<<i<<endl;
}
int main(){
    cin>>n>>m>>izv;
    int a,b,t;
    for(int i=0;i<m;i++){
        cin>>a>>b>>t;
        x[a].pb(b);
        x[b].pb(a);
        y[a].pb(t);
        y[b].pb(t);
    }
    for(int i=0;i<n;i++)
        l[i+1]=INT_MAX;
    l[izv]=0;
    dijkstra();
    int u;
    cin>>u;
    put(u);
}
