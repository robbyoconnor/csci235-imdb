/******************************************************************************
 Title: Actor.h
 Author: Robert O'Connor, Nick Trippel
 Created on: September 2, 2012
 Description: Represents a Actor
 *******************************************************************************/

#ifndef _ACTOR_H
#define _ACTOR_H

#include <string>

#include "Movie.h"

#include <vector>

class Actor {
	public:
		Actor(std::string firstName, std::string lastName);
		Actor();
		std::string getFirstName();
		void setFirstName(std::string firstName);
		std::string getLastName();
		void setLastName(std::string lastName);
		std::vector<Movie> getMovies();
		void addMovie(Movie movie);
	private:
		std::string firstName;
		std::string lastName;
		std::vector<Movie> movies;

};

#endif
