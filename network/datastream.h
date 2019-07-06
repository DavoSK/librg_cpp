#pragma once
#include <assert.h>
#include "librg/librg.h"

namespace network
{
	class DataStream
	{
	public:
		DataStream(librg_data* librgData) :
			mLibrgData(librgData)
		{
			assert(librgData != nullptr);
		}

		template<typename T>
		T Read()
		{
			T varToRead;
			librg_data_rptr(mLibrgData, &varToRead, sizeof(T));
			return varToRead;
		}

		template<typename T>
		void Read(T * varPtr, u64 size)
		{
			librg_data_rptr(mLibrgData, varPtr, size);
		}

		template<typename T>
		void Write(T varToWrite)
		{
			librg_data_wptr(mLibrgData, &varToWrite, sizeof(varToWrite));
		}

		template<typename T>
		void Write(T * varToWrite, u64 size)
		{
			librg_data_wptr(mLibrgData, &varToWrite, size);
		}
	private:
		librg_data* mLibrgData;
	};
}