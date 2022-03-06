#include "head/core.h"
#include "head/Commodity.h"
void Commodity::Read() {
    ifstream fs;
    fs.open(target);
    char tem[500];
    fs.getline(tem,500);
    assert(fs.is_open() && "文件打开失败");
    char *ptr;
    int i = 0;
    while (!fs.eof()) {
        fs.getline(tem,500);
        ptr=(char*)(&commodity[i]);
        char* cur = tem, * cpy = cur;
        for(int j=0;j<COM_NUM;j++) {
            while (*cpy != ',') cpy++;
            *cpy = '\0';
            strcpy(ptr, cur);
            ptr += com_table[j];
            cpy++;
            cur = cpy;
        }
        memset(tem, '\0', 500);
        i++;
    }
    this->num=i;
    fs.close();
}
void Commodity::Write(){
    ofstream fs;
    fs.open(target);
    fs<<head<<endl;
    for(int i=0; i<num; i++){
        char *ptr=(char*)&commodity[i];
        for(int j=0;j<COM_NUM;j++){
            fs<<ptr;
            if(j!=COM_NUM-1) fs<<',';
            ptr+=com_table[j];
        }
        if(i!=num-1) fs<<endl;
    }
    fs.close();
}
void Commodity::Printhead() {
    int j;
    vector<string> h = split(head,",");
    for(int i=0; i<COM_NUM;i++) {
        if(i==4) continue;
        j = com_print_table[i] - len(h.at(i).c_str());
        printf("%s",h.at(i).c_str());
        for(; j > 0; j--) printf(" ");
    }
    cout<<endl;
}
void Commodity::Insert(string &value, int identity) {
    vector<string> res = split(value,",");
    char *ptr = (char*)&commodity[num];
    for(int i=0;i<COM_NUM;i++){
        // value should be full version
        strcpy(ptr,res.at(i).c_str());
        ptr+=com_table[i];
    }
}
void Commodity::Select(string &value, string &attribute, int identity) {
    int j, compare;
    // assign compare according to attribute
    if(attribute=="") compare = -1;
    else compare = com_map[attribute];
    vector<string> h = split(head,",");
    Printhead();
//    printf("商品ID   名称          价格         数量   卖家ID       上架时间     商品状态\n");
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&commodity[i];
        if(compare==-1|| is_substr(value,ptr+compare)) {
            for (int cnt = 0; cnt < COM_NUM; cnt++) {
                if (cnt == 4) {
                    ptr += com_table[cnt];
                    continue;
                }
                printf("%s", ptr);
                j = com_print_table[cnt] - len(ptr);
                for (; j > 0; j--) printf(" ");
                ptr += com_table[cnt];
            }
            printf("\n");
        }
    }
}
void Commodity::Delete(string &value, string &attribute, int identity) {
    int compare;
    bool flag= false;
    if(attribute=="") compare = -1;
    else compare = com_map[attribute];
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&commodity[i];
        if(compare==-1|| is_substr(value,ptr+compare)) {
            ptr+=com_map["商品状态"];
            if(!strcmp("已下架",ptr)) continue;
            flag=true;
            strcpy(ptr,"已下架");
        }
    }
    if(!flag) cout<<"没有对应商品!"<<endl;
    else cout<<"商品下架成功!"<<endl;
}
void Commodity::Update(string &value, string &attribute, string &set, int identity) {
    int compare;
    bool flag= false;
    if(attribute=="") compare = -1;
    else compare = com_map[attribute];
    vector<string> res = split(set,",");
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&commodity[i];
        if(compare==-1|| is_substr(value,ptr+compare)) {
            //if(!strcmp("已下架",ptr+com_map["商品状态"])) continue;
            flag=true;
            for(auto j=res.begin(); j!=res.end(); j++){
                string::size_type pos = j->find("=");
                string tem1 = j->substr(0,pos);
                string tem2 = j->substr(pos+1);
                strcpy(ptr+com_map[tem1],tem2.c_str());
            }
        }
    }
    if(!flag) cout<<"没有对应商品!"<<endl;
    else cout<<"商品更新成功!"<<endl;
}
