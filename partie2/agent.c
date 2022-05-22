//#include "agent.h"
#include "draughtboard_Env.h"
#include "agent.h"
#include "storage.h"



int alloc_Q(){

taille_tableau = 200000;
nombre_actions=2*rows*cols/2;
Q = malloc(sizeof(int*)*taille_tableau);

/*Test = malloc(sizeof(int)*5);
Test[1]=Test[2];
for(int i=0;i<1000;i++){
	printf("d");
}
free(Test);

*/
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
n_operation=0;
int stockage;

    tirage.end=0;
while(tirage.end==0){
	action_rand=rand()%2;
	stockage = random_position_with_a_pawn(e);
	//printf("%d avec n_3 = %d\n",stockage,n_3);
	//L_render(e);
	col_rand=(stockage%(cols));
	row_rand=(stockage-(stockage%(cols)))/cols;
	if(n_operation>seuil){
		printf("Rentrons en action !!!!!!!!!!!!!\n");
		col_rand=col_playable;
		row_rand=row_playable;
		action_rand=move_playable;
	}
	tirage=draughtboard_step((enum action)(action_rand), col_rand, row_rand, e);
	n_operation++;
	choix=action_rand+2*(col_rand/2+row_rand*cols/2);//Modifier le cols/2 valait 5
}

//printf("Le pion situé en (%d,%d) fait le choix : %d , case occupé par %d en %d opérations\n",tirage.new_col,tirage.new_row,tirage.choice,maze[tirage.new_row][tirage.new_col],n_operation);
n_operation=0;
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
void actualise_etat(){
etat_p=find_position(maze);
if(etat_p==-1){
	etat_p=curseur;
	fill_storage(maze);
}	
}
void training(){
victoire=0;
egalite=0;
tirage.done=0;
n_iter=0;
n_boucle=1000;


	while(n_iter<n_boucle){
		etat=0;
		etat_p=0;
	while(tirage.done==0){


etat=etat_p;

		greedy_method();
		if(choix!=-1){
		//printf("L'action sera %d la col %d sera la ligne sera %d\n",choix%2,((choix-(choix%2))/2)%5,((choix-(choix-(choix%2))/2)%5)/10);
			tirage=draughtboard_step(choix%2, ((choix-(choix-(choix%2))/2)%(cols/2)/cols)%2+2*((choix-(choix%2))/2)%(cols/2),((choix-(choix-(choix%2))/2)%(cols/2))/cols,1);//Ligne douteuse suite au changement
		
		}else{
			act_random(1);
		}
		
		
		//printf("etat = %d choice = %d\n",etat, choix);
		//draughtboard_render(maze);
		
//printf("On est rendu au %d épisode, on a %d positions dans notre stockage\n",n_iter,curseur);

if(tirage.done!=1){



if(tirage.end==1){
	tirage.end=0;
	//actualise_etat();
	act_random(0);

	

}
actualise_etat();
Q[etat][choix]=Q[etat][choix]*(1-alpha) + alpha*(tirage.reward+gammma*max_a_Q(etat_p));
}
printf("On est rendu au %d épisode, on a %d positions dans notre stockage\n",n_iter,curseur);

}
if(tirage.reward>0){
	victoire++;
}
if(tirage.reward==-9){
	egalite++;
}
n_iter++;
if(find_position(maze)!=curseur-1){
	deja_vu++;
}
tirage.done=0;
draughtboard_make();
actualise_etat();

}
printf("Les blancs ont gagnés : %d matchs sur %d et on fait %d egalités\n", victoire,n_iter, egalite);
printf("On a eu %d positions de fin différentes\n",n_boucle-deja_vu);
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
rows=8;
cols=8;
epsilon=0.3;
alpha=0.4;
gammma=0.4;
//nb_pawn=cols/2;
if(cols==8&&rows==8){
	nb_pawn=12;
}
if(cols==10&&rows==10){
	nb_pawn=20;
}
deja_vu=0;
    n_3=nb_pawn;
    n_1=nb_pawn;
    n_position_reconnu=0;
    n_passage_dans_le_dico=0;
    seuil=100; // nombre de coup au bout duquel on va jouer un coup possible donnée par is block (valable pour l'équipe 0 uniquement)
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


//draughtboard_render(maze);

printf("Sur %d situations on en a reconnu %d",n_passage_dans_le_dico,n_position_reconnu);

free_storage();
printf("Ce free s'est bien passé\n");

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

printf("Ce free s'est aussi bien passé\n");

free_draughtboard();

}

/*


Pour améliorer il faut réduire le temps de recherche dans les positions connus pour augmenter le nombre d'itéartion
Il faut vérifier qu'on arrive à finir plusieurs fois de la même façon
Réduire le damier...



*/