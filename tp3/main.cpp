//
//  main.cpp
//  tp3
//
//  Created by Daehli Nadeau Otis on 2015-03-25.
//  Copydroit (c) 2015 Daehli Nadeau-Otis. All droits reserved.
//

/*----------------Bibliothèque----------------*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <fstream>
#include "Header.h"
using namespace std;

/*----------------Function----------------*/
void printPretty(noeud *root, int level, int indentSpace, ostream& out);
void enrFichier(string seq);

//Struct pour classer par niveau
struct lvl {
	int valor;
	int niveau;
	bool operator < (const lvl& a) const {
		return niveau < a.niveau;
	}
};
void Niveler (noeud *&racine, vector <lvl> &pile_daffichage, int &nv);

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

noeud* ABR :: SupprimerMin(noeud *&racine){
	if ( racine->gauche != NULL ) // on continue à gauche
		return SupprimerMin (racine->gauche) ;
	else {// le minimum est trouvé à ce stade
		noeud* temp = racine;
		racine = racine->droit;
		return temp;
	}
} 

void ABR::Supprimer(noeud *&racine, int d){
    if ( racine == NULL )
		cout << d << " n'est pas dans l'arbre.";
    else if (d < racine->valeur){
		Supprimer(racine->gauche, d);
	}
	else if (d > racine->valeur){
		Supprimer(racine->droit,d);
    }
    else {
		noeud *temp = racine;
		if ( racine->gauche == NULL ) // a seulement un fils droit
			racine = racine->droit ; // faire pointer vers la droite
		else if ( racine->droit == NULL ) // seulement un fils gauche
			racine = racine->gauche ;
		else { // le noeud a deux fils
			temp = SupprimerMin ( racine->droit ) ;
			// supprime le plus petit du fils droit
			racine->valeur = temp->valeur;
			}
		delete temp ;
	}
}

void ABR:: Afficher_Arbre(noeud *racine, int niveau){
	vector <lvl> output;
	Niveler (racine, output, niveau);
    // Imprime les éléments de la liste Output
	cout << "Niveau 0 : ";
	
	// Répéter aussi longtemps qu’il reste des éléments dans la liste
	for (int i=0; i <output.size(); i++) {
		if (output[i].niveau > niveau)
			cout << endl << "Niveau " << output[i].niveau << " : ";
		cout << output[i].valor << " ";
		niveau = output[i].niveau;
	}
}

