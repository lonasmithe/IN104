//#include "agent.h"
#include "draughtboard_Env.h"
  #include "agent.h"
  #include "storage.h"



  int alloc_Q() {

  taille_tableau = 500000;
  nombre_actions=2*rows*cols/2;
  Q = malloc(sizeof(float*)*taille_tableau);

  /*Test = malloc(sizeof(int)*5);
   Test[1]=Test[2];
   for(int i=0;i<1000;i++){
   printf("d");
   }
   free(Test);
   
   */
  if (Q==NULL) {
    return 1;// exit 1 si fonction
  }
  for (int i=0; i<taille_tableau; i++) {
    Q[i] = malloc(sizeof(float)*nombre_actions);
    if (Q[i]==NULL) {
      return 1;// exit 1 si fonction
    }else{
      for(int k=0;k<nombre_actions;k++){Q[i][k]=0;}
    }
  }
  if (Q==NULL) {
    return 1;
  }
  return 0;
}



void free_Q() {
  for (int i=0; i<taille_tableau; i++) {

    free(Q[i]);
  }
  free(Q);
}




void init_Q() {
  for (int i=0; i<taille_tableau; i++) {
    for (int j=0; j<nombre_actions; j++) {
      Q[i][j]=0;
    }
  }
}



float max_a_Q(int e) {
  int h = rand()%nombre_actions;
  float ref = Q[e][h];
  //enum action choix2 = h;
  //printf("J'aurais pu avoir ");
  for (int i=0; i<nombre_actions; i++) {
    //  printf("%f ou",Q[s][i]);
    if (Q[e][i]>ref) {

      ref = Q[e][i];
      //choix2 = i;
    }
  }
  return ref;
}

void act_random(int e) {
 // printf("Nous avons déterminé le coup avec la méthode act_random\n");
  n_operation=0;
  int stockage;

  tirage.end=0;
  while (tirage.end==0) {
    action_rand=rand()%2;
    stockage = random_position_with_a_pawn(e);
    //printf("%d avec n_3 = %d\n",stockage,n_3);
    //L_render(e);
    col_rand=(stockage%(cols));
    row_rand=(stockage-(stockage%(cols)))/cols;
    if (n_operation>seuil) {
      printf("Rentrons en action !!!!!!!!!!!!!\n");
      col_rand=col_playable;
      row_rand=row_playable;
      action_rand=move_playable;
    }
    tirage=draughtboard_step((enum action)(action_rand), col_rand, row_rand, e);
    n_operation++;
    choix=action_rand+2*((col_rand-(row_rand%2))/2+row_rand*cols/2);//Modifier le cols/2 valait 5
  }

  //printf("Le pion situé en (%d,%d) fait le choix : %d , case occupé par %d en %d opérations\n",tirage.new_col,tirage.new_row,tirage.choice,maze[tirage.new_row][tirage.new_col],n_operation);
  n_operation=0;
  //printf("En fait non\n");
}
void greedy_method() {
  //printf("Le bug se situe ici\n");

  tirage.end=0;

  //algorithme permettant de choisir une action
  //enum action direction;
  if (rand()%101<epsilon*100) {

//printf("Laissons faire le hasard\n");
    choix=-1;
    //return (enum action)(rand() % number_actions);
  } else {

    int h = rand()%nombre_actions;
    float ref = Q[etat][h];
    choix = h;
    //printf("J'aurais pu avoir ");
    for (int i=0; i<nombre_actions; i++) {
      //  printf("%f ou",Q[s][i]);
      if (Q[etat][i]>ref) {
//printf("TRoooooooooooop fort\n");
        ref = Q[etat][i];
        choix = i;
      }

    }
    
  //  printf("La valeur de ref = %f et choix = %d et etat = %d",ref, choix,etat);
    //return direction;//renvoie une action


    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //recevoir la récompense
  }
  //printf("En fait non\n");
}
void actualise_etat() {
//printf("LE VRAI VRAI BUG EST LA ! n_1=%d n_3=%d\n",n_1,n_3);	
  etat_p=find_position2(maze);

//printf("Le bug se situe ici et done = %d et end %d et etat_p=%d\n",tirage.done,tirage.end,etat_p); //dernière élimination

  //printf("Youhou\n");
  if (etat_p==-1) {
    etat_p=(n_1)*50000+(n_3)*5000+T_curseur[(n_1)*(nb_pawn+1)+n_3];
    fill_storage2(maze);


  }
  //printf("EN FAIT NON\n");
}

