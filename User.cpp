#include "head/core.h"
#include "head/User.h"
void User::Read() {
    ifstream fs;
    fs.open(target);
    char tem[500];
    fs.getline(tem,500);
    assert(fs.is_open() && "文件打开失败");
    char *ptr;
    int i = 0;
    while (!fs.eof()) {
        fs.getline(tem,500);
        ptr=(char*)(&user[i]);
        char* cur = tem, * cpy = cur;
        for(int j=0;j<USE_NUM;j++) {
            while (*cpy != ',') cpy++;
            *cpy = '\0';
            strcpy(ptr, cur);
            ptr += use_table[j];
            cpy++;
            cur = cpy;
        }
        memset(tem, '\0', 500);
        i++;
    }
    this->num=i;
    fs.close();
}
void User::Write(){
    ofstream fs;
    fs.open(target);
    assert(fs.is_open() && "文件打开失败");
    fs<<head<<endl;
    for(int i=0; i<num; i++){
        char *ptr=(char*)&user[i];
        for(int j=0;j<USE_NUM;j++){
            fs<<ptr;
            if(j!=USE_NUM-1) fs<<',';
            ptr+=use_table[j];
        }
        if(i!=num-1) fs<<endl;
    }
    fs.close();
}
void User::Printhead() {
    int j;
    vector<string> h = split(head,",");
    for(int i=0; i<USE_NUM;i++) {
        if(i==4) continue;
        j = use_print_table[i] - len(h.at(i).c_str());
        printf("%s",h.at(i).c_str());
        for(; j > 0; j--) printf(" ");
    }
    cout<<endl;
}
void User::Insert(string &value, int identity) {
    vector<string> res = split(value,",");
    char *ptr = (char*)&user[num];
    for(int i=0;i<USE_NUM;i++){
        // value should be full version
        strcpy(ptr,res.at(i).c_str());
        ptr+=use_table[i];
    }
}
void User::Select(string &value, string &attribute, int identity) {
    int j, compare;
    // assign compare according to attribute
    if(attribute=="") compare = -1;
    else compare = use_map[attribute];
    vector<string> h = split(head,",");
    Printhead();
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&user[i];
        if(compare==-1|| is_substr(value,ptr+compare)) {
            for (int cnt = 0; cnt < USE_NUM; cnt++) {
                if (cnt == 4) {
                    ptr += use_table[cnt];
                    continue;
                }
                printf("%s", ptr);
                j = use_print_table[cnt] - len(ptr);
                for (; j > 0; j--) printf(" ");
                ptr += use_table[cnt];
            }
            printf("\n");
        }
    }
}
void User::Delete(string &value, string &attribute, int identity) {
    int compare;
    bool flag= false;
    if(attribute=="") compare = -1;
    else compare = use_map[attribute];
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&user[i];
        if(compare==-1|| value==ptr+compare) {
            ptr+=use_map["用户状态"];
            if(!strcmp("封禁",ptr)) continue;
            flag=true;
            strcpy(ptr,"封禁");
        }
    }
    if(!flag) cout<<"没有对应用户!"<<endl;
    else cout<<"用户封禁成功!"<<endl;
}

