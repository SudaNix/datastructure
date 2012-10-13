#include "student.h"
#include "profile.h"

namespace Model
{

Student::Student() :
	m_id(0), m_profile(new Profile())
{}

Student::Student(int id, Profile* profile) :
	m_id(id), m_profile(profile)
{}

Student::~Student()
{
	delete m_profile;
	m_profile = 0;
}

Student::Student(const Student& rhs) :
	m_id(rhs.m_id)
{
	m_profile = new Profile(*(rhs.m_profile));
}

Student& Student::operator=(const Student& rhs)
{
	if (this == &rhs)
		return *this;
	
	m_id = rhs.m_id;

	delete m_profile;
	m_profile = new Profile(*(rhs.m_profile));

	return *this;
}

}
