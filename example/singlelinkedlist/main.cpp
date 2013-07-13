#include <iostream>
#include <exception>
#include <stdexcept>
#include "../../include/singlelinkedlist.h"


int main(int argc, char** argv)
{
	try
	{
		DataStructure::SingleLinkedList list;
		std::cout << "count: " << list.count() << std::endl;

		list.insert(100, list.begin());
	
		DataStructure::SingleLinkedList::Iterator i = list.begin();
		while ( i != list.end() ) {
			std::cout << *i << " -> " ;
			++i;
		}

		std::cout << std::endl;

	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
