#include <iostream>
#include <string>
#include <vector> 
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

// 表名及其列
/* 
Student(sid,dept,age)
Course(cid,name)
Teacher(tid,dept,age)
Grade(sid,cid,score)
Teach(cid,tid)
*/

// TABLE根据表名存储不同表的记录
unordered_map<string, vector<vector<string>>> TABLE;

// 列与记录索引的映射
unordered_map<string, int> col_to_index = {
    {"sid", 0}, {"cid", 1}, {"tid", 2}, {"score", 3},
    {"name", 4}, {"dept", 5}, {"age", 6}
};

// 处理输入记录，存储到TABLE对应的表中
void process_data() {
    for (int i = 0; i < 5; i++) {
        int n;
        cin >> n;
        while (n > 0) {
            n--;
            switch (i) {
                case 0: { // Student(sid,dept,age)
                    long long sid, age;
                    string dept;
                    cin >> sid >> dept >> age;
                    vector<string> temp = {to_string(sid), "", "", "", "", dept, to_string(age)};
                    TABLE["Student"].push_back(temp);
                    break;
                }
                case 1: { // Course(cid,name)
                    long long cid;
                    string name;
                    cin >> cid >> name;
                    vector<string> temp = {"", to_string(cid), "", "", name, "", ""};
                    TABLE["Course"].push_back(temp);
                    break;
                }
                case 2: { // Teacher(tid,dept,age)
                    long long tid, age;
                    string dept;
                    cin >> tid >> dept >> age;
                    vector<string> temp = {to_string(tid), "", "", "", "", dept, to_string(age)};
                    TABLE["Teacher"].push_back(temp);
                    break;
                }
                case 3: { // Grade(sid,cid,score)
                    long long sid, cid, score;
                    cin >> sid >> cid >> score;
                    vector<string> temp = {to_string(sid), to_string(cid), "", to_string(score), "", "", ""};
                    TABLE["Grade"].push_back(temp);
                    break;
                }
                default: { // Teach(cid,tid)
                    long long cid, tid;
                    cin >> cid >> tid;
                    vector<string> temp = {"", to_string(cid), "", "", "", "", to_string(tid)};
                    TABLE["Teach"].push_back(temp);
                    break;
                }
            }
        }
    }
}

// 移除字符串中的所有空格
string removeSpaces(const string& str) {
    string result;
    for (char ch : str) {
        if (!isspace(static_cast<unsigned char>(ch))) { // 使用isspace检查是否为空格
            result += ch;
        }
    }
    return result;
}

// 分割字符串的函数，基于提供的分隔符(char)，同时去除无用的空格
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(removeSpaces(token));
    }

    return tokens;
}

