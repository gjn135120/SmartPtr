#ifndef AUTO_PTR_H
#define AUTO_PTR_H
#include <iostream>

template <typename T>
class AutoPtr
{
public:
	typedef T 	value_type;
	typedef T*	pointer;
	typedef T&	reference;


	AutoPtr(T *ptr = NULL);
	AutoPtr(AutoPtr &other);
	~AutoPtr();
	AutoPtr &operator= (AutoPtr &other) throw();

	reference operator*() const throw()
	{ return *_ptr; }

	pointer operator->() const throw()
	{ return _ptr; }

	void reset(T *ptr = NULL) throw()
	{
		if(_ptr != ptr)
		{
			delete _ptr;
			_ptr = ptr;
		}
	}

	pointer release() throw()
	{
		pointer tmp(_ptr);
		_ptr = NULL;
		return tmp;
	}

	operator bool() throw() { return _ptr != NULL; }

private:
	value_type *_ptr;
};


template <typename T>
AutoPtr<T>::AutoPtr(T *ptr)
	:_ptr(ptr)
{

}

template <typename T>
AutoPtr<T>::AutoPtr(AutoPtr<T> &other)
	:_ptr(other._ptr)
{
	other._ptr = NULL;
}

template <typename T>
AutoPtr<T>::~AutoPtr()
{
	delete _ptr;
}

template <typename T>
AutoPtr<T> &AutoPtr<T>::operator= (AutoPtr<T> &other) throw()
{
	reset(other.release());

	return *this;
}
#endif  /*AUTO_PTR_H*/
