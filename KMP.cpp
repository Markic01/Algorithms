#include <iostream>
#include <vector>
#include <string>

void makeLPS(const std::string& pattern, std::vector<int>& lps){
    lps[0]=0;
    int len=0,i=1;
    int patternLength=pattern.length();
    while(i<patternLength){
        if(pattern[i]==pattern[len]){
            len++;
            lps[i]=len;
            i++;
        }
        else{
            if(len>0){
                len=lps[len-1];
            }
            else{
                lps[i]=0;
                i++;
            }
        }
    }
}

void KnuthMorrisPratt(const std::string& inputText, const std::string& pattern){
    std::vector<int> lps(pattern.length());
    makeLPS(pattern,lps);

    int i=0,j=0;
    int textLength=inputText.length();
    int patternLength=pattern.length();
    while(i<textLength){
        if(inputText[i]==pattern[j]){
            i++;
            j++;
        }
        else{
            if(j>0)
                j=lps[j-1];
            else
                i++;
        }
        if(j==patternLength){
            std::cout<<i-j<<'\n';
            j=lps[j-1];
        }
    }
}

int main(){
    std::string inputText,pattern;
    std::cin>>inputText>>pattern;

    KnuthMorrisPratt(inputText,pattern);

    exit(EXIT_SUCCESS);
}
