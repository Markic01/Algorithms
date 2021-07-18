#include <iostream>
#include <vector>

void dfs(int i, int currParent, const std::vector<std::vector<int>>& adjacent, 
         std::vector<int>& parent, std::vector<int>& discovered, std::vector<int>& lowest,
         std::vector<bool>& isVisited, std::vector<bool>& isArticulationPoint){

    static int startTime=0;
    parent[i]=currParent;
    discovered[i]=lowest[i]=startTime++;
    isVisited[i]=true;
    int children=0;

    for(int j=0;j<(int)adjacent[i].size();j++){
        if(!isVisited[adjacent[i][j]]){
            dfs(adjacent[i][j],i,adjacent,parent,discovered,lowest,isVisited,isArticulationPoint);
            children++;
            lowest[i]=std::min(lowest[i],lowest[adjacent[i][j]]);
            if(parent[i]==-1&&children>1)
                isArticulationPoint[i]=1;
            if(parent[i]!=-1&&lowest[adjacent[i][j]]>=discovered[i])
                isArticulationPoint[i]=1;
        }
        else{
            lowest[i]=std::min(lowest[i],discovered[adjacent[i][j]]);
        }
    }
}

int main(){
    int nodes,edges;
    std::cin>>nodes>>edges;

    std::vector<std::vector<int>> adjacent(nodes);
    std::vector<int> discovered(nodes),lowest(nodes),parent(nodes,-1);
    std::vector<bool> isVisited(nodes,false),isArticulationPoint(nodes,false);

    int from,to;
    for(int i=0;i<edges;i++){
        std::cin>>from>>to;
        adjacent[from].push_back(to);
        adjacent[to].push_back(from);
    }

    dfs(0,-1,adjacent,parent,discovered,lowest,isVisited,isArticulationPoint);

    std::cout<<"Articulation points are: ";
    for(int i=0;i<nodes;i++){
        if(isArticulationPoint[i]){
            std::cout<<i<<" ";
        }
    }
    std::cout<<'\n';
    
    exit(EXIT_SUCCESS);
}
