

from code.Dot import dot
from code.Tree import cons_arbre
from code.Compression import compression, compression_bdd, luka



def main ():
    print("Tapez un nombre pour avoir l'arbre de decision et sa compression")
    n = int(input())
    (tree,d) = luka(cons_arbre(n))
    dot(cons_arbre(n),"const_arbre")
    dot(tree,"luka_arbre")
    dot(compression(cons_arbre(n)),"compression arbre")
    dot(compression_bdd(d,tree),"compression_bdd")
    print("La representation des arbres est dans le repertiore dot, mettez ces fichiers sur le site https://graphs.grevian.org/graph pour voir la representation graphique de ces arbres\n")


if __name__ == "__main__":
    main()