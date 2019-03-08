#include "updateField.h"


int ExtractField(struct tuille * tutuille, struct field * fieldTutuille[]){
  int taille = 0;
  struct tuille * tmp_t;
  struct triplet * tmp_p;
  for(int i = 0;i<4;i++){
    for(int j = 0;j<3;j++){
      if(tutuille->type[i][j] == 0){
	tmp_t = (struct tuille *)(fieldTutuille[taille])->lst_tutuille->head->data;
	struct lelement * llm_p = llm_empty();
	llm_p->data = (struct triplet *)malloc(sizeof(struct triplet));
	lnk_add2((fieldTutuille[taille])->lst_triplet,llm_p);
        tmp_p = (struct triplet *)llm_p->data;
	tmp_p->x = NONE;
	tmp_p->y = NONE;
	tmp_p->z = NONE;

	copie_tuile_town(tmp_t,tutuille);
	tmp_p->x = tutuille->position[0];
	tmp_p->y = tutuille->position[1];
	tmp_p->z = j + i*3;
	taille ++;
      }
    }
  }
  return taille;
}

struct position ReverseZ(struct triplet * tr){
  struct position pos;
  pos.x = tr->z /3;
  pos.y = (tr->z)%3;
  return pos;
}

int MeepleInField(struct tuille * tutuille, struct field * f){
  struct lelement * current = f->lst_triplet->head;
  struct triplet * tr = (struct triplet *)current->data;
  struct position pos;
  for(int i = 0;i<f->lst_triplet->taille;i++){
    pos = ReverseZ(tr);
    if(tutuille->pion[pos.x][pos.y] != NONE){
      return tutuille->pion[pos.x][pos.y];
    }
    if(current->next != NULL)
      current = current->next;
    tr = (struct triplet *)current->data;
  }
  return NONE;
}

void copie_triple(struct triplet *t1,struct triplet *t2){
  t1->x = t2->x;
  t1->y = t2->y;
  t1->z = t2->z;
}

void MonasteryField(struct tuille * tutuille,struct field *fieldTutuille[], struct field *fieldInTown[],int res[]){
  for(int i = 1;i<res[0];i++){
    lnk_add2(fieldTutuille[0]->lst_triplet,fieldTutuille[i]->lst_triplet->head);
  }
  fieldTutuille[0]->len = 1;
  fieldTutuille[0]->inTown = FALSE;
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      if(tutuille->pion[i][j] != NONE && (i != 0 || j!=1))
	fieldTutuille[0]->paysans[tutuille->pion[i][j]] = 1;
    }
  }
  (void)fieldInTown;
  res[0] = 1;
  res[1] = 0;
}

int NumberField(struct tuille * tutuille){
  if(tutuille->id == CARD_MONASTERY_ROAD) 
    return 1;
  else {
    int numbRoad = NumberRoadTown((*tutuille));
    if(numbRoad == 0)
      return 1;
    if(numbRoad == 1 || numbRoad == 2)
      return 2;
    else if(numbRoad == 3)
      return 3;
    else
      return 4;
  }
}

