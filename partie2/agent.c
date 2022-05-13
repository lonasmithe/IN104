//#include "agent.h"
#include "draughtboard_Env.h"
#include "agent.h"
#include "storage.h"



int alloc_Q(){

taille_tableau=1000;
nombre_actions=4*20;
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



float max_a_Q(int e){
int h = rand()%nombre_actions;
float ref = Q[e][h];
choix = h;
//printf("J'aurais pu avoir ");
for(int i=0;i<nombre_actions;i++){
//	printf("%f ou",Q[s][i]);
if(Q[e][i]>ref){
	
	ref = Q[e][i];
	choix = i;
}
}
return ref;

}

void act_random(int e){
int n=0;
    
    tirage.end=0;
while(tirage.end==0){
	tirage=draughtboard_step((enum action)(rand()%(4)),rand()%10,rand()%10,e);
	n++;
}

printf("Le pion situé en (%d,%d) fait le choix : %d , case occupé par %d en %d opérations\n",tirage.new_col,tirage.new_row,tirage.choice,maze[tirage.new_row][tirage.new_col],n);

}
void greedy_method(){
tirage.end=0;

	//algorithme permettant de choisir une action
//enum action direction;
if(rand()%101<epsilon*100){

choix=-1;
//return (enum action)(rand() % number_actions);	

}
else{
	while(tirage.end==0){
int h = rand()%nombre_actions;
float ref = Q[etat][h];
choix = h;
//printf("J'aurais pu avoir ");
for(int i=0;i<nombre_actions;i++){
//	printf("%f ou",Q[s][i]);
if(Q[etat][i]>ref){
	
	ref = Q[etat][i];
	choix = i;
}
}
//return direction;//renvoie une action 


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//recevoir la récompense
}
}
}
void actualise_etat(){
etat=find_position(maze);
if(etat==-1){
	etat=curseur;
	fill_storage(maze);
}	
}
void training(){


tirage.done=0;


	//while(i<10){
	while(tirage.done==0){



		greedy_method();
		if(choix!=-1){
		
			tirage=draughtboard_step(choix);
		
		}else{
			act_random(1);
		}
actualise_etat();
Q[etat][choice]=Q[etat][choice]*(1-alpha) + alpha*(recompense+gammma*max_a_Q(Q,etat_p));
if(tirage.end==1){
	tirage.end=0;
	act_random(0);
	actualise_etat();
}

}



}
void double_dumb(){


//float recompense=1;
tirage.done=0;

int i=0;

	//while(i<10){
	while(tirage.done==0){

act_random(i%2);

		i++;
	}

}

int main(){
srand( time( NULL ) );
rows=10;
cols=10;
epsilon=0.3;
alpha=0.4;
gammma=0.4;
alloc_draughtboard();
draughtboard_make();
//draughtboard_render();
//struct envOutput tirage;
/*tirage = draughtboard_step((enum action)(0),3,3,1);
tirage = draughtboard_step((enum action)(0),4,6,0);
tirage = draughtboard_step((enum action)(3),2,4,1);
tirage = draughtboard_step((enum action)(2),5,7,0);*/
//tirage = draughtboard_step((enum action)(3),5,7,0);
//tirage = draughtboard_step((enum action)(1),7,5,0);
//tirage = draughtboard_step((enum action)(0),0,2,1);

//draughtboard_render();


int e = alloc_Q();
printf("%d\n",e);


create_storage();
training();
draughtboard_render(maze);

free_storage();
printf("%d",e);
//draughtboard_render();
/*act_random(0);
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
draughtboard_render();*/
free_Q();
free_draughtboard();

}