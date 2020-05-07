#include "Movie.h"
#include <sstream>
#include <iostream>
#include<vector>
#include <iomanip>
using namespace std;
void Movie::ispis()
{
	stringstream ss;
	if (revenue != 0) {
		
		ss << "Naziv: " << title << endl << "Opis: " << description << endl << "Godina izdanja: " << year << endl << "Zarada: " <<setprecision(10) << revenue << " USD"<<endl;
	}
	else {
		ss << "Naziv: " << title << endl << "Opis: " << description << endl << "Godina izdanja: " << year << endl << "Zarada: N/A"<<endl;
	}
	cout << ss.str() << endl;
}

void Movie::set_rank(string rank)
{
	this->rank = rank;
}

void Movie::set_title(string title)
{
	this->title = title;
}

void Movie::set_genre(string genree)
{
	genre.push_back(genree);

}

void Movie::set_description(string description)
{
	this->description = description;
}

void Movie::set_director(string director)
{
	this->director = director;
}

void Movie::set_actors(string actorss)
{
	actors.push_back(actorss);
}

void Movie::set_year(int year)
{
	this->year = year;
}

void Movie::set_runtime(int runtime)
{
	this->runtime = runtime;
}

void Movie::set_votes(int votes)
{
	this->votes = votes;
}

void Movie::set_metascore(int metascore)
{
	this->metascore = metascore;
}

void Movie::set_revenue(double revenue)
{
	this->revenue = revenue*1000000;
}

void Movie::set_rating(double rating)
{
	this->rating = rating;
}

void Movie::print_genre()
{
	for (auto i = genre.begin(); i!= genre.end(); ++i)
		cout << *i << " ";
}

vector<string> Movie::get_genre()
{
	return genre;
}

int Movie::get_year()
{
	return year;
}

string Movie::get_description()
{
	return description;
}

int Movie::get_metascore()
{
	return metascore;
}

double Movie::get_rating()
{
	return rating;
}

vector<string> Movie::get_actors()
{
	return actors;
}

double Movie::get_revenue()
{
	return revenue;
}

int Movie::get_runtime()
{
	return runtime;
}

int Movie::get_votes()
{
	return votes;
}

string Movie::get_rank()
{
	return rank;
}

string Movie::get_title()
{
	return title;
}

string Movie::get_director()
{
	return director;
}
