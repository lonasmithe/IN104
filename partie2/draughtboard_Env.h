#ifndef DRAUGHTBOARD_ENV_H
#define DRAUGHTBOARD_ENV_H

#include <stdio.h>
#include <stdlib.h>

int** maze;//renommer draughtboard
int* L_1;
int* L_3;
int* attaquable_1;
int* attaquable_3;
int a_1;
int a_3;
int n_1;
int n_3;
int** visited;
int rows;
int cols;//possibilité d'en mettre que 5 pour gagner en espace de stockage mais moins instinctif
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;
int nb_pawn;

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

void draughtboard_render(int** D); 

void draughtboard_reset();

int id_pawn_on_knowncase(int x, int y, int e);

int random_position_with_a_pawn(int e);

void add_attaquable(int x, int y, int e);

void L_render(int e);


envOutput draughtboard_step(action a, int col_position, int row_position, int team); 

#endif /* DRAUGHTBOARD_ENV_H*/
