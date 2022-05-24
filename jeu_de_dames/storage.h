#ifndef STORAGE_H
#define STORAGE_H

#include <stdio.h>
#include <stdlib.h>

int*** storage;//renommer draughtboard
int** storage2;
int n_position;
int* T_curseur;
int here;
void create_storage();
void free_storage();
void fill_storage(int** T);
int find_position(int** T);
void fill_storage2();
int find_position2();
int total_position();


#endif /* STORAGE_H */
