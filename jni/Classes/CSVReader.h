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
	//���Դ洢����
	vector<vector<string> > data;
private:
	string fieldsep;
	int cols;
	void StringSplit(const string &str, vector<string> &tokens, const char& delimiters);
	void split(vector<string> &field, string line);
	int     advplain(const string& line, string& fld, int);
	int     advquoted(const string& line, string& fld, int);
public:
	//��CSV�ļ�  
	bool            openFile(const char* fileName);
	//�������л�ȡ����  
	const   char*   getData(int rows, int cols);
	//��ȡָ�����ݵ����±�  
	int             findColsData(int cols, const char* value);
	//�õ�������  
	inline  int     getCols(){ return cols; }
	//�õ�������  
	inline  int     getRows(){ return data.size(); }
};

#endif
