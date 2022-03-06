#include "head/core.h"
//string substr(string &str,string::size_type begin,string::size_type n){
//    cout<<"?"<<endl;
//    string tem = str.substr(begin,n);
//    tem.erase(tem.end());
//    return tem;
//}
vector<string> split(string &str, string pattern){
    string::size_type pos;
    vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();
    for(int i=0; i<size; i++){
        pos=str.find(pattern,i);
        if(pos<size){
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}
bool is_substr(string &sub,const char *str){
    string str1 = str;
    if(str1.find(sub)!=str1.npos) return true;
    return false;
}
int len(const char *str) {
    int i = 0, cnt1 = 0, cnt2 = 0;
    while (str[i] != '\0') {
        if (str[i] < 0) cnt1++;
        else cnt2++;
        i++;
    }
    return (cnt1 / 3) * 2 + cnt2;
}
