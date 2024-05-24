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
unordered_set<string>att = {"sid","cid","age","score","name","dept","tid"};
unordered_map<string,vector<vector<string>>>TABLE;
vector<string>id = {"Student","Course","Teacher","Grade","Teach"};
vector<string>xid = {"sid","cid","age","score","name","dept","tid"};
unordered_map<string,int>mp ={{"sid",0},{"cid",1},{"age",2},{"score",3},{"name",4},{"dept",5},{"tid",6}};
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
                    vector<string>temp = {to_string(id),"",to_string(age),"","",dept,""};
                    TABLE["Student"].push_back(temp);
                    break;
                }
                case 1: {
                    long long cid;
                    string name;
                    cin >> cid >> name;
                    vector<string>temp = {"",to_string(cid),"","",name,"",""};
                    TABLE["Course"].push_back(temp);

                    break;
                }
                case 2: {
                    long long id, age;
                    string dept;
                    cin >> id >> dept >> age;
                    vector<string>temp = {to_string(id),"",to_string(age),"","",dept,""};
                    TABLE["Teacher"].push_back(temp);
                    break;
                }
                case 3: {
                    long long sid, cid, score;
                    cin >> sid >> cid >> score;
                     vector<string>temp = {to_string(sid),to_string(cid),"",to_string(score),"","",""};
                    TABLE["Grade"].push_back(temp);
                    break;
                }
                default: {
                    long long cid, tid;
                    cin >> cid >> tid;
                    vector<string>temp = {"",to_string(cid),"","","","",to_string(tid)};
                    TABLE["Teach"].push_back(temp);
                    break;
                }
            }
        }
    }
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
vector<string>xy1(string w,string str){
    vector<string>t;
    t = splitString_str(w,str);
    string x=t[0],y=t[1];
    vector<string>xt = splitString(x,'.');
    vector<string>yt = splitString(y,'.');
    string xx = xt.size()==1 ? xt[0]:xt[1];
    string yy = yt.size()==1 ? yt[0]:yt[1];
    if(xx[0]=='\"'&&xx.back()=='\"'){
        xx = xx.substr(1,xx.size()-2);
    }
    if(yy[0]=='\"'&&yy.back()=='\"'){
        yy = yy.substr(1,yy.size()-2);
    }
    return {xx,yy};
}

