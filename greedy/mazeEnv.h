#ifndef MAZEENV_H
#define MAZEENV_H

#include <stdio.h>
#include <stdlib.h>

char** maze;
int** visited;
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

enum terrain{
    unknown,
    wall,
    known,
    goal,
    crumb
};

enum action{
     up,
     down,
     left,
     right,
     number_actions 
};
 
typedef enum action action ;

struct envOutput{ //Hyper utile, c'est ce qu'on envoie au fichier afin de 
  int new_col; //donner la nouvelle case
  int new_row;//idem
  float reward;// la récompense
  int done;//Si c'est terminal

};

typedef struct envOutput envOutput;

void alloc_maze();

void maze_make(char* );

void maze_render(); 

void maze_reset();

envOutput maze_step(action a); 

action env_action_sample();

void alloc_visited();

void init_visited();

#endif /* MAZEENV_H */
