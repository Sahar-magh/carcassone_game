#ifndef UPDATE_CLOISTER_H
#define UPDATE_CLOISTER_H

#include <stdlib.h>
#include <stdio.h>

#include "../structure/carte.h"
#include "../structure/link.h"


//Fonction prenant en argument une tuille et renvoyant le nombre de proches voisins qui sont des tuilles non nulles//
int NumberVoisin(struct boardgame * boboard, struct tuille tutuille);

//Fonction accordant les points dans le plateau de jeu//
void CreditPointAbbaye(struct boardgame * boboard, struct abbaye * chapel);

//Copie a2 dans a1//
void copieAbbaye(struct abbaye * a1, struct abbaye * a2);

//Programme prenant en argument une tuille et renvoie le nombre de ses voisins qui sont des chapelles ainsi que la liste de leur positions//
int WhereAbbaye(struct boardgame * boboard, struct tuille tutuille, struct position lst[]);

//Fonction prenant en argument une position de tuile, et rajoute 1 point si c'est une chapelle//
void AddOneVoisin(struct boardgame * boboard, struct position pos);

//Fonction principale permettant de générer une structure chapelle et de les mettre toutes à jour//
void updateCloister(struct boardgame * boboard, struct tuille tutuille);

//Fonction d'affichage//
void aff_cloister(struct abbaye * chapel);
#endif
