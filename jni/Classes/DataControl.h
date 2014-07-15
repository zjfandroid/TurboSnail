#ifndef DATA_CONTROL_H
#define DATA_CONTROL_H
#include "cocos2d.h"
#include "CSVReader.h"
#include "Defines.h"

USING_NS_CC;
using namespace std;

class DataControl
{
public:
	/*数据列信息*/
	enum DATA_COLUMN
	{
		COL_ID,
		COL_FIRST_LETTER,
		COL_WORD,
		COL_QUSETION_TYPE,
		COL_TYPE_CHILD,
		COL_QUESTION,
		COL_ANSWER,
		COL_OPTION1,
		COL_OPTION2,
		COL_OPTION3,
		COL_OPTION4,
	};

	/*2选一 : 1-276
	  3选一 : 277-722
	  4选一 : 723-1201
	*/
	enum DIFFICULTY
	{
		DIFF_START = 1,
		DIFF_EASY = 276,
		DIFF_MIDDLE = 722,
		DIFF_HARD = 1201,
	};
public:
	DataControl();
	~DataControl();

	void initQuestion(int level);
	void setCurrentRow(int level);
	void replaceString(string &s1, const string &s2, const string &s3);

	CC_SYNTHESIZE(string, idiom, Idiom);//考核的词
	CC_SYNTHESIZE(string, question, Question);//问题
	CC_SYNTHESIZE(int, rightOption, RightOption);//答案
	vector<string> options;//选项

private:
	int row;//行

	CSVReader *csvFile;
};

#endif