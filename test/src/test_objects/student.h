#ifndef STUDENT_H
#define STUDENT_H

#include "profile.h"

namespace Model
{

class Student 
{
public:
	Student();
	Student(int id, Profile* profile);
	~Student();
	Student(const Student& rhs);
	Student& operator=(const Student& rhs);

	bool operator==(const Student& rhs);

	// accessors
	int id() const { return m_id; }
	void setId(int id) { m_id = id; }

	Profile* profile() const { return m_profile; }
	void setProfile(Profile* profile) { delete m_profile; m_profile = profile; }

private:
	int m_id;
	Profile* m_profile;	
};
}

#endif //STUDENT_H
