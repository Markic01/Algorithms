#include<bits/stdc++.h>
using namespace std;
struct Tacka{
	int x,y;
	bool operator==(Tacka a){
		return a.x==x&&a.y==y;
	}
};
Tacka input[100000],rez[100000];
bool ima[100000];
int n;
int orientation(Tacka p1,Tacka p2,Tacka p3) { 
    int val = (p2.y - p1.y) * (p3.x - p2.x) - 
              (p2.x - p1.x) * (p3.y - p2.y); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
bool postoji(int y,Tacka w[],int r){
	for(int i=0;i<r;i++)
		if(w[i]==input[y])
			return 1;
	return 0;
}
void brute(int i,int j,Tacka res[],int &a){                            //radi brute
	a=0;
	int pos,neg;
	for(int u=i;u<j;u++)
		for(int q=u+1;q<=j;q++){
			pos=0;neg=0;
			for(int r=i;r<=j;r++){
				int w=orientation(input[u],input[q],input[r]);
				if(w==1||w==0)
					pos++;
				if(w==2||w==0)
					neg++;
			}
			if(pos==(j-i+1)||neg==(j-i+1)){
				if(!postoji(u,res,a))
					res[a++]=input[u];
				if(!postoji(q,res,a))
					res[a++]=input[q];
			}
		}
}
void spoj(Tacka levo[],int a,Tacka desno[],int b){                      //jos ovo
	
}
void rek(int i,int j,Tacka res[],int &m){
	if(j-i<5){
		brute(i,j,res,m);
		return;
	}
	Tacka levo[100000],desno[100000];
	int mid=(i+j)/2,k1,k2;
	rek(i,mid,levo,k1);
	rek(mid+1,j,desno,k2);
	spoj(levo,k1,desno,k2);
}
bool poredi(Tacka a,Tacka b){
	return a.x<b.x;
}
void unos(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>input[i].x>>input[i].y;
		ima[i]=1;
	}
	sort(input,input+n,poredi);
}
int main(){
	unos();
	int m=0;
	rek(0,n-1,rez,m);
	cout<<m<<endl;
	for(int i=0;i<m;i++)
		cout<<rez[i].x<<" "<<rez[i].y<<endl;
}
