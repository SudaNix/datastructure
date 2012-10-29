#include <iostream>
#include "student.h"
#include "profile.h"

using Model::Student;
using Model::Profile;

void printStudent(const Student& s)
{
	std::cout << "id: " << s.id() << std::endl;
	std::cout << "first name: " << s.profile()->firstName() << std::endl;
	std::cout << "last name: " << s.profile()->lastName() << std::endl;
}

int main()
{
	Student ahmad;
	Profile* ahmad_profile = new Profile("Ahmad", "Essam");
	ahmad.setProfile(ahmad_profile);
	ahmad.setId(10);
	
	Student wajdy = ahmad;
	
	wajdy.setId(20);
	wajdy.profile()->setFirstName("Wajdy");

	Student waleed;
	waleed = wajdy;
	waleed.profile()->setFirstName("Waleed");
	waleed.setId(30);
		
	printStudent(ahmad);
	printStudent(wajdy);
	printStudent(waleed);
	
	return 0;
}
