//#include <math.h>

#include "td2.h"
#include "mazeEnv.h"

float max_a_Q(float** Q,int s){

return fmaxf(fmaxf(Q[s][0],Q[s][1]),fmaxf(Q[s][2],Q[s][3]));

}

void Q_render(float** Q){
	/*
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf(" %.1f ", max_a_Q(Q,j+i*cols));
         	 //       printf(" %.1f ", Q[j+i*cols][0]);
         }
         printf("\n");
     }*/
     
     for (int i=0; i<rows; i++) {
     	for (int j=0; j<cols; j++) {
     	
     		if (max_a_Q(Q,j+i*cols)== Q[j+i*cols][0]){
     			printf("h ");
     		}
     		
     	 	else if (max_a_Q(Q,j+i*cols) == Q[j+i*cols][1]){
     			printf("b ");
     		}
     		else if (max_a_Q(Q,j+i*cols) == Q[j+i*cols][2]){
     			printf("g ");
     		}
     		else {//(max_a_Q(Q,j+i*cols) == Q[j+i*cols][3]){
     			printf("d ");
     		}
     	}
     	printf("\n");
     }     		
     		
     /*
    printf("\n");
      for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf(" %.1f ", Q[j+i*cols][1]);
         }
         printf("\n");
     }
     printf("\n");
      for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf(" %.1f ", Q[j+i*cols][2]);
         }
         printf("\n");
     }
     printf("\n");
      for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf(" %.1f ", Q[j+i*cols][3]);
         }
         printf("\n");
     }
     printf("\n");*/
}

int taille_tableau;
int nombre_actions;


float** somme(float** Q1, float** Q2, float** Q) {
	
	for(int i=0;i<taille_tableau;i++){

	for(int j=0;j<nombre_actions;j++){


			Q[i][j]= Q1[i][j]+Q2[i][j]; 
		

	}
}
return(Q);
}

int greedy_method(float epsilon,float** Q, int s){

	//algorithme permettant de choisir une action
enum action direction;
if(rand()%101<epsilon*100){
//printf("full_hasard");
return (enum action)(rand() % number_actions);	

}
//printf("Pas de hasard !");
int h = rand()%4;
float ref = Q[s][h];
direction = h;
//printf("J'aurais pu avoir ");
for(int i=0;i<4;i++){
//	printf("%f ou",Q[s][i]);
if(Q[s][i]>ref){
	
	ref = Q[s][i];
	direction = i;
}
}//printf("%f mais j'ai choisi %f donc %d\n",Q[s][3],ref,direction);
return direction;//renvoie une action 
//	return (enum action)(rand() % number_actions);



	//return 0; 
}
void add_crumbs2(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  maze[i][j] ='.';
              }
          }
     }
     maze[start_row][start_col]= 's';
}

