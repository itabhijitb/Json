#include "JSONKey.h"

JSON::FwdIter::FwdIter(Key &key) : jsonkey(key), m_root(key.m_json->m_root) { }
//JSONFwdIter& JSONFwdIter::operator ++ ()
//{
//	JSONFwdIter prev_self = *this;
//	switch (m_root->value_type)
//	{
//	case Value::VALUE_TYPE::OBJECT:
//
//	}
//	if (m_root->
//	{
//		m_jsonkey.next();
//	}
//	return prev_self;
//}
//JSONFwdIter& JSONFwdIter::operator ++ (int)
//{
//	JSONFwdIter prev_self = *this;
//	if (!m_jsonkey.IsEOF())
//	{
//		m_jsonkey.next();
//	}
//	return *this;
//}
//JSONFwdIter::reference JSONFwdIter::operator * ()
//{
//	return m_jsonkey;
//}
//bool JSONFwdIter::operator == (const JSONFwdIter &rhs)
//{
//	return m_jsonkey == rhs.m_jsonkey;
//}
//bool JSONFwdIter::operator != (const JSONFwdIter &rhs)
//{
//	return !(m_jsonkey == rhs.m_jsonkey);
//}

JSON::Key::Key(JSON* json) : m_json(json), m_jsonroot(m_json->m_root) {};
JSON::Key& JSON::Key::operator[](std::wstring key)
{
	keys.push_back(
		[=](const JSON* jv)->Key&
	{
		if (jv != nullptr)
		{

			m_jsonroot = (*std::dynamic_pointer_cast<Object>(m_jsonroot)->m_value)[key] = jv->m_root;
		}
		else
		{
			m_jsonroot = (*std::dynamic_pointer_cast<Object>(m_jsonroot)->m_value)[key];
		}
		if (m_jsonroot == nullptr)
		{
			throw RangeError(L"Key %s not found in the Object", key);
		}
		return *this;
	});
	return *this;

}

JSON::Key& JSON::Key::operator[](size_t index)
{
	keys.push_back(
		[=](const JSON* jv)->Key&
	{
		if (jv != nullptr)
		{
			m_jsonroot = (*std::dynamic_pointer_cast<Array>(m_jsonroot)->m_value)[index] = jv->m_root;
		}
		else
		{
			m_jsonroot = (*std::dynamic_pointer_cast<Array>(m_jsonroot)->m_value)[index];
		}
		if (m_jsonroot == nullptr)
		{
			throw RangeError(L"Out of bound while indexing with %d.", index);
		}
		return *this;
	});
	return *this;
}
JSON::Key& JSON::Key::operator=(const JSON& jv)
{
	m_json->processkeys(*this, &jv);
	return *this;
}
void JSON::Key::insert(const std::initializer_list<std::pair<const std::wstring, JSON > > &  il)
{
	m_json->processkeys(*this, nullptr);
	if (m_jsonroot->value_type != Value::VALUE_TYPE::OBJECT)
	{
		throw TypeError(L"JSON Object cannot be inserted for JSON Type %s", ValueName(m_jsonroot->value_type));
	}
	for (auto& item : il)
	{
		std::shared_ptr<Value> rroot = item.second.m_root;
		(*std::dynamic_pointer_cast<Object>(m_jsonroot)->m_value)[item.first] = rroot;
	}
}
void JSON::Key::insert(const std::initializer_list<JSON > & il)
{
	m_json->processkeys(*this, nullptr);
	if (m_jsonroot->value_type != Value::VALUE_TYPE::ARRAY)
	{
		throw TypeError(L"JSON Array cannot be inserted for JSON Type %s", ValueName(m_jsonroot->value_type));
	}
	for (auto& item : il)
	{
		(*std::dynamic_pointer_cast<Array>(m_jsonroot)->m_value).push_back(item.m_root);
	}
}
std::size_t JSON::Key::remove(std::wstring key)
{
	m_json->processkeys(*this, nullptr);
	if (m_jsonroot->value_type != Value::VALUE_TYPE::OBJECT)
	{
		throw TypeError(L"JSON Type %s invalid for key %s", ValueName(m_jsonroot->value_type), key);
	}
	auto &obj = (*std::dynamic_pointer_cast<Object>(m_jsonroot)->m_value);
	if (obj.count(key) == 0) return false;
	return obj.erase(key);
}
bool JSON::Key::remove(size_t index)
{
	m_json->processkeys(*this, nullptr);
	if (m_jsonroot->value_type != Value::VALUE_TYPE::ARRAY)
	{
		throw TypeError(L"JSON Type %s is not indexable.", ValueName(m_jsonroot->value_type));
	}
	auto &vec = (*std::dynamic_pointer_cast<Array>(m_jsonroot)->m_value);
	if (index >= vec.size()) return false;
	return vec.erase(vec.begin() + index) != vec.end();
}