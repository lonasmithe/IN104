#include "draughtboard_Env.h"
#include "agent.h"
#include "storage.h"

void create_storage(){

n_position=10000;
curseur=0;

	storage = malloc(n_position * sizeof(int*));
     for(int i=0; i<n_position; i++) {
         storage[i] = malloc(rows * sizeof(int*));
         for(int j=0; j<rows; j++) {
         storage[i][j] = malloc(cols * sizeof(int*));
    	 }
     }

}

void free_storage(){

printf("Yaaaaaacabaaa\n");
for(int i=0;i<n_position;i++){
for(int j=0;j<rows;j++){

free(storage[i][j]);
}
free(storage[i]);
}
free(storage);
printf("Succès\n");
}

void fill_storage(int** T){

for(int i=0; i<rows; i++) {
         for(int j=0; j<cols; j++) {
         storage[curseur][i][j]=T[i][j];
    	 }
     }
     curseur++;

}

int find_position(int**T){


for(int n=0;n<curseur;n++){
	here=1;
	for(int i=0; i<rows; i++) {
         for(int j=0; j<cols; j++) {
         if(storage[n][i][j]!=T[i][j]){
         	here=0;
break;
         }
    	 }if(here==0){
    	 	break;
    	 }

     }
     if(here==1){
     	return n;
     }
}
return -1;
}