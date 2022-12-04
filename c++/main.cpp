
#include <iostream>
#include <fstream>
#include "fonction_algo.h"

using namespace std;

// Affichage du Dot 
void parcours_arbre(Noeud* racine, string& s,vector<Noeud*>& deja_affiche){
    if (racine->filsDroit == nullptr){return;}
    // Vérifier si un noeud à déja était visité !
    if (find(deja_affiche.begin(),deja_affiche.end(),racine) == deja_affiche.end()){
    s+= '"' + racine->mot_luka + '"' +" -- " + '"'+racine->filsGauche->mot_luka +'"'   + " [color = red] " +  "\n";
    s+= '"' + racine->mot_luka + '"' + " -- " +'"'+ racine->filsDroit->mot_luka + '"'   +" [color = green ]" + " \n";
    deja_affiche.push_back(racine); // On ajoute la racine à la liste!
    }
    parcours_arbre(racine->filsDroit,s,deja_affiche);
    parcours_arbre(racine->filsGauche,s,deja_affiche);
    
}

void dot_racine(Noeud* racine, string path){
    string graph_res;
    vector <Noeud*> deja_affiche;
    parcours_arbre(racine,graph_res,deja_affiche);
    graph_res= "graph { " + graph_res + "}";
    ofstream flux(path);
    flux << graph_res << endl;

}


int main (){

    int nombre = 38;
    // Création de la table des correspondance 

    Noeud* racine1 = creation_arbe(table(nombre,8));
    Noeud* racine2 = creation_arbe(table(nombre,8));
    cout << lukas(racine1) << endl;

    //string sAv = "";
    //dot_racine(racine,sAv);
    //cout<< sAv  << endl;
    
    vector<pair<string,Noeud*>> tableau_robdd;
    vector<pair<string,Noeud*>> tableau_comp;

    racine1 = robdd(racine1,tableau_robdd);
    dot_racine(racine1,"robdd.gv");

    racine2 = compression_arbre(racine2,tableau_comp);
    dot_racine(racine2,"compression.gv");
   
    return 0;
}