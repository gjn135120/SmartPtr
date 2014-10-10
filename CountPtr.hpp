#ifndef COUNT_PTR_H
#define COUNT_PTR_H
#include <iostream>


template <typename T>
class CountPtr
{
public:
	typedef T 				value_type;
	typedef T*				pointer;
	typedef T&				reference;


	explicit CountPtr(T *p = NULL);
	CountPtr(const CountPtr<T> &other);
	~CountPtr();

	CountPtr<T> &operator= (const CountPtr<T> &other);
	reference operator*() const throw() { return *_ptr; }

	pointer operator->() const throw() { return _ptr; }

	size_t count() const throw() { return *_count; }

	void swap(CountPtr<T> &other) throw()
	{
		std::swap(_ptr, other._ptr);
		std::swap(_count, other._count);
	}

	void reset(T *ptr = NULL) throw()
	{
		dispose();

		_ptr = ptr;
		_count = new size_t(1);
	}


	pointer get() const throw() { return _ptr; }

	bool unique() const throw() { return *_count == 1; }

	operator bool() { return _ptr != NULL; }
private:

	void dispose()
	{
		if(-- *_count == 0)
		{
			delete _ptr;
			delete _count;
		}
	}

	T *_ptr;
	size_t *_count;

};

template <typename T>
CountPtr<T>::CountPtr(T *p)
	:_ptr(p),
	 _count(new size_t(1))
{

}

template <typename T>
CountPtr<T>::~CountPtr()
{
	dispose();
}

template <typename T>
CountPtr<T>::CountPtr(const CountPtr<T> &other)
	:_ptr(other._ptr),
	 _count(other._count)
{
	++ (*_count);
}

template <typename T>
CountPtr<T> &CountPtr<T>::operator= (const CountPtr<T> &other)
{
	++(*other._count);			//先++防止自身赋值失败

	dispose();

	_ptr = other._ptr;
	_count = other._count;

	return *this;
}
#endif  /*COUNT_PTR_H*/
