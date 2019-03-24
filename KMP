#include<bits/stdc++.h>
using namespace std;
char txt[100],pat[100];
int lps[100000],n,m;
void duzine(){
    int i;
    for(i=0;txt[i]!='\0';i++){}
    n=i;
    for(i=0;pat[i]!='\0';i++){}
    m=i;
}
void unos(){
    cin.getline(txt,100);
    cin.getline(pat,100);
    duzine();
}
void napravi_lps(){
    lps[0]=0;
    int len=0,i=1;
    while(i<m){
        if(pat[i]==pat[len]){
            len++;
            lps[i]=len;
            i++;
        }
        else{
            if(len>0)
                len=lps[len-1];
            else{
                lps[i]=0;
                i++;
            }
        }
    }
}
void ispislps(){
    for(int i=0;i<m;i++)
        cout<<lps[i];
}
void rresi(){
    napravi_lps();
    int i=0,j=0;
    while(i<n){
        if(txt[i]==pat[j]){
            i++;
            j++;
        }
        else{
            if(j>0)
                j=lps[j-1];
            else
                i++;
        }
        if(j==m){
            cout<<i-j<<endl;
            j=lps[j-1];
        }
    }
}
int main(){
    unos();
    rresi();
}
