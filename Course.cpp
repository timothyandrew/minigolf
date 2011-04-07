/*
 * Course.cpp
 *
 *  Created on: Oct 20, 2008
 *      Author: the1schwartz
 */

#include "Course.h"
#include "Parser.h"

Course::Course()
{
}

Course::~Course()
{
}

void Course::create(const char* file)
{
	holes = new vector<Hole*>;
	parseFile(file, holes);
}
