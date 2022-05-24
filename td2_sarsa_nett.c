#include "td2.h"
#include "mazeEnv.h"

float max_a_Q(float** Q,int s){

	return fmaxf(fmaxf(Q[s][0],Q[s][1]),fmaxf(Q[s][2],Q[s][3]));

}

void Q_render(float** Q){
	
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
     	
     	printf("\n");
     	
      	for (int i=0; i<rows; i++) {
      	
         	for (int j=0; j< cols; j++){
            
            		printf(" %.1f ", max_a_Q(Q,j+i*cols));
          
         	}
         	
      	printf("\n");
      	
     	}
     	
}

// On implemente une fonction pour mettre en place la methode epsilon-greedy

int greedy_method(float epsilon,float** Q, int s){

	// On choisit une action
	
	enum action direction;
	
	if(rand()%101<epsilon*100){
	
		return (enum action)(rand() % number_actions);	

	}

	int h = rand()%4;
	float ref = Q[s][h];
	direction = h;

	for(int i=0;i<4;i++){

		if(Q[s][i]>ref){
	
			ref = Q[s][i];
			direction = i;
			
		}
		
	}
	
	return direction;
 
}

// Pour l'affichage du parcours dans le labyrinthe on implemente la fonction suivante

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
	
	//Initialisation
	
	printf("Etape 1\n");

	int ep_actuel=0;
	int etat=0;
	int n = 0;
	
	enum action direction;
	enum action direction_bis;
	
	struct envOutput tirage;
	
	// Nouvel état
	int etat_p=0; 
	
	// Recompense pour avoir commis une telle action
	float recompense=1; 
	
	//Caractérisation de l'impatience
	float gamma = 0.6; 
	
	while(ep_actuel<n_ep){
		
		printf("Episode n°%d\n",ep_actuel);
		
		etat = start_col+(start_row)*cols; 
		
		tirage.done=0;
		
		direction = greedy_method(epsilon,Q,etat);
		
		while(!tirage.done){
		
			//Il faut récupérer les états terminaux
			
			// On teste pour savoir si on est sur un état terminal
		
			// On choisit une action et puis on fait un pas
			tirage = maze_step(direction); 
		
			// On récupère la récompense et on pose le nouvel état après une action
			etat_p = tirage.new_col+(tirage.new_row)*cols;
		
			recompense=tirage.reward;
		
			direction_bis = greedy_method(epsilon,Q,etat_p);
			Q[etat][direction]=Q[etat][direction]*(1-alpha) + alpha*(recompense+gamma*Q[etat_p][direction_bis]);


			if(tirage.done==0){etat = etat_p; direction=direction_bis;}
		
			n++;
		
		
		}
		
		printf("On a trouvé le trésor en %d ; %d en %d itérations ce qui nous a valu une récompense de %f et donc le dernier Q[s][a] vaut %f et s = %d et a = %d \n",tirage.new_row,tirage.new_col,n,recompense,Q[etat][direction],etat,direction);
		
		maze_render();
		n=0;
		Q_render(Q);

		maze_reset();
		printf("\n\n");
		ep_actuel++;
		
	}
	
	printf("Lancement de Sarsa\n");
	etat = start_col+(start_row)*cols;
	tirage.done=0;
	epsilon = 0;
	n=0;
	direction = greedy_method(epsilon,Q,etat);
	
	
	while(!tirage.done){
	
		//Il faut récupérer les états terminaux
			
		// On teste pour savoir si on est sur un état terminal
		
		// On choisit une action et puis on fait un pas
		tirage = maze_step(direction);
		
		// On récupère la récompense et on pose le nouvel état après une action
		etat_p = tirage.new_col+(tirage.new_row)*cols;
		recompense=tirage.reward;
		
		direction_bis = greedy_method(epsilon,Q,etat_p);
		Q[etat][direction]=Q[etat][direction]*(1-alpha) + alpha*(recompense+gamma*Q[etat_p][direction_bis]);

		if(tirage.done==0){etat = etat_p; direction=direction_bis;}
			
		n++;
		
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
   	
   	// Les actions sont quatre : haut, gauche, bas, droite
	int nombre_actions = 4; 
	
	int taille_tableau = rows*cols; 
	
	printf("taille tableau = %d\n",taille_tableau);
	
	// Valeur choisi au hasard
	float alpha = 0.8; 
	
	// Taux d'apprentissage
	float epsilon = 0.05; 
	
	int n_ep = 800;

	float **Q = malloc(sizeof(float*)*taille_tableau);
	
	for(int i=0;i<taille_tableau;i++){
		
		Q[i] = malloc(sizeof(float)*nombre_actions); 
		
		if(Q[i]==NULL){
		
			return 1;
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

	Q = training(Q,n_ep,alpha,epsilon); 

	epsilon = epsilon+1;
	alpha = alpha +1;
	n_ep = n_ep +1;
	
	Q_render(Q);
	maze_render();

	for(int i=0;i<taille_tableau;i++){

		free(Q[i]);

	}

	free(Q);

	printf("Voici la fin du main");

}


