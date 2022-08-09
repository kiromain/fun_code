#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
/*
1. Crreate
1. Tworzy listê z danych jak w zadaniu p1, wczytywanych z pliku o nazwie podanej przez
u¿ytkownika - korzystaj¹c z funkcji do³¹czania jednego filmu o jakichœ danych na koñcu
listy zaczynaj¹cej siê pod jakimœ adresem (parametrem funkcji do³¹czania jest tylko adres
pocz¹tku listy oraz tytu³, rok i ocena do³¹czanego filmu)
2. Napisaæ funkcjê, która:
a. Do listy dopisuje nowy element przed ka¿dym filmem o tytule zaczynaj¹cym siê
liter¹ 'P' oraz ocen¹ wiêksz¹ od liczby podanej przez u¿ytkownika oraz przed
ka¿dym filmem o tytule zaczynaj¹cym siê liter¹ 'G' oraz ocen¹ wiêksz¹ od œredniej
oceny wszystkich filmów. Nowy element jest uzupe³niany danymi drugiego od
koñca filmu na liœcie.
b. Z listy usuwa co drugi element o parzystym roku.
3. Drukujê listê przed oraz po wywo³aniu funkcji z podpunktu 2.
4. Na koñcu usuwa listê z pamiêci.
*/

using namespace std;

struct Movie{
	string tytul;
	int rok;
	double ocena;
	Movie *nast;
};

void dodaj(Movie *&adres,string tytul, int rok, double ocena){
	Movie *aktualny = new Movie;
	aktualny->tytul = tytul;
	aktualny->rok = rok;
	aktualny->ocena = ocena;

	if(adres == NULL){
		adres=aktualny;
		aktualny->nast=NULL;
	}else if(adres->nast == NULL){
		adres->nast = aktualny;
		aktualny->nast = NULL;
	}else{
		dodaj(adres->nast,tytul,rok,ocena);
	}
}

void drukuj(Movie *adres){
	if(adres==NULL)
		return;
	cout<<adres->tytul<<" "<<adres->rok<<" "<<adres->ocena<<endl;
	drukuj(adres->nast);
}

void zad2i3(Movie *&adres,int liczba,double srednia,int ile,string tytul,int rok,double ocena){
	Movie *nowy,*poprzedni,*aktualny, *temp;
	poprzedni = NULL;
	aktualny=adres;
	// a dodawanie elementow;
	while(aktualny!=NULL){
		//cout<<adres->tytul[0]<<endl;
		if(aktualny->ocena > liczba && aktualny->tytul[0] == 'P'){
			//insert(&adres,tytul,rok,ocena);
			nowy = new Movie();

			nowy->tytul=tytul;
			nowy->rok=rok;
			nowy->ocena=ocena;

			if(poprzedni == NULL){
				adres = nowy;
				adres->nast = aktualny;
			} else {
				poprzedni->nast = nowy;
				nowy->nast = aktualny;
			}
		}else if(aktualny->ocena > srednia && aktualny->tytul[0] == 'G'){
			nowy = new Movie();

			nowy->tytul=tytul;
			nowy->rok=rok;
			nowy->ocena=ocena;

			if(poprzedni == NULL){
				adres = nowy;
				adres->nast = aktualny;
			} else {
				poprzedni->nast = nowy;
				nowy->nast = aktualny;
			}
		}
		poprzedni=aktualny;
		aktualny=aktualny->nast;
	}
	cout<<"Lista po dopisaniu nowych elementow danymi drugiego od konca filmu na liscie: "<<endl;
	drukuj(adres);
	cout<<endl;

	//b usuwanie elementow;
	Movie *tmp;
	aktualny=adres;
	poprzedni=NULL;
	int i=0;
	while(aktualny!=NULL){
		if(aktualny->rok%2==0){
			if(i%2==1){
				if(aktualny==adres){
					adres=adres->nast;
				}else{
					poprzedni->nast=aktualny->nast;
				}
				tmp=aktualny;
				aktualny=aktualny->nast;
				delete tmp;
				i++;
			}else{
				i++;
				poprzedni=aktualny;
				aktualny=aktualny->nast;
			}
		}else{
			i+=2;
			poprzedni=aktualny;
			aktualny=aktualny->nast;
		}
	}
	cout<<"Lista po usunieci co drugiego elementu o parzystym roku: "<<endl;
	drukuj(adres);
}

int main()
{
	//1
	ifstream plik("movies.txt");

	if(!plik) { cout<<"blad podanej nazwy pliku"<<endl; return -1;}

	Movie *poprzedni, *aktualny, *glowa;
	aktualny = NULL;
	glowa = NULL;

	string tytul;
	int rok;
	double ocena;
	double suma=0;
	int ile=0;
	//elemnty drugie od konca
	string dktytul;
	int dkrok;
	double dkocena;
	//ostatnie elementy
	string otytul;
	int orok;
	double oocena;

	while(plik.peek() != EOF){
		plik>>tytul>>rok>>ocena;
		suma+=ocena;
		ile++;
		dktytul=otytul;
		dkrok=orok;
		dkocena=oocena;
		otytul=tytul;
		orok=rok;
		oocena=ocena;
		dodaj(glowa,tytul,rok,ocena);
	}
	double srednia=suma/ile;
	cout<<"Lista przed zadaniem 2: "<<endl;
	drukuj(glowa);
	cout<<endl;
	cout<<"Srednia ocen: "<<srednia<<endl;
	cout<<endl;
	cout<<"Element przed ostatni z listy: "<<dktytul<<" "<<dkrok<<" "<<dkocena<<endl;
	cout<<endl;
	//2 i 3
	int liczba;
	cout<<"Podaj liczbe od 1 do 10 : "<<endl;
	do{
		cin>>liczba;
	}while(liczba<1 || liczba>10);
	cout<<endl;
	zad2i3(glowa,liczba,srednia,ile,dktytul,dkrok,dkocena);

	//4
	while(glowa != NULL){
		poprzedni = glowa;
		glowa=glowa->nast;
		delete poprzedni;
	}
	return 0;
}
