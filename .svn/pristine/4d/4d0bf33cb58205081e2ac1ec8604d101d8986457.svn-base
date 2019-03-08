#ifndef CARTE_H
#define CARTE_H
#include "../client/carcassonne_interface.h"
#include "link.h"
#define NONE -1000
#ifndef CARD_MAX
#define CARD_MAX 72
#endif
#define FALSE 0
#define TRUE 1
#ifndef PLAYER_MAX
#define PLAYER_MAX 5
#endif

///////////////////// Structures //////////////////////////////


/** \brief structure triplet utile pour struct road */
struct triplet{
  int x;
  int y;
  int z;
};


/** \brief  l'implementation d'une tuile du jeu */
struct tuille {
  int type[4][3]; /**< le type de la bordure de la tuile -> (North West East South) */
  enum direction dir; /**< l'orientation de la tuile */
  int milieu; /**< Le type de ce qu'il y a au milieu de la tuille */
  int shield; /**< Est ce qu'il y a un bouclier ?*/
  int position[2]; /**< les coordonnées de la tuile sur le board */
  int pion[4][3]; /**< Ou est ce qu'il y a un pion ? */
  int id; /** <l'id de la tuille */
};



/** \brief la structure correspondant aux champs */
struct field {
  struct link * lst_tutuille; /**< la liste des tuiles qui composent le champ */
  struct link * lst_triplet;/**<la liste des triplets >*/
  int paysans[PLAYER_MAX]; /**< le nombre de pions par joueur dans le champs */
  int len; /**<la taille du champs (en nombre de tuile)*/
  int inTown; /**<booleen : est ce que le field appartient à une ville ? */
};


/** \brief la structure correspondant aux routes */
struct road {
  struct link * lst_tutuille; /**< La listes des tuiles qui composent la route */
  struct link * nys_idea; 
  int voleurs[PLAYER_MAX];/**< Le nombre de pions par joueur sur la route */
  int avencement;/**< L'état de la route (le nombre d'extremités) */
  int len; /**< la taille de la route (en nombre de tuilles) */
};


/** \brief la structure correspondant aux villes */
struct city {
  struct link * lst_tutuille; /**< La liste des tuilles qui composent la ville */
  struct link * lst_champ; /**< La liste des champs autour de la ville */
  struct link * lst_triplet;/**<la liste des triplets*/
  int chevaliers[PLAYER_MAX]; /**< Nombre de pions par joueur dans la ville */
  int border; 
  int len; /**< la taille de la ville (en nombre de tuile) */
  int shield;
};

/** \brief la structure correspondant aux abbayes */
struct abbaye {
  struct tuille cloister;
  int voisin;
  int possesseur;
};


/** \brief : le plateau de jeu (il centralise les informations du jeu) */
struct boardgame {
  //struct player joueurs[PLAYER_MAX]; /**< la liste des joueur */
  struct tuille board[2*CARD_MAX+1][2*CARD_MAX+1]; /**< le plateau du jeux */
  struct link * fields; /**< la liste des champs présents en jeux */
  struct link * roads; /**< la liste des routes presentes en jeux */
  struct link * cities; /**< la liste des villes presentes en jeux */
  struct tuille deck[CARD_MAX]; /**< le deck du jeu */
  struct link * abbayes; /**< la listes des abbayes presentes en jeux */
  int len; /**< la carte au dessus du deck */
  int points[PLAYER_MAX];
};


///////////////////FONCTIONS////////////////////////////////

//Crée une tuile à partir d'un entier choisi//
struct tuille genere_tuille(int id);

//Permet de renvoyer une tuile à partir d'un move donné//
struct tuille identifier(struct move);

//Permet de créer un deck de tuiles//
void creer_deck(struct tuille deck[]);

//Implémente une statégie aléatoire//
struct tuille strat(struct tuille board[][CARD_MAX * 2 + 1], struct tuille possibility[], int len_tab, int len_pos);

//Renvoie TRUE si les types coïncident, FALSE sinon//
int coincide(int type[], int type_test[]);

//Permet de détecter les coups possibles à partir d'une tuile donnée//
int display_possibility(struct tuille board[][CARD_MAX * 2 +1], struct tuille  res[], struct tuille tutuille);

//Génère une tuile vide//
struct tuille gen_tuile_vide();

//Initialise le plateau de jeu//
void initialisation_board(struct boardgame * board);

//Renvoie TRUE si les deux tuiles sonts identiques, FALSE sinon//
int same_card(struct tuille *tuile1, struct tuille *tuile2);


#endif
