#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../structure/carte.h"
#include "../serveur/carcassonne_interface.h"


void aff_tuile(struct tuille t){
  for(int i = 0;i<4;i++){
    for(int j=0;j<3;j++){
      printf( "type[%d][%d] = %d\n",i,j,t.type[i][j]);
      printf( "pion[%d][%d] = %d\n",i,j,t.pion[i][j]);
    }
  }
  printf("direction = %d\n",t.dir);
  printf("milieu = %d\n",t.milieu);
  printf("shield = %d\n",t.shield);
  printf("position = [%d,%d]\n", t.position[0],t.position[1]);
}

void test_identifier()
{
  printf("\ttest_identifier : ");
  
  struct move m;
  m.check = VALID;
  m.player = 0;
  m.card = CARD_CITY_ONE_SIDE;
  m.onto.x = 4;
  m.onto.y = 2;
  m.dir = SOUTH;
  m.place = POS_NORTH;

  struct move m2;
  m2.check = VALID;
  m2.player = 0;
  m2.card = CARD_PLAIN_CITY;
  m2.onto.x = 8;
  m2.onto.y = 7;
  m2.dir = WEST;
  m2.place = POS_SOUTH;
  
  struct tuille tuile;
  int tab[4][3] = {{1,1,1},{0,0,0},{0,0,0},{0,0,0}};
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++){
      tuile.type[i][j] = tab[i][j];
      tuile.pion[i][j] = NONE;
    }
  }
  tuile.dir = m.dir;
  tuile.milieu = 0;
  tuile.shield = 0;
  tuile.position[0] = m.onto.x;
  tuile.position[1] = m.onto.y;

  struct tuille tuile2;
  int tab2[4][3] = {{1,1,1},{1,1,1},{0,0,0},{0,0,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile2.type[i][j] = tab2[i][j];
	tuile2.pion[i][j] = NONE;
      }
    }
    tuile2.dir = m2.dir;
    tuile2.milieu = 0;
    tuile2.shield = 0;
    tuile2.position[0] = m2.onto.x;
    tuile2.position[1] = m2.onto.y;

    struct tuille t = identifier(m);
    struct tuille t2 = identifier(m2);
    assert(same_card(&t, &tuile));
    assert(same_card(&t2, &tuile2));

    printf("\tOK\n");
}

void test_




  
 

int main()
{
  test_identifier();
  
  return 0;
}
