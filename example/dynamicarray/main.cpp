#include <iostream>
#include <exception>
#include <stdexcept>
#include "../../include/dynamicarray.h"


int main(int argc, char** argv)
{
	try
	{
		DataStructure::DynamicArray array(1);
		array.append(4);
		array.append(7);

		array.insert(100, 0);

		std::cout << "Print values" << std::endl;

		for (DataStructure::DynamicArray::Iterator i = array.begin(); i != array.end(); ++i) {
			std::cout << *i << " " ;
		}

		std::cout << std::endl;

	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
