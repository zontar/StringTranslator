#include "StringTranslator.h"

#include <sstream>
#include <iomanip>

StringTranslator::StringTranslator(void)
{
	m_escChar = L'%';
	m_seqLenght = 2;
}


StringTranslator::~StringTranslator(void)
{

}

void StringTranslator::setEscapeCharacter(const wchar_t escChar)
{
	m_escChar = escChar;
}

wchar_t StringTranslator::getEscapeCharacter()
{
	return m_escChar;
}

void StringTranslator::setSequenceLenght(size_t seqLenght)
{
	m_seqLenght = seqLenght;
}

size_t StringTranslator::getSequenceLenght()
{
	return m_seqLenght;
}

void StringTranslator::setEmptyStringCode(const int code)
{
	m_emptyStr = code;
}

int StringTranslator::getEmptyStringCode()
{
	return m_emptyStr;
}

void StringTranslator::setTable(WSVector newTable)
{
	table = newTable;
}

void StringTranslator::dropTable()
{
	table.clear();
}

void StringTranslator::addToTable(const wchar_t first, const int second)
{
	table.push_back(WSPair(first,second));
}

std::wstring StringTranslator::decode(const std::wstring &str)
{
	std::wstringstream stream;
	size_t i=0;
	while(i<str.length())
	{
		if(str[i]!=m_escChar)
		{
			stream << str[i];
			++i;
			continue;
		}
		if(str[i+1]==m_escChar)
		{
			stream << m_escChar;
			i+=2;
			continue;
		}
		int code = _wtoi(str.substr(i+1,m_seqLenght).data());
		if(code==m_emptyStr)
		{
			i+=m_seqLenght+1;
			break;
		}
		for(size_t j=0;j<table.size();++j)
		{
			if(table[j].second==code)
			{
				stream << table[j].first;
				i+=m_seqLenght+1;
				break;
			}
		}
	}
	std::wstring result;
	result += stream.str();
	return result;
}

std::wstring StringTranslator::encode(const std::wstring &str)
{
	std::wstringstream stream;
	if(str.empty())
	{
		stream << m_escChar << std::setw(m_seqLenght) << std::setfill(L'0') << m_emptyStr;
	}
	else
	{
		if(table.empty()) return str;
		for(int i=0;i<str.length();++i)
		{
			bool finded = false;
			for(WSVector::iterator j=table.begin();j!=table.end();++j)
			{
				if(str[i]==j->first)
				{
					stream << m_escChar << std::setw(m_seqLenght) << std::setfill(L'0') << j->second;
					finded = true;
					break;
				}
			}
			if(finded) continue;
			if(str[i]==m_escChar) stream << m_escChar << m_escChar;
			else stream << str[i];
		}
	}
	std::wstring result;
	result = stream.str();
	return result;
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