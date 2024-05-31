//
// Created by oxford on 31.05.24.
//

template <class T>
class circularBuffer 
{
public:
	explicit circularBuffer(size_t size);
	void put(T item);
	T pop();
	void clearAll();
	bool isEmpty() const;
	bool isFull() const;
	size_t capacity() const;
	size_t getDataSize() const;

private:
	std::unique_ptr<T[]> mBuffer;
	size_t mHead = 0;
	size_t mTail = 0;
	const size_t mSize;
	bool mFull = 0;
};
