//
//  main.cpp
//  tp3
//
//  Created by Daehli Nadeau Otis on 2015-03-25.
//  Copyright (c) 2015 Daehli Nadeau-Otis. All rights reserved.
//

/*----------------Bibliothèque----------------*/
#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"
using namespace std;

/*----------------Function----------------*/
string lireFichier(string lecture);
void enrFichier(string);

/*----------------Classe----------------*/
ABR :: ABR(){
	racine = NULL;
}

ABR ::~ABR(){
    delete racine;
}

noeud* ABR::getRacine () {
	return racine;
}

void ABR ::Inserer(noeud *&racine, int d){
	if (racine == NULL){
       racine = new noeud;
	   racine->valeur = d;
	   racine->droit = NULL;
	   racine->gauche = NULL;
    }
    else if (d <= racine->valeur) 
		Inserer (racine->gauche, d);
	else 
		Inserer (racine->droit, d);   
}

void ABR::Supprimer(noeud *&racine, int d){
    if ( racine == NULL )
		cout << d << "n'est pas dans l'arbre \n";
    else if (d < racine->valeur){
		Supprimer(racine->gauche, d);
	}
	else if (d > racine->valeur){
		Supprimer(racine->droit,d);
    }
    else {
		if (racine->gauche==NULL && racine->droit==NULL ) {
			delete racine;
		}
		else if (racine->gauche == NULL){
			racine = racine->droit;
		}
		else if (racine->droit == NULL) {
			racine = racine->gauche;
		}
		else {
			noeud *tamp = SupprimerMin (racine->droit);
			racine->valeur = tamp->valeur;
			Supprimer (tamp, tamp->valeur);
		}
	}
}

noeud* ABR :: SupprimerMin(noeud *&racine){
	if ( racine->gauche != NULL ) // on continue à gauche
		return
		SupprimerMin (racine->gauche) ;
	else // le minimum est trouvé à ce stade
		return racine;
} 
    


void ABR:: Afficher_Arbre(noeud *&racine, int niveau){
	if (racine == NULL) return;
	else {
	Afficher_Arbre (racine->gauche, niveau+1);

	cout << "Niveau " << niveau << "->" << racine->valeur << endl;

	Afficher_Arbre (racine->droit, niveau+1);
	}
}

int ABR ::Afficher_hauteur(noeud *&racine){
	if (racine == NULL) return -1; 
	else {
	int niveauG =1;
	niveauG += Afficher_hauteur (racine->gauche);

	int niveauD = 1;
	niveauD += Afficher_hauteur (racine->droit);
	if (niveauD > niveauG)
		return niveauD;
	else 
		return niveauG;
	}
}

void ABR:: Afficher_Ascendant(noeud *&racine, int d){
}

void ABR:: Archiver (noeud *&racine){
}



int main() {
   ABR arbre;

   noeud* racine = arbre.getRacine();
   arbre.Inserer (racine, 3);
   arbre.Inserer (racine, 4);
   arbre.Inserer (racine, 5);
   arbre.Inserer (racine, 6);
   arbre.Inserer (racine, 7);
   arbre.Inserer (racine, 10);
   arbre.Inserer (racine, 2);
   arbre.Inserer (racine, 0);
   arbre.Inserer (racine, 11);
   arbre.Afficher_Arbre (racine, 0);

   cout << arbre.Afficher_hauteur(racine);

   system ("pause");
   return 0;
}
/* -------------------------------------------------------------------------------*/
/* DESCRIPTION :      Fonction principale du programmme								*/
/* PARAMETRES :		  Aucun															*/
/* VALEUR DE RETOUR : Aucune 														*/
/* REMARQUE : 		  Aucune														*/
/* -------------------------------------------------------------------------------*/

/*string lireFichier(string lecture ){
    ifstream lire(lecture.c_str(), ios::in);
    if  (lire.fail()){
        cout << "Erreur pour l'ouverture du fichier" <<endl;
    }
    else{
        while (!lire.eof()) {
            string commande;
            getline(lire,commande);
            cout << commande; //Pour voir l'intérieur tu contenu.
            
            
        }
    }
    
    
    
};

void enrFichier(string){
}*/