void InternFusionFieldNoTown(struct tuille * tutuille,struct field * fieldTutuille[],struct field * fieldInTown[],int res[]){
  (void)fieldInTown;
  int type[12];
  int numbField = NumberField(tutuille);
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      type[i*3+j] = tutuille->type[i][j];
    }
  }
  int qui = 0;
  int pos = 0;

  struct lelement * llm[12];
  struct triplet *tmp[12];
  for(int i =0; i<12;i++){
    llm[i] = llm_empty();
    llm[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
    tmp[i] = (struct triplet *)llm[i]->data;
  }

  for(int i=0;i<12;i++){
    if(type[i] == 2){
      qui = (qui + 1)%numbField;
    }
    else{
      if(qui != pos){
	copie_triple(tmp[pos],(struct triplet *)fieldTutuille[pos]->lst_triplet->head->data);
	lnk_add2(fieldTutuille[qui]->lst_triplet,llm[pos]);
      }
      pos++;
    }
  }


  if(numbField == 3){
    fieldTutuille[1]->lst_triplet->head = fieldTutuille[1]->lst_triplet->head->next;
    fieldTutuille[1]->lst_triplet->head->previous = NULL;
    fieldTutuille[2]->lst_triplet->head = fieldTutuille[2]->lst_triplet->head->next;
    fieldTutuille[2]->lst_triplet->head->previous = NULL;
  }
  else if(numbField == 4){
    fieldTutuille[2]->lst_triplet->head = fieldTutuille[2]->lst_triplet->head->next;
    fieldTutuille[2]->lst_triplet->head->previous = NULL;
    fieldTutuille[3]->lst_triplet->head = fieldTutuille[3]->lst_triplet->head->next;
    fieldTutuille[3]->lst_triplet->head->previous = NULL;
  }

  int meeple;
  for(int i=0;i<numbField;i++){
    fieldTutuille[i]->len = 1;
    fieldTutuille[i]->inTown = 0;
    meeple = MeepleInField(tutuille,fieldTutuille[i]);
    if(meeple != NONE)
      fieldTutuille[i]->paysans[meeple] = 1;
  }
  res[0] = numbField;
  res[1] = 0;
}


void InternFusionFieldTownNoRoad(struct tuille * tutuille, struct field * fieldTutuille[], struct field * fieldInTown[], int res[]){
  
  if(tutuille->id == CARD_PLAIN_CITY_SHLD || tutuille->id == CARD_PLAIN_CITY_SHLD || tutuille->id == CARD_CITY_ONE_SIDE || tutuille->id == CARD_CITY_THREE_SHLD || tutuille->id == CARD_CITY_THREE){
    for(int i = 0;i<res[0];i++){
      lnk_add2(fieldInTown[0]->lst_triplet,fieldTutuille[i]->lst_triplet->head);
    }
    res[1] = 6;
    res[0] = 0;
    int meeple = MeepleInField(tutuille,fieldInTown[0]);
    if(meeple != NONE)
      fieldInTown[0]->paysans[meeple] = 1;
    fieldInTown[0]->inTown = TRUE;
    fieldInTown[0]->len = 1;
  }
  else if (tutuille->id == CARD_CITY_TUNNEL_SHLD && tutuille->id == CARD_CITY_TUNNEL){
    for(int i =0;i<res[0]/2;i++){
      lnk_add2(fieldInTown[0]->lst_triplet,fieldTutuille[i]->lst_triplet->head);
    }
    for(int i =res[0]/2;i<res[0];i++){
      lnk_add2(fieldInTown[1]->lst_triplet,fieldTutuille[i]->lst_triplet->head);
    }
    int meeple = MeepleInField(tutuille,fieldInTown[0]);
    int meeple2 = MeepleInField(tutuille,fieldInTown[1]);
    if(meeple != NONE)
      fieldInTown[0]->paysans[meeple] = 1;
    if(meeple2 != NONE)
      fieldInTown[1]->paysans[meeple2] = 1;
    fieldInTown[0]->inTown = TRUE;
    fieldInTown[0]->len = 1;
    fieldInTown[1]->inTown = TRUE;
    fieldInTown[1]->len = 1;
    res[0] = 1;
    res[1] = 2;
  }
  else{
    for(int k=0;k<2;k++){
      for(int i = 0;i<res[0];i++){
	lnk_add2(fieldInTown[k]->lst_triplet,fieldInTown[i]->lst_triplet->head);
      }
      int meeple = MeepleInField(tutuille,fieldInTown[k]);
      if(meeple != NONE)
	fieldInTown[k]->paysans[meeple] = 1;
      fieldInTown[k]->inTown = TRUE;
      fieldInTown[k]->len = 1;
    }
    res[0] = 0;
    res[1] = 2;
  }
}

