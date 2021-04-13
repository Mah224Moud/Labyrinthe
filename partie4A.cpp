/*********
DIALLO Mamoudou***/


//  Labyrinthe.hpp
//  Laby-p3
//
//  Created by OB on 18/02/2021.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;
/******************************************************
*******************************************************/
class Sommet
{
private:
    int id;
    int distaceSource;
public:
    Sommet();
    Sommet(int id,int dist);
    int getid();
    Sommet& operator=(const Sommet& s);
    int getDistaceSource();
};

class Pile
{
private:
    int* pile;
    int ligne;
    int col;
    int Sommet;
public:
    Pile(int i,int j);
    ~Pile();
    int getlignePile();
    int getColonnePile();
    int getSommet();
    void push(int x);
    int pop();
    void marquer(int id,char* g);

};




/******************************************************
 * ***************************************************/
class Labyrinthe
{
private:
    int nb_lignes;
    int nb_colonnes;
    int taille;
    char* grille;
    std::string aff;
    
    // Retourne le caractère à afficher pour la valeur val.
    char getAff(char val);

public:
    /// Constructeurs et destructeurs
    Labyrinthe(int nLigne, int nColonnes);
    Labyrinthe(int nLignes, int nColonnes, double density); //Crée un labyrinthe vide.
    Labyrinthe(char data[]) ; //Crée un labyrinthe à partir d'un descripteur.
    ~Labyrinthe(); //Détruit le labyrinthe courant.
    
    /// Méthodes d'accès
    int getID(int ligne, int colonne); //Retourne l'identifiant d'une cellule.
    int getLigne(int id); //Retourne la ligne de la cellule d'identifiant id.
    int getCol(int id); //Retourne la colonne de la cellule d'identifiant id.
    void modifie(int ligne, int colonne, char x); //Modifie la valeur d'une cellule.
    char lit(int ligne, int colonne); //Retourne la valeur de la cellule de coordonnées (i,j).
    
    /// Méthode d'accès supplémentaires
    int getNbLignes(); //Retourne le nombre de lignes de la grille.
    int getNbColonnes(); //Retourne le nombre de lignes de la grille.
    int lit(int id); //Retourne la valeur de la cellule id.
    void modifie(int id, char x); //Modifie la valeur de la cellule id.

    /// Méthodes d'affichage
    // Initialise les caractères utilisés pour l'affichage. Si motif contient n caractères alors
    // motif[i] est affiché pour représenter une case de valeur i entre 0 et n-2.
    // Toute autre valeur provoque l'affichage du caractère motif[n-1].
    void setAff(const char* motifs);
    void affiche(); // Affiche le labyrinthe.
    //void afficheDescr(); //Affiche le descripteur du labyrinthe courant.
    void remiseZero();
    
    /// Méthode de haut niveau
    bool connexe(); //Vérifie si toutes les cellules de valeur 0 sont connectées.
    void genLaby(int nb); //Produit un labyrinthe aléatoire connexe avec nb cases blanches.
    //int distMin(int id1, int id2); //Retourne la distance minimum entre les cases id1 et id2.
    
    /// Méthodes de démonstration
    // Matérialise un chemin de longueur minimale entre les cases d'identifiants
    // id1 et id2 en plaçant des valeurs 2 dans les cases de ce chemin.
    //void chemin(int id1, int id2);
    // Lance une démonstration de productions de labyrinthes et de recherche de
    // chemins de longueur minimale.
    //static void demo();
};

Labyrinthe::Labyrinthe(int nLignes,int nColonnes)
{
    setAff(" XAB.");
    this->nb_lignes = nLignes;
    this->nb_colonnes= nColonnes;
    this->grille = new char[getNbLignes()*getNbColonnes()];
    remiseZero();
}
Labyrinthe::Labyrinthe(char data[])
{
    setAff(" XAB.");
    this->nb_lignes = data[0];
    this->nb_colonnes= data[1];
    this->grille = new char[getNbLignes()*getNbColonnes()];
    for(int i=0;i<getNbLignes()*getNbColonnes();i++)
    {
        modifie(i,data[i+2]);
    }
}

Labyrinthe::Labyrinthe(int nLignes, int nColonnes, double density)
{
    setAff(" XAB.");
    this->nb_lignes = nLignes;
    this->nb_colonnes= nColonnes;
    this->grille = new char[getNbLignes()*getNbColonnes()];
    remiseZero();
    //idRobotA = getID(0,0);
   
    genLaby((int)(density * getNbColonnes() * getNbLignes()));
    modifie(0,0,2);
    modifie(getNbLignes()-1, getNbColonnes()-1,3);
    // Ajouter les initialisations supplémentaire nécessaires, si applicable
}



Labyrinthe::~ Labyrinthe()
{
    delete[] this->grille;
}

