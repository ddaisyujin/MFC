#pragma once
#include "OwnUtility.h"

class DATA_PAIR
{
public:
	string* addr=0;
	int size=0;
};

class INFO
{
public:
	string mode;
	string name;
	DATA_PAIR value;
	HTREEITEM hItem=0;

	void ClearInfo(void);
};

class FILE_HANDLER{
public:
	// key: mode, value: {name, value}
	map<string, map<string, vector<string>>> item;
	
private:
	//상대경로
	string dataFilePath = "FileReaderDataFile.txt";
	string historyFilePath = "FileReaderHistoryFile.txt";

public:
	// FileReaderDataFile에서 데이터를 읽어온 뒤에 멤버변수 item에 데이터를 채운다.
	void UpdateItemMap();
};

extern INFO selectItem;
extern FILE_HANDLER trees;