void InternFusionFieldTownOneRoad2(struct tuille *tutuille, struct field *fieldTutuille[], struct field *fieldInTown[], int res[]){

  int type[12];
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      type[i*3+j] = tutuille->type[i][j];
    }
  }
  int qui = 0;
  int pos = 1; 
  int indice = 1;
  int first_occurance = 0; 
  struct lelement *llm[12]; 
  struct triplet* tmp[12]; 
  for(int i=0;i<12;i++){ 
    llm[i] = llm_empty();
    llm[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
    tmp[i] = (struct triplet *)llm[i]->data;
  }

  copie_triple(tmp[0],(struct triplet*)fieldTutuille[0]->lst_triplet->head->data);
  lnk_add2(fieldInTown[0]->lst_triplet,llm[0]);

  for(int i=0;i<12;i++){ 
    if(type[i] == 2)
      qui = (qui + 1)%2;
    else if(first_occurance == 1){ 
      if(qui == 0 && type[i] == 0){
	copie_triple(tmp[indice],(struct triplet*)fieldTutuille[pos]->lst_triplet->head->data); 
	lnk_add2(fieldTutuille[0]->lst_triplet,llm[indice]);
	lnk_add2(fieldInTown[0]->lst_triplet,llm[indice]);
	pos++;
	indice++;
      }
      else if(qui == 1 && type[i] == 0){
	copie_triple(tmp[indice],(struct triplet*)fieldTutuille[pos]->lst_triplet->head->data);
	
	lnk_add2(fieldTutuille[1]->lst_triplet,llm[indice]);
	pos++;
	indice++;
      }
    }
    if(type[i] == 0){
      first_occurance = 1;
    }
  }

  fieldTutuille[1]->lst_triplet->head = fieldTutuille[1]->lst_triplet->head->next;
  fieldTutuille[1]->lst_triplet->head->previous = NULL;
  fieldTutuille[1]->lst_triplet->taille -= 1;

  int meeple = MeepleInField(tutuille,fieldTutuille[0]);
  if(meeple != NONE)
    fieldTutuille[0]->paysans[meeple] = 1;
  fieldTutuille[0]->len = 1;
  fieldTutuille[0]->inTown = 1;

  meeple = MeepleInField(tutuille,fieldTutuille[1]);
  if(meeple != NONE)
    fieldTutuille[1]->paysans[meeple] = 1;
  fieldTutuille[1]->len = 1;
  fieldTutuille[1]->inTown = 1;

  meeple = MeepleInField(tutuille,fieldInTown[0]);
  if(meeple != NONE)
    fieldInTown[0]->paysans[meeple] = 1;
  fieldInTown[0]->len = 1;
  fieldInTown[0]->inTown = 1;
  res[0] = 1;
  res[1] = 1;
  return;
}


void InternFusionFieldTownOneRoad(struct tuille *tutuille, struct field *fieldTutuille[], struct field *fieldInTown[], int res[]){
  if( tutuille->id == CARD_CITY_THREE_ROAD_SHLD ||  tutuille->id == CARD_CITY_THREE_ROAD){
    lnk_add2(fieldInTown[0]->lst_triplet,fieldTutuille[0]->lst_triplet->head);
    int meeple = MeepleInField(tutuille,fieldInTown[0]);
    if(meeple != NONE)
      fieldInTown[0]->paysans[meeple] = 1;
    fieldInTown[0]->len = 1;
    fieldInTown[0]->inTown = TRUE;

    lnk_add2(fieldInTown[1]->lst_triplet,fieldTutuille[1]->lst_triplet->head);
    meeple = MeepleInField(tutuille,fieldInTown[1]);
    if(meeple != NONE)
      fieldInTown[1]->paysans[meeple] = 1;
    fieldInTown[1]->len = 1;
    fieldInTown[1]->inTown = TRUE;
    res[0] = 0;
    res[1] = 2;
    return;
  }
  else {
    InternFusionFieldTownOneRoad2(tutuille,fieldTutuille,fieldInTown,res);
  }
}