int Labyrinthe:: getID(int ligne, int colonne)
{
    return ligne*nb_colonnes+colonne;
}

int Labyrinthe:: getLigne( int id)
{
    return id/nb_colonnes;
}

int Labyrinthe:: getCol(int id)
{
    return id%nb_colonnes;
}

void Labyrinthe:: modifie(int ligne, int colonne, char x)
{
   this-> grille[getID(ligne, colonne)]= x;
}

void Labyrinthe:: modifie(int id, char x)
{
    this->grille[id]= x;
}

char Labyrinthe:: lit(int ligne, int colonne)
{
    char x;
    if(ligne < nb_lignes && colonne < nb_colonnes)
        x= this->grille[getID(ligne, colonne)];
    return x;
}

int Labyrinthe:: lit(int id)
{
    return this->grille[id];
}

int Labyrinthe:: getNbLignes()
{
    return this->nb_lignes;
}

int Labyrinthe:: getNbColonnes()
{
    return this->nb_colonnes;
}


void Labyrinthe:: setAff(const char* motifs)
{
    this->aff = motifs;
}

char Labyrinthe:: getAff(char val)
{
    return aff[val];
}

void Labyrinthe:: affiche()
{
    int taille= this->aff.length();
    for(int i =-1;i<=getNbLignes();i++)
    {   
        for(int j=-1;j<=getNbColonnes();j++)
        {
            if(i>-1 && j > -1 && i < getNbLignes() && j < getNbColonnes())
                cout<<getAff(lit(i,j));
            else
                cout<<aff[taille-1];
        }
        cout<<endl;
    }
}

void Labyrinthe:: remiseZero()
{
    for(int i=0;i<getNbLignes();i++)
    {
        for(int j=0;j<getNbColonnes();j++)
        {
            modifie(i,j,0);
        }
    }
}

bool Labyrinthe:: connexe()
{
    Pile p(getNbColonnes(), getNbLignes());
    int NbCaseBlaches=0;
    int NBCaseMarquee=0;
    int Depile;

    for(int i=0; i<getNbColonnes()*getNbLignes(); i++)
    {
        if(!this->grille[i])
        {
            NbCaseBlaches++;
            if(!p.getSommet())
                p.marquer(i, this->grille);
        }
    }
    if(!NbCaseBlaches)
    {
        cout<<"Attention !!! Erreur :("<<endl;
        return -1;
    }
    while (p.getSommet() != 0)
    {
        Depile= p.pop();
        if(getCol(Depile) != 0)
            p.marquer(Depile-1, this->grille);
        if(Depile >= getNbColonnes())
            p.marquer(Depile- getNbColonnes(),this->grille);
        if(Depile < getNbColonnes()*(getNbLignes()-1))
            p.marquer(Depile+getNbColonnes(),this->grille);
        if(getCol(Depile) != getNbColonnes()-1)
            p.marquer(Depile+1,this->grille);
    }
    for(int i=0;i<getNbColonnes()*getNbLignes();i++)
    {
        if(this->grille[i] == 2)
        {   
            NBCaseMarquee ++;
            this->grille[i] = 0;
        }
    }
    return NbCaseBlaches==NBCaseMarquee; 
}

void Labyrinthe::genLaby(int k)
{
    remiseZero();
    int marge = (10*k/100);
	int arb =  k-marge + rand()%(2*marge);
	int top = (getNbColonnes()*getNbLignes()) - arb;
	int pos=-1;
	int i = 0;
	while(i<top)
	{
	    pos = 1+rand()%(nb_colonnes*nb_lignes-1);
		this->grille[pos] = 1;
		if(connexe())
		{
			i++;
		}
		else
		{
			this->grille[pos]=0;
		}
	}
}

/******************
 * ****************/

Pile::~Pile()
{
    delete[] this->pile; 
}

Pile::Pile(int i,int j)
{
    this->pile = new int[i*j];
    this->ligne=i;
    this->col = j;
    Sommet = 0;
}

int Pile::getSommet()
{
    return this->Sommet;
}

void Pile::push(int x)
{
    this->pile[this->Sommet++] = x;
}

int Pile::pop()
{   
    return this->pile[--this->Sommet];
}
void Pile::marquer(int id,char* g)
{
    
    if(id < 0 || id > this->getColonnePile()* this->getlignePile() || g[id] != 0)
        return;
    g[id] = 2;
    this->push(id);       
}

int Pile::getColonnePile()
{
    return this->col;
}

int Pile:: getlignePile()
{
    return this->ligne;
}

int main(int argc, const char* argv[])
{
    srand((unsigned)time(NULL));
    Labyrinthe laby(10, 10);
    laby.modifie(1, 1);
    laby.affiche();
}
