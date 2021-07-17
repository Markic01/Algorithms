#include <iostream>
#include <vector>
#include <string>
#include <climits>


void path(int from,int to,const std::vector<std::vector<int>>& prev,std::vector<int>& sol){
    if(sol.size()==0||sol[sol.size()-1]!=from)
        sol.push_back(from);
    
    if(prev[from][to]!=-1){
        path(from,prev[from][to],prev,sol);
        path(prev[from][to],to,prev,sol);
    }
	
    if(sol.size()==0||sol[sol.size()-1]!=to)sol.push_back(to);
}

void FloydWarshall(const int nodes, std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& prev){
    for(int beg=0;beg<nodes;beg++)
        for(int mid=0;mid<nodes;mid++)
            if(mid!=beg&&dist[beg][mid]!=INT_MAX)
                for(int end=0;end<nodes;end++)
                    if(dist[mid][end]!=INT_MAX&&beg!=end&&mid!=end&&dist[beg][mid]+dist[mid][end]<dist[beg][end]){
                        dist[beg][end]=dist[beg][mid]+dist[mid][end];
                        prev[beg][end]=mid;
                    }
}

int main(){
    int nodes,vertices;
    std::cin>>nodes>>vertices;

    std::vector<std::vector<int>> dist(nodes,std::vector<int>(nodes));
    std::vector<std::vector<int>> prev(nodes,std::vector<int>(nodes));

    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++)
            dist[i][j]=INT_MAX;
        dist[i][i]=0;
    }

    int pointA,pointB,length;
    for(int i=0;i<vertices;i++){
        std::cin>>pointA>>pointB>>length;
        dist[pointA][pointB]=dist[pointB][pointA]=length;
        prev[pointA][pointB]=prev[pointB][pointA]=-1;
    }
    
    FloydWarshall(nodes,dist,prev);
    
    std::vector<int> sol;
    int from,to;
    std::cin>>from>>to;
    path(from,to,prev,sol);
    for(int i=0;i<(int)sol.size();i++)
        std::cout<<sol[i]<<" ";
    std::cout<<'\n';
	
    exit(EXIT_SUCCESS);
}
