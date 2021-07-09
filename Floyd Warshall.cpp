#include <bits/stdc++.h>
using namespace std;

#define MEM_ERR "Not enough memory!"

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

void path(int from,int to,int **prev,vector<int> &sol){
    if(sol.size()==0||sol[sol.size()-1]!=from)sol.push_back(from);
    
	if(prev[from][to]!=-1){
		path(from,prev[from][to],prev,sol);
		path(prev[from][to],to,prev,sol);
	}
	
    if(sol.size()==0||sol[sol.size()-1]!=to)sol.push_back(to);
}

void FloydWarshall(int nodes,int*** dist,int*** prev){
	for(int beg=0;beg<nodes;beg++)
        for(int mid=0;mid<nodes;mid++)
			if(mid!=beg&&(*dist)[beg][mid]!=INT_MAX)
				for(int end=0;end<nodes;end++)
					if((*dist)[mid][end]!=INT_MAX&&beg!=end&&mid!=end&&(*dist)[beg][mid]+(*dist)[mid][end]<(*dist)[beg][end]){
						(*dist)[beg][end]=(*dist)[beg][mid]+(*dist)[mid][end];
						(*prev)[beg][end]=mid;
					}
}

int main(){
	int nodes,vertices;
    cin>>nodes>>vertices;

    int **dist,**prev;
    dist=allocate_matrix(nodes,nodes);
    prev=allocate_matrix(nodes,nodes);

    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++)
            dist[i][j]=INT_MAX;
        dist[i][i]=0;
	}

    int pointA,pointB,length;
    for(int i=0;i<vertices;i++){
        cin>>pointA>>pointB>>length;
        dist[pointA][pointB]=dist[pointB][pointA]=length;
        prev[pointA][pointB]=prev[pointB][pointA]=-1;
    }
    
    FloydWarshall(nodes,&dist,&prev);

	vector<int> sol;
    int from,to;
    cin>>from>>to;
    path(from,to,prev,sol);
    for(int i=0;i<(int)sol.size();i++)
        cout<<sol[i]<<" ";
    cout<<'\n';
    
    for(int i=0;i<nodes;i++){
		free(dist[i]);
		free(prev[i]);
	}
	free(dist);
	free(prev);
	
    return 0;
}
