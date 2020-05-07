#pragma once
#include <string>
#include <vector>
using namespace std;
class Movie
{
private:
	string rank,title,description,director;
	int year,runtime,votes,metascore;
	double rating,revenue;
	vector<string> genre;
	vector<string> actors;
public:
	void ispis();
	void set_rank(string rank);
	void set_title(string title);
	void set_genre(string genree);
	void set_description(string description);
	void set_director(string director);
	void set_actors(string actorss);

	void set_year(int year);
	void set_runtime(int runtime);
	void set_votes(int votes);
	void set_metascore(int metascore);

	void set_revenue(double revenue);
	void set_rating(double rating);

	void print_genre();

	vector<string> get_genre();
	int get_year();
	string get_description();
	int get_metascore();
	double get_rating();

	vector<string> get_actors();
	double get_revenue();
	int get_runtime();
	int get_votes();
	string get_rank();
	string get_title();
	string get_director();

};