void InternFusionFieldTownThreeRoad(struct tuille * tutuille, struct field * fieldTutuille[],struct field *fieldInTown[],int res[]){ 
  struct lelement * llm_f2 = fieldTutuille[2]->lst_triplet->head;
  lnk_add2(fieldTutuille[1]->lst_triplet,llm_f2);
  struct lelement * llm_f5 = fieldTutuille[5]->lst_triplet->head;
  lnk_add2(fieldTutuille[0]->lst_triplet,llm_f5);
  struct lelement * llm_f3 = fieldTutuille[3]->lst_triplet->head;
  lnk_add2(fieldTutuille[2]->lst_triplet,llm_f3);
  struct lelement * llm_f4 = fieldTutuille[4]->lst_triplet->head;
  lnk_add2(fieldTutuille[2]->lst_triplet,llm_f4);
  fieldTutuille[2]->lst_triplet->head = fieldTutuille[2]->lst_triplet->head->next;
  fieldTutuille[2]->lst_triplet->head->previous = NULL;
  fieldTutuille[2]->lst_triplet->taille = 2;  

  
  lnk_add2(fieldInTown[0]->lst_triplet,fieldTutuille[0]->lst_triplet->head);
  lnk_add2(fieldInTown[0]->lst_triplet,fieldTutuille[0]->lst_triplet->head->next);
  
  int meeple = MeepleInField(tutuille,fieldInTown[0]);
  if(meeple != NONE){
    fieldInTown[0]->paysans[meeple] = 1;
    fieldTutuille[0]->paysans[meeple] = 1;
  }
  
  fieldInTown[0]->len = 1;
  fieldInTown[0]->inTown = TRUE;
  fieldTutuille[0]->len = 1;
  fieldTutuille[0]->inTown = TRUE;

  meeple = MeepleInField(tutuille,fieldTutuille[1]);
  if(meeple != NONE)
    fieldTutuille[1]->paysans[meeple] = 1;

  fieldTutuille[1]->len = 1;
  fieldTutuille[1]->inTown = FALSE;

  meeple = MeepleInField(tutuille,fieldTutuille[2]);
  if(meeple != NONE)
    fieldTutuille[2]->paysans[meeple] = 1;

  fieldTutuille[2]->len = 1;
  fieldTutuille[2]->inTown = FALSE;

  res[0] = 2;
  res[1] = 1;
  return;
}

int IsTown(struct tuille * tutuille){
  for(int i =0;i<4;i++){
    for(int j=0;j<3;j++){
      if(tutuille->type[i][j] == 1)
	return TRUE;
    }
  }
  return FALSE;
}

void InternFusionFieldTown(struct tuille * tutuille, struct field * fieldTutuille[],struct field *fieldInTown[],int res[]){ 
  int numbRoad = NumberRoadTown((*tutuille));

  if(numbRoad == 0){
    InternFusionFieldTownNoRoad(tutuille,fieldTutuille,fieldInTown,res);
  }
  else if(numbRoad == 1 || numbRoad == 2){
    InternFusionFieldTownOneRoad(tutuille,fieldTutuille,fieldInTown,res);
  }
  else{
    InternFusionFieldTownThreeRoad(tutuille,fieldTutuille,fieldInTown,res);
  }
}
  
void InternFusionField(struct tuille * tutuille, struct field *fieldTutuille[],struct field *fieldInTown[],int res[]){
  int isTown = IsTown(tutuille);

  if(tutuille->id == CARD_MONASTERY_ROAD || tutuille->id == CARD_MONASTERY_ALONE){
    MonasteryField(tutuille,fieldTutuille,fieldInTown,res);
    return;
  }

  if(tutuille->id == CARD_CITY_ALL_SIDES){
    res[0] = 0;
    res[1] = 0;
    return;
  }

  if(isTown == FALSE)
    InternFusionFieldNoTown(tutuille,fieldTutuille,fieldInTown,res);
  else{
    InternFusionFieldTown(tutuille,fieldTutuille,fieldInTown,res);
  }
}

int NotIn(struct field *f,struct triplet tri){
  struct lelement * current = f->lst_triplet->head;
  struct triplet * t = (struct triplet *)current->data;
  for(int i=0;i<f->lst_triplet->taille;i++){
    if(t->x == tri.x && t->y == tri.y && t->z == tri.z)
      return FALSE;
    if(current->next != NULL)
      current = current->next;
    t =(struct triplet *)current->data;
  }
  return TRUE;
}

