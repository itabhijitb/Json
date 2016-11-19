#include "json.h"
const char* ValueName(JSONValue::VALUE_TYPE type)
{
	switch (type)
	{
	case JSONValue::VALUE_TYPE::OBJECT: return "Object";
	case JSONValue::VALUE_TYPE::ARRAY: return "Array";
	case JSONValue::VALUE_TYPE::STRING: return "String";
	case JSONValue::VALUE_TYPE::NUMBER: return "Number";
	case JSONValue::VALUE_TYPE::TRUE:
	case JSONValue::VALUE_TYPE::FALSE:
	case JSONValue::VALUE_TYPE::NONE:
	default:
		return "Literal";
	}
}
std::shared_ptr<JSONValue> JSON::Parse(std::stringstream& strm)
{
	strm >> std::ws;
	auto pos = strm.tellg();
	switch (char ch = strm.peek())
	{
	case '{':
		return std::shared_ptr<JSONObject>(new JSONObject(strm));
		break;
	case '[':
		return std::shared_ptr<JSONArray>(new JSONArray(strm));
		break;
	case '"':
		return std::shared_ptr<JSONString>(new JSONString(strm));
		break;
	case '-':
	default:
	{
		if (isdigit(ch) || ch == '.' || ch =='-' || ch == '+')
		{
			return std::shared_ptr<JSONNumber>(new JSONNumber(strm));;
		}
		else
		{
			throw JSONInvalid("Parse error at %d. Expecting NUMBER but found  %c.", pos, ch);
		}
	}
		break;
	};
}
JSON::JSON() : m_root(nullptr)
{
}
JSON::JSON(JSONLIT lit) : m_root(nullptr)
{
	
	switch (lit)
	{
	case JSONLIT::FALSE:
		m_root = std::unique_ptr<JSONLiteral<JSONLIT::FALSE> >(new JSONLiteral<JSONLIT::FALSE>());
		break;
	case JSONLIT::TRUE:
		m_root = std::unique_ptr<JSONLiteral<JSONLIT::TRUE> >(new JSONLiteral<JSONLIT::TRUE>());
		break;
	case JSONLIT::NONE:
		m_root = std::unique_ptr<JSONLiteral<JSONLIT::NONE> >(new JSONLiteral<JSONLIT::NONE>());
		break;
	}
}
JSON::JSON(std::string& st)
{
	std::stringstream strm;
	strm << st;
	this->m_root = Parse(strm);
}
JSON::JSON(std::stringstream& strm)
{
	this->m_root = Parse(strm);
}
JSON::JSON(EMPTY json)
{
	switch (json)
	{
	case EMPTY::ARRAY:
		m_root = std::unique_ptr<JSONArray>(new JSONArray());
		break;
	case EMPTY::OBJECT:
		m_root = std::unique_ptr<JSONObject>(new JSONObject());
		break;
	}
}
JSON::JSON(const std::initializer_list<std::pair<const std::string, JSON > > &  il) : m_root(nullptr)
{
	
	std::unique_ptr<JSONObject> lroot = std::unique_ptr<JSONObject>(new JSONObject());
	for (auto& item : il)
	{
		std::shared_ptr<JSONValue> rroot = item.second.m_root;
		(*lroot->m_value)[item.first] = rroot;
	}
	m_root = std::move(lroot);
}
JSON::JSON(const std::initializer_list<JSON > & il) : m_root(nullptr)
{
	
	std::unique_ptr<JSONArray> lroot = std::unique_ptr<JSONArray>(new JSONArray());
	for (auto& item : il)
	{
		lroot->m_value->push_back(item.m_root);
	}
	m_root = std::move(lroot);
}

