#pragma once

#include "IDatabase.h"

using namespace std;
using namespace System;

namespace LevelDBClr
{
	public interface class IDatabaseFactory
	{
		public:
			IDatabase^ CreateDatabase(const char* path);
	};
};