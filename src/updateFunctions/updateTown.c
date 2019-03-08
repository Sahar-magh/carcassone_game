#include "updateTown.h"


struct field * FieldVide(){
  struct field * new_field = (struct field * )malloc(sizeof(struct field));
  
  struct lelement * llm_t = llm_empty();
  llm_t->data = (struct tuille *)malloc(sizeof(struct tuille));
  struct tuille * tmp_t = (struct tuille * )llm_t->data;
  (*tmp_t) = gen_tuile_vide();
  
  for(int i=0;i<PLAYER_MAX;i++){
    new_field->paysans[i] = 0;
  }
  new_field->len = NONE;
  
  new_field->inTown = NONE;

  new_field->lst_tutuille = lnk_empty();
  new_field->lst_triplet = lnk_empty();
  lnk_add2(new_field->lst_tutuille,llm_t);
  return new_field;
}

struct city * TownVide(){
  
  struct city * new_town = (struct city * )malloc(sizeof(struct city));

  struct lelement * llm_t = llm_empty();
  llm_t->data = (struct tuille * )malloc(sizeof(struct tuille));
  struct tuille * tmp_t = (struct tuille *)llm_t->data;
  (*tmp_t) = gen_tuile_vide();

  struct lelement * llm_p = llm_empty();
  llm_p->data = (struct triplet *)malloc(sizeof(struct triplet));
  struct triplet * tmp_p = (struct triplet *)llm_p->data;
  tmp_p->x = NONE;
  tmp_p->y = NONE;
  tmp_p->z = NONE;
  
  new_town->lst_tutuille = lnk_empty();
  new_town->lst_triplet = lnk_empty();
  new_town->lst_champ = lnk_empty();

  
  new_town->lst_tutuille = lnk_empty();
  new_town->lst_champ = lnk_empty();
  new_town->lst_triplet = lnk_empty();
  lnk_add2(new_town->lst_tutuille,llm_t);
  lnk_add2(new_town->lst_triplet,llm_p);

  for(int i=0;i<PLAYER_MAX;i++){
    new_town->chevaliers[i] = 0;
  }
  new_town->border = NONE;
  new_town->len = NONE;
  new_town->shield = NONE;
  return new_town;
}

void RemoveTown(struct link *cities, struct city * t){
  struct lelement * current =  cities->head;
  struct city * town = (struct city *)current->data;
  if(t == town){
    cities->head = current->next;
    current->next->previous = NULL;
    free(current);
    free(town);
    cities->taille -=1;
    return;
  }
  for(int i=0;i<cities->taille-1;i++){
    if(t == town){
      current->previous->next = current->next;
      current->next->previous = current->previous;
      free(current);
      free(town);
      cities->taille -=1;
      return;
    }
    current = current->next;
    town = (struct city *)current->data;
  }
  if(t == town){
    cities->tail = current->previous;
    current->previous->next = NULL;
    free(current);
    free(town);
    cities->taille -=1;
    return;
  }
}

void copie_tuile_town(struct tuille * t1, struct tuille * t2){
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      t1->type[i][j] = t2->type[i][j];
      t1->pion[i][j] = t2->pion[i][j];
    }
  }
  t1->dir = t2->dir;
  t1->milieu = t2->milieu;
  t1->shield = t2->shield;
  t1->position[0] = t2->position[0];
  t1->position[1] = t2->position[1];
  t1->id = t2->id;
}

int attribut_z_town(int i){
  if( i == 0 )
    return 1;
  else if( i == 1 )
    return 3;
  else if( i == 2 )
    return 7;
  else
    return 5;
}

int ExtractTown(struct tuille * tutuille, struct city * townTutuille[]){
  int taille = 0;
  struct tuille * tmp_t;
  struct triplet * tmp_p;
  for(int i=0;i<4;i++){
    if(tutuille->type[i][1] == 1){
      tmp_t = (struct tuille * )(townTutuille[taille])->lst_tutuille->head->data;
      tmp_p = (struct triplet * )(townTutuille[taille])->lst_triplet->head->data;
      copie_tuile_town(tmp_t,tutuille);
      tmp_p->x = tutuille->position[0];
      tmp_p->y = tutuille->position[1];
      tmp_p->z = attribut_z_town(i);
      taille ++;
    }
  }
  return taille;
}

int Reverse_z_town(int z){
  if(z == 1)
    return 0;
  else if(z == 3)
    return 1;
  else if(z == 7)
    return 2;
  else 
    return 3;
}

int TownMeeple(struct tuille tutuille, struct triplet * t){
  int pos = Reverse_z_town(t->z);
  return tutuille.pion[pos][1];
}

int NumberRoadTown(struct tuille tutuille){
  int num =0;
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      if(tutuille.type[i][j] == 2){
	num++;
      }
    }
  }
  return num;
}

int ParcourType(struct tuille tutuille, struct triplet lst_t[]){
  int len = 0;
  int tab[12];
  int pos_t;
  int bool = TRUE;
  for(int i = 0;i<4;i++){
    for(int j=0;j<3;j++){
      tab[i*3+j] = tutuille.type[i][j];
      if(tutuille.type[i][j] == 1)
	pos_t = i;
    }
  }
  int dep=(3*(pos_t+1))%12;
  int end=(11+(pos_t*3))%12;
  while(dep <= end){
    if(tab[dep] == 2){
      bool = !bool;
    }
    if(bool == TRUE && tab[dep] != 2){
      lst_t[len].x = tutuille.position[0];
      lst_t[len].y = tutuille.position[1];
      lst_t[len].z = dep;
      len++;
    }
    dep = (dep+1);
  }
  return len;
}
//si pos_t = 0 -> i=3 ... i=11
//si pos_t = 1 -> i=6 ... i=2
//si pos_t = 2 -> i=9 ... i=5
//si pos_t = 3 -> i=0 ... i=8
  

