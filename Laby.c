/**
DIALLO  Mamoudou
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int NB_COLONNES= 40;
int NB_LIGNES= 20;
char AFF_VIDE ='-';
char AFF_MUR ='X';
char AFF_BORD ='+';

char* Grille=NULL;
int* Pile=NULL;
int Sommet= 0;

/**Part1**/
int getID(int ligne, int colonne)
{
    return ligne*NB_COLONNES+colonne;
}
int getLigne(int id)
{
    return id/NB_COLONNES;
}
int getCol(int id)
{
    return id%NB_COLONNES;
}
void modifie(int ligne, int colonne, char x)
{
    Grille[getID(ligne, colonne)]= x;
}
char lit(int ligne, int colonne)
{
    char x;
    if(ligne < NB_LIGNES && colonne < NB_COLONNES)
        x=Grille[getID(ligne, colonne)];
    return x;
   // return Grille[getID(ligne, colonne)];
    }
void affiche(void)
{
    printf("\n"); //saut de ligne avant
    for(int i=-1; i<=NB_LIGNES; i++)
        {
            for(int j=-1; j<=NB_COLONNES; j++)
                {
                   if (i==-1 || i== NB_LIGNES || j==-1 || j== NB_COLONNES)
                   {
                       printf("%c", AFF_BORD);
                   }
                   else
                   {
                        if(lit(i, j)==1)
                            printf("%c", AFF_MUR);
                        else if(lit(i, j)==0)
                            printf("%c", AFF_VIDE);
                   }
                }
                printf("\n");
        }
        printf("\n"); //saut de ligne apres
}



/**Part2**/

//empiler
void push(int x)
{
    Pile [Sommet] = x;
    Sommet++;
}

//depiler
int pop()
{
    Sommet--;
    if(Sommet != -1)
        return Pile[Sommet];
    else
        return -1;
}

//connexité
int connexe()
{
    int NbCasesBlanches=0, empileID= -1, NbCasesMarquee=0;
    for(int i=0; i<NB_LIGNES*NB_COLONNES; i++)
    {
        //Nombre de cases blanches
        if(Grille[i] == 0)
        {
            NbCasesBlanches++;
            empileID= i;
        }
    }
    //verifie s'il n'y aucune case blanche
    if (NbCasesBlanches==0)
    {
        printf("Attention!!! Il n'y a aucune case blanches\n");
    }
    modifie(getLigne(empileID), getCol(empileID), 2); //marquer l'id
    Sommet=0;

    for (;Sommet != -1; )
    {
        //verif gauche
        if(lit(getLigne(empileID), getCol(empileID)-1) == 0)
        {
            push(getID(getLigne(empileID), getCol(empileID)-1));
            modifie(getLigne(empileID), getCol(empileID)-1, 2); //marquer l'id
        }
        //verif bas
        if(lit(getLigne(empileID)+1, getCol(empileID)) == 0)
        {
            push(getID(getLigne(empileID)+1, getCol(empileID)));
            modifie(getLigne(empileID)+1, getCol(empileID), 2); //marquer l'id
        }
        //verif droite
        if(lit(getLigne(empileID), getCol(empileID)+1) == 0)
        {
            push(getID(getLigne(empileID), getCol(empileID)+1));
            modifie(getLigne(empileID), getCol(empileID)+1, 2); //marquer l'id

        }
        //verif haut
        if(lit(getLigne(empileID)-1, getCol(empileID)) == 0)
        {
            push(getID(getLigne(empileID)-1, getCol(empileID)));
            modifie(getLigne(empileID)-1, getCol(empileID), 2); //marquer l'id
        }
        empileID= pop(); //depiler l'id dans pile
    }
    for(int i=0; i<NB_LIGNES*NB_COLONNES; i++)
    {
        //nombre de cases marquees
        if(lit(getLigne(i), getCol(i)) == 2)
        {
            modifie(getLigne(i), getCol(i), 0);
            NbCasesMarquee++;
        }
    }
    //verif de la connexité
    if(NbCasesBlanches==NbCasesMarquee) //si NbCasesBlanches==NbCasesMarquee ou si leurs difference donne 0
        return 1; //connexe
    else
        return 0; //non connexe
}
//remise a zero de toutes les cases de la grille
void remiseZero()
{
	for(int i=0;i<NB_LIGNES*NB_COLONNES;i++)
	{
		modifie(getLigne(i), getCol(i), 0);
	}
}

//Generation du labyrinthe
void genLaby(int k)
{
    remiseZero();
	int marge = (10*k/100);
	int genAleatoire =  k-marge + rand()%(2*marge) ;
	int casesNoires = (NB_LIGNES*NB_COLONNES) - genAleatoire;
	int i = 0;
	while(i<casesNoires)
	{
		int posAleatoire;
	    posAleatoire = 1+rand()%(NB_COLONNES*NB_LIGNES-2);
		Grille[posAleatoire] = 1;
		if(connexe())
		{
			i++;
		}
		else
		{
			Grille[posAleatoire]=0;
		}
	}
}


int main()
{
    srand((unsigned)time(NULL));
    Grille= (char*) calloc (NB_LIGNES*NB_COLONNES, sizeof(char));
    Pile= (int*) calloc(NB_LIGNES*NB_COLONNES, sizeof(int));
    for(int i=0; i<100; i++)
    {genLaby(400);
    affiche();
    }


    free(Pile);
    free(Grille);
    return 0;
}
