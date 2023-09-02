#include "ItemController.h"

void INFO::ClearInfo()
{
	mode = "";
	name = "";
	value = { 0,0 };
	hItem = 0;
}

void FILE_HANDLER::UpdateItemMap()
{
	ifstream readFile(dataFilePath);
	if (readFile.is_open()) {
		vector<string> wordList;
		string line;
		while (getline(readFile, line))
		{
			wordList = StringToWordList(line);
			string mode = wordList[0];
			string name = wordList[1];
			vector<string> values{ wordList.begin() + 2, wordList.end() };

			this->item[mode][name] = values;
		}
	}
}