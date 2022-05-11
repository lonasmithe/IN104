#ifndef AGENT_H
#define AGENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int taille_tableau;
int nombre_actions;
int** Q;

int alloc_Q();
void free_Q();
void act_random(int e);

#endif /* AGENT_H */