void MergeField(struct field *f,struct field * find){
  lnk_merge(f->lst_triplet,find->lst_triplet);
  lnk_merge(f->lst_tutuille,find->lst_tutuille);
  for(int i=0;i<PLAYER_MAX;i++){
    f->paysans[i] += find->paysans[i];
  }
  f->len+=find->len;
  return;
}

  
void FusionField(struct field * f, struct field * find[],struct triplet next[], int len){
  for(int i =0;i<len;i++){
    if(find[i] != NULL && NotIn(f,next[i]) == TRUE){
      MergeField(f,find[i]);
    }
  }
}

int same_triplet(struct triplet * t1,struct triplet * t2){
  if(t1->x != t2->x)
    return FALSE;
  if(t1->y != t2->y)
    return FALSE;
  if(t1->z != t2->z)
    return FALSE;
  return TRUE;
}

int IsEqualField(struct field * f1,struct field * f2){
  if(f1->len != f2->len)
    return FALSE;
  for(int i=0;i<PLAYER_MAX;i++){
    if(f1->paysans[i] != f2->paysans[i])
      return FALSE;
  }

  struct lelement * current1;
  struct lelement * current2;

  if(f1->lst_triplet->taille != f2->lst_triplet->taille)
    return FALSE;
  current1 = f1->lst_triplet->head;
  struct triplet * tr1 = (struct triplet *)current1->data;
  current2 = f2->lst_triplet->head;
  struct triplet * tr2 = (struct triplet *)current2->data;
  for(int i=0;i<f1->lst_triplet->taille;i++){
    if(same_triplet(tr1,tr2) == FALSE)
      return FALSE;
    if(current1->next != NULL)
      current1 = current1->next;
    if(current2->next != NULL)
      current2 = current2->next;
    tr1 = (struct triplet *)current1->data;
    tr2 = (struct triplet *)current2->data;
  }
  return TRUE;
}


struct field * FindFieldInTown(struct city * c,struct field * f){
  struct lelement * current = c->lst_champ->head;
  struct field * ch = (struct field *)current->data;
  for(int i=0;i<c->lst_champ->taille;i++){
    if(IsEqualField(f,ch) == TRUE)
      return ch;
    if(current->next != NULL)
      current = current->next;
    ch = (struct field *)current->data;
  }
  return NULL;
}

struct field * findTownField(struct boardgame * boboard,struct field * f){
  struct lelement * current = boboard->cities->head;
  struct city * c=(struct city *)current->data;
  struct field * res;
  for(int i=0;i<boboard->cities->taille;i++){
    res = FindFieldInTown(c,f);
    if(res != NULL){
      return res;
    }
    if(current->next != NULL)
      current = current->next;
    c = (struct city *)current->data;
  }
  return NULL;
}

struct triplet triplet_vide(){
  struct triplet res;
  res.x = NONE;
  res.y = NONE;
  res.z = NONE;
  return res;
}

struct position DirectionField(struct boardgame * boboard, struct triplet * t){
  int dir = boboard->board[t->x][t->y].dir;
  int where;
  struct position res = {NONE,NONE};
  struct tuille tvide = gen_tuile_vide();
  
  if(same_card(&(boboard->board[t->x][t->y]),&tvide) == TRUE)
    return res;

  if(t->z == 0 || t->z == 1 || t->z == 2)
    where = (0 + dir)%4;
  else if(t->z == 3 || t->z == 4 || t->z == 5)
    where = (1 + dir)%4;
  else if(t->z == 6 || t->z == 7 || t->z == 8)
    where = (2 + dir)%4;
  else if(t->z == 9 || t->z == 10 || t->z == 11)
    where = (3 + dir)%4;

  if(where == 0){
    res.x = t->x - 1;
    res.y = t->y;
  }
  else if(where == 1){
    res.x = t->x;
    res.y = t->y-1;
  }
  else if(where == 2){
    res.x = t->x + 1;
    res.y =t->y;
  }
  else if(where == 3){
    res.x = t->x;
    res.y = t->y + 1;
  }
  return res;
}

