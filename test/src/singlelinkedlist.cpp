#define BOOST_TEST_MODULE SingleLinkedList
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../../include/singlelinkedlist.h"

BOOST_AUTO_TEST_CASE(always_true)
{
	BOOST_CHECK_EQUAL(1+1, 2);
}

BOOST_AUTO_TEST_CASE(test_ctor)
{
	DataStructure::SingleLinkedList* linkedlist = new DataStructure::SingleLinkedList();
	BOOST_CHECK_EQUAL(linkedlist->size(), 0);
}
