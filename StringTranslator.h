#ifndef __STRING_TRANSLATOR_H
#define __STRING_TRANSLATOR_H
#include <vector>

class StringTranslator
{
public:
	typedef std::pair<wchar_t,int> WSPair;
	typedef std::vector<WSPair> WSVector;	
	StringTranslator();
	virtual ~StringTranslator();
	std::wstring encode(const std::wstring &str);
	std::wstring decode(const std::wstring &str);
	void setTable(WSVector newTable);
	void dropTable();
	void addToTable(const wchar_t first, const int second);
	std::wstring fixPath(const std::wstring &str);
	std::wstring fixFilePath(const std::wstring &str);
	void setEscapeCharacter(const wchar_t escChar);
	wchar_t getEscapeCharacter();
	void setSequenceLenght(size_t seqLenght);
	size_t getSequenceLenght();

	void setEmptyStringCode(const int code);
	int getEmptyStringCode();
protected:
	WSVector table;
	int m_emptyStr;
	wchar_t m_escChar;
	size_t m_seqLenght;
};

#endif __STRING_TRANSLATOR_H
