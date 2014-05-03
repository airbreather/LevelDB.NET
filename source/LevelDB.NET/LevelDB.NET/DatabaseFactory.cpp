#pragma once
#include "IDatabaseFactory.h"
#include "leveldb/db.h"
#include "leveldb/db/db_impl.h"

using namespace leveldb;
using namespace LevelDBClr;
using namespace System;

public ref class DatabaseFactory : IDatabaseFactory
{
	public:
		virtual IDatabase^ CreateDatabase(const char* path)
		{
			Database^ d = gcnew Database(path);
			return (IDatabase^)d;
		}
};
