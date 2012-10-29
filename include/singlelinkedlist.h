#ifndef DATASTRUCTURE_SINGLELINKEDLIST_H
#define DATASTRUCTURE_SINGLELINKEDLIST_H

#include <cstddef>
#include <exception>
#include <stdexcept>
#include <iostream>

namespace DataStructure
{

class SingleLinkedList
{
	struct Node; // Forward Declaration
public:
	class Iterator; // Forward Declaration
	SingleLinkedList();
	SingleLinkedList(const SingleLinkedList& rhs);
	virtual ~SingleLinkedList();
	
	SingleLinkedList& operator=(const SingleLinkedList& rhs);
	bool operator==(const SingleLinkedList& rhs);
	
	void append(const int& value);
	void prepend(const int& value);
	void insert(const int& value, Iterator pos);
	bool removeFirst();
	bool removeLast();
	bool remove(const int& value);
	bool remove(Iterator pos);
	void replace(const int& oldValue, const int& newValue);
	Iterator find(const int& value);	//! TODO: remove this method. instead use find from Algorithm namespace.
	void clear();
	
	int count() const { return m_count; }
	int size() const { return m_count; }
	bool isEmpty() const { return m_head == NULL; }

	void debug() {
		for (Node* t = m_head; t != NULL; t = t->next)
			std::cout << t->value << " -> ";
		std::cout << std::endl;
	}

    class Iterator
    {
    public:
        Node* n;
        Iterator(Node* p) : n(p) {}
        ~Iterator() {}
        
        int& operator* () const { return (*n).value; }
        Iterator& operator++ () { 
			if (n == NULL) 
				throw std::out_of_range("LinkedList: out of range iterator access"); 
			n = n->next; 
			return *this; 
		}

        Iterator operator++(int) { 
			if (n == NULL) 
				throw std::out_of_range("LinkedList: out of range iterator access"); 
			Iterator i(*this);
			n = n->next; 
			return i;
		}

        Iterator& operator+=(int i) { 
			if (n == NULL) 
				throw std::out_of_range("LinkedList: out of range iterator access"); 
			while (i-- && n != NULL)
				n = n->next;
			return *this; 
		}

		bool hasValue() const { return n != NULL; }
        bool operator==(const Iterator& rhs) const { if (!rhs.hasValue()) return false; return n->value == rhs.n->value; }
        bool operator!=(const Iterator& rhs) const { if (!rhs.hasValue()) return false; return n->value != rhs.n->value; }
    };

    class ConstIterator
    {
    public:
        const Node* n;
        ConstIterator(Node* p) : n(p) {}
        ~ConstIterator() {}
        
        const int& operator* () const { return (*n).value; }
        ConstIterator& operator++ () { 
			if (n == NULL) 
				throw std::out_of_range("LinkedList: out of range iterator access"); 
			n = n->next; 
			return *this; 
		}

        ConstIterator operator++(int) { 
			if (n == NULL) 
				throw std::out_of_range("LinkedList: out of range iterator access"); 
			ConstIterator i(*this);
			n = n->next; 
			return i;
		}

        ConstIterator& operator+=(int i) { 
			if (n == NULL) 
				throw std::out_of_range("LinkedList: out of range iterator access"); 
			while (i-- && n != NULL)
				n = n->next;
			return *this; 
		}

		bool hasValue() const { return n != NULL; }
        bool operator==(const ConstIterator& rhs) const { return n->value == rhs.n->value; }
        bool operator!=(const ConstIterator& rhs) const { if (!rhs.hasValue()) return false; return n->value != rhs.n->value; }
    };

 
    SingleLinkedList::Iterator begin();
	SingleLinkedList::Iterator end();
    SingleLinkedList::ConstIterator cbegin() const;
	SingleLinkedList::ConstIterator cend() const;

private:

	struct Node
	{
		Node(const int& v, Node* n) :
			value(v), next(n)
		{}

		int value;
		Node* next;
	};

	Node* m_head;
	Node* m_tail;
	int m_count;

