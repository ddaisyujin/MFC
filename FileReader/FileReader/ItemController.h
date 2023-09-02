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
	//�����
	string dataFilePath = "FileReaderDataFile.txt";
	string historyFilePath = "FileReaderHistoryFile.txt";

public:
	// FileReaderDataFile���� �����͸� �о�� �ڿ� ������� item�� �����͸� ä���.
	void UpdateItemMap();
};

extern INFO selectItem;
extern FILE_HANDLER trees;