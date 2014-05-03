#pragma once
#include "IDatabase.h"
#include "leveldb/db.h"
#include "leveldb/db/db_impl.h"

using namespace leveldb;
using namespace LevelDBClr;
using namespace System;

array<uint8_t>^ Database::Get(IEnumerable<uint8_t>^ key)
{
	List<char>^ keyList = gcnew List<char>();
	for each(char keyByte in key)
	{
		keyList->Add(keyByte);
	}

	array<char>^ keyarr = keyList->ToArray();
	pin_ptr<char> keyHeadd = &keyarr[0];
	const char* keyHead = keyHeadd;

	Slice keySlice(keyHead, keyarr->Length);

	ReadOptions options;
	std::string* v;

	this->db->Get(options, keySlice, v);

	List<uint8_t>^ valueList = gcnew List<uint8_t>();
	for (uint8_t b: *v)
	{
		valueList->Add(b);
	}

	return valueList->ToArray();
}

void Database::Put(IEnumerable<uint8_t>^ key, IEnumerable<uint8_t>^ value)
{
	List<char>^ keyList = gcnew List<char>();
	for each(char keyByte in key)
	{
		keyList->Add(keyByte);
	}

	array<char>^ keyarr = keyList->ToArray();
	pin_ptr<char> keyHeadd = &keyarr[0];
	const char* keyHead = keyHeadd;

	Slice keySlice(keyHead, keyarr->Length);

	List<char>^ valueList = gcnew List<char>();
	for each(char valueByte in value)
	{
		valueList->Add(valueByte);
	}

	array<char>^ valuearr = valueList->ToArray();
	pin_ptr<char> valueHeadd = &valuearr[0];
	const char* valueHead = valueHeadd;

	Slice valueSlice(valueHead, valuearr->Length);

	WriteOptions options;
	this->db->Put(options, keySlice, valueSlice);
}

Database::Database(const char* path)
{
	const Options options;
	this->db = new DBImpl(options, path);
}

Database::~Database()
{
	delete this->db;
}