JSON::JSON(std::string st) :m_root(std::unique_ptr<JSONString>(new JSONString(st))) 
{
}
JSON::JSON(double num) : m_root(std::unique_ptr<JSONNumber>(new JSONNumber(num))) 
{
}
JSON::JSON(int num) : m_root(std::unique_ptr<JSONNumber>(new JSONNumber(num)))
{
}
JSON::JSON(JSON&& jn)  
{
	m_root = jn.m_root;
	m_pkeys = std::move(jn.m_pkeys);
};
JSON& JSON::processkeys(JSONKey& jk, const JSON* rhs)
{
	auto it = jk.keys.begin();
	for (; std::distance(it, jk.keys.end()) > 1; it++)
	{
		(*it)(nullptr);
	}
	if (!rhs)
	{
		(*it)(nullptr);
		return *this;

	}
	if (jk.m_jsonroot->value_type != rhs->m_root->value_type)
	{
		(*it)(rhs);
	}
	else
	{
		
		switch (rhs->m_root->value_type)
		{
		case JSONValue::VALUE_TYPE::OBJECT:
			std::dynamic_pointer_cast<JSONObject>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<JSONObject>(rhs->m_root)->m_value);
			break;
		case JSONValue::VALUE_TYPE::ARRAY:
			std::dynamic_pointer_cast<JSONArray>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<JSONArray>(rhs->m_root)->m_value);
			break;
		case JSONValue::VALUE_TYPE::STRING:
			std::dynamic_pointer_cast<JSONString>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<JSONString>(rhs->m_root)->m_value);
			break;
		case JSONValue::VALUE_TYPE::NUMBER:
			std::dynamic_pointer_cast<JSONNumber>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<JSONNumber>(rhs->m_root)->m_value);
			break;
		case JSONValue::VALUE_TYPE::NONE:
			std::dynamic_pointer_cast<JSONObject>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<JSONObject>(rhs->m_root)->m_value);
			break;
		case JSONValue::VALUE_TYPE::TRUE:
			std::dynamic_pointer_cast<JSONObject>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<JSONObject>(rhs->m_root)->m_value);
			break;
		case JSONValue::VALUE_TYPE::FALSE:
			std::dynamic_pointer_cast<JSONObject>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<JSONObject>(rhs->m_root)->m_value);
			break;
		}
	}
	
	m_root->value_type = rhs->m_root->value_type;
	return *this;
}
bool JSON::operator==(JSON& rhs)
{
	return *m_root == *rhs.m_root;
}
JSONKey& JSON::operator[](std::string key)
{
	m_pkeys = std::make_unique<JSONKey>(this);
	return (*m_pkeys)[key];
}
JSONKey& JSON::operator[](size_t index)
{
	m_pkeys = std::make_unique<JSONKey>(this);
	return (*m_pkeys)[index];
}

std::size_t JSON::remove(std::string key)
{
	return (*std::dynamic_pointer_cast<JSONObject>(m_root)->m_value).erase(key);
}
bool JSON::remove(size_t index)
{
	auto &vec = (*std::dynamic_pointer_cast<JSONArray>(m_root)->m_value);
	return vec.erase(vec.begin() + index) != vec.end();
}
void JSON::insert(const std::initializer_list<std::pair<const std::string, JSON > > &  il)
{
	if (m_root->value_type != JSONValue::VALUE_TYPE::OBJECT)
	{
		throw JSONTypeError("JSON Object cannot be inserted for JSON Type", ValueName(m_root->value_type));
	}
	for (auto& item : il)
	{
		std::shared_ptr<JSONValue> rroot = item.second.m_root;
		(*std::dynamic_pointer_cast<JSONObject>(m_root)->m_value)[item.first] = rroot;
	}
}
void JSON::insert(const std::initializer_list<JSON > & il)
{
	if (m_root->value_type != JSONValue::VALUE_TYPE::ARRAY)
	{
		throw JSONTypeError("JSON Array cannot be inserted for JSON Type", ValueName(m_root->value_type));
	}
	for (auto& item : il)
	{
		std::dynamic_pointer_cast<JSONArray>(m_root)->m_value->push_back(item.m_root);
	}
}
std::ostream& operator<<(std::ostream& os, const JSON& js)
{
	std::stringstream st;
	js.m_root->print(st, 0);
	os << st.str();
	return os;
}