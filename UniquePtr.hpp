#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <algorithm>
#include <iostream>

template <typename T>
class UniquePtr
{
public:
	typedef T 	value_type;
	typedef T*	pointer;
	typedef T&	reference;

	explicit UniquePtr(T *ptr = NULL) throw()
		:_ptr(ptr)
	{

	}
	UniquePtr(UniquePtr &&s) throw()
		:_ptr(s._ptr)
	{
		s._ptr = NULL;
	}
	UniquePtr &operator= (UniquePtr &&s) throw()
	{
		if(this != &s)
		{
			delete _ptr;
			_ptr = s._ptr;
			s._ptr = NULL;
		}

		return *this;
	}
	~UniquePtr() throw()
	{
		delete _ptr;
	}

	reference operator* () const throw()
	{ return *_ptr; }

	pointer operator-> () const throw()
	{ return _ptr; }

	pointer get() const throw()
	{ return _ptr; }

	pointer release() throw()
	{
		pointer tmp(_ptr);
		_ptr = NULL;
		return tmp;
	}

	void reset(T *ptr = NULL) throw()
	{
		if(_ptr != ptr)
		{
			delete _ptr;
			_ptr = ptr;
		}
	}


	void swap(UniquePtr &other)
	{
		std::swap(_ptr, other._ptr);
	}

private:
	UniquePtr(const UniquePtr &);
	void operator= (const UniquePtr &);

	pointer _ptr;
};





#endif  /*UNIQUE_PTR_H*/
