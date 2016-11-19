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
#include "json.h"
class JSONKey;
class JSONFwdIter : public std::iterator < std::forward_iterator_tag, JSONKey >
{
	JSONKey &jsonkey;
	std::shared_ptr<JSONValue> m_root;
public:
	JSONFwdIter(JSONKey& jsonkey);
	JSONFwdIter& operator ++ ();
	JSONFwdIter& operator ++ (int);
	reference operator * ();
	bool operator == (const JSONFwdIter &rhs);
	bool operator != (const JSONFwdIter &rhs);
};
class JSONKey
{
public: //Friends
	friend class JSONFwdIter;
	friend class JSON;
public: //Constructors
	JSONKey(JSON* json);
	JSONKey(std::shared_ptr<JSONValue> root) : m_jsonroot(root) {}
	JSONKey& JSONKey::operator[](std::string key);
	JSONKey& JSONKey::operator[](size_t index);
	JSONKey& operator=(const JSON& jv);
public: //Public Methods
	bool remove(std::string key);
	bool remove(size_t index);
	void insert(const std::initializer_list<std::pair<const std::string, JSON > > &  il);
	void insert(const std::initializer_list<JSON > & il);
	friend std::ostream& operator<<(std::ostream& os, const JSON& js);
private: //Deleted Methods
	JSONKey(const JSONKey& jk) = delete;
public: //Iterators
	//enum class DIRTYPE { BREADTH, DEPTH };
	//JSONKey& next()
	//{
	//	switch (m_jsonroot->value_type)
	//	{
	//	case JSONValue::VALUE_TYPE::OBJECT:
	//		std::dynamic_pointer_cast<JSONObject>(m_jsonroot)->m_value.
	//	}
	//}
	//JSONKey& inner();
	//bool operator==(const JSONKey& rhs)
	//{
	//	return m_jsonroot == rhs.m_jsonroot;
	//}
	//template<DIRTYPE DIR = DIRTYPE::BREADTH>	JSONKey& begin();
	//template<DIRTYPE DIR = DIRTYPE::BREADTH>	JSONKey& end();
	//template<>	JSONKey& begin<DIRTYPE::DEPTH>();
	//template<>	JSONKey& end<DIRTYPE::DEPTH>();
private: //Iterators
	bool IsEOF();
private: // Data Members
	JSON* m_json;
	std::shared_ptr<JSONValue> m_jsonroot;
	std::vector < std::function<JSONKey&(const JSON*)> > keys;

};
#endif