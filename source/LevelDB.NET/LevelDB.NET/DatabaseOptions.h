#pragma once
#include <stdint.h>
#include "leveldb/db.h"

namespace LevelDBClr
{
	public enum class CompressionOption
	{
		None = leveldb::CompressionType::kNoCompression,
		Snappy = leveldb::CompressionType::kSnappyCompression
	};

	public ref class DatabaseOptions : System::IDisposable
	{
		leveldb::Options* options;

		public:
			DatabaseOptions();
			~DatabaseOptions();
			void SetCreateIfMissing(bool createIfMissing);
			void SetCompressionOption(CompressionOption compressionOption);
			void SetCacheSizeInBytes(size_t cacheSizeInBytes);

		internal:
			const leveldb::Options& GetUnderlyingOptions();
	};
};
