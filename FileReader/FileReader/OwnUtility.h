#pragma once

#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "afxdialogex.h"
#include <string>

using namespace std;

//string�� trim��� ��� Vector�� return
vector<string> StringToWordList(string str);

// CString to String
string CStringToString(CString cstr);

// String to CString
CString StringToCString(string str);