
#pragma once

#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>



#include "Noeud.h"

using namespace std;

vector<bool> decomposition (boost::multiprecision::int1024_t n){
    vector<bool> result;
    while (n!=0)
    {   
        boost::multiprecision::cpp_int res = n % 2;
        if (res == 1)
            result.push_back(1);
        else {
            result.push_back(0);
        }
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
 
vector<bool> table (boost::multiprecision::int1024_t x, int n){
return completion(decomposition(x),n);
}

// Création de l'arbre initial
shared_ptr<Noeud> creation_arbe(vector<bool> table){
    queue <shared_ptr<Noeud>> liste_noeud;
    // Créations des fuielles
    for (size_t i=0;i<table.size();++i){
        liste_noeud.push(make_shared<Noeud>(nullptr,nullptr,0,table[i]));
    }
    // création des noeuds 
    while (liste_noeud.size()!=1){
        // Constructeur par copie qui alloue la mémoire !!
        shared_ptr<Noeud> n1 = liste_noeud.front();
        liste_noeud.pop();
        shared_ptr<Noeud> n2 = liste_noeud.front();
        liste_noeud.pop();
        // Création du nouveau noeud
        shared_ptr<Noeud> pere =make_shared<Noeud>(n1,n2,n1->id_int+1,true);
        // On modfie le pere des noeuds actuel
        n1->pere = pere;
        n2->pere = pere;
        liste_noeud.push(pere);
        
    }
    // On retourne la racine de l'arbre
    return liste_noeud.front();
} 

// Fonction de luka
string lukas (shared_ptr<Noeud> racine){
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

shared_ptr<Noeud> compression_arbre(shared_ptr<Noeud> racine,vector<pair<string,shared_ptr<Noeud>>>& tableau_comp){
       // Process sur une feuille !
        if (racine!=nullptr){       
            // Process sur un noeud interne !
            shared_ptr<Noeud> newGauche = compression_arbre(racine->filsGauche,tableau_comp);
            shared_ptr<Noeud> newDroite = compression_arbre(racine->filsDroit,tableau_comp);
        
            // Mise a jour des fils du noeud courant !
            racine->filsGauche = newGauche;
            racine->filsDroit = newDroite;
            // On calcule le mot de lukas 
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
shared_ptr<Noeud> robdd ( shared_ptr<Noeud> racine,vector<pair<string,shared_ptr<Noeud>>>& tableau_robdd){

    if (racine != nullptr){
        if (racine->visite == false){
        // On met le sommet visité a vrai ! 
        racine->visite = true;

       shared_ptr<Noeud> newGauche = robdd(racine->filsGauche,tableau_robdd);
       shared_ptr<Noeud> newDroite = robdd(racine->filsDroit,tableau_robdd);

        if (newGauche == newDroite && newGauche!=nullptr && newDroite != nullptr){

            if (racine->pere == nullptr){
                return racine->filsGauche;
            }
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
        
    }
    return nullptr;
}

// Construction des dot 
void parcours_arbre(shared_ptr<Noeud> racine, string& s,vector<shared_ptr<Noeud>>& deja_affiche){
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

void dot_racine(shared_ptr<Noeud> racine, string path){
    string graph_res;
    vector <shared_ptr<Noeud>> deja_affiche;
    parcours_arbre(racine,graph_res,deja_affiche);
    graph_res= "graph { " + graph_res + "}";
    ofstream flux(path);
    flux << graph_res << endl;

}

// Convertion tomporelle 

string convertion (chrono::milliseconds::rep temps_execution){
    string res = to_string(temps_execution % 1000);
    temps_execution = temps_execution/1000;
    res = to_string(temps_execution%60) + "sec:" + res + "ms";
    temps_execution = temps_execution/60;
    return to_string(temps_execution) + "min:" + res;
}