int ABR ::Afficher_hauteur(noeud *racine){
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

bool ABR:: Afficher_Ascendant(noeud *racine, int d){
  if (racine == NULL) {
		return false;
  }
  if (racine->valeur == d){
	  cout << "Ascendant(s) de " << d << " : " ;
	  return true;
  }
  else if (Afficher_Ascendant(racine->gauche, d) || Afficher_Ascendant(racine->droit, d)) {
	  cout << racine->valeur << " ";
	  return true;
  }
  cout <<  d << " n'est pas dans l'arbre.";
  return false;
}

string ABR:: Archiver (noeud *racine){
	string temp;
	if (racine != NULL) {
		cout << racine->valeur;
		temp += to_string(racine->valeur);
		if (racine->gauche != NULL) {
			 cout << " ";
			 temp += " ";
		}
		temp += Archiver (racine->gauche);
		temp += Archiver (racine->droit);
		return temp;
	}
	else {
		cout << "/";
		temp += "/";
		return temp;
	}
}

void ABR::Instruction(noeud *&racine, char lecture,int valeur){
    
    switch (lecture) {
case 'I' :	cout << endl << "------------------------------- Insertion de " << valeur << " ------------------------------" << endl;
			Inserer(racine, valeur);// Appel de la classe
    break;
case 'S':	cout << endl << "--------------------------- Suppression de valeur  ---------------------------" << endl;
			Supprimer(racine, valeur);// Appel de la classe
			cout << endl << "------------------------------------------------------------------------------" << endl;
    break;
case 'A':	cout << endl << "---------------------------- Affichage par niveau ----------------------------" << endl;
			Afficher_Arbre(racine, 0);// Appel de la classe
			cout << endl << "------------------------------------------------------------------------------" << endl;
    break;
case 'H' :	cout << endl << "----------------------------- Hauteur de l'arbre -----------------------------" << endl;
			cout << "La hauteur de l'arbre est : " << Afficher_hauteur(racine) << endl;// Appel de la classe
			cout <<  "------------------------------------------------------------------------------" << endl;
    break;
case 'G' :	cout << endl << "--------------------------- Ascendant(s) de valeur ---------------------------" << endl;
			if (racine->valeur == valeur) cout << "La racine n'a pas d'ascendants !";
			else Afficher_Ascendant(racine, valeur);// Appel de la classe
			cout << endl << "------------------------------------------------------------------------------" << endl;
    break;
case 'T' :	cout << endl << "------------------------- Implementation sequentielle ------------------------" << endl;
			enrFichier(Archiver(racine));// Appel de la classe 
			cout << "		**ARCHIVE dans imple_seq.txt**";
			cout << endl << "------------------------------------------------------------------------------" << endl;
    break;
	}
}


int main() {
   ABR arbre;

   noeud* racine = arbre.getRacine();
   string lecture;
   cout << "Entrer le nom du fichier : "; cin >> lecture;
	
   ifstream lire(lecture.c_str(), ios::in); // ios:: in lecture seulement
   if  (lire.fail()){
       cerr << "Erreur pour l'ouverture du fichier" <<endl;
   }
   else {
	   while (!lire.eof()) {// Je vais esseyer un drôle de code
		   char commande;
           int valeur = 0;
           // si non  getline(lire, commande, ','); // la virgule serait délimiteur
           lire >> commande; 
			commande = toupper(commande);
            lire.ignore();// Enlever la virgule
			if (commande == 'I' || commande == 'S' || commande == 'G') {
				lire >> valeur; // Permet de lire dans un fichier les élément qui y sont inscrit*
			}
            //Pour voir l'intérieur du fichier contenu
            arbre.Instruction(racine, commande,valeur);
        }
        lire.close();
    }
   cout << endl << "================================================================================";
   printPretty (racine, 1, 2, cout);
   cout << endl << "================================================================================" << endl;

   system ("pause");
   return 0;
}
/* -------------------------------------------------------------------------------*/
/* DESCRIPTION :      Fonction principale du programmme								*/
/* PARAMETRES :		  Aucun															*/
/* VALEUR DE RETOUR : Aucune 														*/
/* REMARQUE : 		  Aucune														*/
/* -------------------------------------------------------------------------------*/
void enrFichier(string seq) {
	ofstream o ("imple_seq.txt", ios::out | ios::trunc);
	if (o) 
		o << seq;
	else 
		cerr << "Erreur a l'ouverture !";
	o.close();
}

void Niveler (noeud*&racine, vector <lvl> &pile_daffichage, int &nv) {
	bool visited = false;
	if (racine == NULL) {
		nv++;
		return;
	}
	else {
		Niveler (racine->gauche, pile_daffichage, nv);
		nv = 0;
		Niveler (racine->droit, pile_daffichage, nv);
		if (racine->droit == NULL && racine->gauche == NULL) nv = 0;
		lvl courant;
		courant.niveau = nv;
		courant.valor = racine->valeur;
		pile_daffichage.push_back (courant);
		nv++;
	}
	sort(pile_daffichage.begin(), pile_daffichage.end());
}

/*******************************************************************************************************************************/
/****************************************************MAKE TREE BECOME PRETTY****************************************************/
/*******************************************************************************************************************************/

// Find the maximum height of the binary tree
int maxHeight(noeud *p) {
  if (!p) return 0;
  int leftHeight = maxHeight(p->gauche);
  int rightHeight = maxHeight(p->droit);
  return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
}

// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<noeud*>& nodesQueue, ostream& out) {
  deque<noeud*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {  
    out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << endl;
}
 
// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<noeud*>& nodesQueue, ostream& out) {
  deque<noeud*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->gauche) ? setfill('_') : setfill(' '));
    out << setw(branchLen+2) << ((*iter) ? to_string((*iter)->valeur) : "");
    out << ((*iter && (*iter)->droit) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
  }
  out << endl;
}
 
// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<noeud*>& nodesQueue, ostream& out) {
  deque<noeud*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? to_string((*iter)->valeur) : "");
  }
  out << endl;
}
 
// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the gauche (eg, indentSpace of 0 means the lowest level of the gauche node will stick to the gauche margin)
void printPretty(noeud *root, int level, int indentSpace, ostream& out) {
  int h = maxHeight(root);
  int nodesInThisLevel = 1;
 
  int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between gauche neighbor node's droit arm and droit neighbor node's gauche arm
  int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the gauche most node of each level only)
    
  deque<noeud*> nodesQueue;
  nodesQueue.push_back(root);
  for (int r = 1; r < h; r++) {
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    branchLen = branchLen/2 - 1;
    nodeSpaceLen = nodeSpaceLen/2 + 1;
    startLen = branchLen + (3-level) + indentSpace;
    printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
 
    for (int i = 0; i < nodesInThisLevel; i++) {
      noeud *currNode = nodesQueue.front();
      nodesQueue.pop_front();
      if (currNode) {
       nodesQueue.push_back(currNode->gauche);
       nodesQueue.push_back(currNode->droit);
      } else {
        nodesQueue.push_back(NULL);
        nodesQueue.push_back(NULL);
      }
    }
    nodesInThisLevel *= 2;
  }
  printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
  printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

/*******************************************************************************************************************************/
/*******************************************************************************************************************************/
