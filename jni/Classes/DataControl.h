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
	/*��������Ϣ*/
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

	/*2ѡһ : 1-276
	  3ѡһ : 277-722
	  4ѡһ : 723-1201
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

	CC_SYNTHESIZE(string, idiom, Idiom);//���˵Ĵ�
	CC_SYNTHESIZE(string, question, Question);//����
	CC_SYNTHESIZE(int, rightOption, RightOption);//��
	vector<string> options;//ѡ��

private:
	int row;//��

	CSVReader *csvFile;
};

#endif