void training() {
  victoire=0;
  egalite=0;
  tirage.done=0;
  n_iter=0;
  n_boucle=2000;

  while (n_iter<n_boucle) {
    etat=220000;
    etat_p=220000;
    n=0;
    while (tirage.done==0) {
n++;
actualise_etat();
      //draughtboard_render(maze);
      etat=etat_p;

      greedy_method();
      if (choix!=-1) {
        //printf("L'action sera %d la col %d sera la ligne sera %d\n",choix%2,((choix-(choix%2))/2)%5,((choix-(choix-(choix%2))/2)%5)/10);
         choix=action_rand+2*((col_rand-(row_rand%2))/2+row_rand*cols/2);//Modifier le cols/2 valait 5

        int row_e = (((choix-choix%2)/2)-(((choix-choix%2)/2)%(cols/2)))/(cols/2);
        int col_e = (((choix-choix%2)/2)%(cols/2))*2 + row_e%2;
        tirage=draughtboard_step(choix%2, row_e,col_e, 1);//Ligne douteuse suite au changement
      } else {
        act_random(1);
      }



      //printf("etat = %d choice = %d\n",etat, choix);
      //draughtboard_render(maze);
     // printf("On est rendu au %d épisode, on a %d positions dans notre stockage\n",n_iter,curseur);
        
      if (tirage.done!=1) {

        if (tirage.end==1) {
          tirage.end=0;
          //actualise_etat();

          act_random(0);       
          actualise_etat();
          
          Q[etat][choix]=Q[etat][choix]*(1-alpha) + alpha*(tirage.reward+gammma*max_a_Q(etat_p)); //printf("Q vaut %.2f \n",Q[etat][choix]);
          }else{

            Q[etat][choix]=Q[etat][choix]*(1-alpha) + alpha*(tirage.reward); 
          }



         //printf("ou bien Q vaut %.2f \n",Q[etat][choix]);
     //    printf("Lors de l'ep %d et du coup %d on a Q[%d][%d] = %.2f max_a_Q[%d] = %f et reward = %.2f \n",n_iter,n,etat,choix,Q[etat][choix],etat_p,max_a_Q(etat_p),tirage.reward);
      
       }
      //printf()
     //  draughtboard_render(maze);
     // printf("On est rendu au %d épisode, on a %d positions dans notre stockage\n", n_iter, total_position());
      /*for (int k=0; k<(nb_pawn+1)*(nb_pawn+1); k++) {
        printf("%d ", T_curseur[k]);
      }
      printf("\n");*/

    }
    if (tirage.reward>0) {
      victoire++;
    }
    if (tirage.reward==-7) {
      egalite++;
    }
    if (n_iter%4000==0) {
      epsilon=epsilon/2;
    }
    n_iter++;
    if (find_position2(maze)!=-1) {
      deja_vu++;
    }
    tirage.done=0;
    draughtboard_make();
    actualise_etat();
  }
  printf("Les blancs ont gagnés : %d matchs sur %d et on fait %d egalités\n", victoire, n_iter, egalite);
  printf("On a eu %d positions de fin différentes\n", n_boucle-deja_vu);
}
void double_dumb() {


  //float recompense=1;
  tirage.done=0;

  int i=0;

  //while(i<10){
  while (tirage.done==0) {

    act_random(i%2);

    i++;
  }
}

int main() {
  srand( time( NULL ) );
  rows=8;
  cols=8;
  epsilon=0.05;
  alpha=0.8;
  gammma=0.7;
  //nb_pawn=cols/2;
  if (cols==8&&rows==8) {
    nb_pawn=4;
  }
  if (cols==4&&rows==8) {
    nb_pawn=4;
  }
  if (cols==10&&rows==10) {
    nb_pawn=20;
  }
  deja_vu=0;
  n_3=nb_pawn;
  n_1=nb_pawn;
  n_position_reconnu=0;
  n_passage_dans_le_dico=0;
  seuil=40; // nombre de coup au bout duquel on va jouer un coup possible donnée par is block (valable pour l'équipe 0 uniquement)
  alloc_draughtboard();
  draughtboard_make();

  int e = alloc_Q();
  printf("%d\n", e);


  create_storage();
  training();
/*
for(int k=0;k<nombre_actions;k++){
  printf("%.2f ",Q[220000][k]);
  if(k%8==7){
    printf("\n");
  }
}
printf("\n\n");
for(int k=0;k<nombre_actions;k++){
  printf("%.2f ",Q[220001][k]);
  if(k%8==7){
    printf("\n");
  }
}*/



  //draughtboard_render(maze);

  printf("Sur %d situations on en a reconnu %d", n_passage_dans_le_dico, n_position_reconnu);

  free_storage();
  printf("Ce free s'est bien passé\n");

  printf("%d", e);

  free_Q();

  printf("Ce free s'est aussi bien passé\n");

  free_draughtboard();
}

/*

 
 Pour améliorer il faut réduire le temps de recherche dans les positions connus pour augmenter le nombre d'itéartion
 Il faut vérifier qu'on arrive à finir plusieurs fois de la même façon
 Réduire le damier...
 
 
 
 */