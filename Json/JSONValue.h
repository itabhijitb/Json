#ifndef __JSON__VALUE__H
#define __JSON__VALUE__H
/*******************************************************************************
*                               Standard Headers                               *
*******************************************************************************/
/*******************************************************************************
*                         Standard Template Libraries                          *
*******************************************************************************/
#include <memory>
#include <string>
#include <sstream>
#include <map>
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "JSONException.h"


namespace JSON {
	class Value
	{

	public:
		enum class VALUE_TYPE { OBJECT, ARRAY, STRING, NUMBER, TRUE, FALSE, NONE } value_type;

		Value() {};
		virtual bool operator == (const Value& json) = 0;
		friend std::wostream& operator<<(std::wostream& os, const Value& json);
		virtual std::wstringstream& print(std::wstringstream& ss, size_t depth) = 0;
	protected:

	};
	enum class JSONLIT { NONE = -1, FALSE, TRUE };
	template <JSONLIT lit> class JSONLiteral : public Value {};
	template <> class JSONLiteral <JSONLIT::FALSE> : public Value
	{
	public:
		JSONLiteral()
		{
			value_type = VALUE_TYPE::FALSE;
		}
		operator JSONLIT()
		{
			return JSONLIT::FALSE;
		}
		virtual bool operator == (const Value& json)
		{
			try
			{
				dynamic_cast<const JSONLiteral<JSONLIT::FALSE> &>(json);
			}
			catch (const std::bad_cast&)
			{
				return false;
			}
			return true;
		}
		std::wstringstream& print(std::wstringstream& ss, size_t)
		{
			ss << "False";
			return ss;
		}
	private:
		JSONLiteral& operator=(const JSONLiteral&) = delete;
		JSONLiteral(const JSONLiteral&) = delete;
	};
	template <> class JSONLiteral <JSONLIT::TRUE> : public Value
	{
	public:
		JSONLiteral()
		{
			value_type = VALUE_TYPE::TRUE;
		}
		operator JSONLIT()
		{
			return JSONLIT::TRUE;
		}
		virtual bool operator == (const Value& json)
		{
			try
			{
				dynamic_cast<const JSONLiteral<JSONLIT::TRUE> &>(json);
			}
			catch (const std::bad_cast&)
			{
				return false;
			}
			return true;
		}
		std::wstringstream& print(std::wstringstream& ss, size_t)
		{
			ss << "True";
			return ss;
		}
	private:
		JSONLiteral& operator=(const JSONLiteral&) = delete;
		JSONLiteral(const JSONLiteral&) = delete;
	};
	template <> class JSONLiteral <JSONLIT::NONE> : public Value
	{
	public:
		JSONLiteral()
		{
			value_type = VALUE_TYPE::NONE;
		}
		operator JSONLIT()
		{
			return JSONLIT::NONE;
		}
		virtual bool operator == (const Value& json)
		{
			try
			{
				dynamic_cast<const JSONLiteral<JSONLIT::NONE> &>(json);
			}
			catch (const std::bad_cast&)
			{
				return false;
			}
			return true;
		}
		std::wstringstream& print(std::wstringstream& ss, size_t)
		{
			ss << "NONE";
			return ss;
		}
	private:
		JSONLiteral& operator=(const JSONLiteral&) = delete;
		JSONLiteral(const JSONLiteral&) = delete;
	};
}
#endif