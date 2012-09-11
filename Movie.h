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
		/**
		 * Used to construct a movie by setting the name...
		 * @param name
		 */
		Movie(std::string name);
		/**
		 * Default ctor
		 */
		Movie();
		/**
		 * Get the name
		 * @return the name of the movie
		 */
		std::string getName();

		/**
		 * Set the name...
		 * @param name the name of the movie
		 */
		void setName(std::string name);
	private:
		std::string name;
};

#endif
