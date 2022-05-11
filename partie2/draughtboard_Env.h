#ifndef DRAUGHTBOARD_ENV_H
#define DRAUGHTBOARD_ENV_H

#include <stdio.h>
#include <stdlib.h>

int** maze;//renommer draughtboard
int** visited;
int rows;
int cols;//possibilité d'en mettre que 5 pour gagner en espace de stockage mais moins instinctif
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

/*enum terrain{
    unknown,
    wall,
    known,
    goal,
    crumb
};*/

enum action{
     
     left,
     right,
     eat_left,
     eat_right,
     id
 
};
 
typedef enum action action ;

struct envOutput{ //Hyper utile, c'est ce qu'on envoie au fichier afin de 
  int new_col; //donner la nouvelle case
  int new_row;//idem
  float reward;// la récompense
  int done;//Si c'est terminal
  int combo; // Si d'autres mouvement sont possibles
  enum action choice;
int end;// si le joueur s'est déplacé
};

typedef struct envOutput envOutput;

void alloc_draughtboard();

void free_draughtboard();

void draughtboard_make();

void draughtboard_render(); 

void draughtboard_reset();

envOutput draughtboard_step(action a, int col_position, int row_position, int team); 

#endif /* DRAUGHTBOARD_ENV_H*/
