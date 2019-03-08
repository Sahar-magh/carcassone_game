#include <stdlib.h>
#include <stdio.h>

#include "carte.h"
#include "link.h"



/** \brief Crée une tuile
* \param id : indice de la tuile à générer
* \return une struct tuille initialisée
* La numerotation des tuiles correspond à celle des regles du jeu qui sont fournit dans le pdf.
*/
struct tuille genere_tuille(int id){
  struct tuille tutuille;
  if(id < 2){
    int tab[4][3] = {{0,0,0},{0,0,0},{0,2,0},{0,0,0}};//N W S E
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 3;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 0;
  }
  else if (id < 6) {
    int tab[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 3;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 1;
  }
  else if (id < 7) {
    int tab[4][3] = {{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 1;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 2;
  }
  else if (id < 11) {
    int tab[4][3] = {{0,2,0},{0,0,0},{0,2,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 2;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 3;
  }
  else if (id < 16) {
    int tab[4][3] = {{1,1,1},{0,0,0},{0,0,0},{0,0,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 0;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 4;
  }
  else if (id < 18) {
    int tab[4][3] = {{0,0,0},{1,1,1},{0,0,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 1;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 5;
  }
  else if (id < 19) {
    int tab[4][3] = {{1,1,1},{0,0,0},{1,1,1},{0,0,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 6;
  }
  else if (id < 22) {
    int tab[4][3] = {{0,0,0},{1,1,1},{0,0,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 0;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 7;
  }
  else if (id < 24) {
    int tab[4][3] = {{0,0,0},{0,0,0},{1,1,1},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 0;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 8;
  }
  else if (id < 27) {
    int tab[4][3] = {{1,1,1},{0,0,0},{0,2,0},{0,2,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 2;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 9;
  }
  else if (id < 30) {
    int tab[4][3] = {{0,2,0},{0,2,0},{0,0,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 2;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 10;
  }
  else if (id < 33) {
    int tab[4][3] = {{0,2,0},{0,2,0},{0,2,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 0;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 11;
  }
  else if (id < 35) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{0,0,0}}; 
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 1;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 12;
  }
  else if (id < 38) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{0,0,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 13;
  }
  else if (id < 40) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{0,2,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 1;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 14;
  }
  else if (id < 43) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{0,2,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 15;
  }
  else if (id < 44) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 1;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 16;
  }
  else if (id < 47) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 17;
  }
  else if (id < 49) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 1;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 18;
  }
  else if (id < 50) {
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{1,1,1}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 1;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 19;
  }
  else if (id < 58) {
    int tab[4][3] = {{0,2,0},{0,0,0},{0,2,0},{0,0,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 2;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 20;
  }
  else if (id < 67) {
    int tab[4][3] = {{0,0,0},{0,2,0},{0,2,0},{0,0,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 2;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 21;
  }
  else if (id < 71) {
    int tab[4][3] = {{0,0,0},{0,2,0},{0,2,0},{0,2,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 0;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 22;
  }
  else if (id < 72){
    int tab[4][3] = {{0,2,0},{0,2,0},{0,2,0},{0,2,0}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = 0;
    tutuille.shield = 0;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 23;
  }
  else{
    int tab[4][3] = {{NONE,NONE,NONE},{NONE,NONE,NONE},{NONE,NONE,NONE},{NONE,NONE,NONE}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = NONE;
    tutuille.shield = NONE;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = 24;
  }
  return tutuille;
}


/** \brief 
* \param id : un move
* \return une struct tuille 
*/

struct tuille identifier(struct move m)
{
  int id = m.card;
  int meeple = m.place;
  struct tuille tuile;
  if (id == CARD_MONASTERY_ROAD){
    int tab[4][3] = {{0,0,0},{0,0,0},{0,2,0},{0,0,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] =NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 3;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_MONASTERY_ALONE){
    int tab[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 3;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }  
  else if (id == CARD_CITY_ALL_SIDES){
    int tab[4][3] = {{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 1;
    tuile.shield = 1;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_ROAD_STRAIGHT_CITY){
    int tab[4][3] = {{0,2,0},{0,0,0},{0,2,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_CITY_ONE_SIDE){
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
    tuile.id = m.card;
  }
  else if (id == CARD_CITY_TUNNEL_SHLD){
    int tab[4][3] = {{0,0,0},{1,1,1},{0,0,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 1;
    tuile.shield = 1;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_CITY_TUNNEL){
    int tab[4][3] = {{1,1,1},{0,0,0},{1,1,1},{0,0,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 1;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_PLAIN_TUNNEL){
    int tab[4][3] = {{0,0,0},{1,1,1},{0,0,0},{1,1,1}};
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
    tuile.id = m.card;
  }
  else if (id == CARD_PLAIN_TWO_CITIES){
    int tab[4][3] = {{0,0,0},{0,0,0},{1,1,1},{1,1,1}};
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
    tuile.id = m.card;
  }
  else if (id == CARD_ROAD_TURN_RIGHT_CITY){
    int tab[4][3] = {{1,1,1},{0,0,0},{0,2,0},{0,2,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_ROAD_TURN_LEFT_CITY){
    int tab[4][3] = {{0,2,0},{0,2,0},{0,0,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_JUNCTION_CITY){
    int tab[4][3] = {{0,2,0},{0,2,0},{0,2,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_PLAIN_CITY_SHLD){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{0,0,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 0;
    tuile.shield = 1;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_PLAIN_CITY){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{0,0,0}};
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
    tuile.id = m.card;
  }
  else if (id == CARD_PLAIN_CITY_ROAD_SHLD){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{0,2,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 1;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_PLAIN_CITY_ROAD){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{0,2,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_CITY_THREE_SHLD){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 1;
    tuile.shield = 1;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_CITY_THREE){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,0,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 1;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_CITY_THREE_ROAD_SHLD){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 1;
    tuile.shield = 1;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_CITY_THREE_ROAD){
    int tab[4][3] = {{1,1,1},{1,1,1},{0,2,0},{1,1,1}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 1;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_ROAD_STRAIGHT){
    int tab[4][3] = {{0,2,0},{0,0,0},{0,2,0},{0,0,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_ROAD_TURN){
    int tab[4][3] = {{0,0,0},{0,2,0},{0,2,0},{0,0,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
  }
  else if (id == CARD_JUNCTION_THREE){
    int tab[4][3] = {{0,0,0},{0,2,0},{0,2,0},{0,2,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
 }
  else if (id == CARD_JUNCTION_FOUR){
    int tab[4][3] = {{0,2,0},{0,2,0},{0,2,0},{0,2,0}};
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = tab[i][j];
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = 2;
    tuile.shield = 0;
    tuile.position[0] = m.onto.x;
    tuile.position[1] = m.onto.y;
    tuile.id = m.card;
 }
  else {
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 3; j++){
	tuile.type[i][j] = NONE;
	tuile.pion[i][j] = NONE;
      }
    }
    tuile.dir = m.dir;
    tuile.milieu = NONE;
    tuile.shield = NONE;
    tuile.position[0] = NONE;
    tuile.position[1] = NONE;
    tuile.id = NONE;
  }
  if(meeple == POS_NORTH_EAST){
    tuile.pion[0][0] = m.player;
  }
  else if(meeple == POS_NORTH){
    tuile.pion[0][1] = m.player;
  }
  else if(meeple == POS_NORTH_WEST){
    tuile.pion[0][2] = m.player;
  }
  else if(meeple == POS_WEST_NORTH){
    tuile.pion[1][0] = m.player;
  }
  else if(meeple == POS_WEST){
    tuile.pion[1][1] = m.player;
  }
  else if(meeple == POS_WEST_SOUTH){
    tuile.pion[1][2] = m.player;
  }
  else if(meeple == POS_SOUTH_WEST){
    tuile.pion[2][0] = m.player;
  }
  else if(meeple == POS_SOUTH){
    tuile.pion[2][1] = m.player;
  }
  else if(meeple == POS_SOUTH_EAST){
    tuile.pion[2][2] = m.player;
  }
  else if(meeple == POS_EAST_SOUTH){
    tuile.pion[3][0] = m.player;
  }
  else if(meeple == POS_EAST){
    tuile.pion[3][1] = m.player;
  }
  else if(meeple == POS_EAST_NORTH){
    tuile.pion[3][2] = m.player;
  }		
  return tuile;
}


/** \brief Créer un deck
* \param deck : un tableau de tuile
* \return void
* Remplit le deck de taille CARD_MAX grace à la fonction genere_tuille, puis le melange grace à des permutations entre des indices aléatoire.
*/
void creer_deck(struct tuille deck[]){
  for(int i=0;i<CARD_MAX;i++){
    deck[i] = genere_tuille(i);
  }
  struct tuille tmp;
  int alea;
  for(int i=0;i<CARD_MAX;i++){
    alea = rand()%(CARD_MAX-i) + i;//rand(i,CARDMAX)
    tmp = deck[i];
    deck[i] = deck[alea];
    deck[alea] = tmp;
  }
}


/** \brief La stratégie de l'IA
* \param board : le plateau de jeu
* \param possibility : la liste des coups jouables
* \param len_tab : la taille de board
* \param len_pos : la taille de possibility
* \return la tuile choisit par l'IA
* choisit une tuile à jouer en fonction d'une liste de possibilité, renvoit tuile nul si il ne peut rien jouer : strat actuel  -> random
*/
struct tuille strat(struct tuille board[][CARD_MAX * 2 +1], struct tuille possibility[], int len_tab, int len_pos){
  (void) board;
  (void) len_pos;
  struct tuille tutuille;
  if(len_tab < 1){
    int tab[4][3] = {{NONE,NONE,NONE},{NONE,NONE,NONE},{NONE,NONE,NONE},{NONE,NONE,NONE}};
    for (int i=0;i<4;i++) {
      for (int j=0;j<3;j++) {
	tutuille.type[i][j] = tab[i][j];
	tutuille.pion[i][j] = NONE;
      }
    }
    tutuille.dir = NORTH;
    tutuille.milieu = NONE;
    tutuille.shield = NONE;
    tutuille.position[0] = NONE;
    tutuille.position[1] = NONE;
    tutuille.id = NONE;
    return tutuille;
  }
  else{
    int rand_tuille = rand()%(len_tab);
    return possibility[rand_tuille];
  }
}



/** \brief Est-ce-que 2 cotés coincide ?
* \param type : le bord de la tuile posée
* \param type_test : le bord à comparer
* \return Un booléen
* Si les deux bords coincide ou que bord à comparé est le bord vide alors return true, sinon return false
*/
int coincide(int type[], int type_test[]){
  for(int i=0;i<3;i++){
    if( (type_test[i] != NONE) && (type_test[i] != type[i]))
      return FALSE;
  }
  return TRUE;
}


/** \brief
* \param board :le plateau de jeu 
*\param tutuille : la tuille
*\param test : tuille 
*\param res :tableau de tuilles
*\param begin : int						\
* \return un int
*/

static int is_join(struct tuille board[][CARD_MAX*2+1], struct tuille tutuille,struct tuille test,struct tuille res[],int begin){
  int taille = 0;
  int x = test.position[0];
  int y = test.position[1];
  struct tuille vide = gen_tuile_vide();
  struct tuille copy;
  //on met la tutuille en haut de test
  /////////////////////////////////////////////////////
  if(same_card(&vide,&(board[x-1][y])) == TRUE){
    //orientation NORD
    if( ((same_card(&vide,&(board[x-2][y]))==TRUE)  || coincide(tutuille.type[0],(board[x-2][y]).type[(2 - board[x-2][y].dir + 4)%4  ])) &&
	((same_card(&vide,&(board[x-1][y-1]))==TRUE) || coincide(tutuille.type[1],(board[x-1][y-1]).type[(3 - board[x-1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[2],(board[x][y]).type[(0 - board[x][y].dir + 4)%4]) &&
	((same_card(&vide,&(board[x-1][y+1]))==TRUE) || coincide(tutuille.type[3],(board[x-1][y+1]).type[(1 - board[x-1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = NORTH;
      copy.position[0] = x-1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation WEST
    if( ((same_card(&vide,&(board[x-2][y]))==TRUE)  || coincide(tutuille.type[3],(board[x-2][y]).type[(2 - board[x-2][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x-1][y-1]))==TRUE) || coincide(tutuille.type[0],(board[x-1][y-1]).type[(3 - board[x-1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[1],(board[x][y]).type[(0 - board[x][y].dir + 4)%4]) &&
	((same_card(&vide,&(board[x-1][y+1]))==TRUE) || coincide(tutuille.type[2],(board[x-1][y+1]).type[(1 - board[x-1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = WEST;
      copy.position[0] = x-1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
  //orientation SOUTH
    if( ((same_card(&vide,&(board[x-2][y]))==TRUE)  || coincide(tutuille.type[2],(board[x-2][y]).type[(2 - board[x-2][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x-1][y-1]))==TRUE) || coincide(tutuille.type[3],(board[x-1][y-1]).type[(3 - board[x-1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[0],(board[x][y]).type[(0 - board[x][y].dir + 4)%4]) &&
	((same_card(&vide,&(board[x-1][y+1]))==TRUE) || coincide(tutuille.type[1],(board[x-1][y+1]).type[(1 - board[x-1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = SOUTH;
      copy.position[0] = x-1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation EAST
    if( ((same_card(&vide,&(board[x-2][y]))==TRUE)  || coincide(tutuille.type[1],(board[x-2][y]).type[(2 - board[x-2][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x-1][y-1]))==TRUE) || coincide(tutuille.type[2],(board[x-1][y-1]).type[(3 - board[x-1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[3],(board[x][y]).type[(0 - board[x][y].dir + 4)%4]) &&
	((same_card(&vide,&(board[x-1][y+1]))==TRUE) || coincide(tutuille.type[0],(board[x-1][y+1]).type[(1 - board[x-1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = EAST;
      copy.position[0] = x-1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
  }
  ///////////////////////////////
  //on met la tutuille à gauche de test
  /////////////////////////////////////////////////////
  if(same_card(&vide,&(board[x][y-1])) == TRUE ){
    //orientation NORD
    if( ((same_card(&vide,&(board[x-1][y-1]))==TRUE)  || coincide(tutuille.type[0],(board[x-1][y-1]).type[(2 - board[x-1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y-2]))==TRUE) || coincide(tutuille.type[1],(board[x][y-2]).type[(3 - board[x][y-2].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[2],(board[x+1][y-1]).type[(0 - board[x+1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[3],(board[x][y]).type[(1 - board[x][y].dir + 4)%4])){
      copy = tutuille;
      copy.dir = NORTH;
      copy.position[0] = x;
      copy.position[1] = y-1;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation WEST
    if( ((same_card(&vide,&(board[x-1][y-1]))==TRUE) || coincide(tutuille.type[3],(board[x-1][y-1]).type[(2 - board[x-1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y-2]))==TRUE) || coincide(tutuille.type[0],(board[x][y-2]).type[(3 - board[x][y-2].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[1],(board[x+1][y-1]).type[(0 - board[x+1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[2],(board[x][y]).type[(1 - board[x][y].dir + 4)%4])){
      copy = tutuille;
      copy.dir = WEST;
      copy.position[0] = x;
      copy.position[1] = y-1;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation SOUTH
    if( ((same_card(&vide,&(board[x-1][y-1]))==TRUE) || coincide(tutuille.type[2],(board[x-1][y-1]).type[(2 - board[x-1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y-2]))==TRUE) || coincide(tutuille.type[3],(board[x][y-2]).type[(3 - board[x][y-2].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[0],(board[x+1][y-1]).type[(0 - board[x+1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[1],(board[x][y]).type[(1 - board[x][y].dir + 4)%4])){
      copy = tutuille;
      copy.dir = SOUTH;
      copy.position[0] = x;
      copy.position[1] = y-1;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation EAST
    if( ((same_card(&vide,&(board[x-1][y-1]))==TRUE) ||  coincide(tutuille.type[1],(board[x-1][y-1]).type[(2 - board[x-1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y-2]))==TRUE) || coincide(tutuille.type[2],(board[x][y-2]).type[(3 - board[x][y-2].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[3],(board[x+1][y-1]).type[(0 - board[x+1][y-1].dir + 4)%4])) &&
	coincide(tutuille.type[0],(board[x][y]).type[(1 - board[x][y].dir + 4)%4])){
      copy = tutuille;
      copy.dir = EAST;
      copy.position[0] = x;
      copy.position[1] = y-1;
      res[taille+begin] = copy;
      taille++;
    }
  }
  ///////////////////////////////
  //on met la tutuille en bas de test
  /////////////////////////////////////////////////////
  if(same_card(&vide,&(board[x+1][y])) == TRUE){
    //orientation NORD
    if( (coincide(tutuille.type[0],(board[x][y]).type[(2 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[1],(board[x+1][y-1]).type[(3 - board[x+1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+2][y]))==TRUE) || coincide(tutuille.type[2],(board[x+2][y]).type[(0 - board[x+2][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[3],(board[x+1][y+1]).type[(1 - board[x+1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = NORTH;
      copy.position[0] = x+1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation WEST
    if( (coincide(tutuille.type[3],(board[x][y]).type[(2 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[0],(board[x+1][y-1]).type[(3 - board[x+1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+2][y]))==TRUE) || coincide(tutuille.type[1],(board[x+2][y]).type[(0 - board[x+2][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[2],(board[x+1][y+1]).type[(1 - board[x+1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = WEST;
      copy.position[0] = x+1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation SOUTH
    if( (coincide(tutuille.type[2],(board[x][y]).type[(2 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[3],(board[x+1][y-1]).type[(3 - board[x+1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+2][y]))==TRUE) || coincide(tutuille.type[0],(board[x+2][y]).type[(0 - board[x+2][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[1],(board[x+1][y+1]).type[(1 - board[x+1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = SOUTH;
      copy.position[0] = x+1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation EAST
    if( (coincide(tutuille.type[1],(board[x][y]).type[(2 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y-1]))==TRUE) || coincide(tutuille.type[2],(board[x+1][y-1]).type[(3 - board[x+1][y-1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+2][y]))==TRUE) || coincide(tutuille.type[3],(board[x+2][y]).type[(0 - board[x+2][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[0],(board[x+1][y+1]).type[(1 - board[x+1][y+1].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = EAST;
      copy.position[0] = x+1;
      copy.position[1] = y;
      res[taille+begin] = copy;
      taille++;
    }
  }
  ///////////////////////////////
  //on met la tutuille à droite de test
  /////////////////////////////////////////////////////
  if(same_card(&vide,&(board[x][y+1])) == TRUE){
    //orientation NORD
    if( (same_card(&vide,&(board[x-1][y+1])) || coincide(tutuille.type[0],(board[x-1][y+1]).type[(2 - board[x-1][y+1].dir + 4)%4])) &&
	(coincide(tutuille.type[1],(board[x][y]).type[(3 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[2],(board[x+1][y+1]).type[(0 - board[x+1][y+1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y+2]))==TRUE) || coincide(tutuille.type[3],(board[x][y+2]).type[(1 - board[x][y+2].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = NORTH;
      copy.position[0] = x;
      copy.position[1] = y+1;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation WEST
    if( (same_card(&vide,&(board[x-1][y+1])) || coincide(tutuille.type[3],(board[x-1][y+1]).type[(2 - board[x-1][y+1].dir + 4)%4])) &&
	(coincide(tutuille.type[0],(board[x][y]).type[(3 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[1],(board[x+1][y+1]).type[(0 - board[x+1][y+1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y+2]))==TRUE) || coincide(tutuille.type[2],(board[x][y+2]).type[(1 - board[x][y+2].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = WEST;
      copy.position[0] = x;
      copy.position[1] = y+1;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation SOUTH
    if( (same_card(&vide,&(board[x-1][y+1])) || coincide(tutuille.type[2],(board[x-1][y+1]).type[(2 - board[x-1][y+1].dir + 4)%4])) &&
	(coincide(tutuille.type[3],(board[x][y]).type[(3 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[0],(board[x+1][y+1]).type[(0 - board[x+1][y+1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y+2]))==TRUE) || coincide(tutuille.type[1],(board[x][y+2]).type[(1 - board[x][y+2].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = SOUTH;
      copy.position[0] = x;
      copy.position[1] = y+1;
      res[taille+begin] = copy;
      taille++;
    }
    //orientation EAST
    if( (same_card(&vide,&(board[x-1][y+1])) || coincide(tutuille.type[1],(board[x-1][y+1]).type[(2 - board[x-1][y+1].dir + 4)%4])) &&
	(coincide(tutuille.type[2],(board[x][y]).type[(3 - board[x][y].dir + 4)%4])) &&
	((same_card(&vide,&(board[x+1][y+1]))==TRUE) || coincide(tutuille.type[3],(board[x+1][y+1]).type[(0 - board[x+1][y+1].dir + 4)%4])) &&
	((same_card(&vide,&(board[x][y+2]))==TRUE) || coincide(tutuille.type[0],(board[x][y+2]).type[(1 - board[x][y+2].dir + 4)%4]))){
      copy = tutuille;
      copy.dir = EAST;
      copy.position[0] = x;
      copy.position[1] = y+1;
      res[taille+begin] = copy;
      taille++;
    }
  }
  return taille;
}




/** \brief Combien il y a de coté libre ?
* \param board : le plateau de jeux
* \param x : l'abscisse de la tuile à tester
* \param y : l'ordonnée de la tuile à tester
* \return le nombre de coté libre
* Renvoit combien il y a de tuile vide autour de la tuile en position (x,y) sur le plateau.
*/
static int is_free(struct tuille board[][CARD_MAX*2+1],int x,int y){
  int booleen = 0;
  if( (board[x+1][y]).milieu == NONE )
    booleen++;
  if(  (board[x-1][y]).milieu == NONE )
    booleen++;
  if(  (board[x][y+1]).milieu == NONE )
    booleen++;
  if(  (board[x][y-1]).milieu == NONE )
    booleen++;
  return booleen;
}


/** \brief Quel sont les possibilité de jeux à partir de tutuille
* \param board : le plateau de jeux
* \param res : la liste des coup jouables
* \param tutuile : la tuile que l'on a pioché
* \param len : la taille de board
* \return la taille de res et la listes des coup jouable à partir de tutuile dans res
* Regarde sur toutes les zones disponible toutes les position et toutes les orientation possibles que l'on peut jouer à partir de tutuile et les renvoit dans une liste.
*/
int display_possibility(struct tuille board[][CARD_MAX*2+1], struct tuille res[],  struct tuille tutuille){//int = la taille de res
  int taille = 0;
  int len = 2*CARD_MAX+1;
  struct tuille vide = gen_tuile_vide();
  for(int i=0;i<len;i++){
    for(int j=0;j<len;j++){
      if( same_card(&vide,&(board[i][j])) == FALSE && is_free(board,i,j) > 0){
	taille = taille + is_join(board,tutuille,board[i][j],res,taille);
      }
    }
  }
  return taille;
}

/** \brief generer une tuile vide 
* \param id : void
* \return une struct tuille vide
*/
struct tuille gen_tuile_vide(){
  struct tuille tuile_vide;
  for(int i =0;i<4;i++){
    for(int j=0;j<3;j++){
      tuile_vide.type[i][j]=NONE;
      tuile_vide.pion[i][j]=NONE;
    }
  }
  tuile_vide.id =NONE;
  tuile_vide.dir = NORTH;
  tuile_vide.position[0] = NONE;
  tuile_vide.position[1] = NONE;
  tuile_vide.shield =NONE;
  tuile_vide.milieu=NONE;
  return tuile_vide;
}
/** \brief initialiser le plateau de jeu
* \param b : boardgame : plateau de jeu 
* \return une struct tuille initialisée
*/
void initialisation_board(struct boardgame * b){
  for(int i=0;i<2*CARD_MAX+1;i++){
    for(int j=0;j<2*CARD_MAX+1;j++){
      b->board[i][j] = gen_tuile_vide();
    }
  }
  b->fields = lnk_empty();
  b->roads = lnk_empty();
  b->cities = lnk_empty();
  creer_deck(b->deck);
  b->abbayes = lnk_empty();
  b->len = 0;
  b->board[72][72] = genere_tuille(7);
  b->board[72][72].position[0] = 72;
  b->board[72][72].position[1] = 72;
  for(int i=0;i<PLAYER_MAX;i++){
    b->points[i] = 0;
  }
}

/** \brief tester si c'est la meme tuille 
* \param tuile1 : un pointeur vers tuille 1
* \param tuile2 : un pointeur vers tuille 2
* \return un booleen
*/
int same_card(struct tuille *tuile1, struct tuille *tuile2)
{
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++){
      if (tuile1->type[i][j] != tuile2->type[i][j])
	return FALSE;
      if (tuile1->pion[i][j] != tuile2->pion[i][j])
	return FALSE;
    }
  }
  if (tuile1->dir != tuile2->dir)
    return FALSE;
  if (tuile1->milieu != tuile2->milieu)
    return FALSE;
  if (tuile1->shield != tuile2->shield)
    return FALSE;
  if (tuile1->position[0] != tuile2->position[0] || tuile1->position[1] != tuile2->position[1])
    return FALSE;
  return TRUE;
}
	  


