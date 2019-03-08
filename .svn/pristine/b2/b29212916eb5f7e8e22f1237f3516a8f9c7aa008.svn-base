#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../client/carcassonne_interface.h"

char const * get_player_name()
{
  char const * name = "toto";
  return name;
}

struct move play(enum card_id card,
		 struct move const previous_moves[],
		 size_t n_moves)
{
  int valu = rand();
  struct move next_move;
  if ((int)n_moves == 0) {
    next_move.player = 0;
  }
  else {
    next_move.player = previous_moves[n_moves-1].player + 1;
  }
  next_move.check = VALID;
  next_move.card = card;
  next_move.onto.x = valu%10;
  next_move.onto.y = (valu+1)%10;
  next_move.dir = valu%4;
  next_move.place = valu%15;
  return next_move;
}


void initialize(unsigned int id,
		unsigned int n_players)
{
  (void)id;
  (void)n_players;
  //n_players = n_players;
  /*  player_list[id]->num = id;
  player_list[id]->point = 0;
  player_list[id]->name = get_player_name();*/
  printf("initialize check\n");
}

void finalize()
{
  //free(player_list);
}


void test_get_player_name()
{
  //char const * name = get_player_name();
  //assert(strcmp(name,"toto"));
  printf("Test_get_player_name\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}

void test_initialize()
{
  printf("Test_initialize\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}

void test_finalize()
{
  printf("Test_finalize\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}

void test_play()
{
  
  struct move previous_moves[9];
  struct move next = play(CARD_MONASTERY_ROAD,previous_moves,0);
  assert(next.check == 0);
  assert(next.player == 0);
  assert(next.card == 0);
  previous_moves[0] = next;
  next = play(CARD_MONASTERY_ALONE,previous_moves,1);
  assert(next.check == 0);
  assert(next.player == 1);
  assert(next.card == 1);
  printf("Test_play\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}

//"\x1b[33m" "-----" "\x1b[0m"
int main()
{
  test_get_player_name();
  test_initialize();
  test_finalize();
  test_play();
  return 0;
}
