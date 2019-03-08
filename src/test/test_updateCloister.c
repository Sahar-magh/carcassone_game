#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../structure/carte.h"
#include "../structure/link.h"
#include "../updateFunctions/updateCloister.h"

////////////Function used to debug////////////
///////////////affichage de la tuille ////////

/** \brief afficher une tuille
* \param t : tuille à afficher 
* \return affichage des nformations stockés dans la tuille 
.
*/
void aff_tuile(struct tuille t){
  printf("----------tuile-------------\n");
  printf("type : { ");
  for(int i =0;i<4;i++){
    printf("{ ");
    for(int j=0;j<3;j++){
      printf("%d, ",t.type[i][j]);
    }
    printf("} ");
  }
  printf("}\n");
  printf("pion : { ");
  for(int i =0;i<4;i++){
    printf("{ ");
    for(int j=0;j<3;j++){
      printf("%d, ",t.pion[i][j]);
    }
    printf("} ");
  }
  printf("}\n");
  printf("id : %d\n",t.id);
  printf("dir : %d\n",t.dir);
  printf("milieu : %d\n",t.milieu);
  printf("shield : %d\n",t.shield);
  printf("position : (%d,%d)\n",t.position[0],t.position[1]);
  printf("---------------------------\n");
  printf("\n");
}

//////////////////////////////////////////////
/////////////////TESTS functions ////////////////////////

