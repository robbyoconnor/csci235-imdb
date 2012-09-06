/******************************************************************************
 Title: Actor.cc
 Author: Robert O'Connor, Nick Trippel
 Created on: September 2, 2012
 Description: Represents an Actor
 *******************************************************************************/

#include "Actor.h"
#include <string>
#include <vector>
#include "Movie.h"

using namespace std;

Actor::Actor(string firstName, string lastName) :
		firstName(firstName), lastName(lastName) {
}

Actor::Actor() {
}
string Actor::getFirstName() {
	return this->firstName;
}

void Actor::setFirstName(string fName) {
	this->firstName = fName;
}

string Actor::getLastName() {
	return this->lastName;
}

void Actor::setLastName(string lName) {
	this->lastName = lName;
}
vector<Movie> Actor::getMovies() {
	return this->movies;
}

void Actor::addMovie(Movie movie) {
	this->movies.push_back(movie);
}
