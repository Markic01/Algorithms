#include<bits/stdc++.h>
using namespace std;
static int sparse[100000][20],n,x[100000];
int mah(int i,int j){
    if(x[sparse[i][j-1]]<x[sparse[i+(1<<(j-1))][j-1]])
        return sparse[i][j-1];
    return sparse[i+(1<<(j-1))][j-1];
}
int query(int l,int d){
    int a=d-l+1;
    int r=log2(a);
    if(x[sparse[l][r]]<x[sparse[d-(1<<r)+1][r]])
        return sparse[l][r];
    return sparse[d-(1<<r)+1][r];
}
int main(){
    cin>>n;
    int l=log2(n)+1;
    for(int i=0;i<n;i++)cin>>x[i],sparse[i][0]=i;
    for(int j=1;j<l;j++)
        for(int i=0;i<(n-(1<<j)+1);i++)
            sparse[i][j]=mah(i,j);//,cout<<i<<" "<<j<<" "<<(n-(1<<j)+1)<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<l;j++)
            cout<<sparse[i][j]<<" ";
        cout<<endl;
    }
    cout<<"koji je query?"<<endl;
    int a,b;
    cin>>a>>b;
    cout<<x[query(a,b)];
}
