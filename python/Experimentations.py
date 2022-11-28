from math import pow
import time
from code.Compression import compression_bdd
from code.Tools import taille_arbre_compresse_robdd
from code.Tree import cons_arbre
from experimentations.Gnuplot import plot
from experimentations.Table import *
from datetime import timedelta
import sys

if len(sys.argv) != 2 : 
    nombre_var = int(input("Tapez le nombre de variables des fonctions a experimente : "))
else :
    nombre_var = int(sys.argv[1])
if nombre_var <= 1:
     borne_inf = 0
else:
    borne_inf = int(pow(2,pow(2,nombre_var - 1)))
borne_sup = int(pow(2,pow(2,nombre_var))) 
dict = {}
nbr_taille_differentes = 0

print("Patientez SVP ...")

temps_debut = time.time()
for i in range(borne_inf,borne_sup):
    tree = compression_bdd(cons_arbre(i))
    taille = taille_arbre_compresse_robdd(tree)    
    try:
        dict[taille] = dict[taille] + 1
    except KeyError :
        dict[taille] = 1
        nbr_taille_differentes += 1


temps_fin = time.time()
temps = temps_fin - temps_debut
nbr_taille_differentes = 0
with open(f"./experimentations/gnuplot_data/nombre_var{nombre_var}.dat","w") as f:
    for k in {k: v for k, v in sorted(dict.items(), key=lambda item: item[0])}:
        f.write(f"{k} {dict[k]}\n")
        nbr_taille_differentes += 1
plot(nombre_var)
nbr_func = borne_sup - borne_inf
temps_par_robdd = temps/ nbr_func

add_line_in_table(nombre_var ,nbr_func ,nbr_taille_differentes ,str(timedelta(temps)) ,temps_par_robdd)


