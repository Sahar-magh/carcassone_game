#include <stdio.h>
#include <stdlib.h>
#include "carcassonne_interface.h"
#include <time.h>
#include "../structure/carte.h"
#include "../updateFunctions/updateRoad.h"
#include "../structure/Free.h"
#include "../updateFunctions/updateCloister.h"
#include "../updateFunctions/updateTown.h"


struct boardgame * boboard;
int nb_player;
int id_player;


char const * get_player_name()
{
  char const * name = "toto";
  return name;
}

void update_board_client(struct move const m[],size_t n_moves){
  int pos_x;
  int pos_y;
  int len = (int)n_moves;//pour enlever les warning
  if(len < nb_player){
    for(int i=0;i<len;i++){
      if(m[i].check == VALID){
	pos_x = m[i].onto.x;
	pos_y = m[i].onto.y;
	boboard->board[pos_x][pos_y] = identifier(m[i]);
	UpdateRoad(boboard,identifier(m[i]));
	updateCloister(boboard,identifier(m[i]));
	UpdateTown(boboard,identifier(m[i]));
      }
    }
  }
  else {
    for(int i = len - nb_player +1; i< len;i++){
      if(m[i].check == VALID){
	pos_x = m[i].onto.x;
	pos_y = m[i].onto.y;
	boboard->board[pos_x][pos_y] = identifier(m[i]);
	UpdateRoad(boboard,identifier(m[i]));
	updateCloister(boboard,identifier(m[i]));
	UpdateTown(boboard,identifier(m[i]));
      }
    }
  }
}


struct move play(enum card_id card, struct move const previous_moves[], size_t n_moves)
{
  update_board_client(previous_moves,n_moves);
  struct move m ={FAILED,0,CARD_MONASTERY_ROAD,{0,0},NORTH,NO_MEEPLE};
  m.card = card;
  struct tuille vide = gen_tuile_vide();
  struct tuille possibility[8*CARD_MAX+8];
  for(int i =0; i<8*CARD_MAX+8;i++){
    possibility[i] = vide;
  }
  int len_possibility = display_possibility(boboard->board,possibility,identifier(m));
  int possibility_meeple[12];
  int len_possibility_meeple = 0;  
  (void)len_possibility_meeple;
  (void)possibility_meeple;
  if(len_possibility > 0){
    int alea = rand()%len_possibility;
    m.check = FAILED;
    m.player = (unsigned int)id_player;
    m.onto.x = possibility[alea].position[0];
    m.onto.y = possibility[alea].position[1];
    m.dir = possibility[alea].dir;
    m.place = rand()%12;
  }
  else {
    m.check = FAILED;
    m.player = (unsigned int)id_player;
    m.onto.x = NONE;
    m.onto.y = NONE;
    m.dir = NORTH;
    m.card = LAST_CARD;
    m.place = NO_MEEPLE;
  }
  return m;
}


void initialize(unsigned int id, unsigned int n_players)
{
  id_player = (int)id;
  nb_player = (int)n_players;
  boboard = (struct boardgame *)malloc(sizeof(struct boardgame));
  initialisation_board(boboard);
  UpdateRoad(boboard,boboard->board[72][72]);
  UpdateTown(boboard,boboard->board[72][72]);
}

void finalize()
{
  FreeBordgame(boboard);
}

