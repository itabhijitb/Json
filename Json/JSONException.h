#ifndef __JSON__EXCEPTION__H
#define __JSON__EXCEPTION__H
/*******************************************************************************
*                               Standard Headers                               *
*******************************************************************************/
/*******************************************************************************
*                         Standard Template Libraries                          *
*******************************************************************************/
#include <exception>
#include <cstdarg>
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "Util.h"

struct JSONException : std::exception
{
	virtual operator std::string() const
	{
		return "Unknown JSON Exception";
	}
};
struct JSONTypeError : JSONException
{
	JSONTypeError(const char *  msg, ...)
	{
		va_list args;
		va_start(args, msg);
		std::unique_ptr<char[]> buffer = nullptr;
		size_t sz = vsnprintf(buffer.get(), 0, msg, args);
		buffer = std::make_unique<char[]>(sz + 1);
		vsnprintf(buffer.get(), sz, msg, args);
		errmsg = buffer.get();
		va_end(args);
	}
	virtual operator std::string() const
	{
		std::stringstream ss;
		ss << "JSON Type Error: " << errmsg;
		return ss.str();
	}
	std::string errmsg;
};
struct JSONInvalid : JSONException
{
	JSONInvalid(const char *  msg, ...)
	{
		va_list args;
		va_start(args, msg);
		std::unique_ptr<char[]> buffer = nullptr;
		size_t sz = vsnprintf(buffer.get(), 0, msg, args);
		buffer = std::make_unique<char[]>(sz + 1);
		vsnprintf(buffer.get(), sz, msg, args);
		errmsg = buffer.get();
		va_end(args);
	}
	virtual operator std::string() const
	{
		std::stringstream ss;
		ss << "Invalid JSON: " << errmsg;
		return ss.str();
	}
	std::string errmsg;
};
struct JSONPgmErr : JSONException
{
	JSONPgmErr(const char *  msg, ...)
	{
		va_list args;
		va_start(args, msg);
		std::unique_ptr<char[]> buffer = nullptr;
		size_t sz = vsnprintf(buffer.get(), 0, msg, args);
		buffer = std::make_unique<char[]>(sz + 1);
		
		vsnprintf(buffer.get(), sz, msg, args);
		errmsg = buffer.get();
		va_end(args);
	}
	virtual operator std::string() const
	{
		std::stringstream ss;
		ss << "Program Error: " << errmsg;
		return ss.str();
	}
	std::string errmsg;
};
struct JSONRangeError : JSONException
{
	JSONRangeError(const char *  msg, ...)
	{
		va_list args;
		va_start(args, msg);
		std::unique_ptr<char[]> buffer = nullptr;
		size_t sz = vsnprintf(buffer.get(), 0, msg, args);
		buffer = std::make_unique<char[]>(sz + 1);

		vsnprintf(buffer.get(), sz, msg, args);
		errmsg = buffer.get();
		va_end(args);
	}
	virtual operator std::string() const
	{
		std::stringstream ss;
		ss << "Out of Range Error: " << errmsg;
		return ss.str();
	}
	std::string errmsg;
};
#endif