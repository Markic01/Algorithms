#include <iostream>
#include <vector>
#include <algorithm>

struct Point{
    int x,y;
};

bool compare(const Point& a, const Point& b){
    return a.x<b.x;
}

bool equalPoints(const Point& p1, const Point& p2){
    return (p1.x==p2.x && p1.y==p2.y);
}

int orientation(const Point& p1, const Point& p2, const Point& p3){
    int val = (p2.y - p1.y) * (p3.x - p2.x) - 
              (p2.x - p1.x) * (p3.y - p2.y); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
}

void bruteForce(int i, int j, std::vector<Point>& result, const std::vector<Point>& inArray){
    int leftmostPoint=i;
    for(int k=i+1;k<=j;k++){
		if(inArray[k].x<inArray[leftmostPoint].x){
			leftmostPoint=k;
		}
	}
    result.push_back(inArray[leftmostPoint]);
    
    int segLength=(j-i+1);
    int numPointsClocwise;
    bool endLoop=false;
    while(!endLoop){
        for(int p1=i;p1<=j;p1++){
            if(equalPoints(result.back(),inArray[p1])){
                continue;
            }
            
            numPointsClocwise=0;
            for(int p2=i;p2<=j;p2++){
                int currOrientation=orientation(result.back(),inArray[p1],inArray[p2]);
                if(currOrientation==1||currOrientation==0){
                    numPointsClocwise++;
                }
            }

            if(numPointsClocwise==segLength){
                if(p1==i){
                    endLoop=true;
                    break;
                }

                result.push_back(inArray[p1]);
            }
        }
    }
}

void merge(std::vector<Point>& left, std::vector<Point>& right, std::vector<Point>& result){
    int largestXInLeft=0,smallestXInRight=0;
    for(int i=1;i<(int)left.size();i++){
        if(left[i].x>left[largestXInLeft].x){
            largestXInLeft=i;
        }
    }
    for(int i=1;i<(int)right.size();i++){
        if(right[i].x<right[smallestXInRight].x){
            smallestXInRight=i;
        }
    }

	//finding upper tangent
	int leftIndexUp=largestXInLeft;
	int rightIndexUp=smallestXInRight;
	bool isEnd;
	while(true){
		isEnd=true;
		
		int newLeftIndex=(leftIndexUp-1+left.size())%left.size();
		int newRightIndex=(rightIndexUp+1)%right.size();
		
		if(orientation(left[leftIndexUp],right[rightIndexUp],right[newRightIndex])!=1){
			rightIndexUp=newRightIndex;
			isEnd=false;
		}
		if(orientation(right[rightIndexUp],left[leftIndexUp],left[newLeftIndex])!=2){
			leftIndexUp=newLeftIndex;
			isEnd=false;
		}
		
		if(isEnd){
			break;
		}
	}

	//finding lower tangent
	int leftIndexDown=largestXInLeft;
	int rightIndexDown=smallestXInRight;
	while(true){
		isEnd=true;
		
		int newLeftIndex=(leftIndexDown+1)%left.size();
		int newRightIndex=(rightIndexDown-1+right.size())%right.size();
		
		if(orientation(left[leftIndexDown],right[rightIndexDown],right[newRightIndex])!=2){
			rightIndexDown=newRightIndex;
			isEnd=false;
		}
		if(orientation(right[rightIndexDown],left[leftIndexDown],left[newLeftIndex])!=1){
			leftIndexDown=newLeftIndex;
			isEnd=false;
		}
		
		if(isEnd){
			break;
		}
	}

	int i=leftIndexDown;
	while(i!=leftIndexUp){
		result.push_back(left[i]);
		i=(i+1)%left.size();
	}
	result.push_back(left[i]);

	i=rightIndexUp;
	while(i!=rightIndexDown){
		result.push_back(right[i]);
		i=(i+1)%right.size();
	}
	result.push_back(right[i]);
}

void splitSolve(int leftIndex, int rightIndex, std::vector<Point>& result, const std::vector<Point>& inArray){
    int length=rightIndex-leftIndex+1;
    if(length<5){
        bruteForce(leftIndex,rightIndex,result,inArray);
        return;
    }

    std::vector<Point> left,right;
    int midIndex=(leftIndex+rightIndex)/2;
    splitSolve(leftIndex,midIndex,left,inArray);
    splitSolve(midIndex+1,rightIndex,right,inArray);
    merge(left,right,result);
}

void input(std::vector<Point>& inArray){
	int numPoints;
    std::cin>>numPoints;
    for(int i=0,x,y;i<numPoints;i++){
        std::cin>>x>>y;
        inArray.push_back({x,y});
    }
}

void convexHull(const std::vector<Point>& inArray, std::vector<Point>& result){
	splitSolve(0,inArray.size()-1,result,inArray);
}

int main(){
    std::vector<Point> inArray;
    input(inArray);
    sort(inArray.begin(),inArray.end(),compare);

    std::vector<Point> result;

	convexHull(inArray,result);

    std::cout<<result.size()<<'\n';
    for(int i=0;i<(int)result.size();i++)
        std::cout<<result[i].x<<' '<<result[i].y<<'\n';
    exit(EXIT_SUCCESS);
}
