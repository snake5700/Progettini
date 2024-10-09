//Adamska-Shalansaska IX/XII/MMXX

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "functions.h"

const std::string index = "INDEX_OUT_OF_BOUND";
const std::string Empty = "EMPTY_VECTOR";
const std::string input = "INPUT_NOT_VALID";
const std::string Full = "VECTOR_IS_FULL";
const int min = 0;

struct Tweet{
	std::string author;
	std::string text;
	std::vector<std::string> hashtags;
	std::vector<std::string> mentions;
};

void menu(){
	std::system("cls");
	std::cout << "1 Inserimento" << std::endl;
	std::cout << "2 Stampa" << std::endl;
	std::cout << "3 Ordinamento" << std::endl;
	std::cout << "4 Ricerca Tweet" << std::endl;
	std::cout << "5 Conteggio Hashtags (No doppioni)" << std::endl;
	std::cout << "6 Conteggio Mentions (No doppioni)" << std::endl;
	std::cout << "7 Tweets di tendenza" << std::endl;
	std::cout << "8 Da String a Tweet" << std::endl;
	std::cout << "9 Check Hashtags" << std::endl;
	std::cout << "10 Creazione Backup" << std::endl;
}

Tweet tweetRead(){
	Tweet t;

	std::cout << "Autore -->";
	do{std::getline(std::cin, t.author);}while(t.author.empty());
	std::transform(t.author.begin(), t.author.end(), t.author.begin(), [](unsigned char c){ return std::tolower(c); });
	
	std::cout << "Testo -->"; 
	do{std::getline(std::cin, t.text);}while(t.text.empty());
	std::transform(t.text.begin(), t.text.end(), t.text.begin(), [](unsigned char c){ return std::tolower(c); });
	
	std::cout << "Menzioni @ o Hashtags # -->";
	std::string h = "";
	do{std::cin >> h;}while(h.empty());
	std::transform(h.begin(), h.end(), h.begin(), [](unsigned char c){ return std::tolower(c); });
	
	while((h[min] == '#') || (h[min] == '@')){
		if(h[min] == '#') t.hashtags.push_back(h);
		if(h[min] == '@') t.mentions.push_back(h);
		do{std::cin >> h;}while(h.empty());
		std::transform(h.begin(), h.end(), h.begin(), [](unsigned char c){ return std::tolower(c); });
	}
	std::cin.ignore(10000, '\n');
	return t;
}

void read(twitter &t){
	Tweet T = tweetRead();
	t.push_back(T);
}

void tweetWrite(const twitter &t){
	if(t.empty()) throw -1;
	
	for(unsigned int i = 0; i < t.size(); i++){
		std::cout << t.at(i).author << std::endl;
		std::cout << t.at(i).text << std::endl;
		for(unsigned int j = 0; j < t.at(i).hashtags.size(); j++) std::cout << t.at(i).hashtags.at(j) << (j < (t.at(i).hashtags.size() - 1) ? " " : "\n");
		for(unsigned int j = 0; j < t.at(i).mentions.size(); j++) std::cout << t.at(i).mentions.at(j) << (j < (t.at(i).mentions.size() - 1) ? " " : "\n");
	}
}

void write(const std::vector<std::string> &v, const std::vector<int> &c){
	if(v.empty()) throw -1;
	for(unsigned int i = 0; i < v.size() && c.size(); i++) std::cout << v.at(i) << " \212 apparso " << c.at(i) << " volte ";
}

void sort(twitter &t){
	if(t.empty()) throw -1;
	
	for(unsigned int i = 0; i < t.size(); i++){
		int man = i;
		for(unsigned int j = (i + 1); j < t.size(); j++){
			if(t.at(j).author <= t.at(man).author) man = j;
		}
		Tweet aux = t.at(i);
		t.at(i) = t.at(man);
		t.at(man) = aux;
	}
}

int binarySearch(const twitter &t, std::string elem){
	if(t.empty()) throw -1;
	if(elem.empty()) throw -3;
	
	int first = min, last = (t.size() -1), middle = (first + last) /2, pos = -1;
	bool trovato = false;

	while((!trovato) && (first <= last)){
		middle = (first + last) /2;
		if(t.at(middle).author == elem){
			trovato = true;
			pos = middle;
		}else{
			if(t.at(middle).author < elem) first += 1;
			else last -= 1;
		}
	}
	return pos;
}

/*//Manutenzione vector, pericolo di Index out of Bound..
void write(const std::vector<std::string> &v){
	if(v.empty()) throw -1;
	for(unsigned int i = 0; i < v.size(); i++) std::cout << v.at(i) << " ";
	std::cout << "\n\n";
}

//Manutenzione vector cont..
void write(const std::vector<int> &v){
	if(v.empty()) throw -1;
	for(unsigned int i = 0; i < v.size(); i++) std::cout << v.at(i) << " ";
	std::cout << "\n\n";
}*/

bool contest(const std::vector<std::string> &v, std::string t){
	if(v.empty()) return false;
	if(t.empty()) throw -3;
	
	bool trovato = false;
	int i = 0;
	while((!trovato) && (i < v.size())){
		if(v.at(i) == t) trovato = true;
		i++;
	}
	return trovato;
}

std::vector<std::string> insertHashtags(twitter &t){
	if(t.empty()) throw -1;
	
	std::vector<std::string> Hashtags;
	for(unsigned int i = 0; i < t.size(); i++){
		for(unsigned int j = 0; j < t.at(i).hashtags.size(); j++){
			std::string temp = t.at(i).hashtags.at(j);
			if((t.at(i).hashtags.at(j) == temp) && (contest(Hashtags, temp))) continue;
			else Hashtags.push_back(temp);
		}
	}
	return Hashtags;
}

