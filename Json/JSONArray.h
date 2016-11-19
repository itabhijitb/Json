#ifndef __JSON__ARRAY__H
#define __JSON__ARRAY__H
/*******************************************************************************
*                               Standard Headers                               *
*******************************************************************************/
/*******************************************************************************
*                         Standard Template Libraries                          *
*******************************************************************************/
#include <vector>
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "json.h"
#include "JSONValue.h"
namespace JSON {
	class Array : public Value
	{
		static const char starttoken = '[';
		static const char endtoken = ']';
		static const char septoken = ',';
		typedef  std::vector<std::shared_ptr<Value> > VALUE_TYPE;
		typedef VALUE_TYPE::iterator iterator;
		typedef VALUE_TYPE::const_iterator const_iterator;
	public:
		friend class JSON;
		friend class Key;
		friend class Iter;
	private:
		Array();
		Array(const std::initializer_list< std::shared_ptr<Value>>& il);
	public:
		void insert(const std::initializer_list<std::shared_ptr<Value>>& il);
		void remove(const std::initializer_list<size_t >& il);
		void update(const std::initializer_list< std::pair < size_t, std::shared_ptr<Value>> >& il);
		const Value& operator[](size_t index) const;
		Array(std::wstringstream& strm);
		operator Value& ()
		{
			return *this;
		}
		virtual bool operator == (const Value& json);
		std::wstringstream& print(std::wstringstream& ss, size_t depth);
		//VALUE_TYPE::iterator begin() { return m_value->begin(); }
		//VALUE_TYPE::iterator end() { return m_value->end(); }
		//VALUE_TYPE::const_iterator begin() const { return m_value->begin(); }
		//VALUE_TYPE::const_iterator end() const { return m_value->end(); }
		//VALUE_TYPE::const_iterator cbegin() const { return m_value->begin(); }
		//VALUE_TYPE::const_iterator cend() const { return m_value->end(); }
	private:


		Array& operator=(const Array&) = delete;
		//Array(const Array&) = delete;

	private:
		std::shared_ptr<VALUE_TYPE> m_value;
	};
}
#endif