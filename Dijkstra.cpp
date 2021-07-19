#include <iostream>
#include <vector>
#include <climits>


int findMinDist(const std::vector<bool>& visited,
                const std::vector<int>& dist,const int numNodes){
    int minIndex=-1;
    for(int i=0;i<numNodes;i++){
        if((minIndex==-1&&!visited[i]) || (!visited[i]&&dist[i]<dist[minIndex])){
            minIndex=i;
        }
    }
    return minIndex;
}

void dijkstra(const int numNodes,const int startNode,
              const std::vector<std::vector<int>>& adjacent,
              const std::vector<std::vector<int>>& weight,
              std::vector<int>& parent,std::vector<int>& dist){
    static std::vector<bool> visited(numNodes,0);
    int currMin;
    dist[startNode]=0;
    parent[startNode]=-1;
    
    for(int i=0;i<numNodes;i++){
        currMin=findMinDist(visited,dist,numNodes);
        if(currMin==-1){
            break;
        }
        visited[currMin]=1;
        for(int j=0;j<adjacent[currMin].size();j++){
            int to=adjacent[currMin][j];
            int currWeight=weight[currMin][j];
            if(dist[currMin]+currWeight<dist[to]){
                dist[to]=dist[currMin]+currWeight;
                parent[to]=currMin;
            }
        }
    }
}

void path(int i,const std::vector<int>& parent){
    if(parent[i]==-1){
        std::cout<<i<<'\n';
        return;
    }
    
    path(parent[i],parent);
    std::cout<<i<<'\n';
}

int main(){
    int numNodes,numVertices,startNode;
    std::cin>>numNodes>>numVertices;
    
    std::vector<std::vector<int> > adjacent(numNodes),weight(numNodes);
    std::vector<int> visited(numNodes,0),dist(numNodes,INT_MAX);
    std::vector<int> parent(numNodes);
    
    int from,to,value;
    for(int i=0;i<numVertices;i++){
        std::cin>>from>>to>>value;
        adjacent[from].push_back(to);
        adjacent[to].push_back(from);
        weight[from].push_back(value);
        weight[to].push_back(value);
    }
    std::cin>>startNode;
    
    dijkstra(numNodes,startNode,adjacent,weight,parent,dist);
    
    int endNode;
    std::cin>>endNode;
    std::cout<<"Distance from "<<startNode<<" to "<<endNode<<" is "<<dist[endNode]<<'\n';
    path(endNode,parent);
    exit(EXIT_SUCCESS);
}
