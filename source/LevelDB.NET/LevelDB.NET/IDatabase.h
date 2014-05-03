#pragma once
#include <stdint.h>
#include "leveldb/db.h"
#include "DatabaseOptions.h"

namespace LevelDBClr
{
	public interface class IDatabase : System::IDisposable
	{
		public:
			array<uint8_t>^ Get(array<uint8_t>^ key);
			void Put(array<uint8_t>^ key, array<uint8_t>^ value);
			void Delete(array<uint8_t>^ key);
	};

	ref class Database : IDatabase
	{
		leveldb::DB* db;

		public:
			virtual array<uint8_t>^ Get(array<uint8_t>^ key);
			virtual void Put(array<uint8_t>^ key, array<uint8_t>^ value);
			virtual void Delete(array<uint8_t>^ key);

		internal:
			Database(System::String^ path, DatabaseOptions^ options);
			~Database();
	};
};