//
//  Header.h
//  tp3
//
//  Created by Daehli Nadeau Otis on 2015-03-25.
//  Copyright (c) 2015 Daehli Nadeau-Otis. All rights reserved.
//

#ifndef tp3_Header_h
#define tp3_Header_h
using namespace std;

struct noeud { // Je croix qu'on pourrait mettre la strucure dans le private de la classe
    int valeur;
    noeud *gauche;
    noeud *droit;
};

class ABR {
private:
    noeud *racine; // La racine l’arbre
public:
    ABR ();// Construit l’arbre dont la racine est à l’adresse racine. 1
    ~ABR(); // Désalloue l’espace mémoire occupé par l’arbre. // Le destructeur ne peut pas avoir des //////parametre
	noeud* getRacine (); //retourne la racine de l'arbre
    void Inserer(noeud *&racine, int d); // insère le noeud de valeur d à l’arbre.
    void Supprimer(noeud *&racine, int d); // Supprime le nœud de valeur d de l’arbre.
	noeud* SupprimerMin(noeud *&racine);
    void Afficher_Arbre(noeud *racine, int niveau); /*Affiche les éléments de l’arbre niveau par niveau. Un bonus de
    5pts est donné à ceux qui commencent par le premier niveau, ensuite le deuxième niveau, ainsi de suite, jusqu’à arriver à la racine ; le premier niveau étant l’ensemble des noeuds qui n’ont pas de descendants.*/
    int Afficher_hauteur(noeud *racine); //Affiche la hauteur de l’arbre.
    void Afficher_Ascendant(noeud *racine, int d); // Affiche les ascendants du noeud de valeur d.
	void Instruction(noeud*&racine, char lecture,int valeur);
    void Archiver (noeud *racine);// Archiver en implémentation séquentielle l’arbre dont la racine est racine
    //dans un fichier texte que vous allez définir. (bonus 10pts)
}; // fin de la déclaration de la classe ABR

#endif
