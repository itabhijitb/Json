#include "json.h"
const wchar_t* JSON::ValueName(Value::VALUE_TYPE type)
{
	switch (type)
	{
	case Value::VALUE_TYPE::OBJECT: return L"Object";
	case Value::VALUE_TYPE::ARRAY: return L"Array";
	case Value::VALUE_TYPE::STRING: return L"String";
	case Value::VALUE_TYPE::NUMBER: return L"Number";
	case Value::VALUE_TYPE::TRUE:
	case Value::VALUE_TYPE::FALSE:
	case Value::VALUE_TYPE::NONE:
	default:
		return L"Literal";
	}
}
std::shared_ptr<JSON::Value> JSON::JSON::Parse(std::wstringstream& strm)
{
	strm >> std::ws;
	auto pos = strm.tellg();
	switch (auto ch = strm.peek())
	{
	case '{':
		return std::shared_ptr<Object>(new Object(strm));
		break;
	case '[':
		return std::shared_ptr<Array>(new Array(strm));
		break;
	case '"':
		return std::shared_ptr<String>(new String(strm));
		break;
	case '-':
	default:
	{
		if (isdigit(ch) || ch == '.' || ch =='-' || ch == '+')
		{
			return std::shared_ptr<Number>(new Number(strm));;
		}
		else
		{
			throw Invalid(L"Parse error at %d. Expecting NUMBER but found  %c.", pos, ch);
		}
	}
		break;
	};
}
JSON::JSON::JSON() : m_root(nullptr)
{
}
JSON::JSON::JSON(JSONLIT lit) : m_root(nullptr)
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
JSON::JSON::JSON(std::wstring& st)
{
	std::wstringstream strm;
	strm << st;
	this->m_root = Parse(strm);
}
JSON::JSON::JSON(std::wstringstream& strm)
{
	this->m_root = Parse(strm);
}
JSON::JSON::JSON(EMPTY json)
{
	switch (json)
	{
	case EMPTY::ARRAY:
		m_root = std::unique_ptr<Array>(new Array());
		break;
	case EMPTY::OBJECT:
		m_root = std::unique_ptr<Object>(new Object());
		break;
	}
}

JSON::JSON::JSON(const std::initializer_list<std::pair<const std::wstring, JSON > > &  il) : m_root(nullptr)
{
	
	std::unique_ptr<Object> lroot = std::unique_ptr<Object>(new Object());
	for (auto& item : il)
	{
		std::shared_ptr<Value> rroot = item.second.m_root;
		(*lroot->m_value)[item.first] = rroot;
	}
	m_root = std::move(lroot);
}
JSON::JSON::JSON(const std::initializer_list<JSON > & il) : m_root(nullptr)
{
	
	std::unique_ptr<Array> lroot = std::unique_ptr<Array>(new Array());
	for (auto& item : il)
	{
		lroot->m_value->push_back(item.m_root);
	}
	m_root = std::move(lroot);
}

JSON::JSON::JSON(std::wstring st) :m_root(std::unique_ptr<String>(new String(st)))
{
}
JSON::JSON::JSON(double num) : m_root(std::unique_ptr<Number>(new Number(num)))
{
}
JSON::JSON::JSON(int num) : m_root(std::unique_ptr<Number>(new Number(num)))
{
}
JSON::JSON::JSON(JSON&& jn)
{
	m_root = jn.m_root;
	m_pkeys = std::move(jn.m_pkeys);
};
JSON::JSON& JSON::JSON::JSON::processkeys(Key& jk, const JSON* rhs)
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
		case Value::VALUE_TYPE::OBJECT:
			std::dynamic_pointer_cast<Object>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<Object>(rhs->m_root)->m_value);
			break;
		case Value::VALUE_TYPE::ARRAY:
			std::dynamic_pointer_cast<Array>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<Array>(rhs->m_root)->m_value);
			break;
		case Value::VALUE_TYPE::STRING:
			std::dynamic_pointer_cast<String>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<String>(rhs->m_root)->m_value);
			break;
		case Value::VALUE_TYPE::NUMBER:
			std::dynamic_pointer_cast<Number>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<Number>(rhs->m_root)->m_value);
			break;
		case Value::VALUE_TYPE::NONE:
			std::dynamic_pointer_cast<Object>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<Object>(rhs->m_root)->m_value);
			break;
		case Value::VALUE_TYPE::TRUE:
			std::dynamic_pointer_cast<Object>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<Object>(rhs->m_root)->m_value);
			break;
		case Value::VALUE_TYPE::FALSE:
			std::dynamic_pointer_cast<Object>((*it)(nullptr).m_jsonroot)->m_value = std::move(std::dynamic_pointer_cast<Object>(rhs->m_root)->m_value);
			break;
		}
	}
	
	m_root->value_type = rhs->m_root->value_type;
	return *this;
}
bool JSON::JSON::operator==(JSON& rhs)
{
	return *m_root == *rhs.m_root;
}
JSON::Key& JSON::JSON::operator[](std::wstring key)
{
	m_pkeys = std::make_unique<Key>(this);
	return (*m_pkeys)[key];
}
JSON::Key& JSON::JSON::operator[](size_t index)
{
	m_pkeys = std::make_unique<Key>(this);
	return (*m_pkeys)[index];
}

std::size_t JSON::JSON::remove(std::wstring key)
{
	return (*std::dynamic_pointer_cast<Object>(m_root)->m_value).erase(key);
}
bool JSON::JSON::remove(size_t index)
{
	auto &vec = (*std::dynamic_pointer_cast<Array>(m_root)->m_value);
	return vec.erase(vec.begin() + index) != vec.end();
}
void JSON::JSON::insert(const std::initializer_list<std::pair<const std::wstring, JSON > > &  il)
{
	if (m_root->value_type != Value::VALUE_TYPE::OBJECT)
	{
		throw TypeError(L"JSON Object cannot be inserted for JSON Type", ValueName(m_root->value_type));
	}
	for (auto& item : il)
	{
		std::shared_ptr<Value> rroot = item.second.m_root;
		(*std::dynamic_pointer_cast<Object>(m_root)->m_value)[item.first] = rroot;
	}
}
void JSON::JSON::insert(const std::initializer_list<JSON > & il)
{
	if (m_root->value_type != Value::VALUE_TYPE::ARRAY)
	{
		throw TypeError(L"JSON Array cannot be inserted for JSON Type", ValueName(m_root->value_type));
	}
	for (auto& item : il)
	{
		std::dynamic_pointer_cast<Array>(m_root)->m_value->push_back(item.m_root);
	}
}
std::wostream& JSON::operator<<(std::wostream& os, const JSON& js)
{
	std::wstringstream st;
	js.m_root->print(st, 0);
	os << st.str();
	return os;
}