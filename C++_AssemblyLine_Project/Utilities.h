
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds
{
	class Utilities
	{
		std::size_t m_widthField = 1;
		static char m_delimiter;
	public:
		// member functions
		void setFieldWidth(std::size_t newWidth);
		std::size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		void trim(std::string& str);
		// class functions
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}

#endif // !SDDS_UTILITIES_H