#pragma once
#include <msclr\marshal_cppstd.h>
#include "IDatabase.h"
#include "DatabaseOptions.h"
#include "leveldb/db.h"

using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;
using namespace leveldb;

namespace LevelDBClr
{
	array<uint8_t>^ Database::Get(array<uint8_t>^ key)
	{
		if (key == nullptr)
		{
			throw gcnew ArgumentNullException("key");
		}

		pin_ptr<uint8_t> pinnedKeyPtr = &key[0];
		const char* keyPtr = (const char*)pinnedKeyPtr;

		Slice keySlice(keyPtr, key->Length);

		ReadOptions options;
		string v;

		Status status = this->db->Get(options, keySlice, &v);
		if (status.IsNotFound())
		{
			return nullptr;
		}

		List<uint8_t>^ valueList = gcnew List<uint8_t>();
		for (uint8_t b : v)
		{
			valueList->Add(b);
		}

		return valueList->ToArray();
	}

	void Database::Put(array<uint8_t>^ key, array<uint8_t>^ value)
	{
		if (key == nullptr)
		{
			throw gcnew ArgumentNullException("key");
		}

		if (value == nullptr)
		{
			throw gcnew ArgumentNullException("value");
		}

		pin_ptr<uint8_t> pinnedKeyPtr = &key[0];
		const char* keyPtr = (const char*)pinnedKeyPtr;

		Slice keySlice(keyPtr, key->Length);

		pin_ptr<uint8_t> pinnedValuePtr = &value[0];
		const char* valuePtr = (const char*)pinnedValuePtr;

		Slice valueSlice(valuePtr, value->Length);

		WriteOptions options;
		this->db->Put(options, keySlice, valueSlice);
	}

	void Database::Delete(array<uint8_t>^ key)
	{
		if (key == nullptr)
		{
			throw gcnew ArgumentNullException("key");
		}

		pin_ptr<uint8_t> pinnedKeyPtr = &key[0];
		const char* keyPtr = (const char*)pinnedKeyPtr;

		Slice keySlice(keyPtr, key->Length);

		WriteOptions options;
		this->db->Delete(options, keySlice);
	}

	Database::Database(String^ path, DatabaseOptions^ options)
	{
		if (String::IsNullOrWhiteSpace(path))
		{
			throw gcnew ArgumentException("Path must be provided", "path");
		}

		if (options == nullptr)
		{
			options = gcnew DatabaseOptions();
		}

		string marshaledPath = marshal_as<string>(path);

		DB* dbPtr;
		Status status = DB::Open(options->GetUnderlyingOptions(), marshaledPath, &dbPtr);
		if (status.ok())
		{
			this->db = dbPtr;
		}
		else
		{
			String^ marshaledStatusMessage = marshal_as<String^>(status.ToString());
			throw gcnew InvalidOperationException(marshaledStatusMessage);
		}
	}

	Database::~Database()
	{
		delete this->db;
	}
};
