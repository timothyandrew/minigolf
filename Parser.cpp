/*
 * Parser.cpp
 *
 *  Created on: Oct 13, 2008
 *      Author: the1schwartz
 */

#include <iostream>
#include <map>
#include "Parser.h"

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


string parseFile(const char* file, vector<Hole*>* hs)
{
	ifstream inp_file(file);
	map<int, Tile*> t_map;
	vector<Tile*>* ts;
	Tee* t;
	Cup* c;
	Hole* h;
	int p;
	string n;
	string c_n;

	if (inp_file.is_open())
	{
		while (! inp_file.eof() )
		{
			string buf,s;
			getline (inp_file,s);
			stringstream ss(s);
			vector<string> *v = new vector<string>;

			while(ss >> buf)
			{
				v->push_back(buf);
			}

			string keyword = v->at(0);
			//cout << keyword << endl;

			if(keyword == "course")
			{
				string::size_type found = s.find_first_of("\"");
				string::size_type last = s.find_last_of("\"");
				if(found != string::npos)
				{
					c_n = s.substr(found+1,last-found-1);
				}
				else
				{
					c_n = v->at(1);
				}
			}
			else if(keyword == "begin_hole")
			{
				ts = new vector<Tile*>;
				t = new Tee();
				c = new Cup();
				h = new Hole();
				t_map.clear();
			}
			else if(keyword == "end_hole")
			{
				for( map<int, Tile*>::iterator iter = t_map.begin(); iter != t_map.end(); ++iter )
				{
					ts->push_back((*iter).second);
				}
				h->create(c,t,p,n,ts);
				hs->push_back(h);
			}
			else if(keyword == "par")
			{
				p = atoi(v->at(1).c_str());
			}
			else if(keyword == "name")
			{
				string::size_type found = s.find_first_of("\"");
				string::size_type last = s.find_last_of("\"");
				if(found != string::npos)
				{
					n = s.substr(found+1,last-found-1);
				}
				else
				{
					n = v->at(1);
				}
			}
			else if(keyword == "tile")
			{
				Tile* t = new Tile;
				t->create(v);

				t_map[t->id] = t;
			}
			else if(keyword == "tee")
			{
				t->create(v);
			}
			else if(keyword == "cup")
			{
				c->create(v);
			}
		}
		inp_file.close();
	}

	return c_n;
}
