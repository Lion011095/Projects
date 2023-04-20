// Name:				Lion Yakubov
// Seneca Student ID:   129517207
// Seneca email:		lyakubov@myseneca.ca
// Date of completion:  27/03/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include <algorithm>

#include "Utilities.h"

using namespace std;

namespace sdds
{
	char Utilities::m_delimiter = {};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string token{};

		auto delimPos = str.find(m_delimiter, next_pos);
		if (delimPos != string::npos && delimPos != next_pos)
		{
			token = str.substr(next_pos, delimPos - next_pos);
			trim(token);
			next_pos = delimPos + 1;
			more = true;
		}
		else if(delimPos == next_pos)
		{
			more = false;
			throw string("Invalid next position.");
		}
		else
		{
			token = str.substr(next_pos);
			trim(token);
			more = false;
		}

		if (m_widthField < token.length())
		{
			m_widthField = token.length();
		}
		
		return token;
	}

	void Utilities::trim(std::string& str)
	{
		while (str[0] == ' ' || str[str.length() - 1] == ' ')
		{
			if (str[0] == ' ')
				str.erase(find(str.begin(), str.end(), ' '));
			else
				str.pop_back();
		}
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}