/** 
Test de la fonction NumberVoisin
*/
void test_NumberVoisin(){
  struct boardgame test_board;
  initialisation_board(&test_board);
  struct tuille tutuille_1 = genere_tuille(66);
  struct tuille tutuille_2 = genere_tuille(66);
  struct tuille tutuille_3 = genere_tuille(66);
  struct tuille tutuille_4 = genere_tuille(66);
  struct tuille tutuille_5 = genere_tuille(66);
  struct tuille tutuille_6 = genere_tuille(66);
  struct tuille tutuille_7 = genere_tuille(66);
  struct tuille tutuille_8 = genere_tuille(66);
  struct tuille tutuille_cloister = genere_tuille(5);
  tutuille_cloister.position[0] = 11;
  tutuille_cloister.position[1] = 11;

  test_board.board[11][11] = tutuille_cloister;

  assert(NumberVoisin(&test_board,tutuille_cloister) == 0);

  test_board.board[10][10] = tutuille_1;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 1);
  test_board.board[10][11] = tutuille_2;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 2);
  test_board.board[10][12] = tutuille_3;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 3);
  test_board.board[11][10] = tutuille_4;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 4);
  test_board.board[11][12] = tutuille_5;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 5);
  test_board.board[12][10] = tutuille_6;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 6);
  test_board.board[12][11] = tutuille_7;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 7);
  test_board.board[12][12] = tutuille_8;
  assert(NumberVoisin(&test_board,tutuille_cloister) == 8);


  printf("TEST_NUMBER_VOISIN\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}



/** 
Test de la fonction test_WhereAbbaye
*/

void test_WhereAbbaye(){
  struct boardgame test_board;
  initialisation_board(&test_board);
  struct tuille tutuille_cloister_1 = genere_tuille(5);
  struct tuille tutuille_cloister_2 = genere_tuille(5);
  struct tuille tutuille_cloister_3 = genere_tuille(5);
  struct tuille tutuille_cloister_4 = genere_tuille(5);
  struct tuille tutuille_cloister_5 = genere_tuille(5);
  struct tuille tutuille_not_cloister_6 = genere_tuille(66);
  struct tuille tutuille_cloister_7 = genere_tuille(5);
  struct tuille tutuille_not_cloister_8 = genere_tuille(66);
  struct tuille tutuille_not_cloister_9 = genere_tuille(66);

  struct position lstPosition[8];
  for(int i = 0;i<8;i++){
    lstPosition[i].x = NONE;
    lstPosition[i].y = NONE;
  }

  tutuille_cloister_1.position[0] = 11;
  tutuille_cloister_1.position[1] = 11;

  test_board.board[11][11] = tutuille_cloister_1;

  assert(WhereAbbaye(&test_board,tutuille_cloister_1,lstPosition) == 0); 
  for(int i = 0;i<8;i++){
    assert(lstPosition[i].x == NONE);
    assert(lstPosition[i].y == NONE);
  }

  test_board.board[10][10] = tutuille_cloister_2;

  assert(WhereAbbaye(&test_board,tutuille_cloister_1,lstPosition) == 1);
  assert(lstPosition[0].x == 10);
  assert(lstPosition[0].y == 10);
  for(int i = 1;i<8;i++){
    assert(lstPosition[i].x == NONE);
    assert(lstPosition[i].y == NONE);
  }

  for(int i = 0;i<8;i++){
    lstPosition[i].x = NONE;
    lstPosition[i].y = NONE;
  }  
  test_board.board[10][12] = tutuille_cloister_4;

  assert(WhereAbbaye(&test_board,tutuille_cloister_1,lstPosition) == 2);
  assert(lstPosition[0].x == 10);
  assert(lstPosition[0].y == 12);
  assert(lstPosition[1].x == 10);
  assert(lstPosition[1].y == 10);
  for(int i = 2;i<8;i++){
    assert(lstPosition[i].x == NONE);
    assert(lstPosition[i].y == NONE);
  }

  test_board.board[10][11] = tutuille_cloister_3;
  test_board.board[11][10] = tutuille_cloister_5;
  test_board.board[11][12] = tutuille_not_cloister_6;
  test_board.board[12][10] = tutuille_cloister_7;
  test_board.board[12][11] = tutuille_not_cloister_8;
  test_board.board[12][12] = tutuille_not_cloister_9;

  assert(WhereAbbaye(&test_board,tutuille_cloister_1,lstPosition) == 5);
  assert(lstPosition[0].x == 10);
  assert(lstPosition[0].y == 12);
  assert(lstPosition[1].x == 10);
  assert(lstPosition[1].y == 11);
  assert(lstPosition[2].x == 10);
  assert(lstPosition[2].y == 10);
  assert(lstPosition[3].x == 11);
  assert(lstPosition[3].y == 10);
  assert(lstPosition[4].x == 12);
  assert(lstPosition[4].y == 10);
  for(int i = 5;i<8;i++){
    assert(lstPosition[i].x == NONE);
    assert(lstPosition[i].y == NONE);
  }


  printf("TEST_WHERE_ABBAYE\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}




/** 
Test de la fonction test_AddOneVoisin
*/

void test_AddOneVoisin(){
  struct boardgame test_board;
  initialisation_board(&test_board);
  struct abbaye chap_1;
  struct abbaye chap_2;
  struct lelement * llm_1 = llm_empty();
  llm_1->data = (struct abbaye * )malloc(sizeof(struct abbaye));
  struct lelement * llm_2 = llm_empty();
  llm_2->data = (struct abbaye * )malloc(sizeof(struct abbaye));
  struct tuille tuille_cloister_1 = genere_tuille(5);
  struct tuille tuille_cloister_2 = genere_tuille(5);

  tuille_cloister_1.position[0] = 10;
  tuille_cloister_1.position[1] = 10;
  tuille_cloister_2.position[0] = 10;
  tuille_cloister_2.position[1] = 12;

  chap_1.cloister = tuille_cloister_1;
  chap_2.cloister = tuille_cloister_2;
  chap_1.voisin = 0;
  chap_2.voisin = 0;
  
  struct abbaye * transition_1 = (struct abbaye * )llm_1->data;
  copieAbbaye(transition_1,&chap_1);
  struct abbaye * transition_2 = (struct abbaye * )llm_2->data;
  copieAbbaye(transition_2,&chap_2);

  lnk_add2(test_board.abbayes,llm_1);
  lnk_add2(test_board.abbayes,llm_2);

  test_board.board[10][10] = tuille_cloister_1;
  test_board.board[10][12] = tuille_cloister_2;

  struct position pos_1;
  struct position pos_2;
  pos_1.x = 10;
  pos_1.y = 10;
  pos_2.x = 10;
  pos_2.y = 12;

  AddOneVoisin(&test_board,pos_1);
  assert(transition_1->voisin == 1);
  assert(transition_2->voisin == 0);
  AddOneVoisin(&test_board,pos_2);
  assert(transition_1->voisin == 1);
  assert(transition_2->voisin == 1);

  printf("TEST_ADD_ONE_VOISIN\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}


/** 
Test de la fonction updateCloister
*/

void test_updateCloister(){
  //init phase//
  struct boardgame test_board;
  initialisation_board(&test_board);

  struct tuille tuille_cloister_1 = genere_tuille(5);
  struct tuille tuille_cloister_2 = genere_tuille(5);
  struct tuille tuille_cloister_3 = genere_tuille(5);

  tuille_cloister_1.position[0] = 10;
  tuille_cloister_1.position[1] = 10;
  tuille_cloister_1.pion[0][1] = 1;
  tuille_cloister_2.position[0] = 9;
  tuille_cloister_2.position[1] = 11;
  tuille_cloister_2.pion[0][0] = 2;
  tuille_cloister_3.position[0] = 8;
  tuille_cloister_3.position[1] = 13;
  tuille_cloister_3.pion[0][1] = 2;

  struct tuille tutuille_1 = genere_tuille(66);
  tutuille_1.position[0] = 10;
  tutuille_1.position[1] = 11;
  tutuille_1.pion[0][1] = 2;

  struct tuille tutuille_2 = genere_tuille(66);
  tutuille_2.position[0] = 9;
  tutuille_2.position[1] = 10;

  //without tuille next to it case//
  test_board.board[10][10] = tuille_cloister_1;
  updateCloister(&test_board,tuille_cloister_1);

  struct lelement * llm_abbaye = test_board.abbayes->head;
  struct abbaye * test_abbaye = (struct abbaye * )llm_abbaye->data;

  assert(llm_abbaye->next == NULL);
  assert(test_abbaye->voisin == 0);
  assert(test_abbaye->possesseur == 1);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_1) == TRUE);

  //adding a not_cloister tuille case//
  test_board.board[10][11] = tutuille_1;
  updateCloister(&test_board,tutuille_1);

  assert(llm_abbaye->next == NULL);
  assert(test_abbaye->voisin == 1);
  assert(test_abbaye->possesseur == 1);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_1) == TRUE);

  //adding a cloister tuille case//
  test_board.board[9][11] = tuille_cloister_2;
  updateCloister(&test_board,tuille_cloister_2);

  assert(llm_abbaye->next->next == NULL);
  assert(test_abbaye->voisin == 2);
  assert(test_abbaye->possesseur == 1);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_1) == TRUE);

  test_abbaye = (struct abbaye * )llm_abbaye->next->data;

  assert(test_abbaye->voisin == 2);
  assert(test_abbaye->possesseur == NONE);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_2) == TRUE);

  //adding a cloister far case//
  test_board.board[8][13] = tuille_cloister_3;
  updateCloister(&test_board,tuille_cloister_3);
  
  test_abbaye = (struct abbaye * )llm_abbaye->data;

  assert(llm_abbaye->next->next->next == NULL);
  assert(test_abbaye->voisin == 2);
  assert(test_abbaye->possesseur == 1);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_1) == TRUE);

  test_abbaye = (struct abbaye * )llm_abbaye->next->data;

  assert(test_abbaye->voisin == 2);
  assert(test_abbaye->possesseur == NONE);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_2) == TRUE);

  test_abbaye = (struct abbaye * )llm_abbaye->next->next->data;
  
  assert(test_abbaye->voisin == 0);
  assert(test_abbaye->possesseur == 2);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_3) == TRUE);

  //adding a not_cloister far case//
  test_board.board[9][10] = tutuille_2;
  updateCloister(&test_board,tutuille_2);
  
  test_abbaye = (struct abbaye * )llm_abbaye->data;

  assert(llm_abbaye->next->next->next == NULL);
  assert(test_abbaye->voisin == 3);
  assert(test_abbaye->possesseur == 1);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_1) == TRUE);

  test_abbaye = (struct abbaye * )llm_abbaye->next->data;

  assert(test_abbaye->voisin == 3);
  assert(test_abbaye->possesseur == NONE);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_2) == TRUE);

  test_abbaye = (struct abbaye * )llm_abbaye->next->next->data;
  
  assert(test_abbaye->voisin == 0);
  assert(test_abbaye->possesseur == 2);
  assert(same_card(&test_abbaye->cloister,&tuille_cloister_3) == TRUE);


  printf("TEST_UPDATE_CLOISTER\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}


//////////////////////////////////////////////

/////////////////MAIN FUNCTION////////////////

int main(){
  test_NumberVoisin();
  test_WhereAbbaye();
  test_AddOneVoisin();
  test_updateCloister();
  return 0;
}

//////////////////////////////////////////////
