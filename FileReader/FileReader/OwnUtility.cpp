#pragma once
#include "OwnUtility.h"

vector<string> StringToWordList(string str)
{
	vector<string> retList;
	if (!str.empty())
	{
		stringstream ss(str);
		string word;
		while (ss >> word)
		{
			retList.push_back(word);
		}
	}
	return retList;
}

string CStringToString(CString cstr)
{
	string retString = string(CT2CA(cstr));
	return retString;
}

CString StringToCString(string str)
{
	CString retString;
	retString = str.c_str();
	return retString;
}