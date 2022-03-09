#include "head/core.h"
#include "head/Commodity.h"
#include "head/People.h"
extern Buyer *buy;
void Commodity::Read() {
    ifstream fs;
    fs.open(target);
    char *tem=new char[1024];
    fs.getline(tem,1024);
    assert(fs.is_open() && "文件打开失败");
    char *ptr;
    int i = 0;
    while (!fs.eof()) {
        fs.getline(tem,1024);
        ptr=(char*)(&commodity[i]);
        char* cur = tem, * cpy = cur;
        for(int j=0;j<COM_NUM;j++) {
            while (*cpy != ','&&*cpy!='\0') cpy++;
            *cpy = '\0';
            strcpy(ptr, cur);
            ptr += com_table[j];
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
void Commodity::Write(){
    ofstream fs;
    fs.open(target);
    assert(fs.is_open() && "文件打开失败");
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
void Commodity::Printhead(int identity) {
    int j;
    vector<string> h = split(head,",");
    vector<int> a={0,1,2,3,5,6,7};
    if(identity==0){
    } else if(identity==1){
        // buyer
        a.erase(find(a.begin(),a.end(),3));
        a.erase(find(a.begin(),a.end(),7));
    } else if(identity==2){
        // seller
        a.erase(find(a.begin(),a.end(),5));
    } else assert(0);
    for(auto i=a.begin(); i!=a.end();i++) {
        j = com_print_table[*i] - len(h.at(*i).c_str());
        printf("%s",h.at(*i).c_str());
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
    num++;
    Write();
}
// identity: 0->admin 1->buyer 2->seller 3->info
bool Commodity::Select(string &value, string &attribute, int identity) {
    int j, compare,l;
    char *ptr=NULL;
    // assign compare according to attribute
    if(attribute=="") compare = -1;
    else compare = com_map[attribute];
    bool flag=compare==-1?true:false;
    vector<int> a={0,1,2,3,5,6,7};
    if(identity==0){
        l=70;
    } else if(identity==1){
        // buyer
        l=50;
        a.erase(find(a.begin(),a.end(),3));
        a.erase(find(a.begin(),a.end(),7));
    } else if(identity==2){
        // seller
        l=50;
        a.erase(find(a.begin(),a.end(),5));
    } else if(identity!=3) assert(0);
    if(compare!=-1) {
        for (int i = 0; i < num; i++) {
            ptr = (char *) &commodity[i];
            if(identity==0||strcmp(ptr+com_map["商品状态"],"销售中")==0) {
                if (is_substr(value, ptr + compare)) {
                    flag = true;
                    break;
                }
            }
        }
    }
    if(identity==3&&flag){
        if(!ptr) assert(0);
        SPLITSTAR(20);
        cout<<"商品ID: "<<((s_commodity*)ptr)->ID<<endl;
        cout<<"商品名称: "<<((s_commodity*)ptr)->Name<<endl;
        cout<<"商品价格: "<<((s_commodity*)ptr)->price<<endl;
        cout<<"上架时间: "<<((s_commodity*)ptr)->addedDate<<endl;
        cout<<"商品描述: "<<((s_commodity*)ptr)->description<<endl;
        cout<<"商品卖家: "<<((s_commodity*)ptr)->sellerID<<endl;
        SPLITSTAR(20);

    } else if (flag) {
        SPLITSTAR(l);
        Printhead(identity);
        for (int i = 0; i < num; i++) {
            ptr = (char *) &commodity[i];
            if (identity==0 || strcmp(ptr + com_map["商品状态"], "销售中") == 0) {  // administrator 0
                if (compare == -1 || is_substr(value, ptr + compare)) {
                    for(int cnt=0; cnt<COM_NUM;cnt++) {
                        if(find(a.begin(),a.end(),cnt)==a.end()){ptr += com_table[cnt]; continue;}
                        printf("%s", ptr);
                        j = com_print_table[cnt] - len(ptr);
                        for (; j > 0; j--) printf(" ");
                        ptr += com_table[cnt];
                    }
                    printf("\n");
                }
            }
        }
        SPLITSTAR(l);
    } else {
        SPLITSTAR(30);
        cout << "没有找到您想要的商品！返回初始界面" << endl;
        SPLITSTAR(30);
    }
    return flag;
}
void Commodity::Delete(string &value, string &attribute, int identity) {
    int compare;
    bool flag= false;
    if(attribute=="") compare = -1;
    else compare = com_map[attribute];
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&commodity[i];
        if(compare==-1|| value==ptr+compare) {
            ptr+=com_map["商品状态"];
            if(strcmp("已下架",ptr)==0) continue;
            flag=true;
            strcpy(ptr,"已下架");
        }
    }
    if(!flag) cout<<"商品已不存在!"<<endl;
    else cout<<"商品下架成功!"<<endl;
    Write();
}
void Commodity::Update(string &value, string &attribute, string &set, int identity) {
    int compare;
    bool flag= false;

    if(attribute==""&&value=="") compare = -1;
    else compare = com_map[attribute];
    vector<string> res = split(set,",");
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&commodity[i];
        if(compare==-1|| value==ptr+compare) {
            //if(!strcmp("已下架",ptr+com_map["商品状态"])){}
            flag=true;
            for(auto j=res.begin(); j!=res.end(); j++){
                string::size_type pos = j->find("=");
                string tem1 = j->substr(0,pos);
                string tem2 = j->substr(pos+1);
                strcpy(ptr+com_map[tem1],tem2.c_str());
            }
        }
    }
    // for update from admin when banning account
    if(identity!=0) {
        if (!flag) cout << "没有对应商品!" << endl;
        else cout << "商品更新成功!" << endl;
    }
    Write();
}
int Commodity::Find(const char *ID) {
    int ret=-1;
    for(int i=0;i<num;i++){
        if(strcmp(ID,commodity[i].ID)==0&&strcmp("销售中",commodity[i].state)==0)  ret=i;
    }
    if(strcmp(buy->u,commodity[ret].sellerID)==0) ret=-2; //cannot buy commodity that buyer itself it selling
    return ret;
}
int Commodity::Find_Seller(const char *ID) {
    int ret=-1;
    for(int i=0;i<num;i++){
        if(strcmp(ID,commodity[i].ID)==0&&strcmp("销售中",commodity[i].state)==0)  ret=i;
    }
    return ret;
}
