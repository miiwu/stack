#pragma once

template<class T>
class Stack {
private:
	T* data;
	size_t size;
	size_t top;
public:
	Stack(size_t s):data(nullptr), size(s), top(0)
	{
		data = new T[size];
	}

	Stack(const Stack&) = delete;

	Stack(Stack&&) = delete;

	Stack& operator = (const Stack&) = delete;

	Stack& operator = (Stack&&) = delete;

	~Stack() {}

	void push(const T& e) {
		if (top < size) {
			*(data + top) = e;
			top++;
		}
	}

	T& pop() {
		return *(data + top--);
	}
};