#include "DatabaseOptions.h"
#include "leveldb/db.h"

using namespace leveldb;

namespace LevelDBClr
{
	DatabaseOptions::DatabaseOptions()
	{
		this->options = new Options();
	}
	
	DatabaseOptions::~DatabaseOptions()
	{
		delete this->options;
	}

	void DatabaseOptions::SetCreateIfMissing(bool createIfMissing)
	{
		this->options->create_if_missing = createIfMissing;
	}

	void DatabaseOptions::SetCompressionOption(CompressionOption compressionOption)
	{
		this->options->compression = (leveldb::CompressionType)compressionOption;
	}

	const leveldb::Options& DatabaseOptions::GetUnderlyingOptions()
	{
		return *this->options;
	}
};