struct triplet NextTripletField(struct triplet * t,struct position p,int dir_next, int dir_origine){
  struct triplet next = {NONE,NONE,NONE};
  if(p.x == NONE || p.y == NONE)
    return next;
  int where = (t->z + 3*dir_origine) %12;
  next.x = p.x;
  next.y = p.y;
  next.z = (where + 6 - dir_next*3)%12;
  return next;
}

// z = 0,1,2 -> N -> 6,7,8
// z = 3,4,5 -> W -> 9,10,11
// z = 6,7,8 -> S -> 0,1,2
// z = 9,10,11 -> E -> 3,4,5

int FindTripletInField(struct field * ch, struct triplet * t){
  struct lelement * current = ch->lst_triplet->head;
  struct triplet * tri = (struct triplet *)current->data;
  for(int i = 0; i<ch->lst_triplet->taille;i++){
    if(same_triplet(tri,t) == TRUE)
      return TRUE;
    if(current->next != NULL)
      current = current->next;
    tri = (struct triplet *)current->data;
  }
  return FALSE;
}

struct field *FindTripletFieldInTown(struct city *c, struct triplet* t){
  struct lelement *current = c->lst_champ->head;
  struct field * ch = (struct field *)current->data;
  for(int i=0;i<c->lst_champ->taille;i++){
    if(FindTripletInField(ch,t) == TRUE)
      return ch;
    if(current->next != NULL)
      current = current->next;
    ch = (struct field *)current->data;
  }
  return NULL;
}

struct field * FindField(struct boardgame * boboard, struct triplet next){

  if(boboard->fields->taille == 0)
    return NULL;
  struct lelement * current = boboard->fields->head;
  struct field * ch =(struct field*)current->data;
  for(int i=0;i<boboard->fields->taille;i++){
    if(FindTripletInField(ch,&next) == TRUE){
      return ch;
    }
    if(current->next != NULL)
      current = current->next;
    ch = (struct field *)current->data;
  }


  struct field * res = NULL;
  current = boboard->cities->head;
  struct city * c = (struct city *)current->data;
  for(int i=0;i<boboard->cities->taille;i++){
    res= FindTripletFieldInTown(c,&next);
    if(res != NULL)
      return res;
    if(current->next != NULL)
      current = current->next;
    c = (struct city *)current->data;
  }

  return NULL;
}

void ExternFusionFieldInTown(struct boardgame * boboard,struct field * f){
  f = findTownField(boboard,f);

  int len = f->lst_triplet->taille;
  struct lelement * current = f->lst_triplet->head;
  struct triplet * trip =(struct triplet * )current->data;
  struct triplet * test[9];
  for(int i =0;i<9;i++){
    test[i] = (struct triplet *)malloc(sizeof(struct triplet));
  }
  for(int i=0;i<len;i++){
    test[i] = trip;
    if(current->next != NULL)
      current = current->next;
    trip = (struct triplet *)current->data;
  }

  for(int i =len;i<9;i++){
    (*test[i]) = triplet_vide();
  }

  struct position junction[9];
  for(int i=0;i<len;i++){
    junction[i] = DirectionField(boboard,test[i]);
  }

  int tab_vide[9] = {};
  TabPositionVide(tab_vide,junction,len,boboard);
  struct triplet next[9];

  for(int i =0;i<len;i++){
    next[i] = NextTripletField(test[i],junction[i],boboard->board[junction[i].x][junction[i].y].dir,boboard->board[test[i]->x][test[i]->y].dir);
  }


  struct field * find[9];
  for(int i = 0;i<len;i++){
    find[i] = FindField(boboard,next[i]);
  }
  f->inTown = 1;
  FusionField(f,find,next,len);

}



