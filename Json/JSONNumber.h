#ifndef __JSON__NUMBER__H
#define __JSON__NUMBER__H
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "JSONValue.h"

namespace JSON {
	class Number : public Value
	{
		typedef double VALUE_TYPE;
	public:
		friend class JSON;
		Number() {}
		Number(double n);
		Number(std::wstringstream& strm);
		bool operator == (const Value& json);
		std::wstringstream& print(std::wstringstream& ss, size_t depth);
	private:
		Number& operator=(const Number&) = delete;
	private:
		std::unique_ptr<VALUE_TYPE> m_value;
	};
}
#endif