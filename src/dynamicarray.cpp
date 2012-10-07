#include <exception>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include "../include/dynamicarray.h"

const std::string DataStructure::DynamicArray::OUT_OF_RANGE_EXCEPTION_MSG = "Out of Range invalid access";

DataStructure::DynamicArray::DynamicArray(int size) :
	m_data(NULL), 
	m_size(size), 
	m_capacity(size * 2)
{
	if (m_capacity == 0)
		return ;

	m_data = new int[m_capacity];
    memset(m_data, 0, m_capacity * sizeof(int));
}

DataStructure::DynamicArray::DynamicArray(const DynamicArray& rhs) :
    m_data(NULL),
    m_size(rhs.m_size),
    m_capacity(rhs.m_capacity)
{
   if (m_capacity == 0)
       return;
       
    m_data = new int[m_capacity];

    // FIXME: if copied data has pointer to another data, this will not work
    // It work only on primitive data type
    memcpy(m_data, rhs.m_data, m_capacity * sizeof(int)); 
}

DataStructure::DynamicArray& DataStructure::DynamicArray::operator=(const DynamicArray& rhs)
{
    if (this == &rhs)
        return *this;

    // remove previous data
    this->clearAll();
    
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;

    if (m_capacity == 0)
        return *this ;

    m_data = new int[m_capacity];
    memcpy(m_data, rhs.m_data, m_capacity * sizeof(int));

    return *this;
}

DataStructure::DynamicArray::~DynamicArray()
{
	this->clearAll();
}

int& DataStructure::DynamicArray::operator [](int index)
{
	if (!this->isIndexValid(index))
		throw std::out_of_range(OUT_OF_RANGE_EXCEPTION_MSG);

	return *(m_data + index);
}

const int& DataStructure::DynamicArray::operator [](int index) const
{
	return this->DynamicArray::operator[](index);
}

const int& DataStructure::DynamicArray::at(int index)
{
    return this->DynamicArray::operator[](index);
}

void DataStructure::DynamicArray::append(int value)
{
    this->insert(value, m_size);	
}

void DataStructure::DynamicArray::prepend(int value)
{
    this->insert(value, 0);
}

void DataStructure::DynamicArray::replace(int value, int index)
{
    this->operator[](index) = value;
}

void DataStructure::DynamicArray::remove(int index)
{
	if (!this->isIndexValid(index))
		throw std::out_of_range(OUT_OF_RANGE_EXCEPTION_MSG);
            
    if (m_size == 1) {
        assert(index == 0);
        m_data[index] = 0;
        m_size--;
        return ;
    }

    // shift elements to the left
    int right_elements_count = (m_size - 1) - index;
    this->shiftValue(m_data, index+1, right_elements_count);
    m_size--;
    m_data[m_size] = 0;
}

int DataStructure::DynamicArray::find(int value)
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

bool DataStructure::DynamicArray::isIndexValid(int index)
{
	return (index < 0 || index >= m_size) ? false: true;
}

bool DataStructure::DynamicArray::isCapacityFull()
{
    return (m_size == m_capacity);
}
    
void DataStructure::DynamicArray::insert(int value, int index)
{
	if (!isCapacityFull() && (index >= m_size)) {

		*(m_data + m_size) = value;
        m_size++;

	} else {
		insertByResizing(value, index);
	}
}

void DataStructure::DynamicArray::insertByResizing(int value, int index)
{
	if (index < 0)
		index = 0;
	else if (index >= m_size)
		index = m_size;

	int size = m_size + 1;
	int capacity = size * 2;

	int* p = new int[capacity];
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

void DataStructure::DynamicArray::clearAll()
{
	if (m_data == NULL)
		return;

	delete [] m_data;
	m_data = NULL;
	m_size = 0;
	m_capacity = 0;
}

int DataStructure::DynamicArray::size() const
{
	return m_size;
}

void DataStructure::DynamicArray::printDebug()  
{
    std::cout << "capacity: " << m_capacity << std::endl;
    std::cout << "size: " << m_size << std::endl;

    for (Iterator i = begin(); i != end(); ++i) {
        std::cout << *i << " " ;
    }

    std::cout << std::endl;
}

DataStructure::DynamicArray::Iterator DataStructure::DynamicArray::begin() 
{
    return DynamicArray::Iterator(m_data); 
}

DataStructure::DynamicArray::Iterator DataStructure::DynamicArray::end() 
{
    return DynamicArray::Iterator(m_data + m_size); 
}


void DataStructure::DynamicArray::shiftValue(int* array, int index, int count)
{
    while (count > 0) {
        array[index -1 ] = array[index];
        ++index;
        --count;
    }
}
