#pragma once

#include<string>
#include<memory>




class Noeud{
    
    public :
    int id_int;
    std::string identifiant;
    std::shared_ptr <Noeud> filsGauche;
    std::shared_ptr <Noeud> filsDroit;
    std::shared_ptr <Noeud>  pere;
    bool reel;
    bool visite;
    std::string mot_luka;

    Noeud(std::shared_ptr <Noeud> filsGauche,std::shared_ptr <Noeud>  filsDroit,int id_int,bool reel) {
      
        // La cohérence des noeuds de l'arbre sera assuré par la fonction de construction
        this->id_int = id_int;
        this->identifiant = "x" + std::to_string(id_int);
        this->filsDroit = filsDroit;
        this->filsGauche = filsGauche;
        this->pere = nullptr;
        this->reel = reel;
        this->visite = false;
        this->mot_luka = "";
    }
    ~Noeud(){}
    

};