vector<string>xy2(string w,string str){
    vector<string>t;
    t = splitString_str(w,str);
    string x=t[0],y=t[1];
    vector<string>xt = splitString(x,'.');
    vector<string>yt = splitString(y,'.');
    string xx = xt.size()==1 ? xt[0]:xt[1];
    string yy = yt.size()==1 ? yt[0]:yt[1];
    if(xx[0]=='\"'&&xx.back()=='\"'){
        xx = xx.substr(1,xx.size()-2);
    }
    if(yy[0]=='\"'&&yy.back()=='\"'){
        yy = yy.substr(1,yy.size()-2);
    }
    return {xx,yy};
}
// "sid","cid","age","score","name","dept","tid"
void get_data(const std::vector<std::string>&table,const std::vector<std::string>&attribute,const std::vector<std::string>&where){
   if(table.size()==1){
    for(auto&it:TABLE[table[0]]){
        int flag=1;
        for(auto&w:where){
            
            if(w.find("!=")!=-1){
                vector<string> t = xy1(w,"!=");
                string xx = t[0],yy=t[1];

                if(xx==yy){
                    flag=0;
                    break;
                }
            }
            else if(w.find(">=")!=-1){
                vector<string> t = xy1(w,">=");
                string xx = t[0],yy=t[1];
                if(stoll(xx)<stoll(yy)){
                    flag=0;
                    break;
                }
            }
            else if(w.find("<=")!=-1){
                 vector<string> t = xy1(w,"<=");
                string xx = t[0],yy=t[1];
                if(stoll(xx)>stoll(yy)){
                    flag=0;
                    break;
                }
            }
            else if(w.find("=")!=-1){
                 vector<string> t = xy1(w,"=");
                string xx = t[0],yy=t[1];
                if(xx!=yy){
                    flag=0;
                    break;
                }
            }
            else if(w.find(">")!=-1){
                 vector<string> t = xy1(w,">");
                string xx = t[0],yy=t[1];
                if(stoll(xx)<=stoll(yy)){
                    flag=0;
                    break;
                }
            }
            else if(w.find("<")!=-1){
                 vector<string> t = xy1(w,"<");
                string xx = t[0],yy=t[1];
               if(stoll(xx)>=stoll(yy)){
                    flag=0;
                    break;
                }
            }
        }
        if(flag){
            if(attribute[0]=="*"){
                for(int i=0;i<7;i++){
                    if(it[i]!=""){
                        cout<<it[i];
                        cout<<" ";
                    }
                }
                cout<<endl;
            }
            else {
                for(int i=0;i<attribute.size();i++){
                    string a=attribute[i];
                    vector<string>t=splitString(a,'.');
                    string s;
                    if(t.size()==1)s=t[0];
                    else s=t[1];
                    cout<<it[mp[s]];
                    if(i!=attribute.size()-1)cout<<" ";
                }
                cout<<endl;
            }
        }
    }
   }
   else{
    for(auto&it1:TABLE[table[0]]){
        for(auto&it2:TABLE[table[1]]){
            int flag = 1;
            for(auto&w:where){
               
                vector<string>t;
            if(w.find("!=")!=-1){
                t = splitString_str(w,"!=");
                string x=t[0],y=t[1];
                string xx,yy;
                vector<string>xt = splitString(x,'.');
                vector<string>yt = splitString(y,'.');
                if(xt.size()==1){
                    if(!mp.count(xt[0])){
                        xx = xt[0];
                        if(xx[0]=='\"'&&xx.back()=='\"')xx = xx.substr(1,xx.size()-2);
                    }
                    else xx = it1[mp[xt[0]]] != "" ? it1[mp[xt[0]]]:it2[mp[xt[0]]];
                }
                else {
                    if(xt[0]==table[0])xx=it1[mp[xt[1]]];
                    else xx=it2[mp[xt[1]]];
                }
                if(yt.size()==1){
                    if(!mp.count(yt[0])){
                        yy = yt[0];
                        if(yy[0]=='\"'&&yy.back()=='\"')
                        yy = yy.substr(1,yy.size()-2);
                    }
                    else yy = it1[mp[yt[0]]] != "" ? it1[mp[yt[0]]]:it2[mp[yt[0]]];
                }
                else {
                    if(yt[0]==table[0])yy=it1[mp[yt[1]]];
                    else yy=it2[mp[yt[1]]];
                }
                if(xx==yy){
                    flag=0;
                    break;
                }
            }
            else if(w.find(">=")!=-1){
                 t = splitString_str(w,">=");
                string x=t[0],y=t[1];
                string xx,yy;
                vector<string>xt = splitString(x,'.');
                vector<string>yt = splitString(y,'.');
                if(xt.size()==1){
                    if(!mp.count(xt[0])){
                        xx = xt[0];
                        if(xx[0]=='\"'&&xx.back()=='\"')xx = xx.substr(1,xx.size()-2);
                    }
                    else xx = it1[mp[xt[0]]] != "" ? it1[mp[xt[0]]]:it2[mp[xt[0]]];
                }
                else {
                    if(xt[0]==table[0])xx=it1[mp[xt[1]]];
                    else xx=it2[mp[xt[1]]];
                }
                if(yt.size()==1){
                    if(!mp.count(yt[0])){
                        yy = yt[0];
                        if(yy[0]=='\"'&&yy.back()=='\"')
                        yy = yy.substr(1,yy.size()-2);
                    }
                    else yy = it1[mp[yt[0]]] != "" ? it1[mp[yt[0]]]:it2[mp[yt[0]]];
                }
                else {
                    if(yt[0]==table[0])yy=it1[mp[yt[1]]];
                    else yy=it2[mp[yt[1]]];
                }
                if(stoll(xx)<stoll(yy)){
                    flag=0;
                    break;
                }
            }
            else if(w.find("<=")!=-1){
                t = splitString_str(w,"<=");
                string x=t[0],y=t[1];
                string xx,yy;
                vector<string>xt = splitString(x,'.');
                vector<string>yt = splitString(y,'.');
                if(xt.size()==1){
                    if(!mp.count(xt[0])){
                        xx = xt[0];
                        if(xx[0]=='\"'&&xx.back()=='\"')xx = xx.substr(1,xx.size()-2);
                    }
                    else xx = it1[mp[xt[0]]] != "" ? it1[mp[xt[0]]]:it2[mp[xt[0]]];
                }
                else {
                    if(xt[0]==table[0])xx=it1[mp[xt[1]]];
                    else xx=it2[mp[xt[1]]];
                }
                if(yt.size()==1){
                    if(!mp.count(yt[0])){
                        yy = yt[0];
                        if(yy[0]=='\"'&&yy.back()=='\"')
                        yy = yy.substr(1,yy.size()-2);
                    }
                    else yy = it1[mp[yt[0]]] != "" ? it1[mp[yt[0]]]:it2[mp[yt[0]]];
                }
                else {
                    if(yt[0]==table[0])yy=it1[mp[yt[1]]];
                    else yy=it2[mp[yt[1]]];
                }
                if(stoll(xx)>stoll(yy)){
                    flag=0;
                    break;
                }
            }
            else if(w.find("=")!=-1){
                t = splitString_str(w,"=");
                string x=t[0],y=t[1];
                string xx,yy;
                vector<string>xt = splitString(x,'.');
                vector<string>yt = splitString(y,'.');
               if(xt.size()==1){
                    if(!mp.count(xt[0])){
                        xx = xt[0];
                        if(xx[0]=='\"'&&xx.back()=='\"')xx = xx.substr(1,xx.size()-2);
                    }
                    else xx = it1[mp[xt[0]]] != "" ? it1[mp[xt[0]]]:it2[mp[xt[0]]];
                }
                else {
                    if(xt[0]==table[0])xx=it1[mp[xt[1]]];
                    else xx=it2[mp[xt[1]]];
                }
                if(yt.size()==1){
                    if(!mp.count(yt[0])){
                        yy = yt[0];
                        
                        if(yy[0]=='\"'&&yy.back()=='\"')yy = yy.substr(1,yy.size()-2);
                        
                    }
                    else yy = it1[mp[yt[0]]] != "" ? it1[mp[yt[0]]]:it2[mp[yt[0]]];
                }
                else {
                    if(yt[0]==table[0])yy=it1[mp[yt[1]]];
                    else yy=it2[mp[yt[1]]];
                }
                if(xx!=yy){
                    flag=0;
                    break;
                }
            }
            else if(w.find(">")!=-1){
                t = splitString_str(w,">");
                string x=t[0],y=t[1];
                string xx,yy;
                vector<string>xt = splitString(x,'.');
                vector<string>yt = splitString(y,'.');
                if(xt.size()==1){
                    if(!mp.count(xt[0])){
                        xx = xt[0];
                        if(xx[0]=='\"'&&xx.back()=='\"')xx = xx.substr(1,xx.size()-2);
                    }
                    else xx = it1[mp[xt[0]]] != "" ? it1[mp[xt[0]]]:it2[mp[xt[0]]];
                }
                else {
                    if(xt[0]==table[0])xx=it1[mp[xt[1]]];
                    else xx=it2[mp[xt[1]]];
                }
                if(yt.size()==1){
                    if(!mp.count(yt[0])){
                        yy = yt[0];
                        if(yy[0]=='\"'&&yy.back()=='\"')
                        yy = yy.substr(1,yy.size()-2);
                    }
                    else yy = it1[mp[yt[0]]] != "" ? it1[mp[yt[0]]]:it2[mp[yt[0]]];
                }
                else {
                    if(yt[0]==table[0])yy=it1[mp[yt[1]]];
                    else yy=it2[mp[yt[1]]];
                }
                if(stoll(xx)<=stoll(yy)){
                    flag=0;
                    break;
                }
            }
            else if(w.find("<")!=-1){
                 t = splitString_str(w,"<");
                string x=t[0],y=t[1];
                string xx,yy;
                vector<string>xt = splitString(x,'.');
                vector<string>yt = splitString(y,'.');

                if(xt.size()==1){
                    if(!mp.count(xt[0])){
                        xx = xt[0];
                        if(xx[0]=='\"'&&xx.back()=='\"')xx = xx.substr(1,xx.size()-2);
                    }
                    else xx = it1[mp[xt[0]]] != "" ? it1[mp[xt[0]]]:it2[mp[xt[0]]];
                }
                else {
                    if(xt[0]==table[0])xx=it1[mp[xt[1]]];
                    else xx=it2[mp[xt[1]]];
                }
        
                if(yt.size()==1){

                    if(!mp.count(yt[0])){
                        yy = yt[0];
                        if(yy[0]=='\"'&&yy.back()=='\"')
                        yy = yy.substr(1,yy.size()-2);
                    }
                    else yy = it1[mp[yt[0]]] != "" ? it1[mp[yt[0]]]:it2[mp[yt[0]]];
                }
                else {
                    if(yt[0]==table[0])yy=it1[mp[yt[1]]];
                    else yy=it2[mp[yt[1]]];
                }
                
               if(stoll(xx)>=stoll(yy)){
                    flag=0;
                    break;
                }
            }
            }
            if(flag){
            if(attribute[0]=="*"){
                for(int i=0;i<7;i++){
                    if(it1[i]!=""){
                        cout<<it1[i];
                        cout<<" ";
                    }
                }
                for(int i=0;i<7;i++){
                    if(it2[i]!=""){
                        cout<<it2[i];
                        cout<<" ";
                    }
                }
                cout<<endl;
            }
            else {
                for(int i=0;i<attribute.size();i++){
                    string a=attribute[i];
                    vector<string>t=splitString(a,'.');
                    if(t.size()==1){
                        string x = it1[mp[t[0]]]=="" ? it2[mp[t[0]]] : it1[mp[t[0]]];
                        cout<<x<<" ";
                    }
                    else {
                        string x = t[0] == table[0] ? it1[mp[t[1]]] : it2[mp[t[1]]];
                        cout<<x<<" ";
                    }
                }
                cout<<endl;
            }
        }
        }
    }
   }
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
            
            //cout<<"Attribute:" << attribute_str<<endl;
            table_str = s.substr(t+5,w - t -5);
            //cout<<"Table:"<<table_str<<endl;
            //cout<<s<<endl;
            
            where_str = (w == s.size()+1 ? " " : s.substr(w+6));
            //cout<<"Where:"<<where_str<<endl;

            vector<string>table = splitString(table_str,',');
            //cout<<"T:"<<endl;
            //printVector(table);
            vector<string>attribute = splitString(attribute_str,',');
            //cout<<"A:"<<endl;
            //printVector(attribute);
            vector<string>where = splitString_str(where_str,"AND");
            
            
            //cout<<"W:"<<endl;
            //printVector(where);
            get_data(table,attribute,where);
            break;   
        }
        
    }
    return 0;
}