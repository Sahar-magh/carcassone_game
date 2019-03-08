#include "meeple.h"


int display_meeple_cloister(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[],int len){
  (void)boboard;
  if(tutuille->milieu == 3){
    possibility[len].x = 1;
    return len++;
  }
  return len;
}

struct position ConvertZRoad(int z){
  struct position res;
  if(z == 1){
    res.x = 0;
    res.y = 1;
  }
  else if(z == 3){
    res.x = 1;
    res.y = 1;
  }
  else if(z == 5){
    res.x = 4;
    res.y = 1;
  }
  else{
    res.x = 3;
    res.y = 1;
  }
  return res;
}
      
int IsMeepleAvailbleRoad(struct road *find[],struct triplet *test[],int taille,struct position possibility[], int len){
  int res = len;
  int cmpt = 0;
  for(int i=0;i<taille;i++){
    cmpt = 0;
    for(int j =0;j<PLAYER_MAX;j++){
      if(find[i]->voleurs[j] != 0)
	cmpt++;
    }
    if(cmpt ==0){
      possibility[res] = ConvertZRoad(test[i]->z);
      res ++;
    }
  }
  return res;
}

int display_meeple_road(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[],int len){
  int res =len;
  struct road * roadTuille[4];
  for(int i=0;i<4;i++){
    roadTuille[i] = RoadVide();
  }
  int taille = ExtractRoad(tutuille,roadTuille);
  struct triplet *test[4];
  struct position junction[4];
  struct triplet next[4];
  struct road * find[4];
  for(int i=0;i<taille;i++){
    test[i] = (struct triplet *)roadTuille[i]->nys_idea->head->data;
    junction[i] = DirectionRoad(boboard,(*test[i]));
    next[i] = NextTriplet(test[i],junction[i],boboard->board[junction[i].x][junction[i].y].dir,boboard->board[test[i]->x][test[i]->y].dir);
    find[i] = FindRoad(boboard,&next[i]);
  }
  res = IsMeepleAvailbleRoad(find,test,taille,possibility,len);
  return res;
} 


int IsMeepleAvailbleTown(struct city *find[],struct triplet *test[],int taille,struct position possibility[], int len){
  int res = len;
  int cmpt = 0;
  for(int i=0;i<taille;i++){
    cmpt = 0;
    for(int j =0;j<PLAYER_MAX;j++){
      if(find[i]->chevaliers[j] != 0)
	cmpt++;
    }
    if(cmpt ==0){
      possibility[res] = ConvertZRoad(test[i]->z);
      res ++;
    }
  }
  return res;
}

int display_meeple_town(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[],int len){
  int res =len;
  struct city * townTuille[4];
  for(int i=0;i<4;i++){
    townTuille[i] = TownVide();
  }
  int taille = ExtractTown(tutuille,townTuille);
  struct triplet *test[4];
  struct position junction[4];
  struct triplet next[4];
  struct city * find[4];
  for(int i=0;i<taille;i++){
    test[i] = (struct triplet *)townTuille[i]->lst_triplet->head->data;
    junction[i] = DirectionTown(boboard,test[i]);
    next[i] = NextTripletTown(test[i],junction[i],boboard->board[junction[i].x][junction[i].y].dir,boboard->board[test[i]->x][test[i]->y].dir);
    find[i] = FindTown(boboard,next[i]);
  }
  res = IsMeepleAvailbleTown(find,test,taille,possibility,len);
  return res;
}

int IsMeepleAvailbleField(struct field *find[],struct triplet *test[],int taille,struct position possibility[], int len){
  int res = len;
  int cmpt = 0;
  for(int i=0;i<taille;i++){
    cmpt = 0;
    for(int j =0;j<PLAYER_MAX;j++){
      if(find[i]->paysans[j] != 0)
	cmpt++;
    }
    if(cmpt ==0){
      possibility[res].x = test[i]->z/3;
      possibility[res].y = test[i]->z%3;
      res ++;
    }
  }
  return res;
}

int display_meeple_field(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[],int len){
  int res =len;
  struct  field* fieldTuille[12];
  for(int i=0;i<12;i++){
    fieldTuille[i] = FieldVide();
  }
  int taille = ExtractField(tutuille,fieldTuille);
  struct triplet *test[12];
  struct position junction[12];
  struct triplet next[12];
  struct field * find[12];
  for(int i=0;i<taille;i++){
    test[i] = (struct triplet *)fieldTuille[i]->lst_triplet->head->data;
    junction[i] = DirectionField(boboard,test[i]);
    next[i] = NextTripletField(test[i],junction[i],boboard->board[junction[i].x][junction[i].y].dir,boboard->board[test[i]->x][test[i]->y].dir);
    find[i] = FindField(boboard,next[i]);
  }
  res = IsMeepleAvailbleField(find,test,taille,possibility,len);
  return res;
}
  
int display_meeple(struct boardgame * boboard,struct tuille *tutuille, struct position possibility[]){
  int len = 0;
  len = display_meeple_cloister(boboard,tutuille,possibility,len);
  len = display_meeple_road(boboard,tutuille,possibility,len);
  len = display_meeple_town(boboard,tutuille,possibility,len);
  len = display_meeple_field(boboard,tutuille,possibility,len);
  return len;
}

/*
int main(){
  printf("meeple\n");
  return 0;
}
*/
