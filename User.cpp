#include "head/core.h"
#include "head/User.h"
void User::Read() {
    ifstream fs;
    fs.open(target);
    char *tem=new char[1024];
    fs.getline(tem,1024);
    assert(fs.is_open() && "文件打开失败");
    char *ptr;
    int i = 0;
    while (!fs.eof()) {
        fs.getline(tem,1024);
        ptr=(char*)(&user[i]);
        char* cur = tem, * cpy = cur;
        for(int j=0;j<USE_NUM;j++) {
            while (*cpy != ','&&*cpy!='\0') cpy++;
            *cpy = '\0';
            strcpy(ptr, cur);
            ptr += use_table[j];
            cpy++;
            cur = cpy;
        }
        memset(tem, '\0', 1024);
        i++;
    }
    this->num=i;
    delete []tem;
    fs.close();
}
void User::Write(){
    ofstream fs;
    fs.open(target);
    assert(fs.is_open() && "文件打开失败");
    fs<<"用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态"<<endl;
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
void User::Printhead(int identity) {
    int j;
    vector<string> h = split(head,",");
    for(int i=0; i<USE_NUM;i++) {
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
    num++;
    Write();
}
bool User::Select(string &value, string &attribute, int identity) {
    int j, compare;
    // assign compare according to attribute
    if(attribute=="") compare = -1;
    else compare = use_map[attribute];
    bool flag=compare==-1?true:false;
    if(compare!=-1) {
        for (int i = 0; i < num; i++) {
            char *ptr = (char *) &user[i];
            if (is_substr(value,ptr+compare)){
                flag=true;
                break;
            }
        }
    }
    if(flag) {
        SPLITSTAR(80);
        Printhead(identity);
        for (int i = 0; i < num; i++) {
            char *ptr = (char *) &user[i];
            if (compare == -1 || is_substr(value, ptr + compare)) {
                for (int cnt = 0; cnt < USE_NUM; cnt++) {
                    printf("%s", ptr);
                    j = use_print_table[cnt] - len(ptr);
                    for (; j > 0; j--) printf(" ");
                    ptr += use_table[cnt];
                }
                printf("\n");
            }
        }
        SPLITSTAR(80);
    } else{
        SPLITSTAR(26);
        cout<<"没有找到对应的用户！返回初始界面"<<endl;
        SPLITSTAR(26);
    }
    return flag;
}
void User::Delete(string &value, string &attribute, int identity) {
    int compare;
    bool flag= false;
    if(attribute=="") compare = -1;
    else compare = use_map[attribute];
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&user[i];
        if(compare==-1|| value==(char*)(ptr+compare)) {
            ptr+=use_map["用户状态"];
            if(strcmp("封禁",ptr)==0) continue;
            flag=true;
            strcpy(ptr,"封禁");
        }
    }
    if(!flag) cout<<"没有对应用户!"<<endl;
    else cout<<"用户封禁成功!"<<endl;
    Write();
}
void User::Update(string &value, string &attribute, string &set, int identity) {
    int compare;
    bool flag= false;
    if(attribute==""&&value=="") compare = -1;
    else compare = use_map[attribute];
    vector<string> res = split(set,",");
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&user[i];
        if(compare==-1|| value==ptr+compare) {
            //if(!strcmp("已下架",ptr+com_map["商品状态"])){}
            flag=true;
            for(auto j=res.begin(); j!=res.end(); j++){
                string::size_type pos = j->find("=");
                string tem1 = j->substr(0,pos);
                string tem2 = j->substr(pos+1);
                strcpy(ptr+use_map[tem1],tem2.c_str());
            }
        }
    }
    // for update from admin when banning account
    if(identity!=0) {
        if (!flag) cout << "更新失败!" << endl;
        else cout << "更新成功!" << endl;
    }
    Write();
}
int User::Find(const char *name) {
    for (int i = 0; i < num; i++) {
        if (strcmp(name,user[i].userID)==0&&strcmp("正常",user[i].state)==0){
            return i;
        }
    }
    return -1;
}
