#ifndef MEEPLE_H
#define MEEPLE_H

#include <stdlib.h>
#include <stdio.h>

#include "carte.h"
#include "link.h"
#include "../updateFunctions/updateTown.h"
#include "../updateFunctions/updateField.h"
#include "../updateFunctions/updateRoad.h"


int display_meeple_cloister(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[],int len);
struct position ConvertZRoad(int z);
int IsMeepleAvailbleRoad(struct road *find[],struct triplet *test[],int taille,struct position possibility[], int len);
int display_meeple_road(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[],int len);
int IsMeepleAvailbleTown(struct city *find[],struct triplet *test[],int taille,struct position possibility[], int len);
int display_meeple_town(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[],int len);
int IsMeepleAvailbleField(struct field *find[],struct triplet *test[],int taille,struct position possibility[], int len);
int display_meeple_field(struct boardgame * boboard,struct tuille *tutuille,struct position possibility[],int len);
int display_meeple(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[]);


#endif
