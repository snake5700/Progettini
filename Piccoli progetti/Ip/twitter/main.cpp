//Adamska-Shalansaska IX/XII/MMXX

/*MicroBlogging*/

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h> //Funzione Sleep
#include "functions.cpp"
using namespace std;

int main(){	
	twitter t;
	vector<string> hashtags; vector<string> mentions;
	vector<int> c_h; vector <int> c_m;
	string stream = "";
	int opz = 0, pos = -1;
	
	do{
		Sleep(1500);
		menu();
		cin >> opz;
		switch(opz){
			case 1: read(t);
					break;
			case 2: try{
						tweetWrite(t);
					}catch(int &e){
						eccezione(e);
					}
					break;
			case 3: try{
						sort(t);
					}catch(int &e){
						eccezione(e);
					}
					break;
			case 4: try{
						cout << "Inserire un autore da ricercare:\t";
						getline(cin, stream);
						pos = binarySearch(t, stream);
						if(pos < 0) std::cout << "L'elemento " << stream << " non \212 in lista" << std::endl;
						else std::cout << "L'elemento " << stream << " \212 stato trovato nella" << pos << "° posizione" << std::endl;
					}catch(int &e){
						eccezione(e);
					}
					stream.clear();
					break;
			case 5: try{
						hashtags = insertHashtags(t);
						c_h = conteggio(hashtags);
						write(hashtags, c_h);
					}catch(int &e){
						eccezione(e);
					}
					break;
			case 6:	try{
						mentions = insertMentions(t);
						c_m = conteggio(mentions);
						write(hashtags, c_m);
					}catch(int &e){
						eccezione(e);
					}
					break;				
			case 7: try{
						trend(t);
					}catch(int &e){
						eccezione(e);
					}
					break;
			case 8: cout << "Inserire .autore,testo #hashtags e/o @mentions-->";
					getline(cin, stream);
					try{
						read(t, stream);
					}catch(int &e){
						eccezione(e);
					}
					stream.clear();
					break;
			case 9: cout << "Inserire un Hashtag: \t";
					getline(cin, stream);
					try{
						presence();
					}catch(int &e){
						eccezione(e);
					}
					stream.clear();
					break;
			case 10: try{
						if(backup(t)) cout << "Ho creato il backup" << endl;
						else cout << "Non ho creato il backup" << endl;
					 }catch(int &e){
						eccezione(e); 
					 }
					 break;
			default: break;
		}
	cin.clear(10000, '\n');
	}while(opz != 10);
	return 0;
}