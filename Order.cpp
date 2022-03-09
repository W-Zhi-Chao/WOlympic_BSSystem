#include "head/Order.h"
void Order::Read() {
    ifstream fs;
    fs.open(target);
    char *tem=new char[1024];
    fs.getline(tem,1024);
    assert(fs.is_open() && "文件打开失败");
    char *ptr;
    int i = 0;
    while (!fs.eof()) {
        fs.getline(tem,1024);
        ptr=(char*)(&order[i]);
        char* cur = tem, * cpy = cur;
        for(int j=0;j<ORD_NUM;j++) {
            while (*cpy != ','&&*cpy!='\0') cpy++;
            *cpy = '\0';
            strcpy(ptr, cur);
            ptr += ord_table[j];
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
void Order::Write(){
    ofstream fs;
    fs.open(target);
    assert(fs.is_open() && "文件打开失败");
    fs<<head<<endl;
    for(int i=0; i<num; i++){
        char *ptr=(char*)&order[i];
        for(int j=0;j<ORD_NUM;j++){
            fs<<ptr;
            if(j!=ORD_NUM-1) fs<<',';
            ptr+=ord_table[j];
        }
        if(i!=num-1) fs<<endl;
    }
    fs.close();
}
void Order::Printhead(int identity) {
    int j;
    vector<string> h = split(head,",");
    vector<int> a={0,1,2,3,4,5,6};
    if(identity==0){
    } else if(identity==1){
        // buyer
        a.erase(find(a.begin(),a.end(),6));
    } else if(identity==2){
        // seller
        a.erase(find(a.begin(),a.end(),5));
    } else if(identity!=3) assert(0);
    for(auto i=a.begin(); i!=a.end();i++) {
        j = ord_print_table[*i] - len(h.at(*i).c_str());
        printf("%s",h.at(*i).c_str());
        for(; j > 0; j--) printf(" ");
    }
    cout<<endl;
}
void Order::Insert(string &value, int identity) {
    vector<string> res = split(value,",");
    char *ptr = (char*)&order[num];
    for(int i=0;i<ORD_NUM;i++){
        // value should be full version
        strcpy(ptr,res.at(i).c_str());
        ptr+=ord_table[i];
    }
    num++;
    Write();
}
bool Order::Select(string &value, string &attribute, int identity) {
    int j, compare,l;
    // assign compare according to attribute
    if(attribute=="") compare = -1;
    else compare = ord_map[attribute];
    bool flag=compare==-1?true:false;
    vector<int> a={0,1,2,3,4,5,6};
    if(identity==0){
        l=60;
    } else if(identity==1){
        // buyer
        l=50;
        a.erase(find(a.begin(),a.end(),6));
    } else if(identity==2){
        // seller
        l=50;
        a.erase(find(a.begin(),a.end(),5));
    } else if(identity!=3) assert(0);
    if(compare!=-1) {
        for (int i = 0; i < num; i++) {
            char *ptr = (char *) &order[i];
            if (is_substr(value,ptr+compare)){
                flag=true;
                break;
            }
        }
    }
    if(flag) {
        SPLITSTAR(l);
        Printhead(identity);
        for (int i = 0; i < num; i++) {
            char *ptr = (char *) &order[i];
            if (compare == -1 || is_substr(value, ptr + compare)) {
                for (int cnt = 0; cnt < ORD_NUM; cnt++) {
//                if (cnt == 4) {
//                    ptr += ord_table[cnt];
//                    continue;
//                }
                    if(find(a.begin(),a.end(),cnt)==a.end()){ptr += ord_table[cnt]; continue;}
                    printf("%s", ptr);
                    j = ord_print_table[cnt] - len(ptr);
                    for (; j > 0; j--) printf(" ");
                    ptr += ord_table[cnt];
                }
                printf("\n");
            }
        }
        SPLITSTAR(l);
    } else {
        SPLITSTAR(30);
        cout<<"没有找到您想要的订单！返回初始界面"<<endl;
        SPLITSTAR(30);
    }
    return flag;
}



