#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "Movie.h"
#include <stack>
#include <list>
#include <queue>

using namespace std;

template <class T>
T Convert(string temp) {
	T result;
	stringstream conv(temp);
	if (temp == "") return 0;
	conv >> result;

	return (result);
}

void vectorUMultimap(vector<string>& rijeciDescript, multimap<int, string, greater<>>& Multimap) {


	for (int i = 0; i < rijeciDescript.size(); i++)
	{
		bool stavi = true;

		for (auto& elm : Multimap) {


			if (elm.second == rijeciDescript[i]) {

				stavi = false;
				
			}
		}

		if (stavi) {
			int m = count(rijeciDescript.begin(), rijeciDescript.end(), rijeciDescript[i]);
			Multimap.insert(make_pair(m, rijeciDescript[i]));
		}
	}
}

void ispisTopPetRijeci(multimap<int, string, greater<>>& Multimap) {
	cout << "TOP 5 RIJECI KOJE JE POJAVLJUJU U DESCRIPTIONU: " << endl;
	int top = 0;
	for (auto& elm : Multimap) {

		if (top == 5)break;
		cout << elm.first << " " << elm.second << endl;
		top++;

	}

}
void rijeciUVektor(vector<string>& rijeciDescript, vector<Movie>& filmovi,vector<string> &nedozvoljene) {

	for (int i = 0; i < filmovi.size(); i++)
	{
		stringstream ss(filmovi[i].get_description());
		do {

			string word;
			ss >> word;

			transform(word.begin(), word.end(), word.begin(), tolower);

			if (word == "")continue;
			if (count(nedozvoljene.begin(), nedozvoljene.end(), word)) continue;
			if (word[word.size() - 1] == '.' || word[word.size() - 1] == ',') { word.erase(word.size() - 1); }//brisem zareze i tocke


			rijeciDescript.push_back(word);


		} while (ss);
	}




}

void print(Movie& film)
{
	 film.ispis();
}

