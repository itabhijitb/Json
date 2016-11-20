#ifndef __JSON__H_
#define __JSON__H_
/*******************************************************************************
*                               Standard Headers                               *
*******************************************************************************/
/*******************************************************************************
*                         Standard Template Libraries                          *
*******************************************************************************/
#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>
#include <initializer_list>
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "JSONString.h"
#include "JSONNumber.h"
#include "JSONValue.h"
#include "JSONKey.h"
/*******************************************************************************
*                             Forward Declaration                              *
*******************************************************************************/
namespace JSON {
	class Number;
	class Object;
	class Array;
	class String;
	const wchar_t* ValueName(Value::VALUE_TYPE type);
	/**
	*  JSON class. A factory class to generate a nested recursive structure of
				   JSON Values.
	*/
	class JSON
	{
	private:
		/**
		* JSON Parser.
		* Parses a stream of JSON data to a nested recursive structure of
		* JSON Values.
		*/
		static std::shared_ptr<Value> Parse(std::wstringstream& strm);
	public:
		friend class Object;
		friend class Array;
		friend class Number;
		friend class String;
		friend class FwdIter;
		friend class Key;
		/**
		* An enumerator to designate an empty object or array
		*/
		enum class EMPTY { OBJECT, ARRAY };
		JSON();
		JSON(std::wstring& strm);
		JSON(std::wstringstream& strm);
		JSON(EMPTY);
		JSON(JSONLIT lit);
		JSON(JSON&&);
		JSON(const std::initializer_list<JSON > & il);
		JSON(const std::initializer_list<std::pair<const std::wstring, JSON > > &  il);
		JSON(std::shared_ptr<Value> root) : m_root(root) {};
		JSON(std::wstring st);
		JSON(double num);
		JSON(int num);
		Key& operator[](std::wstring key);
		Key& operator[](size_t index);
		bool operator==(JSON& rhs);
		std::size_t remove(std::wstring key);
		bool remove(size_t index);
		void insert(const std::initializer_list<std::pair<const std::wstring, JSON > > &  il);
		void insert(const std::initializer_list<JSON > & il);
		friend std::wostream& operator<<(std::wostream& os, const JSON& js);
	private:
		JSON(const JSON&) = delete;
		std::unique_ptr<Key> m_pkeys;
		std::shared_ptr<Value> m_root;
		JSON& processkeys(Key& jk, const JSON* rhs);
	};
}
#endif