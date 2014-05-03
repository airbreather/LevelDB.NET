#pragma once
#include "IDatabaseFactory.h"

using namespace leveldb;
using namespace System;

namespace LevelDBClr
{
	IDatabase^ DatabaseFactory::CreateDatabase(String^ path, DatabaseOptions^ options)
	{
		Database^ d = gcnew Database(path, options);
		return (IDatabase^)d;
	}
};
