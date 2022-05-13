#ifndef AGENT_H
#define AGENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int taille_tableau;
int nombre_actions;
struct envOutput tirage;
enum action choix;
int** Q;
int etat;
int etat_p;
float epsilon;
float alpha;
float gammma;
int action_rand,col_rand,row_rand;
int n_boucle;
int n_iter;

int alloc_Q();
void free_Q();
float max_a_Q(int e);
void act_random(int e);
void double_dumb();
void actualise_etat();
void training();
void greedy_method();

#endif /* AGENT_H */
