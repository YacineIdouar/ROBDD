
from code.Tools import hash_luka
from code.Tree import Tree,makeNode,makeLeaf
from math import log2 as log


def luka (tree: Tree) :
    dict = {}
    dictl = {}
    dictl[True] = 1
    dictl[False] = 0
    (tree,_) = __luka(tree,dict,dictl,2,tree)
    return (tree,dict)

def __luka(tree: Tree,dict:dict,dictl : dict,indice_label_dictl : int,racine : Tree) -> Tree:
    #If tree.false == None also tree.true == None
    if tree.false == None :
        leaf = makeLeaf(dictl[tree.label])
        dict[dictl[tree.label]] = tree
        return (leaf,dictl[tree.label])
    n = 0
    try :
        n = dictl[tree.label]   
    except KeyError:
        indice_label_dictl = indice_label_dictl +1 
        dictl[tree.label] = indice_label_dictl
        n = indice_label_dictl

    (labelFalse,h1) = __luka(tree.false, dict, dictl , indice_label_dictl, racine)
    (labelTrue,h2) = __luka(tree.true, dict, dictl, indice_label_dictl, racine)
    h = hash_luka(n,h1,h2,racine.taille,racine.hauteur)
    node = makeNode(h,labelFalse,labelTrue)
    dict[h] = tree
    return (node,h)


def compression(tree: Tree) -> Tree :
    (treeLuka,dict) = luka (tree)
    return __compression(treeLuka,dict)


def __compression(tree: Tree,dict:dict) -> Tree :
    if tree.false == None :
        return dict[tree.label]
    t = dict[tree.label]
    t.false = __compression(tree.false,dict)
    t.true = __compression(tree.true,dict)
    return t

def compression_bdd(tree:Tree):
    (tree,dict) = luka(tree)
    return deletion_rules(dict,{},margin_rules({},terminal_rules(dict,tree)))

def terminal_rules(dict : dict, tree:Tree):
    if tree.false == None :
        return dict[tree.label]
    return makeNode(tree.label,terminal_rules(dict,tree.false),terminal_rules(dict,tree.true))
    

def margin_rules(dict:dict,tree:Tree):
    try :
        dict[tree.label]
        return dict[tree.label]

    except KeyError :
        if tree.false == None :
            dict[tree.label] = tree
            return tree
        dict[tree.label] = makeNode(tree.label,margin_rules(dict, tree.false),margin_rules(dict, tree.true))
        return dict[tree.label]



def deletion_rules(dict:dict,dict2 : dict,tree:Tree):
    try :
        return dict2[tree.label]
    except KeyError :
        if tree.false == None :
            return dict[tree.label]
        if tree.false == tree.true :
            if tree.false.false == None:
                return tree.false
            dict2[tree.label] = deletion_rules(dict,dict2,makeNode(tree.false.label, tree.false.false,tree.false.true))
            return dict2[tree.label]
        dict2[tree.label] = makeNode(dict[tree.label].label,deletion_rules(dict,dict2,tree.false),deletion_rules(dict,dict2,tree.true))
        return dict2[tree.label]