#include "CSVReader.h"

//��ȡָ�����е�����
const char* CSVReader::getData(int rows, int cols)
{
	if (rows < 0 || rows >= data.size() || cols < 0 || cols >= data[rows].size()) {
		return "";
	}

	return data[rows][cols].c_str();
}

//��ȡָ�����ݵ����±�
int  CSVReader::findColsData(int cols, const char* value)
{
	int size = data.size();
	for (int i = 0; i < size; i++) {
		if (strcmp(getData(i, cols), value) == 0)
		{
			return i;
		}
	}
	return -1;
}
//����CSV�ļ�
bool CSVReader::openFile(const char* fileName)
{
	//����ļ���ϵͳ�ľ���·��
	string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	unsigned char* pBuffer = NULL;
	//��ȡ���ֽ�������ȡʧ����Ϊ0
	unsigned long bufferSize = 0;
	pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pathKey.c_str(), "r", &bufferSize);

	string s = (char *)pBuffer;
	string str = s.substr(0, bufferSize);

	vector<string> line;
	StringSplit(str, line, '\n');
	for (int i = 0; i < line.size(); i++)
	{
		vector<string> field;
		split(field, line[i]);
		data.push_back(field);
		cols = max(cols, (int)field.size());
	}

	//�ͷ��ڴ�  
	if (bufferSize >0 && pBuffer) delete[] pBuffer;
	return true;
}
void CSVReader::StringSplit(const string & str, vector<string> & tokens, const char & delimiters)
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void CSVReader::split(vector<string>& field, string line)
{
	string fld;
	int i, j;

	if (line.length() == 0)
		return;
	i = 0;

	do {
		if (i < line.length() && line[i] == '"')
			j = advquoted(line, fld, ++i);
		else
			j = advplain(line, fld, i);

		field.push_back(fld);
		i = j + 1;
	} while (j < line.length());

}

int CSVReader::advquoted(const string& s, string& fld, int i)
{
	int j;
	fld = "";
	for (j = i; j < s.length(); j++)
	{
		if (s[j] == '"' && s[++j] != '"')
		{
			int k = s.find_first_of(fieldsep, j);
			if (k > s.length())
				k = s.length();
			for (k -= j; k-- > 0;)
				fld += s[j++];
			break;
		}
		fld += s[j];
	}
	return j;
}

int CSVReader::advplain(const string& s, string& fld, int i)
{
	int j;
	j = s.find_first_of(fieldsep, i);
	if (j > s.length())
		j = s.length();
	fld = string(s, i, j - i);
	return j;
}

//�����������ͷ��ڴ�
CSVReader::~CSVReader()
{
	for (int i = 0; i < data.size(); i++) {
		data[i].clear();
	}
	data.clear();
}
