//
// Created by oxford on 31.05.24.
//

#include "circularBuffer.h"

template <class T>
circularBuffer<T>::circularBuffer(size_t size):
		mBuffer(std::unique_ptr<T[]>(new T[size])),
		mSize(size) {}


template <class T>
void circularBuffer<T>::put(T item) 
{
	mBuffer[head] = item;

	if(mFull)
	{
		mTail = (mTail + 1) % mSize;
	}

	mHead = (mHead + 1) % mSize;
	mFull = mHead == mTail;
}

template <class T>
T circularBuffer<T>::pop()
{
	if(isEmpty())
	{
		return T();
	}

	//Read data and advance the tail (we now have a free space)
	auto val = mBuffer[mTail];
	mFull = false;
	mTail = (mTail + 1) % mSize;

	return val;
}

template <class T>
void circularBuffer<T>::clearAll() 
{
	std::lock_guard<std::mutex> lock(mutex_);
	mHead = mTail;
	full_ = false;
}

template <class T>
bool circularBuffer<T>::isEmpty() const 
{
  return (!full_ && (mHead == mTail));
}

template <class T>
bool circularBuffer<T>::isFull() const 
{
  	//If tail is ahead the head by 1, we are full
	return full_;
}

template <class T>
size_t circularBuffer<T>::capacity() const 
{
  return mSize;
}

template <class T>
size_t circularBuffer<T>::getDataSize() const 
{
  	size_t size = mSize;

	if(!full_)
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
