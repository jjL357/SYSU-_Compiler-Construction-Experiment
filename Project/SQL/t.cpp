#include<iostream>
#include<string>
#include<vector> 
#include<unordered_map>
#include <unordered_set>
#include <sstream>
using namespace std;
int main(){
    string s = "info";
    s = s.substr(1,s.size()-2);
    cout<<s;
}