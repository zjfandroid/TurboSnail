#ifndef CSV_READER_H
#define CSV_READER_H
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class CSVReader
{
public:
	CSVReader(istream& fin = cin, string sep = ",") :
		fieldsep(sep),
		cols(0){}
	~CSVReader();
	//用以存储数据
	vector<vector<string> > data;
private:
	string fieldsep;
	int cols;
	void StringSplit(const string &str, vector<string> &tokens, const char& delimiters);
	void split(vector<string> &field, string line);
	int     advplain(const string& line, string& fld, int);
	int     advquoted(const string& line, string& fld, int);
public:
	//打开CSV文件  
	bool            openFile(const char* fileName);
	//根据行列获取数据  
	const   char*   getData(int rows, int cols);
	//获取指定数据的列下标  
	int             findColsData(int cols, const char* value);
	//得到总列数  
	inline  int     getCols(){ return cols; }
	//得到总行数  
	inline  int     getRows(){ return data.size(); }
};

#endif
