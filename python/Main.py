

from code.Dot import dot
from code.Tree import cons_arbre
from code.Compression import compression, compression_bdd, luka



def main ():
    
    n = int(input("Tapez un nombre pour avoir l'arbre de decision et sa compression: "))
    tree = cons_arbre(n)
    (tree_luka,_) = luka(tree)
    dot(tree,"const_arbre")
    dot(tree_luka,"luka_arbre")
    dot(compression(tree),"compression arbre")
    dot(compression_bdd(tree),"compression_bdd")
    print("La representation des arbres est dans le repertiore dot, mettez ces fichiers sur le site https://graphs.grevian.org/graph pour voir la representation graphique de ces arbres\n")


if __name__ == "__main__":
    main()