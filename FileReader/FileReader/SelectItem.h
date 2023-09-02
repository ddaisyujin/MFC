#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class DATA_PAIR
{
	vector<string>* addr;
	int size;
};

class INFO
{
public:
	string mode;
	string name;
	DATA_PAIR value;
};

INFO selectItem;
// key: mode, value: {name, value}
map<string, map<string, vector<string>>> treeItem;