#include "updateCloister.h"



int NumberVoisin(struct boardgame * boboard, struct tuille tutuille){
  int num = 0;
  int x = tutuille.position[0];
  int y = tutuille.position[1];
  struct tuille tvide = gen_tuile_vide();
  if(same_card(&(boboard->board[x-1][y+1]), &(tvide)) == FALSE)
    num++;
  if(same_card(&(boboard->board[x-1][y]), &(tvide)) == FALSE)
    num++;
  if(same_card(&(boboard->board[x-1][y-1]), &(tvide)) == FALSE)
    num++;
  if(same_card(&(boboard->board[x][y-1]), &(tvide)) == FALSE)
    num++;
  if(same_card(&(boboard->board[x+1][y-1]), &(tvide)) == FALSE)
    num++;
  if(same_card(&(boboard->board[x+1][y]), &(tvide)) == FALSE)
    num++;
  if(same_card(&(boboard->board[x+1][y+1]), &(tvide)) == FALSE)
    num++;
  if(same_card(&(boboard->board[x][y+1]), &(tvide)) == FALSE)
    num++;
  return num;
}


void CreditPointAbbaye(struct boardgame * boboard, struct abbaye * chapel){
  int point = chapel->voisin + 1;
  if(chapel->possesseur != NONE)
    boboard->points[chapel->possesseur] += point;
}

void copieAbbaye(struct abbaye * a1, struct abbaye * a2){
  a1->cloister = a2->cloister;
  a1->voisin = a2->voisin;
  a1->possesseur = a2->possesseur;
}

int WhereAbbaye(struct boardgame * boboard, struct tuille tutuille, struct position lst[]){
  int num = 0;
  int x = tutuille.position[0];
  int y = tutuille.position[1];
  if(boboard->board[x-1][y+1].milieu == 3){
    lst[num].x = x-1;
    lst[num].y = y+1;
    num++;
  }
  if(boboard->board[x-1][y].milieu == 3){
    lst[num].x = x-1;
    lst[num].y = y;
    num++;
  }
  if(boboard->board[x-1][y-1].milieu == 3){
    lst[num].x = x-1;
    lst[num].y = y-1;
    num++;
  }
  if(boboard->board[x][y-1].milieu == 3){
    lst[num].x = x;
    lst[num].y = y-1;
    num++;
  }
  if(boboard->board[x+1][y-1].milieu == 3){
    lst[num].x = x+1;
    lst[num].y = y-1;
    num++;    
  }
  if(boboard->board[x+1][y].milieu == 3){
    lst[num].x = x+1;
    lst[num].y = y;
    num++;
  }
  if(boboard->board[x+1][y+1].milieu == 3){
    lst[num].x = x+1;
    lst[num].y = y+1;
    num++;
  }
  if(boboard->board[x][y+1].milieu == 3){
    lst[num].x = x;
    lst[num].y = y+1;
    num++;
  }
  return num; 
}

void AddOneVoisin(struct boardgame * boboard, struct position pos){ 
  struct lelement * current = boboard->abbayes->head;
  struct abbaye * chapel = (struct abbaye * )current->data;
  for(int i = 0;i<boboard->abbayes->taille;i++){
    if((chapel->cloister.position[0] == pos.x) && (chapel->cloister.position[1] == pos.y)){
      chapel->voisin += 1;
    }
    if(current->next != NULL)
      current = current->next;
    chapel = (struct abbaye * )current->data;
  }
}

void updateCloister(struct boardgame * boboard, struct tuille tutuille){
  if(tutuille.milieu == 3){
    struct abbaye chapel;
    chapel.cloister = tutuille;
    chapel.voisin = NumberVoisin(boboard,tutuille);
    chapel.possesseur = NONE;
    if(tutuille.pion[0][1] != NONE)
      chapel.possesseur = tutuille.pion[0][1];
    if(chapel.voisin == 8 && chapel.possesseur != NONE)
      CreditPointAbbaye(boboard,&chapel);
    struct lelement * llm_a = llm_empty();
    llm_a->data = (struct abbaye * )malloc(sizeof(struct abbaye));
    struct abbaye * tmp_a = (struct abbaye * )llm_a->data;
    copieAbbaye(tmp_a,&chapel);
    lnk_add2(boboard->abbayes,llm_a);
  }
  struct position lstPositon[8];
  int len_pos = WhereAbbaye(boboard,tutuille,lstPositon);
  if(len_pos > 0){
    for(int i=0; i<len_pos;i++){
      AddOneVoisin(boboard,lstPositon[i]);
    }
  }
}

void aff_cloister(struct abbaye * chapel){
  printf("-----Cloister-----\n");
  printf("tuile : %d\n",chapel->cloister.id);
  printf("voisin : %d\n",chapel->voisin);
  printf("possesseur : %d\n",chapel->possesseur);
}
