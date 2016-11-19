#ifndef __JSON__KEY__H
#define __JSON__KEY__H
/*******************************************************************************
*                               Standard Headers                               *
*******************************************************************************/
/*******************************************************************************
*                         Standard Template Libraries                          *
*******************************************************************************/
#include <initializer_list>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <iterator>
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "JSONValue.h"
#include "JSONObject.h"
#include "JSONArray.h"
#include "JSONKey.h"
#include "json.h"
class Key;
namespace JSON {
	class FwdIter : public std::iterator < std::forward_iterator_tag, Key >
	{
		Key &jsonkey;
		std::shared_ptr<Value> m_root;
	public:
		FwdIter(Key& jsonkey);
		FwdIter& operator ++ ();
		FwdIter& operator ++ (int);
		reference operator * ();
		bool operator == (const FwdIter &rhs);
		bool operator != (const FwdIter &rhs);
	};
	class Key
	{
	public: //Friends
		friend class FwdIter;
		friend class JSON;
	public: //Constructors
		Key(JSON* json);
		Key(std::shared_ptr<Value> root) : m_jsonroot(root) {}
		Key& Key::operator[](std::wstring key);
		Key& Key::operator[](size_t index);
		Key& operator=(const JSON& jv);
	public: //Public Methods
		std::size_t remove(std::wstring key);
		bool remove(size_t index);
		void insert(const std::initializer_list<std::pair<const std::wstring, JSON > > &  il);
		void insert(const std::initializer_list<JSON > & il);
		friend std::wostream& operator<<(std::wostream& os, const JSON& js);
	private: //Deleted Methods
		Key(const Key& jk) = delete;
	public: //Iterators
		//enum class DIRTYPE { BREADTH, DEPTH };
		//Key& next()
		//{
		//	switch (m_jsonroot->value_type)
		//	{
		//	case Value::VALUE_TYPE::OBJECT:
		//		std::dynamic_pointer_cast<Object>(m_jsonroot)->m_value.
		//	}
		//}
		//Key& inner();
		//bool operator==(const Key& rhs)
		//{
		//	return m_jsonroot == rhs.m_jsonroot;
		//}
		//template<DIRTYPE DIR = DIRTYPE::BREADTH>	Key& begin();
		//template<DIRTYPE DIR = DIRTYPE::BREADTH>	Key& end();
		//template<>	Key& begin<DIRTYPE::DEPTH>();
		//template<>	Key& end<DIRTYPE::DEPTH>();
	private: //Iterators
		bool IsEOF();
	private: // Data Members
		JSON* m_json;
		std::shared_ptr<Value> m_jsonroot;
		std::vector < std::function<Key&(const JSON*)> > keys;

	};
}
#endif