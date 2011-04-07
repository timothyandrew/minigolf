/*
 * Parser.h
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Point.h"
#include "Tile.h"
#include "Tee.h"
#include "Cup.h"
#include "Hole.h"

using namespace std;

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters = " ");
string parseFile(const char* file, vector<Hole*>* hs);

#endif /* PARSER_H_ */
