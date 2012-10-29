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

		list.append(1);
		list.append(2);
		list.append(3);
	
		list.debug();
		std::cout << "count: " << list.count() << std::endl;


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
