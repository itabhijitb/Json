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
class JSONNumber;
class JSONObject;
class JSONArray;
class JSONString;
const char* ValueName(JSONValue::VALUE_TYPE type);
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
	static std::shared_ptr<JSONValue> Parse(std::stringstream& strm);
public:
	friend class JSONObject;
	friend class JSONArray;
	friend class JSONNumber;
	friend class JSONString;
	friend class JSONFwdIter;
	friend class JSONKey;
	/**
	* An enumerator to designate an empty object or array
	*/
	enum class EMPTY {OBJECT, ARRAY};
	JSON() ; 
	JSON::JSON(std::string& strm);
	JSON::JSON(std::stringstream& strm);
	JSON(EMPTY);
	JSON(JSONLIT lit);
	JSON(JSON&&);
	JSON(const std::initializer_list<JSON > & il);
	JSON(const std::initializer_list<std::pair<const std::string, JSON > > &  il);
	JSON(std::shared_ptr<JSONValue> root) : m_root(root) {};
	JSON(std::string st);
	JSON(double num);
	JSON(int num);
	JSONKey& operator[](std::string key);
	JSONKey& JSON::operator[](size_t index);
	bool operator==(JSON& rhs);
	std::size_t remove(std::string key);
	bool remove(size_t index);
	void insert(const std::initializer_list<std::pair<const std::string, JSON > > &  il);
	void insert(const std::initializer_list<JSON > & il);
	friend std::ostream& operator<<(std::ostream& os, const JSON& js);
private:
	JSON(const JSON&) = delete;
	std::unique_ptr<JSONKey> m_pkeys;
	std::shared_ptr<JSONValue> m_root;
	JSON& processkeys(JSONKey& jk, const JSON* rhs);
};
#endif