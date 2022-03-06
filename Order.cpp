#include "head/Order.h"
void Order::Read() {
    ifstream fs;
    fs.open(target);
    char tem[500];
    fs.getline(tem,500);
    assert(fs.is_open() && "文件打开失败");
    char *ptr;
    int i = 0;
    while (!fs.eof()) {
        fs.getline(tem,500);
        ptr=(char*)(&order[i]);
        char* cur = tem, * cpy = cur;
        for(int j=0;j<ORD_NUM;j++) {
            while (*cpy != ',') cpy++;
            *cpy = '\0';
            strcpy(ptr, cur);
            ptr += ord_table[j];
            cpy++;
            cur = cpy;
        }
        memset(tem, '\0', 500);
        i++;
    }
    this->num=i;
    fs.close();
}
void Order::Write(){
    ofstream fs;
    fs.open(target);
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
void Order::Printhead() {
    int j;
    vector<string> h = split(head,",");
    for(int i=0; i<ORD_NUM;i++) {
        if(i==4) continue;
        j = ord_print_table[i] - len(h.at(i).c_str());
        printf("%s",h.at(i).c_str());
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
}
void Order::Select(string &value, string &attribute, int identity) {
    int j, compare;
    // assign compare according to attribute
    if(attribute=="") compare = -1;
    else compare = ord_map[attribute];
    Printhead();
    for(int i = 0;i<num;i++){
        char *ptr = (char*)&order[i];
        if(compare==-1|| is_substr(value,ptr+compare)) {
            for (int cnt = 0; cnt < ORD_NUM; cnt++) {
                if (cnt == 4) {
                    ptr += ord_table[cnt];
                    continue;
                }
                printf("%s", ptr);
                j = ord_print_table[cnt] - len(ptr);
                for (; j > 0; j--) printf(" ");
                ptr += ord_table[cnt];
            }
            printf("\n");
        }
    }
}



