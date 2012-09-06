/******************************************************************************
 Title: Movie.cc
 Author: Robert O'Connor, Nick Trippel
 Created on: September 2, 2012
 Description: Represents a Movie
 *******************************************************************************/

#include "Movie.h"
#include "Actor.h"


#include <string>
#include <vector>
#include <iostream>

using namespace std;

Movie::Movie(string name) :
		name(name) {
}

Movie::Movie() {
}

string Movie::getName() {
	return this->name;
}

void Movie::setName(string name) {
	this->name = name;
}
