#include <iostream>
#include <conio.h>

using namespace std;

class Lista;

class Avion 
{
private:
	int tip;
	char *nume, *culoare;
	
	Avion *urm;
public:
	float rent;
	Avion(char *n, char *cul,int t)
	{
		nume = new char(sizeof(strlen(n) + 1));
		culoare = new char(sizeof(strlen(cul) + 1));
		strcpy(nume, n);
		strcpy(culoare, cul);
		tip = t;
		
	}
	virtual void afisare()
	{
		cout << "------------------\n";
		cout << "Nume: " << nume << endl;
		cout << "Culoare: " << culoare << endl;
		
	}
	friend class Lista;
	

};

class Pasageri :public Avion
{
private:
	int nr_loc, autonomie;
	
public:
	
	Pasageri(char *n,char *cul,int t, int n_l, int aut) :Avion(n, cul,t)   //atentia la *?
	{
		nr_loc = n_l;
		autonomie = aut;
		Avion::rent = ((float)nr_loc+(float)autonomie)/100;
	}
	void afisare()
	{
		Avion::afisare();
		cout << "Numar locuri: " << nr_loc << endl;
		cout << "Autonomie: " << autonomie << endl;
		
	}
	
	
};

class Lupta :public Avion
{
private:
	int viteza, raza_actiune;
public:
	Lupta(char *n, char *cul,int t, int vit, int raza) :Avion(n, cul,t) //si aici
	{
		viteza = vit;
		raza_actiune = raza;
	}
	void afisare()
	{
		Avion::afisare();
		cout << "Viteza: " << viteza<<endl;
		cout << "Raza actiune: " << raza_actiune << " km\n";
	}
	friend class Lista;
};
class Lista
{
public:
	Avion *head;
	void adaugare(Avion *a);
	void afisare();
	void stergere(char *nume);
	void afisare_rentabilitate();
	
};
void Lista::adaugare(Avion *a)
{
	Avion *p;
	p = head;
	if (p == NULL)
	{
		head = a;
	}
	else
	{
		while (p->urm != NULL && p->tip==1) //atentie aici tip
			p = p->urm;
		p->urm = a;
	}
}
void introducere(Lista &l, int t)
{
	char nume[30], culoare[30];
	Avion *p;
	cout << "Nume: ";
	cin >> nume;
	cout << "Culoare: ";
	cin >> culoare;
	if (t == 0)
	{
		int nr, aut;
		cout << "Numar locuri: ";
		cin >> nr;
		cout << "Autonomie: ";
		cin >> aut;
		Pasageri *h=new Pasageri(nume,culoare,t,nr,aut);
		p = h;
		l.adaugare(p);

	}
	if (t == 1)
	{
		int vit, raza;
		cout << "Viteza: ";
		cin >> vit;
		cout << "Raza:";
		cin >> raza;
		Lupta *h = new Lupta(nume, culoare, t, vit, raza);
		p = h;
		l.adaugare(p);
	}
}
void Lista::afisare()
{
	int t;
	cout << "--------------\nCe tip de avion?\n 0.Pasageri\n 1.Lupta\nOptiune: ";
	cin >> t;
	Avion *p;
	p = head;
	while (p != NULL)
	{
		if (p->tip == t)
		{
			p->afisare();
		}
		p = p->urm;
	}

}
void Lista::stergere(char *nume)
{
	Avion *p,*aux;
	p = head;
	if (strcmp(head->nume, nume) == 0)
	{
		aux = head;
		head = head->urm;
		free(aux);
	}
	else
	while (p->urm != NULL)
	{
		if (strcmp(p->urm->nume, nume) == 0)
		{
			aux = p->urm;
			p->urm = p->urm->urm;
			free(aux);
		}
	}
}
void Lista::afisare_rentabilitate()
{
	Avion *p;
	p = head;
	float rentmax=0;
	while (p!= NULL)
	{
		if (rentmax < p->rent)
			rentmax = p->rent;
		p = p->urm;
	}
	p = head;
	while (p != NULL)
	{
		if (rentmax == p->rent)
		{
			cout << "Cel mai rentabil avion!"<<endl;
			p->afisare();
		}
		p = p->urm;
	}
		
}
int main()
{
	int opt;
	Lista l;
	l.head = NULL;
	cout << "=============\n1.Introducere\n2.Afisare dupa categorie\n3.Sterge\n4.Cel mai rentabil avion\n5.Exit\n=============\n";
	do {
		cout << "Optiune Meniu: ";
		cin >> opt;
		switch (opt)
		{
		default:
		{
			break;
		}
		case 1:
		{
			int t;
			cout << "======\nIntroducere\n======\n------------\nTip avion?\n0.Pasageri\n1.Lupta\nOptiune: ";
			cin >> t;
			introducere(l, t);
			break;
		}
		case 2:
		{
			l.afisare();
			break;
		}
		case 3:
		{
			char nume[30];
			cout << "Introdu nume: ";
			cin >> nume;
			l.stergere(nume);
			break;
		}
		case 4:
		{
			l.afisare_rentabilitate();
			break;
		}
		}
	} while (opt != 5);
	return 0;
}