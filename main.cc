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

#include "Actor.h"
#include "Movie.h"
using namespace std;
/**
 * Display the menu allowing for a more pleasing user experience.
 * @param done the sentinel value (passed by reference) to determine when to terminate the program.
 */
void displayMenu(bool &done);
vector<Movie> findMoviesFor(string actorName, string fileName);
vector<Actor> findCostars(string actorName, vector<Movie> movies, string fileName);
vector<Actor> findActorsIn(string movie, string fileName);

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
	cout << "2010 Movie DB." << endl;
	cout << "1. Find actors" << endl;
	cout << "2. Find actresses" << endl;
	cout << "3. Find costars (actors)" << endl;
	cout << "4. Find costars (actresses)" << endl;
	cout << "Please select an option (or type\"0\" to end the program: ";
	cin>>response;
	cout<<response<<endl;
	switch (response) {
		case 1: {
			cout << "Name of movie? ";
			string name;
			getline(cin, name);
			vector<Actor> actors = findActorsIn(name, "actors.2010.list");
			cout << "Actors in " << name << ": " << endl;
			for(int i = 0;i < actors.size();i++) {
				cout << " * " << actors[i].getFirstName().append(" ").append(
						actors[i].getLastName());
			}
			break;
		}
		case 2: {
			cout << "Name of movie? ";
			string name;
			getline(cin, name);
			vector<Actor> actors = findActorsIn(name, "actresses.2010.list");
			cout << "Actresses in " << name << ": " << endl;
			for(int i = 0;i < actors.size();i++) {
				cout << " * " << actors[i].getFirstName().append(" ").append(
						actors[i].getLastName());
			}
			break;
		}
		case 3: {
			cout << "Name of actor? ";
			string name;
			getline(cin, name);
			vector<Actor> costars = findCostars(name, findMoviesFor(name, "actors.2010.list"),
					"actors.2010.list");
			cout << "The following are costars of " << name << ": " << endl;
			for(int i = 0;i < costars.size();i++) {
				cout << " * " << costars[i].getFirstName().append(" ").append(
						costars[i].getLastName());
			}
			break;
		}

		case 4: {
			cout << "Name of actresses? ";
			string name;
			getline(cin, name);
			vector<Actor> costars = findCostars(name, findMoviesFor(name, "actresses.2010.list"),
					"actresses.2010.list");
			cout << "The following are costars of " << name << ": " << endl;
			for(int i = 0;i < costars.size();i++) {
				cout << " * " << costars[i].getFirstName().append(" ").append(
						costars[i].getLastName());
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
	while (file) {
		string line = "";
		string fullName = "";
		while (getline(file, line)) {
			if (line.find(',') != string::npos) { // actor or actress name
				string last = line.substr(0, line.find_first_of(",") + 2);
				string first = line.substr(last.size(), line.size());
				fullName = first.append(" ").append(last);
			} else if (line.find('(') != string::npos) { // movie name
				string movieName = line.substr(0, line.find('('));
				Movie movie(movieName);
				if (actor == fullName) {
					movies.push_back(movie);
				}
			}
		}
		file.close();
	}
	return movies;
}

vector<Actor> findCostars(string actor, vector<Movie> movies, string fileName) {
	vector<Actor> costars;
	for(int i = 0;i < movies.size();i++) {
		ifstream file(fileName.c_str());
		string line = "";
		string fullName = "";
		string first, last;
		while (getline(file, line)) {
			if (line.find(',') != string::npos) { // actor or actress name
				last = line.substr(0, line.find_first_of(",") + 2);
				first = line.substr(last.size(), line.size());
				fullName = first.append(" ").append(last);
			} else if (line.find('(') != string::npos) { // movie name
				string movieName = line.substr(0, line.find('('));
				Movie movie(movieName);
				if (actor == fullName && movies[i].getName() == movieName) {
					costars.push_back(Actor(first, last));
				}
			}
		}
		file.close();
	}
	return costars;
}

vector<Actor> findActorsIn(string movie, string fileName) {
	vector<Actor> actors;
	ifstream file(fileName.c_str());
	string line = "";
	string fullName = "";
	string first, last;
	while (getline(file, line)) {
		if (line.find(',') != string::npos) { // actor or actress name
			last = line.substr(0, line.find_first_of(",") + 2);
			first = line.substr(last.size(), line.size());
			fullName = first.append(" ").append(last);
		} else if (line.find('(') != string::npos) { // movie name
			string movieName = line.substr(0, line.find('('));
			if (movieName == movie) {
				actors.push_back(Actor(first, last));
			}
		}
		file.close();
	}
	return actors;
}
