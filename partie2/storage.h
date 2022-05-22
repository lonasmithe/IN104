#ifndef STORAGE_H
#define STORAGE_H

#include <stdio.h>
#include <stdlib.h>

int*** storage;//renommer draughtboard
int n_position;
int curseur;
int here;
void create_storage();
void free_storage();
void fill_storage(int** T);
int find_position(int** T);


#endif /* STORAGE_H */
