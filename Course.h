/*
 * Course.h
 *
 *  Created on: Oct 20, 2008
 *      Author: the1schwartz
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <string>
#include "Hole.h"

using namespace std;

class Course
{
public:
	Course();
	virtual ~Course();
	void create(const char* file);

	string name;
	vector<Hole*>* holes;
};

#endif /* COURSE_H_ */
