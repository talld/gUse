#include <gList.h>
#include <gTable.h>
#include <gCircularBuffer.h>

////////////////////////////////////////////////////////////////////////////////
/// List Tests                                                               ///
////////////////////////////////////////////////////////////////////////////////

int ListReverseTest()
{
	const size_t listSize = 5;

	// fill list
	GListInt32_t* gList = GListInt32_Create();
	for(size_t i = 0; i < listSize; i++)
	{
		GListInt32_PushBack(gList, i);
	}

	// reverse list
	for(size_t i = 0; i < listSize; i++)
	{
		int32_t value = GListInt32_Back(gList);
		GListInt32_PushFront(gList, value);
		GListInt32_PopBack(gList);
	}

	// test list
	for(size_t i = 0; i < listSize; i++)
	{
		int32_t v = GListInt32_Front(gList);
		if(v != i) {goto FAIL;}
		GListInt32_PopFront(gList);
	}


	return 0;

	FAIL:
	return 1;
}

int doListTests()
{
	int err = 0;

	err = ListReverseTest(); if(err) {goto FAIL;}
	return 0;

	FAIL:
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
/// Table Tests                                                              ///
////////////////////////////////////////////////////////////////////////////////

int TableIdentityTest()
{
	const size_t tableSize = 10;

	GTableInt32_t* gTable = GTableInt32_Create(tableSize /3);

	for(int i = 0; i < tableSize; i++)
	{
		GTableInt32_Insert(gTable, i, i);
	}

	// check without removals
	for(int i = 0; i < tableSize; i++)
	{
		int val = GTableInt32_Get(gTable, i);
		if(val != i)
		{
			goto FAIL;
		}
	}

	// check with removals
	for(int i = 0; i < tableSize; i++)
	{
		int val = GTableInt32_Get(gTable, i);
		GTableInt32_Remove(gTable, i);
		if(val != i)
		{
			goto FAIL;
		}
	}

	// check after removals
	for(int i = 0; i < tableSize; i++)
	{
		int val = GTableInt32_Get(gTable, i);
		GTableInt32_Remove(gTable, i);
		if(val != 0)
		{
			goto FAIL;
		}
	}

	GTableInt32_Destroy(gTable);

	return 0;

	FAIL:
	return 1;
}

int doTableTests()
{
	int err = 0;

	err = TableIdentityTest(); if(err) {goto FAIL;}
	return 0;

	FAIL:
	return 1;
}

int CircularBufferCountingTest()
{
	int err = 0;

	enum {kCircularBufferSize = 10};
	GCircularBufferInt32_t* gCircularBuffer = GCircularBufferInt32_Create(kCircularBufferSize);

	for(int i = 0; i < kCircularBufferSize; i++)
	{
		GCircularBufferInt32_Write(gCircularBuffer, i);
	}

	for(int i = 0; i < kCircularBufferSize; i++)
	{
		int32_t readValue = GCircularBufferInt32_Read(gCircularBuffer);
		GCircularBufferInt32_Write(gCircularBuffer, -i);

		if(readValue != i)
		{
			err |= 1;
		}
	}

	for(int i = 0; i < kCircularBufferSize; i++)
	{
		int32_t readValue = GCircularBufferInt32_Read(gCircularBuffer);
		if(readValue != -i)
		{
			err |= 1;
		}
	}

	return err;
}

int doCircularBufferTests()
{

	int err = 0;

	err = CircularBufferCountingTest(); if(err) {goto FAIL;}

	return 0;
	FAIL:
	return 1;



}

int GAlg_DoTests()
{
	int err = 0;
	err = doListTests(); if(err) {goto FAIL;}
	err = doTableTests(); if(err) {goto FAIL;}
	err = doCircularBufferTests(); if(err) {goto FAIL;}
	return 0;

	FAIL:
	return 1;
}