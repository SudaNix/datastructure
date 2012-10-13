#ifndef DATASTRUCTURE_DYNAMICARRAY_H
#define	DATASTRUCTURE_DYNAMICARRAY_H

#include <string>
#include <exception>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <iostream>

namespace DataStructure
{

template <typename T>
class DynamicArray
{
public:
	DynamicArray(int size=0);
	DynamicArray(const DynamicArray& rhs);
	virtual ~DynamicArray();
    DynamicArray& operator=(const DynamicArray& rhs);

	void append(const T& value);
	void insert(const T& value, int index);
	void prepend(const T& value);
    void replace(const T& value, int index);
    void remove(int index);

    int find(const T& value);
	T& operator [](int index);
	const T& operator [](int index) const;
    const T& at(int index);

	int size() const;
	void clear();
    void printDebug();
    
    class Iterator
    {
    public:
        Iterator(T* p) : m_p(p) {}
        ~Iterator() {}

        // default copy ctor and assignment operator (shallow copy)
        
        T& operator* () const { return *m_p; }
        T& operator[](int i) const { return *(m_p + i); }
        Iterator& operator++ () { m_p = m_p + 1; return *this; }
        Iterator operator++(int) { Iterator i(*this); m_p = m_p + 1; return i;}
        Iterator& operator+=(int i) { m_p += i; return *this; }
        Iterator& operator-- () { m_p = m_p - 1; return *this; }
        Iterator operator--(int) { Iterator i(*this); m_p = m_p - 1; return i;}
        Iterator& operator-=(int i) { m_p -= i; return *this; }
        bool operator==(const Iterator& rhs) const { return m_p == rhs.m_p; }
        bool operator!=(const Iterator& rhs) const { return !operator==(rhs); }
    private:    
        T* m_p;
    };

    class ConstIterator
    {
    public:
        ConstIterator(T* p) : m_p(p) {}
        ~ConstIterator() {}

        // default copy ctor and assignment operator (shallow copy)
        
        const T& operator* () const { return *m_p; }
        const T& operator[](int i) const { return *(m_p + i); }
        ConstIterator& operator++ () { m_p = m_p + 1; return *this; }
        ConstIterator operator++(int) { ConstIterator i(*this); m_p = m_p + 1; return i;}
        ConstIterator& operator+=(int i) { m_p += i; return *this; }
        ConstIterator& operator-- () { m_p = m_p - 1; return *this; }
        ConstIterator operator--(int) { ConstIterator i(*this); m_p = m_p - 1; return i;}
        ConstIterator& operator-=(int i) { m_p -= i; return *this; }
        bool operator==(const ConstIterator& rhs) const { return m_p == rhs.m_p; }
        bool operator!=(const ConstIterator& rhs) const { return !operator==(rhs); }

    private:
        const T* m_p;
    };

    friend class Iterator;
    friend class ConstIterator;
    
    DynamicArray::Iterator begin();
    DynamicArray::Iterator end();

    DynamicArray::ConstIterator cbegin() const;
    DynamicArray::ConstIterator cend() const;

protected:
	T* m_data;
	int m_size;
	int m_capacity;

	void clearAll();
	int capacity() const;
	bool isIndexValid(int index);
    bool isCapacityFull();
	void insertByResizing(const T& value, int index);
    void shiftValue(T* array, int index, int count);

