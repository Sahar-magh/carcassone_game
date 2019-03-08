#ifndef LINK_H
#define LINK_H


/** \brief une liste doublement chainé */
struct link {// a discuter: est ce qu'on rajoute un pointeur vers la queue de la chaine
  struct lelement * head; /**< le debut de la liste */
  struct lelement * tail;/**<la fin de la liste */
  int taille; /**< la taille de la liste */
};
 
/** \brief un element de la liste */
struct lelement {
  void * data; /**< la donné de l'element */
  struct lelement * next; /**< l'element suivant */
  struct lelement * previous; /**< l'element precedent */
};

//Initialise un link vide//
struct link * lnk_empty();

//Initialise un lelement vide//
struct lelement * llm_empty();

//Libère l'espace alloué au link lnk//
void lnk_free(struct link * lnk);

//Libère l'espace alloué au lelement llm//
void llm_free(struct lelement * llm);

//Fusionne deux links//
void lnk_merge(struct link * lnk1, struct link * lnk2);

//Ajoute un élement dans le link lnk//
void lnk_add2(struct link * lnk, struct lelement * new_llm);


#endif