float** training(float** Q,int n_ep,float alpha, float epsilon){
	printf("Etape 1\n");
 /* stepOut.reward = reward-0.1; //permet de minimiser
    stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; */
	int ep_actuel=0;
	int etat=0;
	enum action direction;
	struct envOutput tirage;
	//int terminal = ; //Il faut récupérer la position du terminal
	int etat_p=0; // nouvel état
	float recompense=1; //recompense pour avoir commis une telle action
	float gamma = 0.3; //Caractérise l'impatience, si c'est proche de 1 on voit sur le très long terme, proche de 0 on veut le court terme 

	while(ep_actuel<n_ep){
		
		printf("Episode n°%d\n",ep_actuel);
		etat = start_col+(start_row)*cols; //Initialisation ? 
		tirage.done=0;
		//printf("Colonne et Ligne de départ :%d ; %d\n",start_col,start_row);
		
		while(!tirage.done){//Il faut récupérer les états terminaux / On teste afin de savoir si on est sur un état terminal ou pas
		
			direction = greedy_method(epsilon,Q,etat);
			tirage = maze_step(direction);//Choisi une action, puis fais un pas 
			etat_p = tirage.new_col+(tirage.new_row)*cols;
		//	printf("Colonne et Ligne actuel :%d ; %d\n",tirage.new_col,tirage.new_row);
			//action = greedy_method(epsilon);//Choisir une action
			//action=
			recompense=tirage.reward;
		//	printf("La recompense pour ce move %.1f\n",recompense);
			//Récupère récompense et le nouvel état qui a évolué car on a choisi une action
			//printf("ça va coincer\n");
			// vérifier si l'état est possible 
	//		printf("Action = %d Etat = %d Etat_p = %d Ligne %d Cols %d\n",direction,etat,etat_p,tirage.new_row,tirage.new_col);
			Q[etat][direction]=Q[etat][direction]*(1-alpha) + alpha*(recompense+gamma*max_a_Q(Q,etat_p));
//printf("ça passe ?!\n");
			if(tirage.done==0){etat = etat_p;}
		//	printf("\n\n");
		}
		printf("On a trouvé le trésor en %d ; %d ce qui nous a valu une récompense de %f et donc le dernier Q[s][a] vaut %f et s = %d et a = %d \n",tirage.new_row,tirage.new_col,recompense,Q[etat][direction],etat,direction);
maze_render();
Q_render(Q);
//printf("Aaaaaaaaaaaaaaaaaaaaaaaah");
		maze_reset();
		printf("\n\n");
		ep_actuel++;
	}printf("Aaaaaaaaaaaaaaaaaaaaaaaah\n");
			etat = start_col+(start_row)*cols;
		tirage.done=0;
		epsilon = 0;
		//int n=0;
	/*while(!tirage.done){//Il faut récupérer les états terminaux / On teste afin de savoir si on est sur un état terminal ou pas
		//printf("Eh oh, eh oh on rentre du boulot\n");
		
		//direction = env_action_sample();
		direction = greedy_method(epsilon,Q,etat);
		tirage = maze_step(direction);//Choisi une action, puis fais un pas 

			etat_p = tirage.new_col+(tirage.new_row)*cols;
		//	printf("Colonne et Ligne actuel :%d ; %d\n",tirage.new_col,tirage.new_row);
			//action = greedy_method(epsilon);//Choisir une action
			//action=
			recompense=tirage.reward;
			//Récupère récompense et le nouvel état qui a évolué car on a choisi une action
			//printf("ça va coincer\n");
			// vérifier si l'état est possible 
	//		printf("Action = %d Etat = %d Etat_p = %d Ligne %d Cols %d\n",direction,etat,etat_p,tirage.new_row,tirage.new_col);
			Q[etat][direction]=Q[etat][direction]*(1-alpha) + alpha*(recompense+gamma*Q[etat_p][direction]);
//printf("ça passe ?!\n");
			etat = etat_p;
			//add_crumbs2();
			maze[tirage.new_row][tirage.new_col] ='.';
		//	maze_render();
			n++;
		}*/
	
return Q;
}