	Node* createNode(const int& value) { ++m_count; return new Node(value, NULL); }
	void removeNode(const Node* node) { --m_count; delete node; }
	void copy(const SingleLinkedList& rhs);
};

SingleLinkedList::SingleLinkedList() :
	m_head(NULL), m_tail(NULL), m_count(0)
{}

SingleLinkedList::SingleLinkedList(const SingleLinkedList& rhs):
	m_head(NULL), m_tail(NULL), m_count(0)
{
	this->copy(rhs);
}

SingleLinkedList::~SingleLinkedList()
{
	this->clear();
}

void SingleLinkedList::copy(const SingleLinkedList& rhs)
{
	int count = rhs.m_count;
	Node* p = rhs.m_head;
	while (count--) {
		this->append(p->value);
		p = p->next;
	}
}

void SingleLinkedList::clear()
{
	Node* node = m_head;
	while (node->next != NULL) {
		Node* tmp = node;
		node = node->next;
		delete tmp;
	}

	if (node != NULL)
		delete node;

	m_count = 0;
	m_head = NULL;
	m_tail = NULL;
}

SingleLinkedList& SingleLinkedList::operator=(const SingleLinkedList& rhs)
{
	if (this == &rhs)
		return *this;
	
	this->clear();
	this->copy(rhs);
	
	return *this;
}

bool SingleLinkedList::operator==(const SingleLinkedList& rhs)
{
	if (m_count != rhs.m_count)
		return false;

	// check every node value
	ConstIterator thisItr = this->cbegin();
	ConstIterator rhsItr = rhs.cbegin();

	while (thisItr != this->cend()) {
		if (*thisItr != *rhsItr)
			return false;

		++thisItr;
		++rhsItr;
	}
	
	return true;
}

void SingleLinkedList::append(const int& value)
{
	Node* newNode = createNode(value);
	if (m_head == NULL) {
		m_head = newNode;
		m_tail = m_head;	
	} else {
		m_tail->next = newNode;
		m_tail = newNode;	
	}
	
}

void SingleLinkedList::prepend(const int& value)
{
	Node* newNode = createNode(value);

	if (m_head == NULL) {
		m_head = newNode;
		m_tail = m_head;	
	} else {
		newNode->next = m_head;
		m_head = newNode;	
	}
}

void SingleLinkedList::insert(const int& value, SingleLinkedList::Iterator pos)
{
	if (pos.n == m_head)
		prepend(value);
	else if (pos.n == m_tail)
		append(value);
	else {
		Node* newNode = createNode(value);
		Node* node = m_head;
		while (node->next != pos.n)
			node = node->next;

		newNode->next = node->next;
		node->next = newNode;
	}
}

bool SingleLinkedList::remove(SingleLinkedList::Iterator pos)
{
	Node* del = pos.n;
	if (del == NULL)
		return false;
	else if (del == m_head)
		return removeFirst();
	else if (del == m_tail)
		return removeLast();
	else {
		Node* t = m_head;
		while (t->next != del)
			t = t->next;

		t->next = del->next;
		removeNode(del);	

		return true;
	}	
}

bool SingleLinkedList::remove(const int& value)
{
	SingleLinkedList::Iterator itr = find(value);
	if (itr.hasValue()) {
		return remove(itr);
	}

	return false;
}

bool SingleLinkedList::removeFirst()
{
	if (m_head == NULL)
		return false;

	Node* del = m_head;
	m_head = m_head->next;
	removeNode(del);	

	if (m_head == NULL)
		m_tail = NULL;

	return true;
}

bool SingleLinkedList::removeLast()
{
	if (m_tail == NULL)
		return false;

	if (m_head->next == NULL) {
		removeNode(m_head);
		m_head = m_tail = NULL;
	} else {
		Node* del = m_tail;
		Node* t = m_head;
		while (t->next != m_tail)
			t = t->next;

		m_tail = t;
		m_tail->next = NULL;
		removeNode(del);
	}

	return true;
}

void SingleLinkedList::replace(const int& oldValue, const int& newValue)
{
	SingleLinkedList::Iterator itr = find(oldValue);
	if (itr.hasValue()) {
		*itr = newValue;
	}
}

SingleLinkedList::Iterator SingleLinkedList::find(const int& value)
{
	SingleLinkedList::Iterator itr = this->begin();
	while (itr != this->end()) {
		if (*itr == value)
			return itr;

		++itr;
	}

	return SingleLinkedList::Iterator(NULL);
}	

SingleLinkedList::Iterator SingleLinkedList::begin()
{
	return SingleLinkedList::Iterator(m_head);
}

SingleLinkedList::Iterator SingleLinkedList::end()
{
	return SingleLinkedList::Iterator(NULL);
}

SingleLinkedList::ConstIterator SingleLinkedList::cbegin() const
{
	return SingleLinkedList::ConstIterator(m_head);
}

SingleLinkedList::ConstIterator SingleLinkedList::cend() const
{
	return SingleLinkedList::ConstIterator(NULL);
}


}

#endif // DATASTRUCTURE_SINGLELINKEDLIST_H
