#pragma once
#include <assert.h>
#include "librg/librg.h"

class DataStream
{
public:
	DataStream(librg_data* librgData) :
		mLibrgData(librgData) 
	{
	}

	template<typename T>
	T Read()
	{
		assert(mLibrgData != nullptr);

		T varToRead;
		librg_data_rptr(mLibrgData, &varToRead, sizeof(T));
		return varToRead;
	}

	template<typename T>
	void Read(T* varPtr, u64 size)
	{
		assert(mLibrgData != nullptr);
		librg_data_rptr(mLibrgData, varPtr, size);
	}

	template<typename T>
	void Write(T varToWrite)
	{
		assert(mLibrgData != nullptr);
		librg_data_wptr(mLibrgData, &varToWrite, sizeof(varToWrite));
	}

	template<typename T>
	void Write(T* varToWrite, u64 size)
	{
		assert(mLibrgData != nullptr);
		librg_data_wptr(mLibrgData, &varToWrite, size);
	}
private:
	librg_data* mLibrgData;
};