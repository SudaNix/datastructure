#ifndef DATASTRUCTURE_DYNAMICARRAY_H
#define	DATASTRUCTURE_DYNAMICARRAY_H

#include <string>

namespace DataStructure
{

class DynamicArray
{
public:
	DynamicArray(int size=0);
	DynamicArray(const DynamicArray& rhs);
	virtual ~DynamicArray();
    DynamicArray& operator=(const DynamicArray& rhs);

	void append(int value);
	void insert(int value, int index);
	void prepend(int value);
    void replace(int value, int index);
    void remove(int index);

    int find(int value);
	int& operator [](int index);
	const int& operator [](int index) const;
    const int& at(int index);

	int size() const;
	void clear();
    void printDebug();
    
    class Iterator
    {
    public:
        Iterator(int* p) : m_p(p) {}
        ~Iterator() {}

        // default copy ctor and assignment operator (shallow copy)
        
        int& operator* () const { return *m_p; }
        int& operator[](int i) const { return *(m_p + i); }
        Iterator& operator++ () { m_p = m_p + 1; return *this; }
        Iterator operator++(int) { Iterator i(*this); m_p = m_p + 1; return i;}
        Iterator& operator+=(int i) { m_p += i; return *this; }
        Iterator& operator-- () { m_p = m_p - 1; return *this; }
        Iterator operator--(int) { Iterator i(*this); m_p = m_p - 1; return i;}
        Iterator& operator-=(int i) { m_p -= i; return *this; }
        bool operator==(const Iterator& rhs) const { return m_p == rhs.m_p; }
        bool operator!=(const Iterator& rhs) const { return !operator==(rhs); }
    private:    
        int* m_p;
    };

    class ConstIterator
    {
    public:
        ConstIterator(int* p) : m_p(p) {}
        ~ConstIterator() {}

        //! TODO: implement const iterator
    private:
        const int* m_p;
    };

    friend class Iterator;
    friend class ConstIterator;
    
    DynamicArray::Iterator begin();
    DynamicArray::Iterator end();

    DynamicArray::ConstIterator cbegin() const;
    DynamicArray::ConstIterator cend() const;

protected:
	int* m_data;
	int m_size;
	int m_capacity;

	void clearAll();
	int capacity() const;
	bool isIndexValid(int index);
    bool isCapacityFull();
	void insertByResizing(int value, int index);
    void shiftValue(int* array, int index, int count);

	static const std::string OUT_OF_RANGE_EXCEPTION_MSG; 
};

}

#endif // DATASTRUCTURE_DYNAMICARRAY_H
