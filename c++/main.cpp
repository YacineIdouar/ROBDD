
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include "fonction_algo.h"


using namespace std;
using namespace chrono;

// Affichage du Dot 


// Réalisation des réprésentation graphiques 
void benchmark(int puissance, string path_table,string path_plot,int nb_element){

    boost::multiprecision::int1024_t fin (pow(2,puissance));
    //fin = fin + ((long)pow(2,1023) - 1); cas de 1024 bits

    cout << fin << endl;
    boost::multiprecision::int1024_t debut (1);
    boost::multiprecision::int1024_t interval((fin-debut)/(nb_element));
    cout << interval << endl;
    
    // Ouverture des deux fichiers fichier 
    ofstream flux_plot;
    flux_plot.open(path_plot);
    ofstream flux_tab;
    flux_tab.open(path_table, ios_base::app);


    vector<pair<unsigned long,int>> taille_differente;

    // Variable du benchmark
    time_point<high_resolution_clock> start_point,end_point;
    milliseconds::rep exec = 0.0;

    boost::multiprecision::int1024_t i;
    for (i =debut; i<fin ; i+= interval){

        shared_ptr<Noeud> racine = creation_arbe(table(i,puissance));
        vector<pair<string,shared_ptr<Noeud>>> tableau_robdd;

        start_point = high_resolution_clock::now();
        racine = robdd(racine,tableau_robdd);
        end_point = high_resolution_clock::now();

        auto start = time_point_cast<milliseconds>(start_point).time_since_epoch().count();
        auto end = time_point_cast<milliseconds>(end_point).time_since_epoch().count();
        exec += end-start;

        auto it = find_if(taille_differente.begin(),taille_differente.end(),[&](auto & elem){ return elem.first == tableau_robdd.size();});

        if(it!=taille_differente.end()){
            it->second ++;
        }else{
            taille_differente.push_back(make_pair(tableau_robdd.size(),1));
        }
        

        cout << i << endl;

    }
    // Les variables à écrire 
    sort(taille_differente.begin(),taille_differente.end(),[](auto& elem1, auto& elem2 ){return elem2.first > elem1.first;});

    for (auto & i : taille_differente){
        flux_plot << i.first  << "\t" << i.second<< endl;
    }
   
    //flux_tab << log2(puissance)  << " " << nb_element << " " << taille_differente.size() << " " << convertion(exec) << " " << exec/double (nb_element) << endl;
    
 
}


int main (){


    benchmark(2,"table.txt","plot.txt",3);
    /*int puiss = 8;
    boost::multiprecision::int1024_t  nombre (17);
    cout << nombre << endl;
    // Création de la table des correspondance 

    shared_ptr<Noeud> racine = creation_arbe(table(nombre,puiss));
    vector<pair<string,shared_ptr<Noeud>>> tableau_robdd;
    cout << lukas(racine) << endl;
    //vector<pair<string,shared_ptr<Noeud>>> tableau_comp;

    racine = robdd(racine,tableau_robdd);
    dot_racine(racine,"robdd.gv");

    //cout << tableau_robdd.size() << endl;

    //racine = compression_arbre(racine,tableau_robdd);
    //dot_racine(racine,"compression.gv");*/
    
    return 0;
}