void SingleTripletField(struct tuille tutuille, struct field * f){
  struct triplet lst_t[9];
  struct lelement *lst_llm[9];
  int len = 0;
  struct triplet * tmp_p;
  for(int i = 0;i<9;i++){
    lst_llm[i] = llm_empty();
    lst_llm[i]->data = (struct triplet * )malloc(sizeof(struct triplet));
  }
  if(NumberRoadTown(tutuille) != 3){
    len = ParcourType(tutuille,lst_t);
    for(int i=0;i<len;i++){
      tmp_p = (struct triplet * )lst_llm[i]->data;
      tmp_p->x = tutuille.position[0];
      tmp_p->y = tutuille.position[1];
      tmp_p->z = lst_t[i].z;
      lnk_add2(f->lst_triplet,lst_llm[i]);
    }
    return;
  }
  else{
    tmp_p = (struct triplet *)lst_llm[0]->data;
    tmp_p->x = tutuille.position[0];
    tmp_p->y = tutuille.position[1];
    tmp_p->z = 0;
    lnk_add2(f->lst_triplet,lst_llm[0]);

    tmp_p = (struct triplet *)lst_llm[1]->data;
    tmp_p->x = tutuille.position[0];
    tmp_p->y = tutuille.position[1];
    tmp_p->z = 8;
    lnk_add2(f->lst_triplet,lst_llm[1]);
    return;
  }
}

int FieldMeeple(struct tuille tutuille, struct field * f){
  int possesseur = NONE;
  int tab[12];
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      tab[i*3+j]=tutuille.pion[i][j];
    }
  }
  struct lelement * current = f->lst_triplet->head;
  struct triplet * t = (struct triplet * )current->data;
  for(int i=0;i < f->lst_triplet->taille;i++){
    if(tab[t->z] != NONE){
      possesseur = tab[t->z];
    }
  }
  return possesseur;
}

void copie_field(struct field * f1,struct field * f2){
  f1->lst_tutuille = f2->lst_tutuille;
  f1->lst_triplet = f2->lst_triplet;
  for(int i=0;i<PLAYER_MAX;i++){
    f1->paysans[i] = f2->paysans[i];
  }
  f1->len =f2->len;
}

void SingleField(struct city * town, struct tuille tutuille){
  
  struct lelement * llm_f = llm_empty();
  llm_f->data = (struct field * )malloc(sizeof(struct field));
  struct field * tmp_f = (struct field *)llm_f->data;
  copie_field(tmp_f,FieldVide());
  struct tuille * tmp_t = (struct tuille *)tmp_f->lst_tutuille->head->data;
  tmp_f->len = 1;
  copie_tuile_town(tmp_t,&tutuille);
  SingleTripletField(tutuille,tmp_f);
  int possesseur = FieldMeeple(tutuille,tmp_f);
  if(possesseur != NONE)
    tmp_f->paysans[possesseur] = 1;
  lnk_add2(town->lst_champ,llm_f);
}

int NumbBorder(struct tuille tutuille){
  int num = 0;
  for(int i=0;i<4;i++){
    if(tutuille.type[i][1] == 1){
      num++;
    }
  }
  return num;
}

int OppositeTriplet(struct triplet * t1, struct triplet * t2){
  if((t1->z == 1 && t2->z == 7) || (t1->z == 3 && t2->z == 5) || (t1->z == 7 && t2->z == 1) || (t1->z == 5 && t2->z == 3))
    return TRUE;
  return FALSE;
}

