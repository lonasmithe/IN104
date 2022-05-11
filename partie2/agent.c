//#include "agent.h"
#include "draughtboard_Env.h"
#include "agent.h"
int alloc_Q(){

taille_tableau=48*49*50/6;
nombre_actions=4*50;
Q = malloc(sizeof(int*)*taille_tableau);
	if(Q==NULL){
	return 1;// exit 1 si fonction
}
for(int i=0;i<taille_tableau;i++){
	Q[i] = malloc(sizeof(int)*nombre_actions);
		if(Q[i]==NULL){
	return 1;// exit 1 si fonction
}
}
if(Q==NULL){
	return 1;
}
return 0;
}

void free_Q(){
	for(int i=0;i<taille_tableau;i++){

free(Q[i]);
}free(Q);
}


void init_Q(){
	for(int i=0;i<taille_tableau;i++){
		for(int j=0;j<nombre_actions;j++){
Q[i][j]=0;
		}
	}
}
void act_random(int e){
int n=0;
    envOutput stepOut;
    stepOut.end=0;
while(stepOut.end==0){
	stepOut=draughtboard_step((enum action)(rand()%(4)),rand()%10,rand()%10,e);
	n++;
}
printf("Le pion situé en (%d,%d) fait le choix : %d , case occupé par %d en %d opérations\n",stepOut.new_col,stepOut.new_row,stepOut.choice,maze[stepOut.new_row][stepOut.new_col],n);

}
int main(){
srand( time( NULL ) );
rows=10;
cols=10;
alloc_draughtboard();
draughtboard_make();
draughtboard_render();
//struct envOutput tirage;
/*tirage = draughtboard_step((enum action)(0),3,3,1);
tirage = draughtboard_step((enum action)(0),4,6,0);
tirage = draughtboard_step((enum action)(3),2,4,1);
tirage = draughtboard_step((enum action)(2),5,7,0);*/
//tirage = draughtboard_step((enum action)(3),5,7,0);
//tirage = draughtboard_step((enum action)(1),7,5,0);
//tirage = draughtboard_step((enum action)(0),0,2,1);

draughtboard_render();

int e = alloc_Q();
printf("%d\n",e);
act_random(0);
draughtboard_render();
act_random(1);
draughtboard_render();
act_random(0);
draughtboard_render();
act_random(1);
draughtboard_render();
act_random(0);
draughtboard_render();
act_random(1);
draughtboard_render();
act_random(0);
draughtboard_render();
act_random(1);
//printf("%f\n",tirage.reward);
draughtboard_render();
free_Q();
free_draughtboard();

}