	static const std::string OUT_OF_RANGE_EXCEPTION_MSG; 
};

template <typename T>
const std::string DynamicArray<T>::OUT_OF_RANGE_EXCEPTION_MSG = "Out of Range invalid access";

template <typename T>
DynamicArray<T>::DynamicArray(int size) :
	m_data(NULL), 
	m_size(size), 
	m_capacity(size * 2)
{
	if (m_capacity == 0)
		return ;

	m_data = new T[m_capacity];

    // FIXME: check T type and if its primitive type then init value with 0s
    // there is no need to init value for user defined data type.
    Iterator i = begin();
    while ( i != end() ) {
        *i = T();
        ++i;
    }

    //memset(m_data, 0, m_capacity * sizeof(T));
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& rhs) :
    m_data(NULL),
    m_size(rhs.m_size),
    m_capacity(rhs.m_capacity)
{
   if (m_capacity == 0)
       return;
       
    m_data = new T[m_capacity];

    //memcpy(m_data, rhs.m_data, m_capacity * sizeof(T)); 

    ConstIterator d = rhs.cbegin();
    Iterator s = begin();
    while ( d != rhs.cend() ) {
       *s = *d;
       ++s;
       ++d; 
    }
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs)
{
    if (this == &rhs)
        return *this;

    // remove previous data
    this->clearAll();
    
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;

    if (m_capacity == 0)
        return *this ;

    m_data = new T[m_capacity];
    //memcpy(m_data, rhs.m_data, m_capacity * sizeof(T));

    ConstIterator d = rhs.cbegin();
    Iterator s = this->begin();
    while ( d != rhs.cend() ) {
       *s = *d;
       ++s;
       ++d; 
    }

    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
	this->clearAll();
}

template <typename T>
T& DynamicArray<T>::operator [](int index)
{
	if (!this->isIndexValid(index))
		throw std::out_of_range(OUT_OF_RANGE_EXCEPTION_MSG);

	return *(m_data + index);
}

template <typename T>
const T& DynamicArray<T>::operator [](int index) const
{
	return this->DynamicArray<T>::operator[](index);
}

template <typename T>
const T& DynamicArray<T>::at(int index)
{
    return this->DynamicArray<T>::operator[](index);
}

template <typename T>
void DynamicArray<T>::append(const T& value)
{
    this->insert(value, m_size);	
}

template <typename T>
void DynamicArray<T>::prepend(const T& value)
{
    this->insert(value, 0);
}

template <typename T>
void DynamicArray<T>::replace(const T& value, int index)
{
    this->operator[](index) = value;
}

template <typename T>
void DynamicArray<T>::remove(int index)
{
	if (!this->isIndexValid(index))
		throw std::out_of_range(OUT_OF_RANGE_EXCEPTION_MSG);
            
    if (m_size == 1) {
        assert(index == 0);
        m_data[index] = T();
        m_size--;
        return ;
    }

    // shift elements to the left
    int right_elements_count = (m_size - 1) - index;
    this->shiftValue(m_data, index+1, right_elements_count);
    m_size--;
    m_data[m_size] = T();
}

template <typename T>
int DynamicArray<T>::find(const T& value)
{
    int index = 0;
    Iterator i = begin();
    while ( i != end() ) {
        if (*i == value)
            return index;

        ++index;
        ++i;
    }

    return -1;
}

template <typename T>
bool DynamicArray<T>::isIndexValid(int index) {
	return (index < 0 || index >= m_size) ? false: true;
}

template <typename T>
bool DynamicArray<T>::isCapacityFull()
{
    return (m_size == m_capacity);
}
    
template <typename T>
void DynamicArray<T>::insert(const T& value, int index)
{
	if (!isCapacityFull() && (index >= m_size)) {

		*(m_data + m_size) = value;
        m_size++;

	} else {
		insertByResizing(value, index);
	}
}

template <typename T>
void DynamicArray<T>::insertByResizing(const T& value, int index)
{
	if (index < 0)
		index = 0;
	else if (index >= m_size)
		index = m_size;

	int size = m_size + 1;
	int capacity = size * 2;

	T* p = new T[capacity];
	p[index] = value;

	for (int i=0; i<m_size; ++i) {
		if (i < index)
			p[i] = m_data[i];
		else
			p[i+1] = m_data[i];
	}

	delete [] m_data;
	m_data = p;
	m_size = size;
	m_capacity = capacity;
}

template <typename T>
void DynamicArray<T>::clearAll()
{
	if (m_data == NULL)
		return;

	delete [] m_data;
	m_data = NULL;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
int DynamicArray<T>::size() const
{
	return m_size;
}

template <typename T>
void DynamicArray<T>::printDebug()  
{
    std::cout << "capacity: " << m_capacity << std::endl;
    std::cout << "size: " << m_size << std::endl;

    for (Iterator i = begin(); i != end(); ++i) {
        std::cout << *i << " " ;
    }

    std::cout << std::endl;
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() 
{
    return DynamicArray<T>::Iterator(m_data); 
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() 
{
    return DynamicArray<T>::Iterator(m_data + m_size); 
}

template <typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cbegin() const
{
    return DynamicArray<T>::ConstIterator(m_data);
}

template <typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cend() const
{
    return DynamicArray<T>::ConstIterator(m_data + m_size);
}

template <typename T>
void DynamicArray<T>::shiftValue(T* array, int index, int count)
{
    while (count > 0) {
        array[index -1 ] = array[index];
        ++index;
        --count;
    }
}

}

#endif // DATASTRUCTURE_DYNAMICARRAY_H
