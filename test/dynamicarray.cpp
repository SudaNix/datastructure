#define BOOST_TEST_MODULE DynamicArray
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "../include/dynamicarray.h"


BOOST_AUTO_TEST_CASE(test_empty_ctor)
{
	DataStructure::DynamicArray array(4);
	BOOST_CHECK_EQUAL(array.size(), 4);

	array[2] = 100;

	BOOST_CHECK_EQUAL(array[3], 0);
	BOOST_CHECK_EQUAL(array[2], 100);
	BOOST_CHECK_EQUAL(array[1], 0);
	BOOST_CHECK_EQUAL(array[0], 0);
}

BOOST_AUTO_TEST_CASE(test_array_size_ctor)
{
	DataStructure::DynamicArray array(100);
	BOOST_CHECK_EQUAL(array.size(), 100);

	array.append(5);
	BOOST_CHECK_EQUAL(array.size(), 101);

	array[0] = 1;
	BOOST_CHECK_EQUAL(array.size(), 101);

	array.insert(1, 10);
	BOOST_CHECK_EQUAL(array.size(), 102);
}

BOOST_AUTO_TEST_CASE(test_cctor)
{
	DataStructure::DynamicArray a(5);
	a[4] = 10;

	DataStructure::DynamicArray b = a;

	b[2] = 2;

	BOOST_CHECK_EQUAL(a[4], 10);

	BOOST_CHECK_EQUAL(b.size(), 5);
	BOOST_CHECK_EQUAL(b[4], 10);	
	BOOST_CHECK_EQUAL(b[3], 0);
	BOOST_CHECK_EQUAL(b[2], 2);
	BOOST_CHECK_EQUAL(b[1], 0);
}

BOOST_AUTO_TEST_CASE(test_assignment_operator)
{
	DataStructure::DynamicArray a(10);
	DataStructure::DynamicArray b(2);

	a[0] = 100;
	a[9] = 1000;

	b[0] = 200;
	b[1] = 300;

	BOOST_CHECK_EQUAL(a.size(), 10);
	BOOST_CHECK_EQUAL(b.size(), 2);

	BOOST_CHECK_EQUAL(a[0], 100);
	BOOST_CHECK_EQUAL(a[9], 1000);

	BOOST_CHECK_EQUAL(b[0], 200);
	BOOST_CHECK_EQUAL(b[1], 300);

	b = a;

	BOOST_CHECK_EQUAL(a.size(), 10);
	BOOST_CHECK_EQUAL(b.size(), 10);
	BOOST_CHECK_EQUAL(a[0], 100);
	BOOST_CHECK_EQUAL(a[9], 1000);
	BOOST_CHECK_EQUAL(b[0], 100);
	BOOST_CHECK_EQUAL(b[9], 1000);
}

BOOST_AUTO_TEST_CASE(test_get_value_by_at)
{
	DataStructure::DynamicArray a;
	for (int i=0; i<5; ++i)
		a.append(i);

	for (int i=0; i<5; ++i)
		BOOST_CHECK_EQUAL(a.at(i), i);
}

BOOST_AUTO_TEST_CASE(test_prepend_value)
{
	DataStructure::DynamicArray a;
	for (int i=0; i<10; ++i)
		a.prepend(i);

	int p[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

	BOOST_CHECK_EQUAL(a.size(), 10);
	for (int i=0; i<10; ++i) {
		BOOST_CHECK_EQUAL(a[i], p[i]);
	}
}

BOOST_AUTO_TEST_CASE(test_replace_value)
{
	DataStructure::DynamicArray a(2);

	a[0] = 10;
	a.replace(a[0]*a[0], 1);

	BOOST_CHECK_EQUAL(a.at(0), 10);
	BOOST_CHECK_EQUAL(a.at(1), 100);
}

BOOST_AUTO_TEST_CASE(test_remove_element)
{
	DataStructure::DynamicArray a(1);	
	BOOST_CHECK_EQUAL(a.size(), 1);
	
	a.remove(0);
	BOOST_CHECK_EQUAL(a.size(), 0);

	a.append(100);
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a[0], 100);

	a.insert(200, 1);
	a.insert(300, 2);
	a.prepend(10);
	BOOST_CHECK_EQUAL(a.size(), 4);
	BOOST_CHECK_EQUAL(a[0], 10);
	BOOST_CHECK_EQUAL(a[1], 100);
	BOOST_CHECK_EQUAL(a[2], 200);
	BOOST_CHECK_EQUAL(a[3], 300);
	
	// Now remove elements
	try
	{
		a.remove(100);		
	}
	catch (...)
	{
		std::cerr << "Unable to remove out of range element" << std::endl;
	}


	a.remove(3);
	BOOST_CHECK_EQUAL(a.size(), 3);
	BOOST_CHECK_EQUAL(a[0], 10);
	BOOST_CHECK_EQUAL(a[1], 100);
	BOOST_CHECK_EQUAL(a[2], 200);
	
	a.remove(0);
	BOOST_CHECK_EQUAL(a.size(), 2);
	BOOST_CHECK_EQUAL(a.at(0), 100);
	BOOST_CHECK_EQUAL(a.at(1), 200);

	a.remove(0);
	a.remove(0);
	BOOST_CHECK_EQUAL(a.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_find_value)
{
	DataStructure::DynamicArray a(10);
	a[5] = 100;

	BOOST_CHECK_EQUAL(a.find(100), 5);
	BOOST_CHECK_EQUAL(a.find(103), -1);
}

BOOST_AUTO_TEST_CASE(test_iterator_begin_value)
{
	DataStructure::DynamicArray array(0);
	array.append(1);

	DataStructure::DynamicArray::Iterator itr = array.begin();
	BOOST_CHECK_EQUAL(*itr, 1);
}

BOOST_AUTO_TEST_CASE(test_iterator_end_value)
{
	DataStructure::DynamicArray array(5);
	array.append(1);

	DataStructure::DynamicArray::Iterator itr = array.end();
	--itr;
	BOOST_CHECK_EQUAL(*itr, 1);
}

BOOST_AUTO_TEST_CASE(test_iterator_modify_value)
{
	DataStructure::DynamicArray array(0);
	array.append(1);

	DataStructure::DynamicArray::Iterator itr = array.begin();
	*itr = 10;

	BOOST_CHECK_EQUAL(*itr, 10);
}

BOOST_AUTO_TEST_CASE(test_print_array_values)
{
	DataStructure::DynamicArray array(1);
	array.append(2);
	array.append(4);
	array.insert(1, 1);

	DataStructure::DynamicArray::Iterator itr = array.begin();
	BOOST_CHECK_EQUAL(*itr, 0);
	++itr;
	BOOST_CHECK_EQUAL(*itr, 1);
	++itr;
	BOOST_CHECK_EQUAL(*itr, 2);
	++itr;
	BOOST_CHECK_EQUAL(*itr, 4);
}

BOOST_AUTO_TEST_CASE(AlwaysSuccess)
{
	BOOST_CHECK(1);
}
