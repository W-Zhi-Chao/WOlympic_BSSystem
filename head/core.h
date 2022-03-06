#ifndef WOLYMPIC_BSSYSTEM_CORE_H
#define WOLYMPIC_BSSYSTEM_CORE_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <vector>
using namespace std;
string substr(string &str,string::size_type begin,string::size_type n);
vector<string> split(string &str, string pattern);
int len(const char *str);
bool is_substr(string &, const char*);
#endif