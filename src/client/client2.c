#include <stdio.h>
#include <stdlib.h>
#include "carcassonne_interface.h"

char const * get_player_name()
{
  char const * name = "toto";
  return name;
}

struct move play(enum card_id card,struct move const previous_moves[],size_t n_moves);



void initialize(unsigned int id,unsigned int n_players){
    printf("l'identifiant du joueur est : %d \n",id);
    printf("Il y a % joueurs \n",n_players);
}


void finalize();

int main()
{
  char const * name = get_player_name();
  printf("%s\n", name);
  return 0;
}
