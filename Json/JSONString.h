#ifndef __JSON__STRING__H
#define __JSON__STRING__H
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "JSONValue.h"

namespace JSON {
	class String : public Value
	{
		static const char starttoken = '"';
		static const char endtoken = '"';
		typedef std::wstring VALUE_TYPE;
	public:
		friend class JSON;
		String();
		String(std::wstring js) : m_value(std::make_unique<std::wstring>(js)) {};
		String(const std::unique_ptr<Value>& jv);
		String(String&& js);
		String(std::wstringstream& strm);
		virtual bool operator == (const Value& json);
		std::wstringstream& print(std::wstringstream& ss, size_t depth);
		operator std::wstring();
	private:
		String& operator=(const String&) = delete;
		String(String& jn) = delete;
	private:
		std::unique_ptr<VALUE_TYPE> m_value;
	};
}
#endif