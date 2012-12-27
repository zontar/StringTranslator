#include "StringTranslator.h"


StringTranslator::StringTranslator(void)
{

}


StringTranslator::~StringTranslator(void)
{

}

std::wstring StringTranslator::decode(const std::wstring &str)
{
	if(table.empty()) return str;
	if(!str.compare(emptyStr)) return L"";
	std::wstring result=str;
	//restore substrings who equal rCodes. example: %1%1 -> %1
	for(WSVector::iterator i=table.begin();i!=table.end();++i)
	{
		for (size_t index = 0; index = result.find(i->second, index), index != std::wstring::npos;)
		{
			if(result.substr(index+i->second.length(),i->second.length()).compare(i->second))
			{
				result.replace(index, i->second.length(), i->first);
				index += i->first.length();
			}
			else
			{
				result.erase(index,i->second.length());
				index +=i->second.length();
			}
		}
	}
	return result;
}

std::wstring StringTranslator::encode(const std::wstring &str)
{
	if(table.empty()) return str;
	if(str.empty()) return emptyStr;
	std::wstring result = str;
	if(!str.compare(emptyStr))
	{
		result+=emptyStr;
		return result;
	}
	//duplicate substrings who equal rCodes. example: %1 -> %1%1
	for(WSVector::iterator i=table.begin();i!=table.end();++i)
	{
		for (size_t index = 0; index = result.find(i->second, index), index != std::wstring::npos;)
		{
			std::wstring t = i->second;
			t += i->second;
			result.replace(index, i->second.length(), t);
			index += t.length();
		}
	}

	//replace substrings who equal rCodes on eCodes. example: * -> %1
	for(WSVector::iterator i=table.begin();i!=table.end();++i)
	{
		for (size_t index = 0; index = result.find(i->first, index), index != std::wstring::npos, index<=result.length();)
		{
			result.replace(index, i->first.length(), i->second);
			index += i->second.length();
		}
	}
	return result;
}

void StringTranslator::setTable(WSVector newTable)
{
	table = newTable;
}

void StringTranslator::dropTable()
{
	table.clear();
}

void StringTranslator::addToTable(const std::wstring &first, const std::wstring &second)
{
	table.push_back(WSPair(first,second));
}

void StringTranslator::setEmptySring(const std::wstring &es)
{
	emptyStr = es;
}

std::wstring StringTranslator::fixPath(const std::wstring &str)
{
	if(str.empty()) return str;
	std::wstring result = str;
	if(!result.substr(result.length()-4,4).compare(L".key"))
		result.erase(result.length()-4,4);
	for (size_t index = 0; index = result.find(L".key\\", index), index != std::wstring::npos, index<=result.length();)
	{
		result.replace(index, 5, L"\\");
		index += 1;
	}
	return result;
}

std::wstring StringTranslator::fixFilePath(const std::wstring &str)
{
	std::wstring result = str;
	result.erase(result.length()-4,4);
	result = fixPath(result);
	return result;
}