#ifndef UPDATE_FIELD_H
#define UPDATE_FIELD_H

#include <stdlib.h>
#include <stdio.h>

#include "../structure/carte.h"
#include "../structure/link.h"
#include "updateTown.h"

//Met dans le tableau un champ par endroit de la tuil (sans se soucier des jonctions)//
int ExtractField(struct tuille * tutuille, struct field * fieldTutuille[]);





//=============================================//
struct position ReverseZ(struct triplet * tr);






//Retourne la valeur du meeple d'un champ s'il y en a un, sinon NONE//
int MeepleInField(struct tuille * tutuille, struct field * f);

//Copie le contenu d'un pointeur de champ dans un autre//
void copie_triple(struct triplet *t1,struct triplet *t2);

//Crée le champ dans le cas d'un monastère//
void MonasteryField(struct tuille * tutuille,struct field *fieldTutuille[], struct field *fieldInTown[],int res[]);

//Retourne le nombre de champ différents dans une tuile//
int NumberField(struct tuille * tutuille);

//Fait la fusion interne dans le cas où il n'y a pas de ville sur la tuile//
void InternFusionFieldNoTown(struct tuille * tutuille,struct field * fieldTutuille[],struct field * fieldInTown[],int res[]);

//Fait la fusion interne dans le cas où il n'y a pas de route//
void InternFusionFieldTownNoRoad(struct tuille * tutuille, struct field * fieldTutuille[], struct field * fieldInTown[], int res[]);

//Fait la fusion interne dans le cas où il y a présence de route//
void InternFusionFieldTownOneRoad2(struct tuille *tutuille, struct field *fieldTutuille[], struct field *fieldInTown[], int res[]);

//S'occupe du cas des bouts de ville triple, et appele la fonction précedente si la ville n'est pas un bout triple//
void InternFusionFieldTownOneRoad(struct tuille *tutuille, struct field *fieldTutuille[], struct field *fieldInTown[], int res[]);

//Fait la fusion interne s'il y a trois route et une ville//
void InternFusionFieldTownThreeRoad(struct tuille * tutuille, struct field * fieldTutuille[],struct field *fieldInTown[],int res[]); 

//Renvoie TRUE si la tuile présente le paysage ville, FALSE sinon//
int IsTown(struct tuille * tutuille);

//Permet de faire la transition vers la bonne fonction, dans le cas où il y a présence de ville// 
void InternFusionFieldTown(struct tuille * tutuille, struct field * fieldTutuille[],struct field *fieldInTown[],int res[]);

//Permet de faire la transition vers la bonne fonction, parmi les différents cas sité précedement//
void InternFusionField(struct tuille * tutuille, struct field *fieldTutuille[],struct field *fieldInTown[],int res[]);

//Renvoie FALSE si le triplet est contenu dans la structure, TRUE sinon//
int NotIn(struct field *f,struct triplet tri);

//Fusionne deux champs//
void MergeField(struct field *f,struct field * find);

//Fusionne les champs présents dans un tableau de champ//
void FusionField(struct field * f, struct field * find[],struct triplet next[], int len);

//Teste si deux triplets sont identiques//
int same_triplet(struct triplet * t1,struct triplet * t2);

//Renvoie TRUE si deux champs sont identiques, FALSE sinon//
int IsEqualField(struct field * f1,struct field * f2);

//Renvoie un champ depuis une ville s'il est égale à F, NULL sinon//
struct field * FindFieldInTown(struct city * c,struct field * f);

//Renvoie le champ depuis le tableau de jeu s'il est égale à f//
struct field * findTownField(struct boardgame * boboard,struct field * f);

//Renvoie un triplet vide//
struct triplet triplet_vide();

//Renvoie la position de la tuile vers laquelle le triplet pointe//
struct position DirectionField(struct boardgame * boboard, struct triplet * t);

//Forme le triplet qui doit être recherché pour la liaison entre les tuiles//
struct triplet NextTripletField(struct triplet * t,struct position p,int dir_next, int dir_origine);

//Renvoie TRUE si le triplet est dans le champ, FALSE sinon//
int FindTripletInField(struct field * ch, struct triplet * t);

//Renvoie le champ de la ville possèdant le triplet, NULL si aucun ne le possède//
struct field *FindTripletFieldInTown(struct city *c, struct triplet* t);

//Cherche le champ, parmi la liste des champs et la liste des champs possèdés par des ville, possèdant le triplet//
struct field * FindField(struct boardgame * boboard, struct triplet next);

//Fusionne dans le cas d'un champ appartenant à une ville//
void ExternFusionFieldInTown(struct boardgame * boboard,struct field * f);

//Renvoie la ville qui possède le champ f, NULL si rien est trouvé//
struct city * IsTownField(struct boardgame * boboard, struct field * f);

//Fusionne deux champs entre eux//
void MergeFieldNoTown(struct boardgame * boboard,struct field * f,struct field * find);

//S'occupe de la fusion des champs avec tout les champs potentiels trouvés//
void FusionFieldNoTown(struct boardgame * boboard, struct field * f, struct field * find[],struct triplet next[], int len, int number_of_finds);

//Fusionne dans le cas où il n'y a pas de ville//
void ExternFusionFieldNoTown(struct boardgame * boboard,struct field * f);

//Focntion coprs du programme//
void UpdateField(struct boardgame * boboard, struct tuille tutuille);

#endif