int main() {

	stringstream s;
	s << "#### ##     ## ########  ########" << endl << " ##  ###   ### ##     ## ##     ## " << endl << " ##  #### #### ##     ## ##     ##" << endl << " ##  ## ### ## ##     ## ########" << endl << " ##  ##     ## ##     ## ##     ## " << endl << " ##  ##     ## ##     ## ##     ##" << endl << "#### ##     ## ########  ######## ";
	cout << s.str() << endl;



	cout << "IZBORNIK" << endl;
	cout << "Uputa: kada se pred vama pojavi 'IZBORNIK', unesite brojku koja se nalazi na pocetku reda opcije koju zelite! Hvala." << endl << endl;
	int d = 0;
	while (d != 1)
	{
		cout << "1   Unos putanje. ";
		cin >> d;
	}
	cin.ignore();
	cout << "	Unesite putanju: ";
	string putanja;
	getline(cin, putanja);
	int duljina = putanja.length();

	ofstream dat1("binarnaputanja.bin", ios_base::binary);
	if (!dat1) {


		cout << "Pogreska kod otvaranja datoteke.";
		return 1;
	}

	dat1.write((char*)(&duljina), sizeof(duljina));
	dat1.write(putanja.c_str(), duljina);
	dat1.close();
	cout << endl;
	cout << "IZBORNIK" << endl;
	d = 0;
	while (d != 1)
	{
		cout << "1   Unos podataka iz datoteke: ";
		cin >> d;
	}
	cin.ignore();


	ifstream dat2("binarnaputanja.bin", ios_base::binary);
	if (!dat2) {


		cout << "Pogreska kod otvaranja datoteke.";
		return 1;
	}
	int n;
	dat2.read((char*)(&n), sizeof(n));

	char* pchar = new char[n];

	dat2.read(pchar, n);
	string binarnaputanja = string(pchar, n);
	delete[] pchar;
	dat2.close();


	ifstream datoteka;
	datoteka.open(binarnaputanja);

	if (!datoteka)
	{
		cout << "Pogreska kod otvaranja datoteke." << endl;
		return 1;
	}



	vector<Movie> filmovi;
	string line;
	getline(datoteka, line);
	while (getline(datoteka, line))
	{

		Movie m;
		stringstream ss(line);
		string temp;

		getline(ss, temp, ';');
		m.set_rank(temp);

		getline(ss, temp, ';');
		m.set_title(temp);

		getline(ss, temp, ';');

		stringstream pomocni(temp);

		while (getline(pomocni, temp, ',')) {
			m.set_genre(temp);

		}


		getline(ss, temp, ';');
		m.set_description(temp);

		getline(ss, temp, ';');
		m.set_director(temp);



		getline(ss, temp, ';');
		stringstream pomocnii(temp);

		while (getline(pomocnii, temp, ',')) {
			m.set_actors(temp);

		}



		getline(ss, temp, ';');
		m.set_year(Convert<int>(temp));

		getline(ss, temp, ';');
		m.set_runtime(Convert<int>(temp));

		getline(ss, temp, ';');
		m.set_rating(Convert<double>(temp));


		getline(ss, temp, ';');
		m.set_votes(Convert<int>(temp));

		getline(ss, temp, ';');
		m.set_revenue(Convert<double>(temp));

		getline(ss, temp, ';');
		m.set_metascore(Convert<int>(temp));




		filmovi.push_back(m);
	}

	
	datoteka.close();
	system("cls");


	vector<string> nedozvoljene;
	ifstream dat("rijeci.txt");
	if (!dat) {
		cout << "Pogreska kod otvaranja datoteke." << endl;
		return 2;
	}
	string rec;
	while (dat >> rec) {
		nedozvoljene.push_back(rec);
	}
	dat.close();


	vector<string> rijeciDescript;
	rijeciUVektor(rijeciDescript, filmovi, nedozvoljene);


	multimap<int, string, greater<>> Multimap;
	vectorUMultimap(rijeciDescript, Multimap);
	ispisTopPetRijeci(Multimap);
	cout <<endl<< "IZBORNIK" << endl;
	d = 0;
	while (d != 1)
	{
		cout << "1 Kopiranje datoteke ";
		cin >> d;
	}
	cin.ignore();


	ifstream in;
	in.open(binarnaputanja);
	
	ofstream out("odredisnadatoteka.txt");

	if (!in || !out) {
		cout << "Pogreska kod otvaranja datoteke." << endl;
		return 1;
	}
izbor:
	cout << "	1 Obrnuti redoslijed" << endl;
	cout << "	2 Isti redoslijed ";
	
	d = 0;
	cin >> d;
	stack<string> stek;
	queue<string> red;
	string lajna;

	switch (d) {
	case 1:

		while (getline(in, lajna))
		{
			stek.push(lajna);
		}
		while (!stek.empty())
		{

			out << stek.top() << endl;
			stek.pop();
		}
		break;
	case 2:
		while (getline(in, lajna))
		{
			red.push(lajna);
		}
		while (!red.empty())
		{

			out << red.front() << endl;
			red.pop();
		}
		
		
		break;
	default:
		cout << "KRIVI ODABIR!!" << endl;
		goto izbor;
		
	}
	in.close();
	out.close();
	cout << "Datoteka kopirana, vasa datoteka se zove odredisnadatoteka.txt" << endl << endl;
	cout << "IZBORNIK" << endl;
	d = 0;
	while (d != 1)
	{
		cout << "1 Obrada po godinama ";
		cin >> d;
	}
	cin.ignore();

	cout << "	Unesite godinu koju zelite obraditi: ";
	cin >> d;

	list<Movie> filmoviUgodini;

	for (int i = 0; i < filmovi.size(); i++)
	{
		if (filmovi[i].get_year() == d)filmoviUgodini.push_back(filmovi[i]);
	}
	while (true) {
		cout << "Unesite metascore vrijednost do koje zelite izbrisati filmove, za prekid unosa unesite negativan broj: ";
		cin >> d;
		if (d < 0)break;
		for (auto it = filmoviUgodini.begin(); it != filmoviUgodini.end();)
		{
			if (it->get_metascore() < d)
			{
				it = filmoviUgodini.erase(it);
			}
			else
			{
				++it;
			}
		}



	}

	cout << "ISPIS FILMOVA U GODINI:" << endl;
	for_each(filmoviUgodini.rbegin(), filmoviUgodini.rend(), print);
	cout << endl << endl;
	stack<Movie> stekRating;

	for (auto it = filmovi.rbegin(); it < filmovi.rend(); it++) {

		if (it == filmovi.rbegin()) {
			stekRating.push(*it);
			//continue;

		}
		else if ((*it).get_rating() >= stekRating.top().get_rating())
		{
			stekRating.push(*it);
		}

	}


	cout << "ISPIS STACKA:" << endl;
	while (!stekRating.empty())
	{
		stekRating.top().ispis();

		stekRating.pop();
	}

	cout << "Statistika ocjena: " << endl;
	int rating1 = 0, rating2 = 0, rating3 = 0, rating4 = 0;
	for (int i = 0; i < filmovi.size(); i++)
	{
		if (filmovi[i].get_rating() <= 3.9)rating1++;
		else if (filmovi[i].get_rating() <= 5.9)rating2++;
		else if (filmovi[i].get_rating() <= 7.9)rating3++;
		else rating4++;
	}
	cout << "0.0-3.9		(" << rating1 << ")" << endl;
	cout << "4.0-5.9		(" << rating2 << ")" << endl;
	cout << "6.0-7.9		(" << rating3 << ")" << endl;
	cout << "8.0-10.0	(" << rating4 << ")" << endl << endl << endl;

	cin.ignore();
	string naredba;
	cout << "Unesite naredbu tipa 'SELECT * FROM Movies WHERE Genre IN('n1', 'n2', …)' gdje su n1,n2 Zanrovi filmova napisani pravilno(Action,Adventure,Sci-Fi,Comedy,Drama,Fantasy...) i stavljeni u jednostruke navodnike bez ikakvih razmaka unutar zagrada! "<<endl;
	cout << "Za prestanak unesite: 'stop'" << endl;
	while (true) {
		string naredba;
		cout << "Unesite naredbu: ";
		getline(cin, naredba);
		if (naredba == "stop")break;
		stringstream naredbica(naredba);
		getline(naredbica, naredba, '(');
		if (naredba != "SELECT * FROM Movies WHERE Genre IN") {
			cout << "Pogresna naredba-pazi na pisanje naredbe/imena zanra" << endl; 
			continue;
		}
		getline(naredbica, naredba, ')');
		stringstream naredbicaa(naredba);
		vector<string> zanrovi;

		while (getline(naredbicaa, naredba, ','))
		{
			naredba.erase(0, 1);
			naredba.erase(naredba.size() - 1);

			zanrovi.push_back(naredba);

		}
		

		sort(zanrovi.begin(), zanrovi.end());

		for (int i = 0; i < filmovi.size(); i++)
		{
			vector<string> temp(filmovi[i].get_genre());
			sort(temp.begin(), temp.end());
			if (includes(temp.begin(), temp.end(),
				zanrovi.begin(), zanrovi.end()))
			{
				filmovi[i].ispis();
			}


		}

	}
	return 0;

}