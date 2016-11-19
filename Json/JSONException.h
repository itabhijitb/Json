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
namespace JSON {
	struct Exception : std::exception
	{
		virtual operator std::wstring() const
		{
			return L"Unknown JSON Exception";
		}
	};
	struct TypeError : Exception
	{
		TypeError(const wchar_t *  msg, ...)
		{
			va_list args;
			va_start(args, msg);
			std::unique_ptr<wchar_t[]> buffer = nullptr;
			size_t sz = vswprintf(buffer.get(), 0, msg, args);
			buffer = std::make_unique<wchar_t[]>(sz + 1);
			vswprintf(buffer.get(), sz, msg, args);
			errmsg = buffer.get();
			va_end(args);
		}
		virtual operator std::wstring() const
		{
			std::wstringstream ss;
			ss << L"JSON Type Error: " << errmsg;
			return ss.str();
		}
		std::wstring errmsg;
	};
	struct Invalid : Exception
	{
		Invalid(const wchar_t *  msg, ...)
		{
			va_list args;
			va_start(args, msg);
			std::unique_ptr<wchar_t[]> buffer = nullptr;
			size_t sz = vswprintf(buffer.get(), 0, msg, args);
			buffer = std::make_unique<wchar_t[]>(sz + 1);
			vswprintf(buffer.get(), sz, msg, args);
			errmsg = buffer.get();
			va_end(args);
		}
		virtual operator std::wstring() const
		{
			std::wstringstream ss;
			ss << "Invalid JSON: " << errmsg;
			return ss.str();
		}
		std::wstring errmsg;
	};
	struct PgmErr : Exception
	{
		PgmErr(const wchar_t *  msg, ...)
		{
			va_list args;
			va_start(args, msg);
			std::unique_ptr<wchar_t[]> buffer = nullptr;
			size_t sz = vswprintf(buffer.get(), 0, msg, args);
			buffer = std::make_unique<wchar_t[]>(sz + 1);

			vswprintf(buffer.get(), sz, msg, args);
			errmsg = buffer.get();
			va_end(args);
		}
		virtual operator std::wstring() const
		{
			std::wstringstream ss;
			ss << "Program Error: " << errmsg;
			return ss.str();
		}
		std::wstring errmsg;
	};
	struct RangeError : Exception
	{
		RangeError(const wchar_t *  msg, ...)
		{
			va_list args;
			va_start(args, msg);
			std::unique_ptr<wchar_t[]> buffer = nullptr;
			size_t sz = vswprintf(buffer.get(), 0, msg, args);
			buffer = std::make_unique<wchar_t[]>(sz + 1);

			vswprintf(buffer.get(), sz, msg, args);
			errmsg = buffer.get();
			va_end(args);
		}
		virtual operator std::wstring() const
		{
			std::wstringstream ss;
			ss << L"Out of Range Error: " << errmsg;
			return ss.str();
		}
		std::wstring errmsg;
	};
}
#endif