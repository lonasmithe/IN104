#include "td2.h"
#include "mazeEnv.h"

float max_a_Q(float** Q,int s){

return fmaxf(fmaxf(Q[s][0],Q[s][1]),fmaxf(Q[s][2],Q[s][3]));

}

void Q_render(float** Q){
	/*
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
        //     printf(" %.1f ", max_a_Q(Q,j+i*cols));
               printf(" %.1f ", Q[j+i*cols][0]);
         }
         printf("\n");
<<<<<<< HEAD
     }
     //
=======
     }*/
     
    /* for (int i=0; i<rows; i++) {
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
     }    */ 		
     		
     
//>>>>>>> refs/remotes/origin/master
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
     printf("\n");//
          for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
            printf(" %.1f ", max_a_Q(Q,j+i*cols));
           //    printf(" %.1f ", Q[j+i*cols][0]);
         }
         printf("\n");
     }
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
	int n = 0;
	enum action direction;
	enum action direction_bis;
	struct envOutput tirage;
	//int terminal = ; //Il faut récupérer la position du terminal
	int etat_p=0; // nouvel état
	float recompense=1; //recompense pour avoir commis une telle action
	float gamma = 0.6; //Caractérise l'impatience, si c'est proche de 1 on voit sur le très long terme, proche de 0 on veut le court terme 

	while(ep_actuel<n_ep){
		
		printf("Episode n°%d\n",ep_actuel);
		etat = start_col+(start_row)*cols; //Initialisation ? 
		tirage.done=0;
		//printf("Colonne et Ligne de départ :%d ; %d\n",start_col,start_row);
		

			direction = greedy_method(epsilon,Q,etat);
		while(!tirage.done){//Il faut récupérer les états terminaux / On teste afin de savoir si on est sur un état terminal ou pas
		
			
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
			direction_bis = greedy_method(epsilon,Q,etat_p);
			Q[etat][direction]=Q[etat][direction]*(1-alpha) + alpha*(recompense+gamma*Q[etat_p][direction_bis]);

//printf("ça passe ?!\n");
			if(tirage.done==0){etat = etat_p;
				direction=direction_bis;}
			n++;
		//	printf("\n\n");
		}
		printf("On a trouvé le trésor en %d ; %d en %d itérations ce qui nous a valu une récompense de %f et donc le dernier Q[s][a] vaut %f et s = %d et a = %d \n",tirage.new_row,tirage.new_col,n,recompense,Q[etat][direction],etat,direction);
maze_render();
n=0;
Q_render(Q);
//printf("Aaaaaaaaaaaaaaaaaaaaaaaah");
		maze_reset();
		printf("\n\n");
		ep_actuel++;
	}printf("LAncement de Sarsa\n");
			etat = start_col+(start_row)*cols;
		tirage.done=0;
		epsilon = 0;
	 n=0;
			direction = greedy_method(epsilon,Q,etat);
		while(!tirage.done){//Il faut récupérer les états terminaux / On teste afin de savoir si on est sur un état terminal ou pas
		
			
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
			direction_bis = greedy_method(epsilon,Q,etat_p);
			Q[etat][direction]=Q[etat][direction]*(1-alpha) + alpha*(recompense+gamma*Q[etat_p][direction_bis]);

//printf("ça passe ?!\n");
			if(tirage.done==0){etat = etat_p;
				direction=direction_bis;}
			n++;
		//	printf("\n\n");
		}

		printf("On est arrive au trésor en %d itération\n",n);
	
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
	float alpha = 0.8; //Valeur choisi au hasard
	float epsilon = 0.05; //Taux d'apprentissage
	int n_ep = 800;

float **Q = malloc(sizeof(float*)*taille_tableau);// Ligne 1 Ligne 2 ... Ligne n (chaque ligne fait p colonnes)
//int T[n][n];
for(int i=0;i<taille_tableau;i++){
	Q[i] = malloc(sizeof(float)*nombre_actions); // G D H B 
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

			Q[i][j]=pow(-1,rand()%2)*(rand()%10); //Initialisation de Q à 0
		}

	}
}
//	int* S=compute_amounts(T,n);
//	printf("%d",S[0]);

//entrainement


Q = training(Q,n_ep,alpha,epsilon); // Où Q représente le nombre d'épisodes 

epsilon = epsilon+1;
alpha = alpha +1;
n_ep = n_ep +1;
Q_render(Q);
maze_render();

for(int i=0;i<taille_tableau;i++){

free(Q[i]);

}

free(Q);

printf("Je crois bien que c'est fini, est ce que ça a fonctionné ooooooh ?\n\n Henri t'es trop fort !!! Je t'aime ! On est dans le programme");
// Tableau de tableau


}
