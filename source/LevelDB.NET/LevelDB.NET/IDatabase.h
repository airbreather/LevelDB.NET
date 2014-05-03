#pragma once
#include <stdint.h>
#include "leveldb/db.h"

using namespace leveldb;
using namespace System;
using namespace System::Collections::Generic;

namespace LevelDBClr
{
	public interface class IDatabase
	{
	public:
		array<uint8_t>^ Get(IEnumerable<uint8_t>^ key);
		void Put(IEnumerable<uint8_t>^ key, IEnumerable<uint8_t>^ value);
	};


	public ref class Database : IDatabase, IDisposable
	{
		DB* db;

	public:
		virtual array<uint8_t>^ Get(IEnumerable<uint8_t>^ key);
		virtual void Put(IEnumerable<uint8_t>^ key, IEnumerable<uint8_t>^ value);

	internal:
		Database(const char* path);
		~Database();
	};
};