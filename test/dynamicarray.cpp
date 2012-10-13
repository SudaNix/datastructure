#define BOOST_TEST_MODULE DynamicArray
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include "../include/dynamicarray.h"
#include "test_objects/student.h"
#include "test_objects/profile.h"
	
typedef boost::mpl::list<int, long, double> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_template_empty_ctor, T, test_types)
{
	DataStructure::DynamicArray<T> array(4);
	BOOST_CHECK_EQUAL(array.size(), 4);

	array[2] = 100;

	BOOST_CHECK_EQUAL(array[3], 0);
	BOOST_CHECK_EQUAL(array[2], 100);
	BOOST_CHECK_EQUAL(array[1], 0);
	BOOST_CHECK_EQUAL(array[0], 0);
}

BOOST_AUTO_TEST_CASE(test_empty_ctor)
{
	DataStructure::DynamicArray<Model::Student> array(4);
	BOOST_CHECK_EQUAL(array.size(), 4);

	array[2].setId(100);
	array[2].setProfile(new Model::Profile("Ahmad", "Essam"));

	BOOST_CHECK_EQUAL(array[3].id(), 0);
	BOOST_CHECK_EQUAL(array[3].profile()->firstName(), "");
	BOOST_CHECK_EQUAL(array[3].profile()->lastName(), "");
	BOOST_CHECK_EQUAL(array[2].id(), 100);
	BOOST_CHECK_EQUAL(array[2].profile()->firstName(), "Ahmad");
	BOOST_CHECK_EQUAL(array[2].profile()->lastName(), "Essam");
	BOOST_CHECK_EQUAL(array[1].id(), 0);
	BOOST_CHECK_EQUAL(array[1].profile()->firstName(), "");
	BOOST_CHECK_EQUAL(array[1].profile()->lastName(), "");
	BOOST_CHECK_EQUAL(array[0].id(), 0);
	BOOST_CHECK_EQUAL(array[0].profile()->firstName(), "");
	BOOST_CHECK_EQUAL(array[0].profile()->lastName(), "");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_template_array_size_ctor, T, test_types)
{
	DataStructure::DynamicArray<T> array(100);
	BOOST_CHECK_EQUAL(array.size(), 100);

	array.append(5);
	BOOST_CHECK_EQUAL(array.size(), 101);

	array[0] = 1;
	BOOST_CHECK_EQUAL(array.size(), 101);

	array.insert(1, 10);
	BOOST_CHECK_EQUAL(array.size(), 102);
}

BOOST_AUTO_TEST_CASE(test_array_size_ctor)
{
	DataStructure::DynamicArray<Model::Student> array(100);
	BOOST_CHECK_EQUAL(array.size(), 100);

	array.append(Model::Student());
	BOOST_CHECK_EQUAL(array.size(), 101);

	array[0].setId(1);
	BOOST_CHECK_EQUAL(array.size(), 101);

	array.insert(Model::Student(42, new Model::Profile("Ahmad", "Essam")), 10);
	BOOST_CHECK_EQUAL(array.size(), 102);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_cctor, T, test_types)
{
	DataStructure::DynamicArray<T> a(5);
	a[4] = 10;

	DataStructure::DynamicArray<T> b = a;

	b[2] = 2;

	BOOST_CHECK_EQUAL(a[4], 10);

	BOOST_CHECK_EQUAL(b.size(), 5);
	BOOST_CHECK_EQUAL(b[4], 10);	
	BOOST_CHECK_EQUAL(b[3], 0);
	BOOST_CHECK_EQUAL(b[2], 2);
	BOOST_CHECK_EQUAL(b[1], 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_assignment_operator, T, test_types)
{
	DataStructure::DynamicArray<T> a(10);
	DataStructure::DynamicArray<T> b(2);

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

BOOST_AUTO_TEST_CASE_TEMPLATE(test_get_value_by_at, T, test_types)
{
	DataStructure::DynamicArray<T> a;
	for (int i=0; i<5; ++i)
		a.append(i);

	for (int i=0; i<5; ++i)
		BOOST_CHECK_EQUAL(a.at(i), i);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_prepend_value, T, test_types)
{
	DataStructure::DynamicArray<T> a;
	for (int i=0; i<10; ++i)
		a.prepend(i);

	T p[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

	BOOST_CHECK_EQUAL(a.size(), 10);
	for (int i=0; i<10; ++i) {
		BOOST_CHECK_EQUAL(a[i], p[i]);
	}
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_replace_value, T, test_types)
{
	DataStructure::DynamicArray<T> a(2);

	a[0] = 10;
	a.replace(a[0]*a[0], 1);

	BOOST_CHECK_EQUAL(a.at(0), 10);
	BOOST_CHECK_EQUAL(a.at(1), 100);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_remove_element, T, test_types)
{
	DataStructure::DynamicArray<T> a(1);	
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

BOOST_AUTO_TEST_CASE_TEMPLATE(test_find_value, T, test_types)
{
	DataStructure::DynamicArray<T> a(10);
	a[5] = 100;

	BOOST_CHECK_EQUAL(a.find(100), 5);
	BOOST_CHECK_EQUAL(a.find(103), -1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_iterator_begin_value, T, test_types)
{
	DataStructure::DynamicArray<T> array(0);
	array.append(1);

	typename DataStructure::DynamicArray<T>::Iterator itr = array.begin();
	BOOST_CHECK_EQUAL(*itr, 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_iterator_end_value, T, test_types)
{
	DataStructure::DynamicArray<T> array(5);
	array.append(1);

	typename DataStructure::DynamicArray<T>::Iterator itr = array.end();
	--itr;
	BOOST_CHECK_EQUAL(*itr, 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_iterator_modify_value, T, test_types)
{
	DataStructure::DynamicArray<T> array(0);
	array.append(1);

	typename DataStructure::DynamicArray<T>::Iterator itr = array.begin();
	*itr = 10;

	BOOST_CHECK_EQUAL(*itr, 10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_print_array_values, T, test_types)
{
	DataStructure::DynamicArray<T> array(1);
	array.append(2);
	array.append(4);
	array.insert(1, 1);

	typename DataStructure::DynamicArray<T>::Iterator itr = array.begin();
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
