#define BOOST_TEST_MODULE SingleLinkedList
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../../include/singlelinkedlist.h"

using namespace DataStructure;

BOOST_AUTO_TEST_CASE(always_true)
{
	BOOST_CHECK_EQUAL(1+1, 2);
}

BOOST_AUTO_TEST_CASE(Append_OneValue)
{
	SingleLinkedList linkedlist;
	linkedlist.append(10);
	BOOST_CHECK_EQUAL(linkedlist.size(), 1);
	SingleLinkedList::Iterator i = linkedlist.begin();
	BOOST_CHECK_EQUAL(*i, 10);
	BOOST_CHECK_EQUAL(linkedlist.count(), 1);
	BOOST_CHECK_EQUAL(linkedlist.isEmpty(), false);
}

BOOST_AUTO_TEST_CASE(Append_MoreThanOneValue)
{
	SingleLinkedList linkedlist;
	linkedlist.append(10);
	linkedlist.append(20);

	BOOST_CHECK_EQUAL(linkedlist.size(), 2);
	BOOST_CHECK_EQUAL(linkedlist.count(), 2);
	BOOST_CHECK_EQUAL(linkedlist.isEmpty(), false);

	SingleLinkedList::Iterator i = linkedlist.begin();
	BOOST_CHECK_EQUAL(*i, 10);
	++i;
	BOOST_CHECK_EQUAL(*i, 20);
}

BOOST_AUTO_TEST_CASE(Prepend_OneValue)
{
	SingleLinkedList linkedlist;
	linkedlist.prepend(10);
	BOOST_CHECK_EQUAL(linkedlist.size(), 1);
	SingleLinkedList::Iterator i = linkedlist.begin();
	BOOST_CHECK_EQUAL(*i, 10);
	BOOST_CHECK_EQUAL(linkedlist.count(), 1);
	BOOST_CHECK_EQUAL(linkedlist.isEmpty(), false);
}

BOOST_AUTO_TEST_CASE(Prepend_MoreThanOneValue)
{
	SingleLinkedList linkedlist;
	linkedlist.prepend(10);
	linkedlist.prepend(20);

	BOOST_CHECK_EQUAL(linkedlist.size(), 2);
	BOOST_CHECK_EQUAL(linkedlist.count(), 2);
	BOOST_CHECK_EQUAL(linkedlist.isEmpty(), false);

	SingleLinkedList::Iterator i = linkedlist.begin();
	BOOST_CHECK_EQUAL(*i, 20);
	++i;
	BOOST_CHECK_EQUAL(*i, 10);
}

BOOST_AUTO_TEST_CASE(Insert_OneValueAtHead)
{
	SingleLinkedList linkedlist;
	linkedlist.insert(10, linkedlist.begin());
	BOOST_CHECK_EQUAL(linkedlist.size(), 1);
	SingleLinkedList::Iterator i = linkedlist.begin();
	BOOST_CHECK_EQUAL(*i, 10);
	BOOST_CHECK_EQUAL(linkedlist.count(), 1);
	BOOST_CHECK_EQUAL(linkedlist.isEmpty(), false);
}

BOOST_AUTO_TEST_CASE(Insert_OneValueAtPos)
{
	SingleLinkedList linkedlist;
	for (int i=0; i<10; ++i)
		linkedlist.append(i);

	linkedlist.insert(100, linkedlist.find(8));
	BOOST_CHECK_EQUAL(linkedlist.size(), 11);

	int i = 0;
	SingleLinkedList::Iterator itr = linkedlist.begin();
	while (itr != linkedlist.end()) {
		BOOST_CHECK_EQUAL(*itr, i++);
		++itr;
	}
}

/*BOOST_AUTO_TEST_CASE(Empty_Constructor)
{
	SingleLinkedList* linkedlist = new SingleLinkedList();
	BOOST_CHECK_EQUAL(linkedlist->size(), 0);
	BOOST_CHECK_EQUAL(linkedlist->count(), 0);
	BOOST_CHECK_EQUAL(linkedlist->isEmpty(), true);

	delete linkedlist;
}*/