struct city * IsTownField(struct boardgame * boboard, struct field * f){
  struct lelement * current = boboard->cities->head;
  struct city * c =(struct city *)current->data;
  for(int i=0;i<boboard->cities->taille;i++){
    if(FindFieldInTown(c,f) != NULL)
      return c;
    if(current->next != NULL)
      current = current->next;
    c = (struct city *)current->data;
  }
  return NULL;
}

void MergeFieldNoTown(struct boardgame * boboard,struct field * f,struct field * find){
  struct city * c = IsTownField(boboard,find);
  if(c != NULL){
    struct field *f2 = FindFieldInTown(c,find); 
    lnk_merge(f2->lst_triplet,f->lst_triplet);
    lnk_merge(f2->lst_tutuille,f->lst_tutuille);
    for(int i=0;i<PLAYER_MAX;i++){
      f2->paysans[i] += f->paysans[i];
    }
    f2->len+=f->len;
    return;
  }
  else{
    lnk_merge(f->lst_tutuille,find->lst_tutuille);
    lnk_merge(f->lst_triplet,find->lst_triplet);
    for(int i=0;i<PLAYER_MAX;i++){
      f->paysans[i] += find->paysans[i];
    }
    f->len +=find->len;
    return;
  }
}

    
void FusionFieldNoTown(struct boardgame * boboard, struct field * f, struct field * find[],struct triplet next[], int len, int number_of_finds){
  if(number_of_finds ==0){
    struct lelement * llm_f = llm_empty();
    llm_f->data = (struct field *)malloc(sizeof(struct field));
    struct field * tmp_f = (struct field *)llm_f->data;
    copie_field(tmp_f,f);
    lnk_add2(boboard->fields,llm_f);
    return;
  }
  
  for(int i=0;i<len;i++){
    if(find[i] != NULL &&  NotIn(f,next[i]) == TRUE)
      MergeFieldNoTown(boboard,f,find[i]);
  }
}

 
void ExternFusionFieldNoTown(struct boardgame * boboard,struct field * f){
  int len = f->lst_triplet->taille;
  struct lelement * current = f->lst_triplet->head;
  struct triplet * trip =(struct triplet * )current->data;
  struct triplet * test[12];
  for(int i = 0;i<12;i++){
    test[i] =  (struct triplet *)malloc(sizeof(struct triplet));
  }
  for(int i=0;i<len;i++){
    test[i] = trip;
    if(current->next != NULL)
      current = current->next;
    trip = (struct triplet *)current->data;
  }

  for(int i =len;i<12;i++){
    (*test[i]) = triplet_vide();
  }
  struct position junction[12];
  for(int i=0;i<len;i++){
    junction[i] = DirectionField(boboard,test[i]);
  }

  int tab_vide[12] = {};
  TabPositionVide(tab_vide,junction,len,boboard);

  struct triplet next[12];
  for(int i =0;i<len;i++){
    next[i] = NextTripletField(test[i],junction[i],boboard->board[junction[i].x][junction[i].y].dir,boboard->board[test[i]->x][test[i]->y].dir);
  }

  struct field * find[12];
  for(int i = 0;i<len;i++){
    find[i] = FindField(boboard,next[i]);
  }

  int number_of_finds = 0;

  for(int i = 0;i<len;i++){
    if(find[i] != NULL){
      number_of_finds++;
    }
  }
  FusionFieldNoTown(boboard,f,find,next,len,number_of_finds);
}


void UpdateField(struct boardgame * boboard, struct tuille tutuille){
  struct field * fieldTutuille[12];
  struct field * fieldInTown[2];
  int len[2] = {12,0};
  for(int i =0;i<12;i++){
    fieldTutuille[i] = FieldVide();
  }
  fieldInTown[0] = FieldVide();
  fieldInTown[1] = FieldVide();
  len[0] = ExtractField(&tutuille,fieldTutuille);

  InternFusionField(&tutuille,fieldTutuille,fieldInTown,len);

  for(int i=0;i<len[1];i++){
    ExternFusionFieldInTown(boboard,fieldInTown[i]);
  }
  for(int i =len[1];i<len[1]+len[0];i++){
    ExternFusionFieldNoTown(boboard,fieldTutuille[i]);
  }
}



