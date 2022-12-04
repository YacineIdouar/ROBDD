
#pragma once

#include <utility>
#include <algorithm>
#include <vector>
#include <queue>

#include "Noeud.h"

using namespace std;

vector<bool> decomposition (int n){
    vector<bool> result;
    while (n!=0)
    {   
        result.push_back(n%2);
        n/=2;
    }
    
    return result;
}

vector<bool> completion(vector<bool> liste, int n){
    int diff = (int)(n - liste.size());
    for (int i=0; i< diff;++i){
        liste.push_back(false);
    }
    auto last = liste.begin()+n;
    return  vector<bool> (liste.begin(),last);
}
 
vector<bool> table (int x, int n){
return completion(decomposition(x),n);
}

// Création de l'arbre initial
Noeud* creation_arbe(vector<bool> table){
    queue <Noeud*> liste_noeud;
    // Créations des fuielles
    for (size_t i=0;i<table.size();++i){
        liste_noeud.push(new Noeud(nullptr,nullptr,0,table[i]));
    }
    // création des noeuds 
    while (liste_noeud.size()!=1){
        // Constructeur par copie qui alloue la mémoire !!
        Noeud* n1 = liste_noeud.front();
        liste_noeud.pop();
        Noeud* n2 = liste_noeud.front();
        liste_noeud.pop();
        // Création du nouveau noeud
        Noeud* pere = new Noeud(n1,n2,n1->id_int+1,true);
        // On modfie le pere des noeuds actuel
        n1->pere = pere;
        n2->pere = pere;
        liste_noeud.push(pere);
        
    }
    // On retourne la racine de l'arbre
    return liste_noeud.front();
} 

// Fonction de luka
string lukas (Noeud* racine){
    if (racine!=nullptr){
        if(racine->id_int == 0){
            switch (racine->reel)
            {
            case true: 
                return "True";
                
            case false : 
                return "False";
            }
        }
        else{
        return racine->identifiant + "(" + lukas(racine->filsGauche) + ")" + "(" + lukas(racine->filsDroit) + ")";
        }
    }
    return "";
}


// La fonction de compression de l'arbre 

Noeud* compression_arbre(Noeud* racine,vector<pair<string,Noeud*>>& tableau_comp){
       // Process sur une feuille !
        if (racine!=nullptr){       
            // Process sur un noeud interne !
            Noeud* newGauche = compression_arbre(racine->filsGauche,tableau_comp);
            Noeud* newDroite = compression_arbre(racine->filsDroit,tableau_comp);
        
            // Mise a jour des fils du noeud courant !
            racine->filsGauche = newGauche;
            racine->filsDroit = newDroite;
        
            // Ajout du noeud de la table si pas existant !
            racine->mot_luka = lukas(racine);
            // On vérifie si le mot existe !
            auto it = find_if(tableau_comp.begin(),tableau_comp.end(),[&racine](auto& param){return  param.first.compare(racine->mot_luka)==0;});
            // Si oui on return le pointeur déja dans le tableau 
            if(it != tableau_comp.end()){   
                        return it->second;
            }
            // Sinon on ajoute le nouveau pointeur trouvé et on return la racine
            else {
                tableau_comp.push_back(make_pair(racine->mot_luka,racine));
                return racine;
            } 
        }
        return nullptr; 
}


// Fonction de ROBDD 
Noeud* robdd (Noeud* racine, vector<pair<string,Noeud*>>& tableau_robdd){

    if (racine != nullptr){
        Noeud* newGauche = robdd(racine->filsGauche,tableau_robdd);
        Noeud* newDroite = robdd(racine->filsDroit,tableau_robdd);

        if (newGauche == newDroite && newGauche!=nullptr && newDroite != nullptr){
            if (racine == racine->pere->filsDroit){
                racine->pere->filsDroit = newGauche;
            }else{
                racine->pere->filsGauche = newGauche;
            }
            return newGauche;
        }else{
            racine->filsGauche = newGauche;
            racine->filsDroit = newDroite;
        
        }
        // Ajout du noeud de la table si pas existant !
            racine->mot_luka = lukas(racine);
            // On vérifie si le mot existe !
            auto it = find_if(tableau_robdd.begin(),tableau_robdd.end(),[&racine](auto& param){return  param.first.compare(racine->mot_luka)==0;});
            // Si oui on return le pointeur déja dans le tableau 
            if(it != tableau_robdd.end()){   
                        return it->second;
            }
            // Sinon on ajoute le nouveau pointeur trouvé et on return la racine
            else {
                tableau_robdd.push_back(make_pair(racine->mot_luka,racine));
                return racine;
            } 
    }
    return nullptr;
}