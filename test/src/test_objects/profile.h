#ifndef PROFILE_H
#define PROFILE_H

#include <string>

namespace Model
{

class Profile
{
public:
	Profile();
	Profile(const std::string& firstName, const std::string& lastName);
	~Profile();
	Profile(const Profile& profile);
	Profile& operator=(const Profile& profile);

	bool operator==(const Profile& rhs);

	// accessors
	const std::string& firstName() const;
	void setFirstName(const std::string& firstName);
	const std::string& lastName() const;
	void setLastName(const std::string& lastName);

private:
	std::string m_firstName;
	std::string m_lastName;
};

}

#endif //PROFILE_H
