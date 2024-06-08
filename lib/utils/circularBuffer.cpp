//
// Created by oxford on 31.05.24.
//

#include "circularBuffer.h"

// template <class T>
// circularBuffer<T>::circularBuffer(size_t size):
// 		mBuffer(std::unique_ptr<T[]>(new T[size])),
// 		mSize(size) {}


// template <class T>
// void circularBuffer<T>::put(T item) 
// {
// 	mBuffer[mHead] = item;

// 	if(mFull)
// 	{
// 		mTail = (mTail + 1) % mSize;
// 	}

// 	mHead = (mHead + 1) % mSize;
// 	mFull = mHead == mTail;
// }

// template <class T>
// T circularBuffer<T>::pop()
// {
// 	if(isEmpty())
// 	{
// 		return T();
// 	}

// 	//Read data and advance the tail (we now have a free space)
// 	auto val = mBuffer[mTail];
// 	mFull = false;
// 	mTail = (mTail + 1) % mSize;

// 	return val;
// }

// template <class T>
// void circularBuffer<T>::clearAll() 
// {
// 	mHead = mTail;
// 	mFull = false;
// }

// template <class T>
// bool circularBuffer<T>::isEmpty() const 
// {
//   return (!mFull && (mHead == mTail));
// }

// template <class T>
// bool circularBuffer<T>::isFull() const 
// {
//   	//If tail is ahead the head by 1, we are full
// 	return mFull;
// }

// template <class T>
// size_t circularBuffer<T>::capacity() const 
// {
//   return mSize;
// }

// template <class T>
// size_t circularBuffer<T>::getDataSize() const 
// {
//   	size_t size = mSize;

// 	if(!mFull)
// 	{
// 		if(mHead >= mTail)
// 		{
// 			size = mHead - mTail;
// 		}
// 		else
// 		{
// 			size = mSize + mHead - mTail;
// 		}
// 	}

// 	return size;
// }

circularBuffer::circularBuffer(size_t size):
		mBuffer(std::unique_ptr<uint8_t[]>(new uint8_t[size])),
		mSize(size) {}


void circularBuffer::put(uint8_t item) 
{
	mBuffer[mHead] = item;

	if(mFull)
	{
		mTail = (mTail + 1) % mSize;
	}

	mHead = (mHead + 1) % mSize;
	mFull = mHead == mTail;
}

bool circularBuffer::pop(uint8_t *item)
{
	if(isEmpty())
	{
		return false;
	}

	//Read data and advance the tail (we now have a free space)
	*item = mBuffer[mTail];
	mFull = false;
	mTail = (mTail + 1) % mSize;

	return true;
}

void circularBuffer::clearAll() 
{
	mHead = mTail;
	mFull = false;
}

bool circularBuffer::isEmpty() const 
{
  return (!mFull && (mHead == mTail));
}

bool circularBuffer::isFull() const 
{
  	//If tail is ahead the head by 1, we are full
	return mFull;
}

size_t circularBuffer::capacity() const 
{
  return mSize;
}

size_t circularBuffer::getDataSize() const 
{
  	size_t size = mSize;

	if(!mFull)
	{
		if(mHead >= mTail)
		{
			size = mHead - mTail;
		}
		else
		{
			size = mSize + mHead - mTail;
		}
	}

	return size;
}