void PluralFieldDouble(struct city * town,struct tuille tutuille){
  int possesseur = NONE;
  if((town->border == 2) && (OppositeTriplet((struct triplet *)town->lst_triplet->head->data,(struct triplet *)town->lst_triplet->head->next->data)==TRUE)){
    //le premier champ
    struct lelement * llm_f1 =llm_empty();
    llm_f1->data = (struct field *)malloc(sizeof(struct field));
    struct field * tmp_f1 = (struct field *)llm_f1->data;
    copie_field(tmp_f1,FieldVide());
    struct tuille * tmp_t1 = (struct tuille *)tmp_f1->lst_tutuille->head->data;
    (*tmp_t1) = tutuille;

    tmp_f1->len=1;
    
    struct lelement * llm_p1[3];
    struct triplet * tmp_p1;
    for(int i=0;i<3;i++){
      llm_p1[i] = llm_empty();
      llm_p1[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
      tmp_p1 = (struct triplet *)llm_p1[i]->data;
      tmp_p1->x = tutuille.position[0];
      tmp_p1->y = tutuille.position[1];
      if(tutuille.type[1][1] == 0)
	tmp_p1->z = 3+i;
      else
	tmp_p1->z = i;
      lnk_add2(tmp_f1->lst_triplet,llm_p1[i]);
    }
    possesseur = FieldMeeple(tutuille,tmp_f1);
    if(possesseur != NONE)
      tmp_f1->paysans[possesseur] = 1;
    lnk_add2(town->lst_champ,llm_f1);
    
    //le deuxieme champ
    struct lelement * llm_f2 =llm_empty();
    llm_f2->data = (struct field *)malloc(sizeof(struct field));
    struct field * tmp_f2 = (struct field *)llm_f2->data;
    copie_field(tmp_f2,FieldVide());
    struct tuille * tmp_t2 = (struct tuille *)tmp_f2->lst_tutuille->head->data;
    (*tmp_t2) = tutuille;
    tmp_f2->len=1;
    
    struct lelement * llm_p2[3];
    struct triplet * tmp_p2;
    for(int i=0;i<3;i++){
      llm_p2[i] = llm_empty();
      llm_p2[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
      tmp_p2 = (struct triplet *)llm_p2[i]->data;
      tmp_p2->x = tutuille.position[0];
      tmp_p2->y = tutuille.position[1];
      if(tutuille.type[1][1] == 0)
	tmp_p2->z = 9+i;
      else
	tmp_p2->z = 6+i;
      lnk_add2(tmp_f2->lst_triplet,llm_p2[i]);
    }

    possesseur = FieldMeeple(tutuille,tmp_f2);
    if(possesseur != NONE)
      tmp_f2->paysans[possesseur] = 1;    
    lnk_add2(town->lst_champ,llm_f2);
    return;
  }
  else{
    if(tutuille.type[2][1] !=2){
      struct lelement * llm_f3 = llm_empty();
      llm_f3->data = (struct field *)malloc(sizeof(struct field));
      struct field * tmp_f3 = (struct field *)llm_f3->data;
      copie_field(tmp_f3,FieldVide());
      struct tuille * tmp_t3 = (struct tuille *)tmp_f3->lst_tutuille->head->data;
      (*tmp_t3) = tutuille;
      tmp_f3->len = 1;
     
      struct lelement *llm_p3[6];
      struct triplet * tmp_p3;
      for(int i=0;i<6;i++){
	llm_p3[i] = llm_empty();
        llm_p3[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
        tmp_p3 = (struct triplet *)llm_p3[i]->data;
        tmp_p3->x = tutuille.position[0];
        tmp_p3->y = tutuille.position[1];
	if(tutuille.milieu == 1){
	  tmp_p3->z = 6+i;
	}
	else {
	  tmp_p3->z = i;
	}
        lnk_add2(tmp_f3->lst_triplet,llm_p3[i]);
      }
      possesseur = FieldMeeple(tutuille,tmp_f3);
      if(possesseur != NONE)
        tmp_f3->paysans[possesseur] = 1;
      lnk_add2(town->lst_champ,llm_f3);
      return;
    }
    else {
      struct lelement * llm_f4 = llm_empty();
      llm_f4->data = (struct field *)malloc(sizeof(struct field));
      struct field * tmp_f4 = (struct field *)llm_f4->data;
      copie_field(tmp_f4,FieldVide());
      struct tuille * tmp_t4 = (struct tuille *)tmp_f4->lst_tutuille->head->data;
      (*tmp_t4) = tutuille;
      tmp_f4->len = 1;
     
      struct lelement *llm_p4[2];
      struct triplet * tmp_p4;
      for(int i=0;i<2;i++){
	llm_p4[i] = llm_empty();
        llm_p4[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
        tmp_p4 = (struct triplet *)llm_p4[i]->data;
        tmp_p4->x = tutuille.position[0];
        tmp_p4->y = tutuille.position[1];
        tmp_p4->z = 6 +5*i;
        lnk_add2(tmp_f4->lst_triplet,llm_p4[i]);
      }
      possesseur = FieldMeeple(tutuille,tmp_f4);
      if(possesseur != NONE)
        tmp_f4->paysans[possesseur] = 1;
      lnk_add2(town->lst_champ,llm_f4);
      return;
    }
  }
}

void PluralFieldTriple(struct city * town,struct tuille tutuille){
  int possesseur = NONE;
  if(tutuille.type[2][1] == 2){
    struct lelement * llm_f3[2];
    llm_f3[0] = llm_empty();
    llm_f3[1] = llm_empty();
    llm_f3[0]->data = (struct field *)malloc(sizeof(struct field));
    llm_f3[1]->data = (struct field *)malloc(sizeof(struct field));
    struct field * tmp_f3[2];
    tmp_f3[0] = (struct field *)llm_f3[0]->data;
    tmp_f3[1] = (struct field *)llm_f3[1]->data;
    copie_field(tmp_f3[0],FieldVide());
    copie_field(tmp_f3[1],FieldVide());
    struct tuille * tmp_t3[2];
    tmp_t3[0] = (struct tuille *)tmp_f3[0]->lst_tutuille->head->data;
    tmp_t3[1] = (struct tuille *)tmp_f3[1]->lst_tutuille->head->data;
    (*tmp_t3[0]) = tutuille;
    (*tmp_t3[1]) = tutuille;
    tmp_f3[0]->len = 1;
    tmp_f3[1]->len = 1;
    struct lelement *llm_p3[2];
    struct triplet * tmp_p3;
    for(int i=0;i<2;i++){
      llm_p3[i] = llm_empty();
      llm_p3[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
      tmp_p3 = (struct triplet *)llm_p3[i]->data;
      tmp_p3->x = tutuille.position[0];
      tmp_p3->y = tutuille.position[1];
      tmp_p3->z = 6+i*2;
      lnk_add2(tmp_f3[i]->lst_triplet,llm_p3[i]);
    }
    possesseur = FieldMeeple(tutuille,tmp_f3[0]);
    if(possesseur != NONE)
      tmp_f3[0]->paysans[possesseur] = 1;
    lnk_add2(town->lst_champ,llm_f3[0]);
    
    possesseur = FieldMeeple(tutuille,tmp_f3[1]);
    if(possesseur != NONE)
      tmp_f3[1]->paysans[possesseur] = 1;
    lnk_add2(town->lst_champ,llm_f3[1]);
    return;
  }
  else {
    struct lelement * llm_f4 = llm_empty();
    llm_f4->data = (struct field *)malloc(sizeof(struct field));
    struct field * tmp_f4 = (struct field *)llm_f4->data;
    copie_field(tmp_f4,FieldVide());
    struct tuille * tmp_t4 = (struct tuille *)tmp_f4->lst_tutuille->head->data;
    (*tmp_t4) = tutuille;
    tmp_f4->len = 1;
    
    struct lelement *llm_p4[3];
    struct triplet * tmp_p4;
    for(int i=0;i<3;i++){
      llm_p4[i] = llm_empty();
      llm_p4[i]->data = (struct triplet *)malloc(sizeof(struct triplet));
      tmp_p4 = (struct triplet *)llm_p4[i]->data;
      tmp_p4->x = tutuille.position[0];
      tmp_p4->y = tutuille.position[1];
      tmp_p4->z = 6 + i;
      lnk_add2(tmp_f4->lst_triplet,llm_p4[i]);
    }
    possesseur = FieldMeeple(tutuille,tmp_f4);
    if(possesseur != NONE)
      tmp_f4->paysans[possesseur] = 1;
    lnk_add2(town->lst_champ,llm_f4);
    return;
  }
}
    
    
void PluralField(struct city * town, struct tuille tutuille){
  if(town->border == 2 || town->border == 1){
    PluralFieldDouble(town,tutuille);
    return;
  }
  
  else if(town->border == 3){
    PluralFieldTriple(town,tutuille);
    return;
  } 
}


int InternFusionTown(struct tuille tutuille,struct city *townTutuille[], int taille){
  int possesseur;
  if(tutuille.milieu != 1){
    for(int i = 0;i<taille;i++){
      townTutuille[i]->border = 1;
      townTutuille[i]->len = 1;
      townTutuille[i]->shield = tutuille.shield;
      possesseur = TownMeeple(tutuille,(struct triplet *)(townTutuille[i]->lst_triplet->head->data));
      if(possesseur != NONE)
	townTutuille[i]->chevaliers[possesseur] = 1;
      if((tutuille.type[1][1] == 1) || (tutuille.type[2][1] == 1)){
	PluralField(townTutuille[i],tutuille);
      }
      else{
	SingleField(townTutuille[i],tutuille);
      }
    }
    for(int i = taille;i<4;i++){
      FreeCity(townTutuille[i]);
    }
    return taille;
  }
  else {
    townTutuille[0]->border = NumbBorder(tutuille);
    townTutuille[0]->len = 1;
    townTutuille[0]->shield = tutuille.shield;
    possesseur = TownMeeple(tutuille,(struct triplet *)(townTutuille[0]->lst_triplet->head->data));
    if(possesseur != NONE){
      townTutuille[0]->chevaliers[possesseur] = 1;
    }
    for(int i = 1;i<taille;i++){
      lnk_add2(townTutuille[0]->lst_triplet,townTutuille[i]->lst_triplet->head);
    }
    PluralField(townTutuille[0],tutuille);
    for(int i = taille;i<4;i++){
      FreeCity(townTutuille[i]);
    }
    for(int i = 1;i<taille;i++){
      free(townTutuille[i]->lst_tutuille);
      free(townTutuille[i]->lst_champ);
      free(townTutuille[i]->lst_triplet);
      free(townTutuille[i]);
    }
    return 1;
  }
}

void copie_town(struct city * t1, struct city * t2){
  t1->lst_tutuille = t2->lst_tutuille;
  t1->lst_triplet = t2->lst_triplet;
  t1->lst_champ = t2->lst_champ;
  for(int i =0;i<PLAYER_MAX;i++){
    t1->chevaliers[i] = t2->chevaliers[i];
  }
  t1->border = t2->border;
  t1->len = t2->len;
  t1->shield = t2->shield;
}

struct position DirectionTown(struct boardgame * boboard, struct triplet *t){
  int dir = boboard->board[t->x][t->y].dir;
  int where;
  struct position res = {NONE,NONE};
  if(t->z == 1)
    where = (0 + dir)%4;
  else if(t->z == 3)
    where = (1 + dir)%4;
  else if(t->z == 7)
    where = (2 + dir)%4;
  else if(t->z == 5)
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



int posDiff(struct position p1, struct position p2){
  if(p1.x != p2.x)
    return FALSE;
  else if(p1.y != p2.y)
    return  FALSE;
  return TRUE;
}

int IsDuoTuile(struct city * t){
  int len1 = 0;
  int len2 = 0;
  
  struct position p1[6];
  struct position p2[4];
  struct lelement * current = t->lst_tutuille->head;
  struct tuille * tutuille = (struct tuille *)current->data;
  
  for(int i=0;i<t->lst_tutuille->taille;i++){
    if(tutuille->id == CARD_PLAIN_TUNNEL){
      p1[len1].x = tutuille->position[0];
      p1[len1].y = tutuille->position[1];
      len1++;
    }
    if(tutuille->id == CARD_PLAIN_TWO_CITIES){
      p2[len2].x = tutuille->position[0];
      p2[len2].y = tutuille->position[1];
      len1++;
    }
    if(current->next != NULL)
      current = current->next;
    tutuille = (struct tuille *)current->data;
  }
  for(int i=0;i<len1;i++){
    for(int j=i+1;j<len1;j++){
      if(posDiff(p1[i],p1[j]) == TRUE)
	return FALSE;
    }
  }
  for(int i=0;i<len2;i++){
    for(int j=i+1;j<len2;j++){
      if(posDiff(p2[i],p2[j]) == TRUE)
	return FALSE;
    }
  }
  return TRUE;
}
  

void CreditPointTown(struct boardgame * boboard,struct city * t){
  int point = 0;
  if(t->border == 0)
    point = 2*(t->len + t->shield);
  else
    point = t->len + t->shield;
  if(IsDuoTuile(t)){
    if(t->border == 0)
      point -= 2;
    else
      point -= 1;
  }
  int max = t->chevaliers[0];
  for(int i=0;i<PLAYER_MAX;i++){
    if(t->chevaliers[i] > max)
      max = t->chevaliers[i];
  }
  if(max != 0){
    for(int i=0;i<PLAYER_MAX;i++){
      if(t->chevaliers[i] == max)
	boboard->points[i] += point;
    }
  }
}

struct triplet NextTripletTown(struct triplet * t, struct position p, int dir_next, int dir_origine){
  struct triplet next;
  int reverse_z = (Reverse_z_town(t->z) + dir_origine)%4;
  next.x = p.x;
  next.y = p.y;

  if( reverse_z == 0)
    next.z = attribut_z_town((2 - dir_next + 4)%4);

  else if( reverse_z == 1)
    next.z = attribut_z_town((3 - dir_next + 4)%4);

  else  if( reverse_z == 2)
    next.z = attribut_z_town((0 - dir_next + 4)%4);

  else if( reverse_z == 3)
    next.z = attribut_z_town((1 - dir_next + 4)%4);

  return next;
}

void MergeTown(struct city *t1,struct city *t2){
  lnk_merge(t1->lst_tutuille,t2->lst_tutuille);
  lnk_merge(t1->lst_triplet,t2->lst_triplet);
  struct lelement * current1 = t2->lst_champ->head;
  for(int i=0;i<t2->lst_champ->taille;i++){
    lnk_add2(t1->lst_champ,current1);
    if(current1->next != NULL)
      current1 = current1->next;
  }
  struct lelement * current = t1->lst_champ->head;
  struct field * f = (struct field *)current->data;
  for(int i =0;i<t1->lst_champ->taille;i++){
    if(f->inTown != 1)
      f->inTown = 1;
    if(current->next != NULL)
      current = current->next;
    f = (struct field *)current->data;
  }
  for(int i=0;i<PLAYER_MAX;i++){
    t1->chevaliers[i] += t2->chevaliers[i];
  }
  t1->len += t2->len;
  t1->shield += t2->shield;
}

int FindTripletInTown(struct city * c, struct triplet t){
  struct lelement * current = c->lst_triplet->head;
  struct triplet * tri = (struct triplet *)current->data;
  for(int i =0;i<c->lst_triplet->taille;i++){
    if(tri->x == t.x && tri->y == t.y && tri->z == t.z){
      return TRUE;
    }
    if(current->next != NULL)
      current = current->next;
    tri = (struct triplet *)current->data;
  }
  return FALSE;
}

struct city * FindTown(struct boardgame *boboard, struct triplet t){
  struct lelement * current = boboard->cities->head;
  struct city * c = (struct city *)current->data;
  for(int i=0;i<boboard->cities->taille;i++){
    if(FindTripletInTown(c,t) == TRUE){
      return c;
    }
    if(current->next != NULL){
      current = current->next;
      c = (struct city *)current->data;
    }
  }
  return NULL;
}



void SingleExternFusion(struct boardgame * boboard, struct city * town){

  struct lelement * llm_c = llm_empty();
  llm_c->data = (struct city *)malloc(sizeof(struct city));
  struct city * tmp_c = (struct city *)llm_c->data;
  copie_town(tmp_c,town);
  
  struct triplet * test =(struct triplet *)town->lst_triplet->head->data;
  struct position junction = DirectionTown(boboard,test);

  struct tuille tvide = gen_tuile_vide();

  if(same_card(&tvide,&(boboard->board[junction.x][junction.y])) == TRUE){
    lnk_add2(boboard->cities,llm_c);
    return;
  }

  else{
    struct triplet next = NextTripletTown(test,junction,boboard->board[junction.x][junction.y].dir,boboard->board[test->x][test->y].dir);
    struct city * find = FindTown(boboard,next);
    MergeTown(find,town);
    free(town);
    find->border -= 1;
    if(find->border ==0)
      CreditPointTown(boboard,find);
    return;
  }
}

void TabPositionVide(int tab[],struct position junction[],int len,struct boardgame * b){
  struct tuille tvide = gen_tuile_vide();
  for(int i =0;i<len;i++){
    if(same_card(&tvide,&(b->board[junction[i].x][junction[i].y])) == TRUE){
      tab[i] = 0;
    }
    else{
      tab[i] = 1;
    }
  }
}

void DoubleExternFusion(struct boardgame * boboard, struct city * town){

  struct lelement * llm_c = llm_empty();
  llm_c->data = (struct city *)malloc(sizeof(struct city));
  struct city * tmp_c = (struct city *)llm_c->data;
  copie_town(tmp_c,town);

  struct triplet * test[2];
  test[0] =(struct triplet *)town->lst_triplet->head->data;
  test[1] =(struct triplet *)town->lst_triplet->head->next->data;

  struct position junction[2];
  junction[0] = DirectionTown(boboard,test[0]);
  junction[1] = DirectionTown(boboard,test[1]);
  int tab_vide[2] = {0,0};
  TabPositionVide(tab_vide,junction,2,boboard);
  if(tab_vide[0] == 0 && tab_vide[1] == 0){
    lnk_add2(boboard->cities,llm_c);
    return;
  }
  else if(tab_vide[0] == 1 && tab_vide[1] == 0){
    struct triplet next = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    struct city * find = FindTown(boboard,next);
    MergeTown(find,town);
    free(town);
    if(find->border ==0)
      CreditPointTown(boboard,find);
    return;
  }
  else if(tab_vide[0] == 0 && tab_vide[1] == 1){
    struct triplet next1 = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    struct city * find1 = FindTown(boboard,next1);
    MergeTown(find1,town);
    free(town);
    if(find1->border ==0)
      CreditPointTown(boboard,find1);
   return;
  } 
  else if(tab_vide[0] == 1 && tab_vide[1] == 1){
    struct triplet next2 = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    struct city * find2 = FindTown(boboard,next2);
    struct triplet next3 = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    struct city * find3 = FindTown(boboard,next3);
    if(find2 == find3){
      MergeTown(find2,town);
      free(town);
      find2->border -=2;
    }
    else{
      MergeTown(find2,town);
      MergeTown(find2,find3);
      free(town);
      find2->border = find2->border + find3->border -2;
      RemoveTown(boboard->cities,find3);
    }
    if(find2->border == 0)
      CreditPointTown(boboard,find3);
    return;
  }
}

void TripleExternFusion(struct boardgame * boboard, struct city * town){
  struct lelement * llm_c = llm_empty();
  llm_c->data = (struct city *)malloc(sizeof(struct city));
  struct city * tmp_c = (struct city *)llm_c->data;
  copie_town(tmp_c,town);


  struct triplet * test[3];
  test[0] =(struct triplet *)town->lst_triplet->head->data;
  test[1] =(struct triplet *)town->lst_triplet->head->next->data;
  test[2] =(struct triplet *)town->lst_triplet->head->next->next->data;
  struct position junction[3];
  junction[0] =  DirectionTown(boboard,test[0]);
  junction[1] =  DirectionTown(boboard,test[1]);
  junction[2] =  DirectionTown(boboard,test[2]);
  int tab_vide[3] = {0,0,0};
  TabPositionVide(tab_vide,junction,3,boboard);
  struct triplet next[3];
  struct city * find[3];

  if(tab_vide[0] == 0 && tab_vide[1] == 0 && tab_vide[2] == 0){
    lnk_add2(boboard->cities,llm_c);
    return;
  }
  
  if(tab_vide[0] == 1 && tab_vide[1] == 0 && tab_vide[2] == 0){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    MergeTown(find[0],town);
    free(town);
    find[0]->border += 1;
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  if(tab_vide[0] == 0 && tab_vide[1] == 1 && tab_vide[2] == 0){
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    MergeTown(find[1],town);
    free(town);
    find[1]->border += 1;
    if(find[1]->border == 0)
      CreditPointTown(boboard,find[1]);
    return;
  }

  if(tab_vide[0] == 0 && tab_vide[1] == 0 && tab_vide[2] == 1){
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    MergeTown(find[2],town);
    free(town);
    find[2]->border += 1;
    if(find[2]->border == 0)
      CreditPointTown(boboard,find[2]);
    return;
  }

  if(tab_vide[0] == 1 && tab_vide[1] == 1 && tab_vide[2] == 0){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    if(find[0] == find[1]){
      MergeTown(find[0],town);
      free(town);
      find[0]->border -=1;
    }
    else{
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border =find[0]->border + find[1]->border - 1;
      RemoveTown(boboard->cities,find[1]);
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  if(tab_vide[0] == 1 && tab_vide[1] == 0 && tab_vide[2] == 1){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    if(find[0] == find[2]){
      MergeTown(find[0],town);
      free(town);
      find[0]->border -= 1;
    }
    else {
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[2]->border + find[0]->border  -1;
      RemoveTown(boboard->cities,find[2]);
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }
  
  if(tab_vide[0] == 0 && tab_vide[1] == 1 && tab_vide[2] == 1){
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    if(find[1] == find[2]){
      MergeTown(find[1],town);
      free(town);
      find[0]->border -= 1;
    }
    else{
      MergeTown(find[1],town);
      MergeTown(find[1],find[2]);
      free(town);
      find[1]->border = find[1]->border + find[2]->border -1;
      RemoveTown(boboard->cities,find[2]);
    }
    if(find[1]->border == 0)
      CreditPointTown(boboard,find[1]);
    return;
  }

  if(tab_vide[0] == 1 && tab_vide[1] == 1 && tab_vide[2] == 1){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    if(find[0] != find[1] && find[0] != find[2] && find[1] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border + find[2]->border - 3;
      RemoveTown(boboard->cities,find[1]);
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[0] == find[1] && find[0] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[2]->border -3;
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[0] != find[1] && find[0] == find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -3;
      RemoveTown(boboard->cities,find[1]);
    }
    else if(find[0] != find[1] && find[1] == find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -3;
      RemoveTown(boboard->cities,find[1]);
    }
    else {
      MergeTown(find[0],town);
      free(town);
      find[0]->border -=3;
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }
}

void QuatraExternFusion(struct boardgame * boboard,struct city * town){
  struct lelement * llm_c = llm_empty();
  llm_c->data = (struct city *)malloc(sizeof(struct city));
  struct city * tmp_c = (struct city *)llm_c->data;
  copie_town(tmp_c,town);

  struct triplet * test[4];
  test[0] =(struct triplet *)town->lst_triplet->head->data;
  test[1] =(struct triplet *)town->lst_triplet->head->next->data;
  test[2] =(struct triplet *)town->lst_triplet->head->next->next->data;
  test[3] =(struct triplet *)town->lst_triplet->head->next->next->next->data;
  struct position junction[4];
  junction[0] = DirectionTown(boboard,test[0]);
  junction[1] = DirectionTown(boboard,test[1]);
  junction[2] = DirectionTown(boboard,test[2]);
  junction[3] = DirectionTown(boboard,test[3]);
  int tab_vide[4] = {0,0,0,0};
  TabPositionVide(tab_vide,junction,4,boboard);
  struct triplet next[4];
  struct city * find[4];

  //0 parmi 4
  
  if(tab_vide[0] == 0 && tab_vide[1] == 0 && tab_vide[2] == 0 && tab_vide[3] == 0){
    lnk_add2(boboard->cities,llm_c);
    return;
  }

  //1 parmi 4 
  
  if(tab_vide[0] == 1 && tab_vide[1] == 0 && tab_vide[2] == 0 && tab_vide[3] == 0){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    MergeTown(find[0],town);
    free(town);
    find[0]->border += 2;
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  else if(tab_vide[0] == 0 && tab_vide[1] == 1 && tab_vide[2] == 0 && tab_vide[3] == 0){
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    MergeTown(find[1],town);
    free(town);
    find[1]->border += 2;
    if(find[1]->border == 0)
      CreditPointTown(boboard,find[1]);
    return;
  }

  else if(tab_vide[0] == 0 && tab_vide[1] == 0 && tab_vide[2] == 1 && tab_vide[3] == 0){
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    MergeTown(find[2],town);
    free(town);
    find[2]->border += 2;
    if(find[2]->border == 0)
      CreditPointTown(boboard,find[2]);
    return;
  }

  else if(tab_vide[0] == 0 && tab_vide[1] == 0 && tab_vide[2] == 0 && tab_vide[3] == 1){
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    MergeTown(find[3],town);
    free(town);
    find[3]->border += 2;
    if(find[3]->border == 0)
      CreditPointTown(boboard,find[3]);
    return;
  }
  
  //2 parmi 4

  else if(tab_vide[0] == 1 && tab_vide[1] == 1 && tab_vide[2] == 0 && tab_vide[3] == 0){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    if(find[0] == find[1]){
      MergeTown(find[0],town);
      free(town);
    }
    else{
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border;
      RemoveTown(boboard->cities,find[1]);
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  else if(tab_vide[0] == 1 && tab_vide[1] == 0 && tab_vide[2] == 1 && tab_vide[3] == 0){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    if(find[0] == find[2]){
      MergeTown(find[0],town);
      free(town);
    }
    else{
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border =  find[0]->border +  find[1]->border;
      RemoveTown(boboard->cities,find[2]);
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  else if(tab_vide[0] == 1 && tab_vide[1] == 0 && tab_vide[2] == 0 && tab_vide[3] == 1){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    if(find[0] == find[3]){
      MergeTown(find[0],town);
      free(town);
    }
    else{
      MergeTown(find[0],town);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border =  find[0]->border +  find[3]->border;
      RemoveTown(boboard->cities,find[3]);
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }
  
  else if(tab_vide[0] == 0 && tab_vide[1] == 1 && tab_vide[2] == 1 && tab_vide[3] == 0){
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    if(find[1] == find[2]){
      MergeTown(find[1],town);
      free(town);
    }
    else{
      MergeTown(find[1],town);
      MergeTown(find[1],find[2]);
      free(town);
      find[1]->border =  find[1]->border + find[2]->border;
      RemoveTown(boboard->cities,find[2]);
    }
    if(find[1]->border == 0)
      CreditPointTown(boboard,find[1]);
    return;
  }

  else if(tab_vide[0] == 0 && tab_vide[1] == 1 && tab_vide[2] == 0 && tab_vide[3] == 1){
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    if(find[1] == find[3]){
      MergeTown(find[1],town);
      free(town);
    }
    else{
      MergeTown(find[1],town);
      MergeTown(find[1],find[3]);
      free(town);
      find[1]->border =  find[1]->border + find[3]->border;
      RemoveTown(boboard->cities,find[3]);
    }
    if(find[1]->border == 0)
      CreditPointTown(boboard,find[1]);
    return;
  }

  else if(tab_vide[0] == 0 && tab_vide[1] == 0 && tab_vide[2] == 1 && tab_vide[3] == 1){
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    if(find[2] == find[3]){
      MergeTown(find[2],town);
      free(town);
    }
    else{
      MergeTown(find[2],town);
      MergeTown(find[2],find[3]);
      free(town);
      find[2]->border =  find[2]->border + find[3]->border;
      RemoveTown(boboard->cities,find[3]);
    }
    if(find[2]->border == 0)
      CreditPointTown(boboard,find[2]);
    return;
  }

  // 3 parmi 4
  
  else if(tab_vide[0] == 1 && tab_vide[1] == 1 && tab_vide[2] == 1 && tab_vide[3] == 0){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    if(find[0] != find[1] && find[0] != find[2] && find[1] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border + find[2]->border - 2;
      RemoveTown(boboard->cities,find[1]);
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[0] == find[1] && find[0] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[2]->border -2;
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[0] != find[1] && find[0] == find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -2;
      RemoveTown(boboard->cities,find[1]);
    }
    else if(find[0] != find[1] && find[1] == find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -2;
      RemoveTown(boboard->cities,find[1]);
    }
    else {
      MergeTown(find[0],town);
      find[0]->border -=2;
      free(town);
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  else if(tab_vide[0] == 1 && tab_vide[1] == 1 && tab_vide[2] == 0 && tab_vide[3] == 1){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    if(find[0] != find[1] && find[0] != find[3] && find[1] != find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border + find[3]->border - 3;
      RemoveTown(boboard->cities,find[1]);
      RemoveTown(boboard->cities,find[3]);
    }
    else if(find[0] == find[1] && find[0] != find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[3]->border -2;
      RemoveTown(boboard->cities,find[3]);
    }
    else if(find[0] != find[1] && find[0] == find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -2;
      RemoveTown(boboard->cities,find[1]);
    }
    else if(find[0] != find[1] && find[1] == find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -2;
      RemoveTown(boboard->cities,find[1]);
    }
    else {
      MergeTown(find[0],town);
      find[0]->border -=2;
      free(town);
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  else if(tab_vide[0] == 1 && tab_vide[1] == 0 && tab_vide[2] == 1 && tab_vide[3] == 1){
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    if(find[0] != find[3] && find[0] != find[2] && find[3] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[3]);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[3]->border + find[2]->border - 2;
      RemoveTown(boboard->cities,find[3]);
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[0] == find[3] && find[0] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[2]->border -2;
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[0] != find[3] && find[0] == find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[3]->border -2;
      RemoveTown(boboard->cities,find[3]);
    }
    else if(find[0] != find[3] && find[3] == find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[3]->border -2;
      RemoveTown(boboard->cities,find[3]);
    }
    else {
      MergeTown(find[0],town);
      free(town);
      find[0]->border -=2;
    }
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }

  else if(tab_vide[0] == 0 && tab_vide[1] == 1 && tab_vide[2] == 1 && tab_vide[3] == 1){
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    if(find[3] != find[1] && find[3] != find[2] && find[1] != find[2]){
      MergeTown(find[3],town);
      MergeTown(find[3],find[1]);
      MergeTown(find[3],find[2]);
      free(town);
      find[3]->border = find[3]->border + find[1]->border + find[2]->border - 2;
      RemoveTown(boboard->cities,find[1]);
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[3] == find[1] && find[3] != find[2]){
      MergeTown(find[3],town);
      MergeTown(find[3],find[2]);
      free(town);
      find[3]->border = find[3]->border + find[2]->border -2;
      RemoveTown(boboard->cities,find[2]);
    }
    else if(find[3] != find[1] && find[3] == find[2]){
      MergeTown(find[3],town);
      MergeTown(find[3],find[1]);
      free(town);
      find[3]->border = find[3]->border + find[1]->border -2;
      RemoveTown(boboard->cities,find[1]);
    }
    else if(find[3] != find[1] && find[1] == find[2]){
      MergeTown(find[3],town);
      MergeTown(find[3],find[1]);
      free(town);
      find[3]->border = find[3]->border + find[1]->border -2;
      RemoveTown(boboard->cities,find[1]);
    }
    else {
      MergeTown(find[3],town);
      free(town);
      find[3]->border -=2;
    }
    if(find[1]->border == 0)
      CreditPointTown(boboard,find[1]);
    return;
  }

  // 4 parmis 4
  else{
    next[0] = NextTripletTown(test[0],junction[0],boboard->board[junction[0].x][junction[0].y].dir,boboard->board[test[0]->x][test[0]->y].dir);
    find[0] = FindTown(boboard,next[0]);
    next[1] = NextTripletTown(test[1],junction[1],boboard->board[junction[1].x][junction[1].y].dir,boboard->board[test[1]->x][test[1]->y].dir);
    find[1] = FindTown(boboard,next[1]);
    next[2] = NextTripletTown(test[2],junction[2],boboard->board[junction[2].x][junction[2].y].dir,boboard->board[test[2]->x][test[2]->y].dir);
    find[2] = FindTown(boboard,next[2]);
    next[3] = NextTripletTown(test[3],junction[3],boboard->board[junction[3].x][junction[3].y].dir,boboard->board[test[3]->x][test[3]->y].dir);
    find[3] = FindTown(boboard,next[3]);
    if(find[0] != find[1] && find[0] != find[2] && find[0] != find[3] && find[1] != find[2] && find[1] != find[3] && find[2] != find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      MergeTown(find[0],find[2]);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border + find[2]->border + find[3]->border -4;
      RemoveTown(boboard->cities,find[1]);
      RemoveTown(boboard->cities,find[2]);
      RemoveTown(boboard->cities,find[3]);
    }

    else if (find[0] == find[1] && find[0] != find[2] && find[0] != find[3] && find[2] != find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[2]->border + find[3]->border -4;
      RemoveTown(boboard->cities,find[2]);
      RemoveTown(boboard->cities,find[3]);
    }
    else if (find[0] == find[1] && find[0] != find[2] && find[0] != find[3] && find[2] == find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[2]->border -4;
      RemoveTown(boboard->cities,find[2]);
    }
    
    else if (find[0] == find[2] && find[0] != find[1] && find[0] != find[3] && find[1] != find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border + find[3]->border -4;
      RemoveTown(boboard->cities,find[1]);
      RemoveTown(boboard->cities,find[3]);
    }
    else if (find[0] == find[2] && find[0] != find[1] && find[0] != find[3] && find[1] == find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -4;
      RemoveTown(boboard->cities,find[1]);
    }

    else if (find[0] == find[3] && find[0] != find[1] && find[0] != find[2] && find[1] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border + find[2]->border -4;
      RemoveTown(boboard->cities,find[1]);
      RemoveTown(boboard->cities,find[2]);
    }
    else if (find[0] == find[3] && find[0] != find[1] && find[0] != find[2] && find[1] == find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[0]->border + find[1]->border -4;
      RemoveTown(boboard->cities,find[1]);
    }

    else if (find[1] == find[2] && find[1] != find[0] && find[1] != find[3] && find[0] != find[3]){
      MergeTown(find[1],town);
      MergeTown(find[1],find[0]);
      MergeTown(find[1],find[3]);
      free(town);
      find[1]->border = find[1]->border + find[0]->border + find[3]->border -4;
      RemoveTown(boboard->cities,find[0]);
      RemoveTown(boboard->cities,find[3]);
    }
    else if (find[1] == find[2] && find[1] != find[0] && find[1] != find[3] && find[0] == find[3]){
      MergeTown(find[1],town);
      MergeTown(find[1],find[0]);
      free(town);
      find[1]->border = find[1]->border + find[0]->border -4;
      RemoveTown(boboard->cities,find[0]);
    }


    else if (find[0] == find[1] && find[0] == find[2] && find[0] != find[3]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[3]);
      free(town);
      find[0]->border = find[0]->border + find[3]->border -4;
      RemoveTown(boboard->cities,find[3]);
    }
    
    else if (find[0] == find[1] && find[0] == find[3] && find[0] != find[2]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[2]);
      free(town);
      find[0]->border = find[0]->border + find[2]->border -4;
      RemoveTown(boboard->cities,find[2]);
    }
    
    else if (find[0] == find[2] && find[0] == find[3] && find[0] != find[1]){
      MergeTown(find[0],town);
      MergeTown(find[0],find[1]);
      free(town);
      find[0]->border = find[1]->border + find[0]->border -4;
      RemoveTown(boboard->cities,find[1]);
    }

    else if (find[1] == find[2] && find[1] == find[3] && find[1] != find[0]){
      MergeTown(find[1],town);
      MergeTown(find[1],find[0]);
      free(town);
      find[1]->border = find[1]->border + find[0]->border -4;
      RemoveTown(boboard->cities,find[0]);
    }

    else{
      MergeTown(find[0],town);
      free(town);
      find[0]->border -=4;
    }
    
    if(find[0]->border == 0)
      CreditPointTown(boboard,find[0]);
    return;
  }
}
  


  
void ExternFusionTown(struct boardgame * boboard, struct city * town){
  if(town->border == 1){
    SingleExternFusion(boboard,town);
  }
  else if(town->border == 2){
    DoubleExternFusion(boboard,town);
  }
  else if(town->border == 3){
    TripleExternFusion(boboard,town);
  }
  else{
    QuatraExternFusion(boboard,town);
  }
}


void UpdateTown(struct boardgame * boboard, struct tuille tutuille){
  struct city * townTutuille[4];
  for(int i = 0;i<4;i++){
    townTutuille[i] = TownVide();
  }
  int numbTown = ExtractTown(&tutuille,townTutuille);
  numbTown = InternFusionTown(tutuille,townTutuille,numbTown);
  for(int i = 0;i<numbTown;i++){
    ExternFusionTown(boboard,townTutuille[i]);
  }
}


void aff_lnk_tuile_town(struct link * lnk){
  if(lnk->head == NULL){
    printf("NONE\n");
    return;
  }
  int len = lnk->taille; 
  struct lelement * current = lnk->head;
  struct tuille * t = (struct tuille *)lnk->head->data;
  for(int i =0;i<len;i++){
    printf("tuile %d : pos = (%d, %d), dir = %d, id = %d\n",i,t->position[0],t->position[1],t->dir,t->id);
    if(current->next != NULL)
      current = current->next;
    t = (struct tuille *)current->data;
  }
}

void aff_lnk_triplet(struct link * lnk){
  if(lnk->head == NULL){
    printf("NONE\n");
    return;
  }
  int len = lnk->taille;
  struct lelement * current = lnk->head;
  struct triplet * t = (struct triplet *)lnk->head->data;
  for(int i =0;i<len;i++){
    printf("triplet %d : pos = (%d, %d, %d)\n",i,t->x,t->y,t->z);
    if(current->next != NULL){
      current = current->next;
    }
    t = (struct triplet *)current->data;
  }
}

void aff_lnk_field(struct link *lnk){
  if(lnk == NULL){
    printf("NONE\n");
    return;
  }
  struct lelement * current = lnk->head;
  if(current == NULL){
    printf("NONE\n");
    return;
  }
  struct field * tmp_f = (struct field *)current->data;
  for(int i=0;i<lnk->taille;i++){
    printf("----champ %d----\n",i);
    printf("len : %d\n",tmp_f->len);
    printf("paysans : ");
    for(int i = 0;i<PLAYER_MAX;i++){
      printf(" player %d : %d |",i,tmp_f->paysans[i]);
    }
    printf("\n");
    printf(" lst_tuille : \n");
    aff_lnk_tuile_town(tmp_f->lst_tutuille);
    printf(" lst_triplet ; \n");
    aff_lnk_triplet(tmp_f->lst_triplet);
    printf("---------------\n");
    if(current->next != NULL){
      current = current->next;
    }
    tmp_f = (struct field *)current->data;
  }
}

void aff_Town(struct city * town){
  printf("\n");
  printf("-----------------------------------------------------\n");
  printf("-----------------------TOWN--------------------------\n");
  printf(" lst_tuille : \n");
  aff_lnk_tuile_town(town->lst_tutuille);
  printf(" lst_triplet : \n");
  aff_lnk_triplet(town->lst_triplet);
  printf("chevalier : "); 
  for(int i = 0;i<PLAYER_MAX;i++){
    printf(" player %d : %d |",i,town->chevaliers[i]);
  }
  printf("\n");
  printf("----------fields---------\n");
  if(town->lst_champ == NULL)
    printf("NONE\n");
  else
    aff_lnk_field(town->lst_champ);
  printf("------------------------\n");
  printf("border : %d\n",town->border);
  printf("len : %d\n",town->len);
  printf("shield : %d\n",town->shield);
  printf("-----------------------------------------------------\n");
  printf("-----------------------------------------------------\n");
  printf("\n");
}
  
