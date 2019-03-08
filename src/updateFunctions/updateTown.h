#ifndef UPDATE_TOWN_H
#define UPDATE_TOWN_H

#include <stdlib.h>
#include <stdio.h>

#include "../structure/carte.h"
#include "../structure/link.h"
#include "../structure/Free.h"

//initialisation d'un champ vide//
struct field * FieldVide();

//initialisation d'une ville vide//
struct city * TownVide();

//prend en parametre une ville city et un link de villes 
//recherche dans link de villes la ville city et la supprime 
void RemoveTown(struct link *cities, struct city *t);

//Copie une tuile à partir d'un pointeur//
void copie_tuile_town(struct tuille * t1, struct tuille * t2);

//Convertir une orientation : Nord, Sud ..., en un entier utilisable pour les triplets//
int attribut_z_town(int i);

//Prends une tuille en argument, et stocke toute les potentiels villes dans un tableau de struct city//
int ExtractTown(struct tuille * tutuille, struct city * townTutuille[]);

//Fait le travail inverse de attribut_z_town//
int Reverse_z_town(int z);

//Renvoie le meeple placé sur la tuille//
int TownMeeple(struct tuille tutuille, struct triplet * t);

//Renvoie le nombre de routes dans une tuile (deux dans le cas d'un segment)//
int NumberRoadTown(struct tuille tutuille);

//Linéarise un tableau bidimentionnel "type", en ne prenant que les cases de champs//
int ParcourType(struct tuille tutuille, struct triplet lst_t[]);

//Permet d'obtenir les triplets de champs dans le cas d'un bout de ville simple//
void SingleTripletField(struct tuille tutuille, struct field * f);

//Renvoie le joueur possédant la tuille//
int FieldMeeple(struct tuille tutuille, struct field * f);

//Copie le contenu d'un pointeur de champ dans un autre//
void copie_field(struct field * f1,struct field * f2);

//Crée les champs pour un bout de ville simple//
void SingleField(struct city * town, struct tuille tutuille);

//Compte le nombre de bords de type ville//
int NumbBorder(struct tuille tutuille);

//Permet de savoir si la tuile présente un "pont" de ville//
int OppositeTriplet(struct triplet * t1, struct triplet * t2);

//Forme les champs dans la ville dans le cas d'une ville double//
void PluralFieldDouble(struct city * town,struct tuille tutuille);

//Forme les champs dans la ville dans le cas d'une ville triple//
void PluralFieldTriple(struct city * town,struct tuille tutuille);

//Associe la tuile à l'étude qui lui correspond//
void PluralField(struct city * town, struct tuille tutuille);

//Fusionne les villes internes de la tuile si besoin (pour les bouts de villes prennant plus qu'un seul côté sur une tuille) et met les extremités et les meeples a terme//
int InternFusionTown(struct tuille tutuille,struct city *townTutuille[], int taille);

//Copie le contenu d'un pointeur ville dans un autre//
void copie_town(struct city * t1, struct city * t2);

//Renvoie la position vers laquelle pointe le triplet//
struct position DirectionTown(struct boardgame * boboard, struct triplet *t);

//Renvoie TRUE si les deux positions sont identiques, FALSE sinon//
int posDiff(struct position p1, struct position p2);

//Renvoie vrai si une tuille présente deux bouts de villes simples, FALSE sinon//
int IsDuoTuile(struct city * t);

//Met les points d'une ville dans le plateau de jeu et au bon joueur//
void CreditPointTown(struct boardgame * boboard,struct city * t);

//Permet d'obtenir le triplet en contact avec la ville (celui de la tuile posé précedement//
struct triplet NextTripletTown(struct triplet * t, struct position p, int dir_next, int dir_origine);

//Fusionne deux villes//
void MergeTown(struct city *t1,struct city *t2);

//Renvoie TRUE si le triplet se trouve dans la ville, FALSE sinon//
int FindTripletInTown(struct city * c, struct triplet t);

//Cherche la ville possèdant le triplet passé en argument//
struct city * FindTown(struct boardgame *boboard, struct triplet t);

//Fusionne un bout de ville simple avec une ville du tableau de jeu//
void SingleExternFusion(struct boardgame * boboard, struct city * town);

//Renvoie le tableau tab[] de booléen, 1 si le bout de ville possède une jonction possible avec une ville, et 0 sinon//
void TabPositionVide(int tab[],struct position junction[],int len,struct boardgame * boboard);

//Fusionne un bout de ville double avec une ville du tableau de jeu//
void DoubleExternFusion(struct boardgame * boboard, struct city * town);

//Fusionne un bout de ville triple avec une ville du tableau de jeu//
void TripleExternFusion(struct boardgame * boboard, struct city * town);

//Fusionne un bout de ville de type centre avec une ville du tableau de jeu//
void QuatraExternFusion(struct boardgame * boboard,struct city * town);

//Fusionne un bout de ville ajouté avec une ville déjà éxistante, ou en crée une nouvelle//
void ExternFusionTown(struct boardgame * boboard, struct city * town);

//Fonction corps du programme: mattre à jour les villes //
void UpdateTown(struct boardgame * boboard, struct tuille tutuille);

//Fonctions d'affichage//
void aff_Town(struct city * town);
void aff_lnk_field(struct link *lnk);
void aff_lnk_triplet(struct link * lnk);
void aff_lnk_tuile_town(struct link * lnk);

#endif
