#pragma once
#include "IDatabase.h"
#include "DatabaseOptions.h"

namespace LevelDBClr
{
	public interface class IDatabaseFactory
	{
		public:
			IDatabase^ CreateDatabase(System::String^ path, DatabaseOptions^ options);
	};

	public ref class DatabaseFactory : IDatabaseFactory
	{
		public:
			virtual IDatabase^ CreateDatabase(System::String^ path, DatabaseOptions^ options);
	};
};