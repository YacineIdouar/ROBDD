#pragma once

#include<string>





class Noeud{
    
    public :
    int id_int;
    std::string identifiant;
    Noeud* filsGauche;
    Noeud *filsDroit;
    Noeud* pere;
    bool reel;
    std::string mot_luka;

    Noeud(Noeud* filsGauche,Noeud* filsDroit,int id_int,bool reel) {
      
        // La cohérence des noeuds de l'arbre sera assuré par la fonction de construction
        this->id_int = id_int;
        this->identifiant = "x" + std::to_string(id_int);
        this->filsDroit = filsDroit;
        this->filsGauche = filsGauche;
        this->pere = nullptr;
        this->reel = reel;
        this->mot_luka = "";
    }
    

};