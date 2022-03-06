#ifndef SQL_H
#define SQL_H
//typedef enum{INSERT,DELETE,UPDATE,SELECT,ERROR} CMD;
#include "core.h"

class SQL{
    /* SPACE in SQL command is strictly restricted
     * ex.: WHERE column=value
     * This pattern does not allow ' ' to be around '='
     * */
public:
    bool suc;   // SQL_STATE
    SQL(){
        suc=true;
    }
    void read(string &cmd,int identity);   // cmd check and call corresponding function
    // SELECT * FROM name WHERE column CONTAINS value
    void SELECT(string &name, string &value, string &attribute, int identity);
    // UPDATE name SET column=value1,column2=value2, ··· WHERE column=value
    void UPDATE(string &name, string &value, string &attribute, string &set, int identity);
    // INSERT INTO name VALUES (value1,value2,···,valueT)
    void INSERT(string &name, string &value, int identity);
    // DELETE FROM name WHERE column=value
    void DELETE(string &name, string &value,string &attribute, int identity);
};
#endif
