#include "DataControl.h"

DataControl::DataControl()
{
	csvFile = new CSVReader();
	csvFile->openFile("snail.bin");
}

DataControl::~DataControl()
{
	delete csvFile;
}

void DataControl::initQuestion(int level)
{
	setCurrentRow(level);

	idiom = csvFile->getData(row, COL_QUESTION);
	string word = csvFile->getData(row, COL_WORD);
	question = idiom.c_str();
	replaceString(question, word, "?");

	options.clear();
	for (int i = COL_OPTION1; i < COL_OPTION4; i++)
	{
		string opt = csvFile->getData(row, i);
		if (opt.length() > 0)
		{
			options.push_back(opt);
		}
	}

	string ans = csvFile->getData(row, COL_ANSWER);
	int size = options.size();
	for (int i = 0; i < size;i++)
	{
		if (ans == options[i])
		{
			rightOption = i;
			break;
		}
	}
}

void DataControl::setCurrentRow(int level)
{
	switch (level)
	{
	case 1:
		row = random_range(DIFF_START, DIFF_EASY);
		break;
	case 2:
		row = random_range(DIFF_EASY, DIFF_MIDDLE);
		break;
	case 3:
		row = random_range(DIFF_MIDDLE, DIFF_HARD);
		break;
	default:
		row = random_range(DIFF_START, DIFF_HARD);
		break;
	}
}

void DataControl::replaceString(string &s1, const string &s2, const string &s3)
{
	string::size_type pos = 0;
	string::size_type a = s2.size();
	string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != string::npos)
	{
		s1.replace(pos, a, s3);
		pos += b;
	}
}