// 分割字符串的函数，使用整个字符串作为分隔符(string)，同时去除无用的空格
vector<string> splitString_str(const string& str, const string& delimiters) {
    vector<string> result;
    size_t pos = 0;
    size_t delimiterPos;
    // 只要还有分隔符，就继续分割
    while ((delimiterPos = str.find(delimiters, pos)) != string::npos) {
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

// 对查询一张表的条件的左右值进行处理
// w : 条件字符串 str: 判别符
vector<string> process_condition(string w, string str) {
    vector<string> t;
    t = splitString_str(w, str);
    string x = t[0], y = t[1];
    // 针对一张表的查询 查询内容中可去除表名
    vector<string> xt = splitString(x, '.');
    vector<string> yt = splitString(y, '.');
    string xx = xt.size() == 1 ? xt[0] : xt[1];
    string yy = yt.size() == 1 ? yt[0] : yt[1];
    // 处理引号
    if (xx[0] == '\"' && xx.back() == '\"') {
        xx = xx.substr(1, xx.size() - 2);
    }
    if (yy[0] == '\"' && yy.back() == '\"') {
        yy = yy.substr(1, yy.size() - 2);
    }
    return {xx, yy};
}

// 处理对1张表的查询
void process_queries_for_one_table(const vector<string>& table, const vector<string>& attribute, const vector<string>& where) {
    for (auto& it : TABLE[table[0]]) {
            int flag = 1; // 条件是否成立标志
            for (auto& w : where) {
                if (w.find("!=") != -1) {
                    vector<string> t = process_condition(w, "!=");
                    string xx = t[0], yy = t[1];
                    if (xx == yy) {
                        flag = 0;
                        break;
                    }
                } else if (w.find(">=") != -1) {
                    vector<string> t = process_condition(w, ">=");
                    string xx = t[0], yy = t[1];
                    if (stoll(xx) < stoll(yy)) {
                        flag = 0;
                        break;
                    }
                } else if (w.find("<=") != -1) {
                    vector<string> t = process_condition(w, "<=");
                    string xx = t[0], yy = t[1];
                    if (stoll(xx) > stoll(yy)) {
                        flag = 0;
                        break;
                    }
                } else if (w.find("=") != -1) {
                    vector<string> t = process_condition(w, "=");
                    string xx = t[0], yy = t[1];
                    if (xx != yy) {
                        flag = 0;
                        break;
                    }
                } else if (w.find(">") != -1) {
                    vector<string> t = process_condition(w, ">");
                    string xx = t[0], yy = t[1];
                    if (stoll(xx) <= stoll(yy)) {
                        flag = 0;
                        break;
                    }
                } else if (w.find("<") != -1) {
                    vector<string> t = process_condition(w, "<");
                    string xx = t[0], yy = t[1];
                    if (stoll(xx) >= stoll(yy)) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) {
                if (attribute[0] == "*") {
                    for (int i = 0; i < 7; i++) {
                        if (it[i] != "") {
                            cout << it[i] << " ";
                        }
                    }
                    cout << endl;
                } else {
                    for (int i = 0; i < attribute.size(); i++) {
                        string a = attribute[i];
                        vector<string> t = splitString(a, '.');
                        string s;
                        if (t.size() == 1) s = t[0];
                        else s = t[1];
                        cout << it[col_to_index[s]];
                        if (i != attribute.size() - 1) cout << " ";
                    }
                    cout << endl;
                }
            }
        }
}

// 处理对两张表的查询
void process_queries_for_two_table(const vector<string>& table, const vector<string>& attribute, const vector<string>& where) {
    for (auto& it1 : TABLE[table[0]]) {
        for (auto& it2 : TABLE[table[1]]) {
            int flag = 1;
            for (auto& w : where) {
                vector<string> t;
                if (w.find("!=") != -1) {
                    t = splitString_str(w, "!=");
                    string x = t[0], y = t[1];
                    string xx, yy;
                    vector<string> xt = splitString(x, '.');
                    vector<string> yt = splitString(y, '.');
                    if (xt.size() == 1) {
                        if (!col_to_index.count(xt[0])) {
                            xx = xt[0];
                            if (xx[0] == '\"' && xx.back() == '\"') xx = xx.substr(1, xx.size() - 2);
                        } else xx = it1[col_to_index[xt[0]]] != "" ? it1[col_to_index[xt[0]]] : it2[col_to_index[xt[0]]];
                    } else {
                        if (xt[0] == table[0]) xx = it1[col_to_index[xt[1]]];
                        else xx = it2[col_to_index[xt[1]]];
                    }
                    if (yt.size() == 1) {
                        if (!col_to_index.count(yt[0])) {
                            yy = yt[0];
                            if (yy[0] == '\"' && yy.back() == '\"') yy = yy.substr(1, yy.size() - 2);
                        } else yy = it1[col_to_index[yt[0]]] != "" ? it1[col_to_index[yt[0]]] : it2[col_to_index[yt[0]]];
                    } else {
                        if (yt[0] == table[0]) yy = it1[col_to_index[yt[1]]];
                        else yy = it2[col_to_index[yt[1]]];
                    }
                    if (xx == yy) {
                        flag = 0;
                        break;
                    }
                } else if (w.find(">=") != -1) {
                    t = splitString_str(w, ">=");
                    string x = t[0], y = t[1];
                    string xx, yy;
                    vector<string> xt = splitString(x, '.');
                    vector<string> yt = splitString(y, '.');
                    if (xt.size() == 1) {
                        if (!col_to_index.count(xt[0])) {
                            xx = xt[0];
                            if (xx[0] == '\"' && xx.back() == '\"') xx = xx.substr(1, xx.size() - 2);
                        } else xx = it1[col_to_index[xt[0]]] != "" ? it1[col_to_index[xt[0]]] : it2[col_to_index[xt[0]]];
                    } else {
                        if (xt[0] == table[0]) xx = it1[col_to_index[xt[1]]];
                        else xx = it2[col_to_index[xt[1]]];
                    }
                    if (yt.size() == 1) {
                        if (!col_to_index.count(yt[0])) {
                            yy = yt[0];
                            if (yy[0] == '\"' && yy.back() == '\"') yy = yy.substr(1, yy.size() - 2);
                        } else yy = it1[col_to_index[yt[0]]] != "" ? it1[col_to_index[yt[0]]] : it2[col_to_index[yt[0]]];
                    } else {
                        if (yt[0] == table[0]) yy = it1[col_to_index[yt[1]]];
                        else yy = it2[col_to_index[yt[1]]];
                    }
                    if (stoll(xx) < stoll(yy)) {
                        flag = 0;
                        break;
                    }
                } else if (w.find("<=") != -1) {
                    t = splitString_str(w, "<=");
                    string x = t[0], y = t[1];
                    string xx, yy;
                    vector<string> xt = splitString(x, '.');
                    vector<string> yt = splitString(y, '.');
                    if (xt.size() == 1) {
                        if (!col_to_index.count(xt[0])) {
                            xx = xt[0];
                            if (xx[0] == '\"' && xx.back() == '\"') xx = xx.substr(1, xx.size() - 2);
                        } else xx = it1[col_to_index[xt[0]]] != "" ? it1[col_to_index[xt[0]]] : it2[col_to_index[xt[0]]];
                    } else {
                        if (xt[0] == table[0]) xx = it1[col_to_index[xt[1]]];
                        else xx = it2[col_to_index[xt[1]]];
                    }
                    if (yt.size() == 1) {
                        if (!col_to_index.count(yt[0])) {
                            yy = yt[0];
                            if (yy[0] == '\"' && yy.back() == '\"') yy = yy.substr(1, yy.size() - 2);
                        } else yy = it1[col_to_index[yt[0]]] != "" ? it1[col_to_index[yt[0]]] : it2[col_to_index[yt[0]]];
                    } else {
                        if (yt[0] == table[0]) yy = it1[col_to_index[yt[1]]];
                        else yy = it2[col_to_index[yt[1]]];
                    }
                    if (stoll(xx) > stoll(yy)) {
                        flag = 0;
                        break;
                    }
                } else if (w.find("=") != -1) {
                    t = splitString_str(w, "=");
                    string x = t[0], y = t[1];
                    string xx, yy;
                    vector<string> xt = splitString(x, '.');
                    vector<string> yt = splitString(y, '.');
                    if (xt.size() == 1) {
                        if (!col_to_index.count(xt[0])) {
                            xx = xt[0];
                            if (xx[0] == '\"' && xx.back() == '\"') xx = xx.substr(1, xx.size() - 2);
                        } else xx = it1[col_to_index[xt[0]]] != "" ? it1[col_to_index[xt[0]]] : it2[col_to_index[xt[0]]];
                    } else {
                        if (xt[0] == table[0]) xx = it1[col_to_index[xt[1]]];
                        else xx = it2[col_to_index[xt[1]]];
                    }
                    if (yt.size() == 1) {
                        if (!col_to_index.count(yt[0])) {
                            yy = yt[0];
                            if (yy[0] == '\"' && yy.back() == '\"') yy = yy.substr(1, yy.size() - 2);
                        } else yy = it1[col_to_index[yt[0]]] != "" ? it1[col_to_index[yt[0]]] : it2[col_to_index[yt[0]]];
                    } else {
                        if (yt[0] == table[0]) yy = it1[col_to_index[yt[1]]];
                        else yy = it2[col_to_index[yt[1]]];
                    }
                    if (xx != yy) {
                        flag = 0;
                        break;
                    }
                } else if (w.find(">") != -1) {
                    t = splitString_str(w, ">");
                    string x = t[0], y = t[1];
                    string xx, yy;
                    vector<string> xt = splitString(x, '.');
                    vector<string> yt = splitString(y, '.');
                    if (xt.size() == 1) {
                        if (!col_to_index.count(xt[0])) {
                            xx = xt[0];
                            if (xx[0] == '\"' && xx.back() == '\"') xx = xx.substr(1, xx.size() - 2);
                        } else xx = it1[col_to_index[xt[0]]] != "" ? it1[col_to_index[xt[0]]] : it2[col_to_index[xt[0]]];
                    } else {
                        if (xt[0] == table[0]) xx = it1[col_to_index[xt[1]]];
                        else xx = it2[col_to_index[xt[1]]];
                    }
                    if (yt.size() == 1) {
                        if (!col_to_index.count(yt[0])) {
                            yy = yt[0];
                            if (yy[0] == '\"' && yy.back() == '\"') yy = yy.substr(1, yy.size() - 2);
                        } else yy = it1[col_to_index[yt[0]]] != "" ? it1[col_to_index[yt[0]]] : it2[col_to_index[yt[0]]];
                    } else {
                        if (yt[0] == table[0]) yy = it1[col_to_index[yt[1]]];
                        else yy = it2[col_to_index[yt[1]]];
                    }
                    if (stoll(xx) <= stoll(yy)) {
                        flag = 0;
                        break;
                    }
                } else if (w.find("<") != -1) {
                    t = splitString_str(w, "<");
                    string x = t[0], y = t[1];
                    string xx, yy;
                    vector<string> xt = splitString(x, '.');
                    vector<string> yt = splitString(y, '.');
                    if (xt.size() == 1) {
                        if (!col_to_index.count(xt[0])) {
                            xx = xt[0];
                            if (xx[0] == '\"' && xx.back() == '\"') xx = xx.substr(1, xx.size() - 2);
                        } else xx = it1[col_to_index[xt[0]]] != "" ? it1[col_to_index[xt[0]]] : it2[col_to_index[xt[0]]];
                    } else {
                        if (xt[0] == table[0]) xx = it1[col_to_index[xt[1]]];
                        else xx = it2[col_to_index[xt[1]]];
                    }
                    if (yt.size() == 1) {
                        if (!col_to_index.count(yt[0])) {
                            yy = yt[0];
                            if (yy[0] == '\"' && yy.back() == '\"') yy = yy.substr(1, yy.size() - 2);
                        } else yy = it1[col_to_index[yt[0]]] != "" ? it1[col_to_index[yt[0]]] : it2[col_to_index[yt[0]]];
                    } else {
                        if (yt[0] == table[0]) yy = it1[col_to_index[yt[1]]];
                        else yy = it2[col_to_index[yt[1]]];
                    }
                    if (stoll(xx) >= stoll(yy)) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) {
                if (attribute[0] == "*") {
                    for (int i = 0; i < 7; i++) {
                        if (it1[i] != "") {
                            cout << it1[i] << " ";
                        }
                    }
                    for (int i = 0; i < 7; i++) {
                        if (it2[i] != "") {
                            cout << it2[i] << " ";
                        }
                    }
                    cout << endl;
                } else {
                    for (int i = 0; i < attribute.size(); i++) {
                        string a = attribute[i];
                        vector<string> t = splitString(a, '.');
                        if (t.size() == 1) {
                            string x = it1[col_to_index[t[0]]] == "" ? it2[col_to_index[t[0]]] : it1[col_to_index[t[0]]];
                            cout << x << " ";
                        } else {
                            string x = t[0] == table[0] ? it1[col_to_index[t[1]]] : it2[col_to_index[t[1]]];
                            cout << x << " ";
                        }
                    }
                    cout << endl;
                }
            }
        }
    }
}

// 处理查询信息
void process_queries(const vector<string>& table, const vector<string>& attribute, const vector<string>& where) {
    if (table.size() == 1) { // 只查询一张表
       process_queries_for_one_table(table,attribute,where);
    } 
    else { // 查询两张表
       process_queries_for_two_table(table,attribute,where);
    }
}

int main() {
    // 处理输入记录
    process_data();

    int n;
    cin >> n;
    cin.ignore();

    // 处理查询
    while (n > 0) {
        n--;
        string s;
        // 读取每个查询
        while (getline(cin, s)) {
            // 对查询语句的不同部分进行分割
            string attribute_str;
            string table_str;
            string where_str;
            int a = s.find("SELECT");
            int t = s.find("FROM");
            int w = s.find("WHERE") == -1 ? s.size() + 1 : s.find("WHERE");
            attribute_str = s.substr(a + 7, t - a - 8);
            table_str = s.substr(t + 5, w - t - 5);
            where_str = (w == s.size() + 1 ? " " : s.substr(w + 6));

            vector<string> table = splitString(table_str, ',');
            vector<string> attribute = splitString(attribute_str, ',');
            vector<string> where = splitString_str(where_str, "AND");

            // 处理查询并输出结果
            process_queries(table, attribute, where);
            break;
        }
    }
    return 0;
}
