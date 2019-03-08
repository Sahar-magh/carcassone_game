#include <stdlib.h>
#include <stdio.h>
#include "link.h"
#include "carte.h"


/** \brief creer un struct link vide
* \param void
* \return un pointeur vers un link vide
* Renvoit un pointeur vers un link initialisé.
*/
struct link * lnk_empty()
{
  struct link * valu;
  valu =(struct link*)malloc(sizeof(struct link));
  valu->taille = 0;
  valu->head = NULL;
  valu->tail = NULL;
  return valu;
}

/** \brief creer un struct  lelement vide
* \param void
* \return un pointeur vers un lelement vide
* Renvoit un pointeur vers un lelement initialisé.
*/
struct lelement * llm_empty()
{
  struct lelement * valu;
  valu =(struct lelement *)malloc(sizeof(struct lelement));
  valu->data = NULL;
  valu->next = NULL;
  valu->previous = NULL;
  return valu;
}


/** \brief ajoute un lelement à un link
* \param lnk : le link de référence
* \param new_llm : lelement à rajouter
* \return void
* Rajoute lelement new_llm au bout de link
*/
void lnk_add2(struct link * lnk, struct lelement * new_llm){
  if(lnk->head == NULL){
    lnk->head = new_llm;
    lnk->tail = new_llm;
    lnk->taille = 1;
    return;
  }
  lnk->tail->next = new_llm;
  new_llm->previous = lnk->tail;
  lnk->tail = lnk->tail->next;
  lnk->taille ++;
}

/** \brief Compare 2 tuile
* \param tutuille1 : la premiere tuile
* \param tutuille2 : la deuxieme tuile
* \return booleen
* Compare tous les champs des deux structures
*/
int is_equal(struct tuille * tutuille1, struct tuille * tutuille2) {
  for(int i =0;i<4;i++){
    for(int j = 0;j<3;j++){
      if(tutuille1->type[i][j] != tutuille2->type[i][j])
	return FALSE;
      if(tutuille2->pion[i][j] != tutuille1->pion[i][j])
	return FALSE;
    }
  }
  if( tutuille2->dir != tutuille1->dir)
    return FALSE;
  if( tutuille1->milieu != tutuille2->milieu)
    return FALSE;
  if( tutuille2->shield != tutuille1->shield)
    return FALSE;
  if( tutuille1->position[0] != tutuille2->position[0])
    return FALSE;
  if( tutuille2->position[1] != tutuille1->position[1])
    return FALSE;
  if( tutuille1->id != tutuille2->id)
    return FALSE;
  return TRUE;
}

/** \brief libere un link
* \param lnk : le link à liberer
* \return void
* Libere le link est tous les lelement à l'interieur
*/
void lnk_free(struct link * lnk)
{
  struct lelement * current = lnk->head->next;
  for (int i = 2; i < lnk->taille ; i++) {
    free(current->previous);
    current = current->next;
  }
  lnk->taille = 0;
  free(current);
  free(lnk);
}


/** \brief libere un lelement
* \param llm : lelement à liberer
* \return void
*/
void llm_free(struct lelement * llm)
{
  free(llm);
}

/** \brief fusionne 2 link
* \param lnk1 : le link de reference
* \param lnk2 : le link à fusionné
* \return void
* Chaine la fin de lnk1 avec le debut de lnk2
*/
void lnk_merge(struct link * lnk1, struct link * lnk2){
  lnk1->tail->next = lnk2->head;
  lnk2->head->previous = lnk1->tail;
  lnk1->tail =lnk2->tail;
  lnk1->taille += lnk2->taille;
  free(lnk2);
}

