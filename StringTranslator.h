#ifndef __STRING_TRANSLATOR_H
#define __STRING_TRANSLATOR_H
#include <vector>

class StringTranslator
{
public:
	typedef std::pair<std::wstring,std::wstring> WSPair;
	typedef std::vector<WSPair> WSVector;	
	StringTranslator();
	virtual ~StringTranslator();
	std::wstring encode(const std::wstring &str);
	std::wstring decode(const std::wstring &str);
	void setTable(WSVector newTable);
	void dropTable();
	void addToTable(const std::wstring &first, const std::wstring &second);
	void setEmptySring(const std::wstring &es);
	std::wstring fixPath(const std::wstring &str);
	std::wstring fixFilePath(const std::wstring &str);
protected:
	WSVector table;
	std::wstring emptyStr;
};

#endif __STRING_TRANSLATOR_H
