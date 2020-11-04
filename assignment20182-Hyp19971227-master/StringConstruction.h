#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using std::vector;

#include <string>
using std::string;


// TODO: your code goes here:
void checkStringMatch(string p,int f[]){
    int m = p.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (p[k] == p[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}

//check whether target string contains the string 
bool foundInTarget(string p,string q){
    int m = p.length();
    int n = q.length();
    int f[m];     
    checkStringMatch(p, f);     
    int i = 0;
    int k = 0;        
    while (i < n)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (q[i] == p[k])
        {
            i++;
            k++;
            if (k == m)
                return 1;
        }
        else
            k = f[k];
    }
    return 0;
}

string checkSubString(string s){
    string subs;
    if (s.find(subs) != std::string::npos) {
        return subs;
    }
}

//for the string which has the longest substring/substrings to be cloned,then clone the substring
bool useClone(string t){
    
    if (t.substr(0,1) == t.substr(2,3)) {
        return true;
    }
    else if (t.substr(0,3) == t.substr(5,8)){
        return true;
    }
    else{
        return false;
    }
}

int stringConstruction(string target, int appendCost, int cloneCost){
    string initialString;
    int cheapestCost;
    int sumAppend;
    int sumClone;
    initialString = "";
    //for the string which only has 2-3 character ,then only append the string
    if(target.size() <= 3 && useClone(target) == false){
        for(int i = 0;i<initialString.size();i++){
            if(foundInTarget(initialString,target)){
                sumAppend = appendCost + appendCost;
            }
        }
    }
    //if(useClone(appendCost,cloneCost)){
    else if(useClone(target) == true){
        for(int i = 0;i<initialString.size();i++){
            if(foundInTarget(initialString,target)){
                sumClone = cloneCost + cloneCost;
            }
        }
    }
    cheapestCost = sumAppend + sumClone;
    return cheapestCost;
}
// do not write or edit anything below this line

#endif
