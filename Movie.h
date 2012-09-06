/******************************************************************************
 Title: Movie.h
 Author: Robert O'Connor, Nick Trippel
 Created on: September 2, 2012
 Description: Represents a Movie
 *******************************************************************************/


#ifndef _MOVIE_H
#define _MOVIE_H

#include <vector>
#include <string>

class Movie {
	public:
		Movie(std::string name);
		Movie();
		std::string getName();
		void setName(std::string name);
	private:
		std::string name;
};

#endif
