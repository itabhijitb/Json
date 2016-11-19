#ifndef __UTIL_H__
#define __UTIL_H__
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
namespace Util
{


	// trim from start
	static inline std::wstring &ltrim(std::wstring &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::wstring &rtrim(std::wstring &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::wstring &trim(std::wstring &s) {
		return ltrim(rtrim(s));
	}
	template<typename Derived, typename Base, typename Del>
	std::unique_ptr<Derived, Del>
		static_unique_ptr_cast(std::unique_ptr<Base, Del>&& p)
	{
		auto d = static_cast<Derived *>(p.release());
		return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
	}

	template<typename Derived, typename Base, typename Del>
	std::unique_ptr<Derived, Del>
		dynamic_unique_ptr_cast(std::unique_ptr<Base, Del>&& p)
	{
		if (Derived *result = std::dynamic_pointer_cast<Derived >(p)) {
			p.release();
			return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
		}
		return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
	}
}
#endif