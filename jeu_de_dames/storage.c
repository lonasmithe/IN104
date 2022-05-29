#include "draughtboard_Env.h"
#include "agent.h"
#include "storage.h"

void create_storage(){

n_position=600000;
//curseur=0;

	storage = malloc(n_position * sizeof(int*));
    storage2 = malloc(n_position * sizeof(int*));
    T_curseur = malloc(sizeof(int)*(nb_pawn+1)*(nb_pawn+1));
    for(int k=0;k<nb_pawn*nb_pawn;k++){
        T_curseur[k]=0;
    }
     for(int i=0; i<n_position; i++) {
        storage2[i] = malloc(nb_pawn*2*sizeof(int*));
         storage[i] = malloc(rows * sizeof(int*));
         for(int j=0; j<rows; j++) {
         storage[i][j] = malloc(cols * sizeof(int*));
    	 }
     }


}

void free_storage(){

//printf("Yaaaaaacabaaa\n");
for(int i=0;i<n_position;i++){
for(int j=0;j<rows;j++){

free(storage[i][j]);
}
free(storage[i]);
free(storage2[i]);
}
free(storage);
printf("Succès\n");
}
int total_position(){
    int total=0;
   for(int k=0;k<(nb_pawn+1)*(nb_pawn+1);k++){
total=total+T_curseur[k];
   } return total;
}

void fill_storage(int** T){

for(int i=0; i<rows; i++) {
         for(int j=0; j<cols; j++) {
         storage[(n_1)*50000+(n_3)*5000+T_curseur[(n_1)*(nb_pawn+1)+n_3]][i][j]=T[i][j];
    	 }
     }
     T_curseur[n_1*(nb_pawn+1)+n_3]++;

}
void fill_storage2(){

for(int i=0; i<nb_pawn*2; i++) {
if(i<nb_pawn){
storage2[(n_1)*50000+(n_3)*5000+T_curseur[(n_1)*(nb_pawn+1)+n_3]][i]=L_1[i];
}else{
storage2[(n_1)*50000+(n_3)*5000+T_curseur[(n_1)*(nb_pawn+1)+n_3]][i]=L_3[i-nb_pawn];
}
     }
     T_curseur[n_1*(nb_pawn+1)+n_3]++;

}
int find_position(int**T){

n_passage_dans_le_dico++;


for(int n=(n_1-1)*50000+(n_3-1)*5000;n<(n_1-1)*50000+(n_3-1)*5000+T_curseur[(n_1-1)*(nb_pawn+1)+n_3-1];n++){
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
        n_position_reconnu++;
     	return n;
     }
}
return -1;
}

int find_position2(){
    sort_L();
/*L_render(1);
printf(" n_1 =%d\n",n_1);
L_render(0);
printf(" n_3 =%d\n",n_3);
//printf("\n\n");*/
n_passage_dans_le_dico++;

//printf("Le bug se situe ici\n");
for(int n=(n_1)*50000+(n_3)*5000;n<(n_1)*50000+(n_3)*5000+T_curseur[(n_1)*(nb_pawn+1)+n_3];n++){
    here=1;
    for(int i=0; i<nb_pawn*2; i++) {
        if(i<n_1){
         if(storage2[n][i]!=L_1[i]){
            here=0;
            break;
         }
        }
        if(i<nb_pawn+n_3&&i>=nb_pawn){
            if(storage2[n][i]!=L_3[i-nb_pawn]){
            here=0;
            break;
         }
        }
     }
     if(here==1){
        n_position_reconnu++;
        //printf("En fait non\n");
        return n;
     }
}
//printf("En fait non\n");
return -1;
}