float** doubletraining(float** Q1, float** Q2, float**Q,int n_ep, float alpha, float epsilon){
	printf("Etape 1\n");
 /* stepOut.reward = reward-0.1; //permet de minimiser
    stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; */
	int ep_actuel=0;
	int etat=0;
	enum action direction;
	struct envOutput tirage;
	//int terminal = ; //Il faut récupérer la position du terminal
	int etat_p=0; // nouvel état
	float recompense=1; //recompense pour avoir commis une telle action
	float gamma = 0.3; //Caractérise l'impatience, si c'est proche de 1 on voit sur le très long terme, proche de 0 on veut le court terme 
	
	//float** Q = somme(Q1,Q2);
	
gamma= gamma*1;
	while(ep_actuel<n_ep){
		
		printf("Episode n°%d\n",ep_actuel);
		etat = start_col+(start_row)*cols; //Initialisation ? 
		tirage.done=0;
		//printf("Colonne et Ligne de départ :%d ; %d\n",start_col,start_row);
		printf("Youhou");
		while(!tirage.done){//Il faut récupérer les états terminaux / On teste afin de savoir si on est sur un état terminal ou pas
		
			direction = greedy_method(epsilon,Q,etat);
			printf("La direction est %d on se situe en %d\n",direction,etat); 
			tirage = maze_step(direction);//Choisi une action, puis fais un pas 
			etat_p = tirage.new_col+(tirage.new_row)*cols;
		//	printf("Colonne et Ligne actuel :%d ; %d\n",tirage.new_col,tirage.new_row);
			//action = greedy_method(epsilon);//Choisir une action
			//action=
			recompense=tirage.reward;
		//	printf("La recompense pour ce move %.1f\n",recompense);
			//Récupère récompense et le nouvel état qui a évolué car on a choisi une action
			//printf("ça va coincer\n");
			// vérifier si l'état est possible 
	//		printf("Action = %d Etat = %d Etat_p = %d Ligne %d Cols %d\n",direction,etat,etat_p,tirage.new_row,tirage.new_col);
			if (rand()%2 == 0) {
			
			Q1[etat][direction]=Q1[etat][direction]*(1-alpha);// + alpha*(recompense+gamma*max_a_Q(Q1,etat_p));
//printf("ça passe ?!\n");
}
			else {
			Q2[etat][direction]=Q2[etat][direction]*(1-alpha) + alpha*(recompense+gamma*max_a_Q(Q2,etat_p));
//printf("ça passe ?!\n");
}
			if(tirage.done==0){etat = etat_p;}
		//	printf("\n\n");
		}
		printf("On a trouvé le trésor en %d ; %d ce qui nous a valu une récompense de %f et donc le dernier Q[s][a] vaut %f et s = %d et a = %d \n",tirage.new_row,tirage.new_col,recompense,Q[etat][direction],etat,direction);
maze_render();
Q_render(Q);
//printf("Aaaaaaaaaaaaaaaaaaaaaaaah");
		maze_reset();
		printf("\n\n");
		ep_actuel++;
	}printf("Aaaaaaaaaaaaaaaaaaaaaaaah\n");
			etat = start_col+(start_row)*cols;
		tirage.done=0;
		epsilon = 0;
		//int n=0;
	/*while(!tirage.done){//Il faut récupérer les états terminaux / On teste afin de savoir si on est sur un état terminal ou pas
		//printf("Eh oh, eh oh on rentre du boulot\n");
		
		//direction = env_action_sample();
		direction = greedy_method(epsilon,Q,etat);
		tirage = maze_step(direction);//Choisi une action, puis fais un pas 

			etat_p = tirage.new_col+(tirage.new_row)*cols;
		//	printf("Colonne et Ligne actuel :%d ; %d\n",tirage.new_col,tirage.new_row);
			//action = greedy_method(epsilon);//Choisir une action
			//action=
			recompense=tirage.reward;
			//Récupère récompense et le nouvel état qui a évolué car on a choisi une action
			//printf("ça va coincer\n");
			// vérifier si l'état est possible 
	//		printf("Action = %d Etat = %d Etat_p = %d Ligne %d Cols %d\n",direction,etat,etat_p,tirage.new_row,tirage.new_col);
			Q[etat][direction]=Q[etat][direction]*(1-alpha) + alpha*(recompense+gamma*Q[etat_p][direction]);
//printf("ça passe ?!\n");
			etat = etat_p;
			//add_crumbs2();
			maze[tirage.new_row][tirage.new_col] ='.';
		//	maze_render();
			n++;
		}*/
	
return Q;
}


int main(){
	maze_make("maze.txt");
   init_visited();
   maze_render();
   maze_reset();

   srand( time( NULL ) );
   printf("Ligne %d Colonne %d\n",rows,cols);
	int nombre_actions = 4; // G D H B 
	int taille_tableau = rows*cols; // Récupérer cela via le fichier // Si on 
	printf("taille tableau = %d\n",taille_tableau);
	float alpha = 0.4; //Valeur choisi au hasard
	float epsilon = 0.3; //Taux d'apprentissage
	int n_ep = 800;

float **Q1 = malloc(sizeof(float*)*taille_tableau);
printf("ça marche");
// Ligne 1 Ligne 2 ... Ligne n (chaque ligne fait p colonnes)
float **Q2 = malloc(sizeof(float*)*taille_tableau);
float** Q = malloc(sizeof(float*)*taille_tableau);
	
printf("Ici ça marche");

//int T[n][n];
for(int i=0;i<taille_tableau;i++){
	Q[i] = malloc(sizeof(float)*nombre_actions);
	Q2[i] = malloc(sizeof(float)*nombre_actions);
	Q1[i] = malloc(sizeof(float)*nombre_actions); // G D H B 
	if(Q[i]==NULL){
	return 1;// exit 1 si fonction
}

}
if(Q==NULL){
	return 1;
}


for(int i=0;i<taille_tableau;i++){

	for(int j=0;j<nombre_actions;j++){

		if(i!=j){

			Q[i][j]=0;Q1[i][j]=0;Q2[i][j]=0; //Initialisation de Q à 0
		}

	}
}
Q = somme(Q1,Q2,Q);
//	int* S=compute_amounts(T,n);
//	printf("%d",S[0]);

//entrainement
printf("Coucou");
Q = doubletraining(Q1,Q2,Q,n_ep,alpha,epsilon); // Où Q représente le nombre d'épisodes 

epsilon = epsilon+1;
alpha = alpha +1;
n_ep = n_ep +1;
Q_render(Q);
maze_render();
for(int i=0;i<taille_tableau;i++){

free(Q[i]);
}

free(Q);

printf("Je crois bien que c'est fini, est ce que ça a fonctionné ooooooh ?\n\n Henri t'es trop fort !!!");
// Tableau de tableau


}
