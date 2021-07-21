#include <iostream>
#include <vector>
#include <math.h>


int minHalf(const std::vector<int>& inArray, std::vector<std::vector<int>>& sparseTable,const int i,const int j){
    if(inArray[sparseTable[i][j-1]]<inArray[sparseTable[i+(1<<(j-1))][j-1]]){
        return sparseTable[i][j-1];
    }
    return sparseTable[i+(1<<(j-1))][j-1];
}

int query(const std::vector<int>& inArray, const std::vector<std::vector<int>>& sparseTable,const int left,const int right){
    int lengthOfSubarray=right-left+1;
    int logLength=log2(lengthOfSubarray);
    if(inArray[sparseTable[left][logLength]]<inArray[sparseTable[right-(1<<logLength)+1][logLength]]){
        return sparseTable[left][logLength];
    }
    return sparseTable[right-(1<<logLength)+1][logLength];
}

int main(){
    int numElements;
    std::cin>>numElements;
    int maxSubarrays=log2(numElements)+1;

    std::vector<std::vector<int>> sparseTable(numElements,std::vector<int>(maxSubarrays));
    std::vector<int> inArray(numElements);

    for(int i=0;i<numElements;i++){
        std::cin>>inArray[i];
        sparseTable[i][0]=i;
    }

    for(int j=1;j<maxSubarrays;j++){
        for(int i=0;i<(numElements-(1<<j)+1);i++){
            sparseTable[i][j]=minHalf(inArray,sparseTable,i,j);
        }
    }

    int leftIndex,rightIndex;
    std::cin>>leftIndex>>rightIndex;
    std::cout<<inArray[query(inArray,sparseTable,leftIndex,rightIndex)]<<'\n';
    exit(EXIT_SUCCESS);
}
