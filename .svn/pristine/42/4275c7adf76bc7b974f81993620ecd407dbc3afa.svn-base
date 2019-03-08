#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <time.h>
#include "carcassonne_interface.h" 
#include "../structure/carte.h"
#include "../updateFunctions/updateRoad.h"
#include "../updateFunctions/updateCloister.h"
#include "../updateFunctions/updateTown.h"
#include "../structure/Free.h"

#ifndef CARD_MAX
#define CARD_MAX 72
#endif
#ifndef PLAYER_MAX
#define PLAYER_MAX 3
#endif

void debug_coup(struct move m,struct tuille t);
void aff_tuile(struct tuille t);

struct player {
  void * PLAYER;
  char const* name;
  unsigned int num;
  unsigned int point;
  void (* initialize)(unsigned int,unsigned int);
  struct move (* play)(enum card_id,struct move const[],size_t);
  void (* finalize)(void);
};

int find_id(struct tuille tutuille){
  return tutuille.id;
}

struct tuille draw_card(struct tuille deck[],int play_number)
{
  return deck[play_number];
}


int test_coup(struct tuille tuile, struct boardgame * board)
{
  //aff_tuile(tuile);
  int x = tuile.position[0];
  int y = tuile.position[1];
  if(x == NONE || y == NONE){
    return FALSE;
  }
  int dir_tuile = tuile.dir;
  int dir_N = board->board[x-1][y].dir;
  int dir_S = board->board[x+1][y].dir;
  int dir_E = board->board[x][y+1].dir;
  int dir_W = board->board[x][y-1].dir;
  struct tuille tuile_vide;
  tuile_vide = gen_tuile_vide();
  //aff_tuile(tuile_vide);
  //aff_tuile(board.board[x][y]);
  if (same_card(&(board->board[x][y]), &tuile_vide) == FALSE){
    printf("deja prit\n");
    return FALSE;
  }
  if(coincide(tuile.type[(0-dir_tuile+4)%4],(board->board[x-1][y]).type[(2-dir_N+4)%4]) == FALSE){
    printf("bla : %d et vav : %d\n",(0-dir_tuile+4)%4, (2-dir_N+4)%4);
    printf("en haut\n");
    return FALSE;
  }
  if(coincide(tuile.type[(1-dir_tuile+4)%4],(board->board[x][y-1]).type[(3-dir_W+4)%4]) == FALSE){
    printf("a gauche\n");
    return FALSE;
  }
  if(coincide(tuile.type[(2-dir_tuile+4)%4],(board->board[x+1][y]).type[(0-dir_S+4)%4]) == FALSE){
    printf("en bas\n");
    return FALSE;
  }
  if(coincide(tuile.type[(3-dir_tuile+4)%4],(board->board[x][y+1]).type[(1-dir_E+4)%4]) == FALSE){
    printf("a droite\n");
    return FALSE;
  }
  //printf(" passe\n");
  return TRUE;
}



void init_moves(struct move moves[]){
  for(int i = 0; i<CARD_MAX;i++){
    moves[i].check = FAILED;
    moves[i].player = NONE;
    moves[i].card = LAST_CARD;
    moves[i].onto.x = NONE;
    moves[i].onto.y = NONE;
    moves[i].dir = NORTH;
    moves[i].place = NO_MEEPLE;
  }
}

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

