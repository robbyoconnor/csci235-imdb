/******************************************************************************
 Title: main.cc
 Author: Robert O'Connor
 Created on: July 22, 2012
 Description: Entry point for the application which transcribes a DNA strand
 to an RNA strand and provides for some other handy things.
 Usage: make (will botb build and run).
 Build with: make
 Modifications:
 *******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>

#include "Actor.h"
#include "Movie.h"
using namespace std;
/**
 * Display the menu allowing for a more pleasing user experience.
 * @param done the sentinel value (passed by reference) to determine when to terminate the program.
 */
void displayMenu(bool &done);

/**
 * This is a helper function to help determine the costars of a given actor or actress.
 * @param actorName the name of the actor or actress
 * @oaram fileName the file name (utility purpose)
 * @return a vector containing the Movies for a given actor. or actress
 */
vector<Movie> findMoviesFor(string actorName, string fileName);

/**
 * Finds all the actors who ever acted with a given actor or actress
 * @param actorName the name of the actor or actress
 * @param movies (a vector of the Movies for a given actor or actress)
 * @param fileName the file name (purely utility purpose
 */
vector<string> findCostars(string actorName, vector<Movie> movies, string fileName);

/**
 * Finds all the actors who were in a given movie.
 * @param movie the movie you wish to get the actors for (note actors and actresses)
 * @param fileName the file name (purely utility purpose
 */
vector<string> findActorsIn(string movie, string fileName);

/**
 * Remove white space
 * @param s the string to trim out the white space
 */
string removeSpaces(const string &s);
/**
 * Trim a string...because we all like neatly trimmed strings...amiright?!
 * @param s the string to trim (returned and passed by reference).
 */
void trim(string &s);

/**
 * Find the costars for a given actor
 *
 * @param the actor to search for
 * @param whether or not are an actress
 */
int main(int argc, char* argv[]) {
	bool done = false;
	do {
		displayMenu(done);
	} while (!done);
}

void displayMenu(bool &choice) {
	int response;
	cout << endl << endl;
	cout << "2010 Movie DB." << endl;
	cout << "1. Find actors" << endl;
	cout << "2. Find actresses" << endl;
	cout << "3. Find costars (actors)" << endl;
	cout << "4. Find costars (actresses)" << endl;
	cout << "Please select an option (or type\"0\" to end the program: ";
	string input;
	getline(cin, input);
	response = atoi(input.c_str());
	switch (response) {
		case 1: {
			cout << "Name of movie? ";
			string name;
			getline(cin, name);
			vector<string> actors = findActorsIn(name, "actors.2010.list");
			if (actors.size() == 0) {
				cout << "No such movie was made in 2010 by that name!!!" << endl;
				break;

			} else {
				cout << "\nActors in " << name << ": " << endl;
				for(int i = 0;i < actors.size();i++) {
					cout << " * " << actors[i] << endl;
				}
			}
			break;
		}
		case 2: {
			cout << "Name of movie? ";
			string name;
			getline(cin, name);
			vector<string> actresses = findActorsIn(name, "actresses.2010.list");
			if (actresses.size() == 0) {
				cout << "No such movie was made in 2010 by that name!!!" << endl;

			} else {
				cout << "\nActresses in " << name << ": " << endl;
				for(int i = 0;i < actresses.size();i++) {
					cout << " * " << actresses[i] << endl;
				}
			}
			break;
		}
		case 3: {
			cout << "Name of actor? ";
			string name;
			getline(cin, name);
			vector<string> costars = findCostars(name, findMoviesFor(name, "actors.2010.list"),
					"actors.2010.list");
			cout << "\nThe following are costars of " << name << ": " << endl;
			for(int i = 0;i < costars.size();i++) {
				cout << " * " << costars[i] << endl;
			}
			break;
		}

		case 4: {
			cout << "Name of actresses? ";
			string name;
			getline(cin, name);
			vector<string> costars = findCostars(name, findMoviesFor(name, "actresses.2010.list"),
					"actresses.2010.list");
			if (costars.size() == 0) {
				cout << "No costars found." << endl;

			} else {
				cout << "\nThe following are costars of " << name << ": " << endl;
				for(int i = 0;i < costars.size();i++) {
					cout << " * " << costars[i] << endl;
				}
			}
			break;
		}
		case 0: {
			choice = true;
			break;

		}
		default: {
			cout << "Invalid choice! Please select only 1-4 or \"0\" to quit: ";
			cin >> response;
			break;
		}
	}
}

vector<Movie> findMoviesFor(string actor, string fileName) {
	ifstream file(fileName.c_str());
	vector<Movie> movies;
	string line = "";
	string fullName = "";
	while (file && getline(file, line)) {
		if (line.find("\t") == string::npos && line.find(',') != string::npos) {
			string last = line.substr(0, line.find_first_of(","));
			string first = line.substr(line.find_first_of(",") + 2, line.length());
			fullName = first.append(" ").append(last);
		} else if (line != "" && line.find("\t") != string::npos
				&& line.find("(") != string::npos) {
			string movieName = line.substr(0, line.find('('));
			trim(movieName);
			movieName = removeSpaces(movieName);
			Movie movie(movieName);
			if (actor == fullName) {
				movies.push_back(movie);
			}
		}
	}
	file.close();
	return movies;
}

vector<string> findCostars(string actor, vector<Movie> movies, string fileName) {
	vector<string> costars;
	for(int i = 0;i < movies.size();i++) {
		ifstream file(fileName.c_str());
		string line = "";
		string fullName = "";
		string first, last;
		while (file && getline(file, line)) {
			if (line.find("\t") == string::npos && line.find(',') != string::npos) {
				last = line.substr(0, line.find_first_of(","));
				first = line.substr(last.size() + 2, line.size());
				fullName = first.append(" ").append(last);
			} else if (line != "" && line.find("\t") != string::npos
					&& line.find("(") != string::npos) {
				string movieName = line.substr(0, line.find('('));
				trim(movieName);
				movieName = removeSpaces(movieName);
				if (movies[i].getName() == movieName) {
					if (actor != fullName) {
						costars.push_back(fullName);
						cout<<fullName<<endl;
					}
				}
			}
		}
		file.close();
	}
	return costars;
}

vector<string> findActorsIn(string movie, string fileName) {
	ifstream file(fileName.c_str());
	vector<string> actors;
	string line = "";
	string fullName = "";
	while (file && getline(file, line)) {
		if (line.find("\t") == string::npos && line.find(',') != string::npos) {
			string last = line.substr(0, line.find_first_of(","));
			string first = line.substr(line.find_first_of(",") + 2, line.length());
			fullName = first.append(" ").append(last);
		} else if (line != "" && line.find("\t") != string::npos
				&& line.find("(") != string::npos) {
			string movieName = line.substr(0,line.find('('));
			movieName = removeSpaces(movieName);
			trim(movieName);
			movieName = removeSpaces(movieName);
			if (movie==movieName) {
				actors.push_back(fullName);
			}
		}
	}
	file.close();
	return actors;
}

// removes tabs
void trim(string &s) {
	int k = 0;
	while ((k = s.find('\t', k)) != s.npos) {
		s.erase(k, 1);
	}
}
// taken from http://stackoverflow.com/a/6057320
string removeSpaces(const string &s) {
  int last = s.size() - 1;
  while (last >= 0 && s[last] == ' ' || s[last]=='\t')
    --last;
  return s.substr(0, last + 1);
}
