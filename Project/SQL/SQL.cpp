#include<iostream>
#include<string>
#include<vector> 
#include<unordered_map>
#include <unordered_set>
#include <sstream>


using namespace std;
/*
Student(sid,dept,age)
Course(cid,name)
Teacher(tid,dept,age)
Grade(sid,cid,score)
Teach(cid,tid)
*/
unordered_map<long long,pair<string,long long>>Student;
unordered_map<long long ,string>Course;
unordered_map<long long,pair<string,long long>>Teacher;
unordered_map<string,long long>Grade;
unordered_map<long long,unordered_set<long long>>Teach;

string key(long long sid,long long cid){
    string k = to_string(sid) + "|" + to_string(cid);
    return k;
}
void process_data(){
    for(int i = 0 ;i < 5 ;i++){
        int n;
        cin>>n;
        while(n>0){
            n--;
            switch(i) {
                case 0: {
                    long long id, age;
                    string dept;
                    cin >> id >> dept >> age;
                    Student[id] = make_pair(dept,age);
                    break;
                }
                case 1: {
                    long long cid;
                    string name;
                    cin >> cid >> name;
                    Course[cid] = name;
                    break;
                }
                case 2: {
                    long long id, age;
                    string dept;
                    cin >> id >> dept >> age;
                    Teacher[id] = make_pair(dept,age);
                    break;
                }
                case 3: {
                    long long sid, cid, score;
                    cin >> sid >> cid >> score;
                    string k = key(sid,cid);
                    Grade[k] = score;
                    break;
                }
                default: {
                    long long cid, tid;
                    cin >> cid >> tid;
                    Teach[cid].insert(tid);
                    break;
                }
            }
        }
    }
}
void get_data(string attribute,string table, string where){

}

// 移除字符串中的所有空格
std::string removeSpaces(const std::string& str) {
    std::string result;
    for (char ch : str) {
        if (!isspace(static_cast<unsigned char>(ch))) { // 使用isspace检查是否为空格
            result += ch;
        }
    }
    return result;
}
// 分割字符串的函数，基于提供的分隔符集合
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(removeSpaces(token));
    }

    return tokens;
}
// 分割字符串的函数，使用整个字符串作为分隔符
std::vector<std::string> splitString_str(const std::string& str, const std::string& delimiters) {
    std::vector<std::string> result;
    size_t pos = 0;
    size_t delimiterPos;

    // 只要还有分隔符，就继续分割
    while ((delimiterPos = str.find(delimiters, pos)) != std::string::npos) {
        // 如果分隔符前面有文本，添加到结果中
        if (delimiterPos != pos) {
            result.push_back(removeSpaces(str.substr(pos, delimiterPos - pos)));
        }
        // 更新位置，跳过分隔符
        pos = delimiterPos + delimiters.length();
    }
    
    // 添加剩余的文本
    if (pos != str.length()) {
        result.push_back(removeSpaces(str.substr(pos)));
    }

    return result;
}
// 打印字符串向量的函数
void printVector(const std::vector<std::string>& vec) {
    for (const std::string& str : vec) {
        std::cout << str <<" ";
    }
    cout<<endl;
}
int main(){
    process_data();
    int n;
    cin>>n;
    cin.ignore(); 
    while(n>0){
        n--;
        string s;
        // 读取每个查询
        while (getline(cin, s)) {
            //cout<<s;
            string attribute_str;
            string table_str;
            string where_str;
            int a = s.find("SELECT");
            int t = s.find("FROM");
            int w = s.find("WHERE") == -1 ? s.size() + 1  : s.find("WHERE");
            //cout<<a<<" "<<t;
            attribute_str = s.substr(a+7, t - a -8);
            
            cout<<"Attribute:" << attribute_str<<endl;
            table_str = s.substr(t+5,w - t -5);
            cout<<"Table:"<<table_str<<endl;
            //cout<<s<<endl;
            
            where_str = (w == s.size()+1 ? " " : s.substr(w+6));
            cout<<"Where:"<<where_str<<endl;

            vector<string>table = splitString(table_str,',');
            cout<<"T:"<<endl;
            printVector(table);
            vector<string>attribute = splitString(attribute_str,',');
            cout<<"A:"<<endl;
            printVector(attribute);
            vector<string>where = splitString_str(where_str,"AND");
            
            
            cout<<"W:"<<endl;
            printVector(where);
            break;   
        }
        
    }
    return 0;
}