void debug_coup(struct move m,struct tuille t){
  printf("\n");
  printf("------------MOVE-----------\n");
  printf("check : %d\n",m.check);
  printf("player : %d\n",m.player);
  printf("card : %d\n",m.card);
  printf("onto : (%d,%d)\n",m.onto.x,m.onto.y);
  printf("dir : %d\n",m.dir);
  printf("place : %d\n",m.place);
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
  
void aff_move(struct move m){
  printf("\n");
  printf("------------MOVE-----------\n");
  printf("check : %d\n",m.check);
  printf("player : %d\n",m.player);
  printf("card : %d\n",m.card);
  printf("onto : (%d,%d)\n",m.onto.x,m.onto.y);
  printf("dir : %d\n",m.dir);
  printf("place : %d\n",m.place);
  printf("----------tuile-------------\n");
}


int main(int argc,char **argv) {
  printf("serveur \n");
  //int seedOfDoom = time(NULL);
  //int seedOfDoom = 1525780561;
  //srand(seedOfDoom);
  //initialisation
  int f = 0;
  int v = 0;
  

  struct boardgame * boboard = (struct boardgame *)malloc(sizeof(struct boardgame));
  initialisation_board(boboard);
  
  UpdateTown(boboard,boboard->board[72][72]);
  UpdateRoad(boboard,boboard->board[72][72]);
  struct player players[PLAYER_MAX];
  int current_player = 0;
  struct move moves[CARD_MAX];
  init_moves(moves);
  char *error;
  if(argc > PLAYER_MAX){
    printf("NUMBER OF PLAYERS NOT ALLOWED !\n"); //NUMBER OF NOT ALLOWED PLAYERS
    return 0;
  }
  if(argc == 1){ 
    printf("NO PLAYER DETECTED !\n"); //NUMBER OF NOT ALLOWED PLAYERS
    return 0;
  }

  for(int i=0;i<argc-1;i++) {
    char const* (*get_player_name)(void);
    players[i].num = i;
    players[i].point = 0;
    players[i].PLAYER = dlopen(argv[i+1],RTLD_LAZY);
    if(!players[i].PLAYER){
      fputs(dlerror(),stderr);
      exit(1);
    }
    
    get_player_name = dlsym(players[i].PLAYER,"get_player_name");
    if( (error = dlerror()) != NULL){
      fputs(error,stderr);
      exit(1);
    }
    players[i].name = get_player_name();

    players[i].initialize = dlsym(players[i].PLAYER, "initialize");
    if( (error = dlerror()) != NULL){
      fputs(error,stderr);
      exit(1);
    }

    players[i].play = dlsym(players[i].PLAYER, "play");
    if( (error = dlerror()) != NULL){
      fputs(error,stderr);
      exit(1);
    }

    players[i].finalize = dlsym(players[i].PLAYER,"finalize");
    if( (error = dlerror()) != NULL){
      fputs(error,stderr);
      exit(1);
    }
    players[i].initialize(argc-1,PLAYER_MAX);
  }
  //printf("sortie for\n");
  struct move m;
  struct tuille draw_tutuille;
  int c;
  int play_number = 0;

  
  struct tuille deck[CARD_MAX];
  creer_deck(deck);
  current_player = 0;
  while(play_number < CARD_MAX){
    draw_tutuille = draw_card(deck,play_number);
    c = find_id(draw_tutuille);
    m = players[current_player].play(c,moves,play_number);
    draw_tutuille = identifier(m); 
    if(test_coup(draw_tutuille,boboard) == FALSE){
      m.check = FAILED;
      f++;
    }
    else{
      m.check = VALID;
      boboard->board[m.onto.x][m.onto.y] = draw_tutuille;
      UpdateRoad(boboard,draw_tutuille);
      UpdateTown(boboard,draw_tutuille);
      updateCloister(boboard,draw_tutuille);
      v++;
    }
    moves[play_number] = m;
    current_player = (current_player + 1 )%(argc -1);
    play_number++;
  }
  
  printf("sortie de while\n");
  for(int i=0;i<argc-1;i++){
    players[i].finalize();
    dlclose(players[i].PLAYER);
  }

  printf("||||||||||||||||||||||||||||||||||||||||||||\n");
  printf("turn : %d\n",play_number);
  printf("failed : %d\n",f);
  printf("valid : %d\n",v);
  //printf("seedOfDoom : %d\n",seedOfDoom);
  
  FreeBordgame(boboard);

  return 0;
}

