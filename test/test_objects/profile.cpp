#include "profile.h"

namespace Model
{

Profile::Profile()
{}

Profile::Profile(const std::string& firstName, const std::string& lastName) :
	m_firstName(firstName),
	m_lastName(lastName)
{}

Profile::~Profile()
{}

Profile::Profile(const Profile& rhs) :
	m_firstName(rhs.m_firstName),
	m_lastName(rhs.m_lastName)
{}

Profile& Profile::operator=(const Profile& rhs)
{
	if (this == &rhs)
		return *this;

	m_firstName = rhs.m_firstName;
	m_lastName = rhs.m_lastName;

	return *this;
}

bool Profile::operator==(const Profile& rhs)
{
	return ( (m_firstName == rhs.m_firstName) && (m_lastName == rhs.m_lastName) );
}

const std::string& Profile::firstName() const
{
	return m_firstName;
}

void Profile::setFirstName(const std::string& firstName)
{
	m_firstName = firstName;
}

const std::string& Profile::lastName() const
{
	return m_lastName;
}

void Profile::setLastName(const std::string& lastName)
{
	m_lastName = lastName;
}

}