std::vector<std::string> insertHashtagsR(twitter &t){
	if(t.empty()) throw -1;
	
	std::vector<std::string> Hashtags;
	for(unsigned int i = 0; i < t.size(); i++){
		for(unsigned int j = 0; j < t.at(i).hashtags.size(); j++) Hashtags.push_back(t.at(i).hashtags.at(j));
	}
	return Hashtags;
}

std::vector<std::string> insertMentions(twitter &t){
	if(t.empty()) throw -1;
	
	std::vector<std::string> Mentions;
	for(unsigned int i = 0; i < t.size(); i++){
		for(unsigned int j = 0; i < t.size(); i++){
			std::string temp = t.at(i).mentions.at(j);
			if((t.at(i).mentions.at(j) == temp) && (contest(Mentions, temp))) continue;
			else Mentions.push_back(temp);
		}
	}
	return Mentions;
}

std::vector<int> conteggio(std::vector<std::string> &v){
	if(v.empty()) throw -1;
	
	std::vector<int> cont (v.size(), 0);
	for(unsigned int i = 0; i < v.size(); i++){
		std::string temp = v.at(i);
		for(unsigned int j = 0; j < v.size(); j++){
			if(v.at(j) == temp) cont.at(i)++;
		}
	}
	return cont;
}

std::vector<int> conteggio(std::vector<std::string> &h_r, std::vector<std::string> &h){
	if(h_r.empty()) throw -1;
	if(h.empty()) throw -1;
	
	std::vector<int> cont(h.size(), 0);
	for(unsigned int i = 0; i < h.size(); i++){
		std::string temp = h.at(i);
		for(unsigned int j = 0; j < h_r.size(); j++){
			if(h_r.at(j) == temp) cont.at(i)++;
		}
	}
	return cont;
}

int findPos(const std::vector<int> &c){
	if(c.empty()) throw -1;
	
	int pos = 0, max = c.at(min), i = 0;
	while(i < c.size()){
		if(max < c.at(i)) pos = i;
		i++;
	}
	return pos;
}

twitter built(twitter &t, std::string elem){
	if(t.empty()) throw -1;
	if(elem.empty()) throw -3;
	
	twitter aux;
	for(unsigned int i = 0; i < t.size(); i++){
		for(unsigned int j = 0; j < t.at(i).hashtags.size(); j++){
			if(t.at(i).hashtags.at(j) == elem) aux.push_back(t.at(i));
		}
	}
	return aux;
}

void trend(twitter &t){
	if(t.empty()) throw -1;
	
	std::vector<std::string> h_r = insertHashtagsR(t);
	std::vector<std::string> h = insertHashtags(t);
	std::vector<int> Cont = conteggio(h_r, h);
	std::string elem = h.at(findPos(Cont));
	twitter aux = built(t, elem);
	tweetWrite(aux);
}

std::string slice(std::string &elem){
	int j = elem.length() - 1, i = elem.length();
	std::string piece = "";
	while(piece.empty()){
		switch(elem[j]){
			case'#': piece = elem.substr(j, i);
					 break;
			case'@': piece = elem.substr(j, i);
					 break;
			case',': piece = elem.substr(j, i);
					 break;
			case'.': piece = elem.substr(j, i);
					 break;
			default: break;
		}
		j--;
	}
	return piece;
}

void charPop(std::string &elem, unsigned int length){
	while(length > 0){
		elem.pop_back();
		length--;
	}
}

Tweet tweetRead(std::string elem){
	Tweet t;
	while(!elem.empty()){
		std::string piece = slice(elem);
		std::cout << piece << std::endl;
		switch(piece[min]){
			case'#': t.hashtags.push_back(piece);
					 break;
			case'@': t.mentions.push_back(piece);
					 break;
			case',': t.text = piece;
					 break;
			case'.': t.author = piece;
					 break;
		}
		charPop(elem, piece.length());
	}
	return t;
}

void read(twitter &t, std::string elem){
	if(elem.empty()) throw -3;
	
	Tweet T = tweetRead(elem);
	t.push_back(T);
}

bool hashtag(Tweet a, std::string c){
	if(c.empty()) throw -3;
	
	int i = 0; bool trovato = false;
	while((!trovato) && (i < a.hashtags.size())){
		if(a.hashtags.at(i) == c) trovato = true;
		i++;
	}
	return trovato;
}

void presence(twitter &t, std::string contest){
	if(t.empty()) throw -1;
	if((contest.empty()) || (contest[min] != '#')) throw -3;
	
	for(unsigned int i = 0; i < t.size(); i++){
		Tweet aux = t.at(i);
		std::cout << std::boolalpha << hashtag(aux, contest) << " ";
	}
} 

bool backup(twitter &t){
	if(t.empty()) throw -1;
	
	ofstream backup("backup.txt");
	for(unsigned int i = 0; i < t.size(); i++){
		std::string buffer = t.at(i).author + " " + t.at(i).text;
		for(unsigned int j = 0; j < t.at(i).hashtags.size(); j++) buffer += t.at(i).hashtags.at(j) + " ";
		for(unsigned int j = 0; j < t.at(i).mentions.size(); j++) buffer += t.at(i).mentions.at(j) + " ";
		backup << buffer;
	}
	return true;
}

void eccezione(int &e){
	switch(e){
		case -1: std::cerr << Empty << std::endl;
				 break;
		case -2: std::cerr << index << std::endl;
				 break;
		case -3: std::cerr << input << std::endl;
				 break;
		case -4: std::cerr << Full << std::endl;
				 break;
	}
}