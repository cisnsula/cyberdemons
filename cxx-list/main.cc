#include <iostream>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstdlib>

#define DEFAULT_SIZE 10

template<typename T>
class list {
public:
	virtual void add(T data) = 0;
	virtual void remove(uint64_t index) = 0;
	virtual T &get(uint64_t index) const = 0;
	virtual T &operator[](uint64_t) = 0;
};

template<typename T>
class fast_vec : public list<T> {
private:
	T *arr;
	uint64_t size;
	uint64_t capacity;

	void grow() {
		arr = (T *)realloc(arr, (capacity = (capacity << 1)));
	}

public:
	fast_vec() {
		arr = (T *)malloc(sizeof(T) * (capacity =
		    (DEFAULT_SIZE << 1)));
		size = 0;
	}

	~fast_vec() {
		if (arr != NULL)
			free(arr);

		size = 0;
		capacity = 0;
	}

	void add(T data) override {
		if (size < (capacity - 1))
			grow();

		arr[size++] = data;
	}

	void remove(uint64_t index) override {
		if (index >= size) [[unlikely]]
			throw 1;

		arr[index] = arr[size--];
	}

	T &get(uint64_t index) const override {
		if (index >= size) [[unlikely]]
			throw 1;

		return arr[index];
	}

	T &operator[](uint64_t index) override {
		if (index >= size) [[unlikely]]
			throw 1;

		return arr[index];
	}
};

int main() {
	fast_vec<uint64_t> vec{};

	
	for (int i = 0; i < 1000; i++)
		vec.add(i);


	for (int i = 0; i < 1000; i++)
		std::cout << vec[i] << std::endl;


//	auto *vector = new fast_vec<uint64_t>;
//
//	for (int i = 0; i < 1000; i++)
//		vector->add(i);
//
//
//	for (int i = 0; i < 1000; i++)
//		std::cout << (*vector)[i] << std::endl;
//
//	
//	delete vector;
	exit(EXIT_SUCCESS);
}
