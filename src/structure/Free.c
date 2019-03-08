#include "meeple.h"



//////////////////////////////////////

void FreeLstTriplet(struct link * lnk){
  if(lnk != NULL){
    if(lnk->head != NULL){
      if(lnk->head->next == NULL){
	      struct triplet * t = (struct triplet *)lnk->head->data;
	      free(t);
	      free(lnk->head);
	      free(lnk);
      }
      else{
	struct triplet * t = (struct triplet *)lnk->head->data;
	free(t);
	for(struct lelement * current=lnk->head->next ; current->next != NULL; current = current->next){
	  t = (struct triplet *)current->data;
	  free(t);
	  free(current->previous);
	}
	free(lnk->tail);
	free(lnk);
      }
    }
    else
      free(lnk);
  }
}

void FreeLstTuile(struct link * lnk){
  if(lnk != NULL){
    if(lnk->head != NULL){
      if(lnk->head->next == NULL){
	struct tuille * tutuille = (struct tuille *)lnk->head->data;
	free(tutuille);
	free(lnk->head);
	free(lnk);
      }
      else{
	struct tuille * tutuille = (struct tuille *)lnk->head->data;
	free(tutuille);
	for(struct lelement * current=lnk->head->next ;current->next != NULL; current = current->next){
	  tutuille = (struct tuille *)current->data;
	  free(tutuille);
	  free(current->previous);
	}
	free(lnk->tail);
	free(lnk);
      }
    }
    else
      free(lnk);
  }
}

/////////////////////////////////
///////// Roads ////////////////

void FreeRoad(struct road * route){
  if(route != NULL){
    FreeLstTuile(route->lst_tutuille);
    FreeLstTriplet(route->nys_idea);
    free(route);
  }
}

void FreeRoads(struct link * lnk){
  if(lnk != NULL){
    if(lnk->head != NULL){
      struct road * route = (struct road *)lnk->head->data;
      FreeRoad(route);
      for(struct lelement* current = lnk->head->next;current->next != NULL;current = current->next){
	route =(struct road *)current->data;
	FreeRoad(route);
	free(current->previous);
      }
      free(lnk->tail);
      free(lnk);
    }
    else
      free(lnk);
  }
}

/////////////////////////////////
/////////Abbayes/////////////////

void FreeAbbayes(struct link * lnk){
  if(lnk != NULL){
    struct lelement * current = lnk->head;
    if( current != NULL){
      struct abbaye * cloister = (struct abbaye *)current->data;
      for(int i =0;i<lnk->taille;i++){
	free(cloister);
	if(current->next != NULL)
	  current = current->next;
	cloister =(struct abbaye *)current->data;
	if(i<lnk->taille -1)
	  free(current->previous);
      }
      free(lnk->tail);
      free(lnk);
    }
    else
      free(lnk);
  }
}

////////////////////////////////
/////////// Fields /////////////

void FreeField(struct field * f){
  if(f != NULL){
    FreeLstTuile(f->lst_tutuille);
    FreeLstTriplet(f->lst_triplet);
    free(f);
  }
}

void FreeLstChamp(struct link * lnk){
  if(lnk != NULL){
    struct lelement * current = lnk->head;
    if(current != NULL){
      struct field * f = (struct field *)current->data;
      for(int i =0;i<lnk->taille;i++){
	FreeField(f);
	if(current->next != NULL)
	  current = current->next;
	f =(struct field *)current->data;
	if(i<lnk->taille -1)
	  free(current->previous);
      }
      free(lnk->tail);
      free(lnk);
    }
    else
      free(lnk);
  }
}

////////////////////////////////////////////
///////////////// cities ///////////////////

void FreeCity(struct city *c){
  if(c != NULL){
    FreeLstTuile(c->lst_tutuille);
    FreeLstTriplet(c->lst_triplet);
    FreeLstChamp(c->lst_champ);
    free(c);
  }
}

void FreeCities(struct link * lnk){
  if(lnk != NULL){
    struct lelement * current = lnk->head;
    if(current != NULL){
      struct city * c = (struct city *)current->data;
      for(int i =0;i<lnk->taille;i++){
	FreeCity(c);
	if(current->next != NULL)
	  current = current->next;
	c =(struct city *)current->data;
	if(i<lnk->taille -1)
	  free(current->previous);
      }
      free(lnk->tail);
      free(lnk);
    }
    else{
      free(lnk);
    }
  }
}

////////////////////Board game //////////////////
////////////////////////////////////////////////

void FreeBordgame(struct boardgame * boboard){
  if(boboard != NULL){
    FreeRoads(boboard->roads);
    FreeAbbayes(boboard->abbayes);
    FreeCities(boboard->cities);
    FreeLstChamp(boboard->fields);
    free(boboard);
  }
}

