#include <iostream>
#include <vector>
#include <algorithm>

struct Point{
    int x,y;
};

int orientation(const Point& p1,const Point& p2,const Point& p3){
    int val = (p2.y - p1.y) * (p3.x - p2.x) - 
              (p2.x - p1.x) * (p3.y - p2.y); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
}

bool isInside(const Point& toFind,const std::vector<Point>& in){
    int length=in.size();
    for(int i=0;i<length;i++){
        if(in[i].x==toFind.x&&in[i].y==toFind.y){
            return true;
        }
    }
    return false;
}

void bruteForce(int i,int j,std::vector<Point>& result,const std::vector<Point>& inArray){
    int segLength=(j-i+1);
    int pos,neg;
    for(int u=i;u<j;u++)
        for(int q=u+1;q<=j;q++){
            pos=0;neg=0;
            for(int r=i;r<=j;r++){
                int currOrientation=orientation(inArray[u],inArray[q],inArray[r]);
                if(currOrientation==1||currOrientation==0)
                    pos++;
                if(currOrientation==2||currOrientation==0)
                    neg++;
            }
            if(pos==segLength||neg==segLength){
                if(!isInside(inArray[u],result)){
                    result.push_back(inArray[u]);
                }
                if(!isInside(inArray[q],result)){
                    result.push_back(inArray[q]);
                }
            }
        }
}

//TODO
void merge(std::vector<Point>& levo,std::vector<Point>& desno){

}

void splitSolve(int i,int j,std::vector<Point>& result,const std::vector<Point>& inArray,int n){
    if(j-i<10){
        bruteForce(i,j,result,inArray);
        return;
    }
    std::vector<Point> left(n/2),right(n);
    int mid=(i+j)/2;
    splitSolve(i,mid,left,inArray,n);
    splitSolve(mid+1,j,right,inArray,n);
    merge(left,right);
}

bool compare(const Point& a,const Point& b){
    return a.x<b.x;
}

void input(int& n,std::vector<Point>& inArray){
    std::cin>>n;
    for(int i=0,x,y;i<n;i++){
        std::cin>>x>>y;
        inArray.push_back({x,y});
    }
    sort(inArray.begin(),inArray.end(),compare);
}

int main(){
    int numPoints;
    std::vector<Point> inArray;
    input(numPoints,inArray);
    std::vector<Point> result;
    bruteForce(0,numPoints-1,result,inArray);
    int m=result.size();
    std::cout<<m<<'\n';
    for(int i=0;i<m;i++)
        std::cout<<result[i].x<<' '<<result[i].y<<'\n';
    exit(EXIT_SUCCESS);
}
