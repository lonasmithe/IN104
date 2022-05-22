#include "draughtboard_Env.h"
#include "agent.h"
#include "storage.h"
void alloc_draughtboard(){
     maze = malloc(rows * sizeof(int*));

     for(int i=0; i<rows; i++) {
         maze[i] = malloc(cols * sizeof(int*));
     }
     L_1 = malloc(nb_pawn*sizeof(int));
     L_3 = malloc(nb_pawn*sizeof(int));
     attaquable_1 = malloc(nb_pawn*sizeof(int));
     attaquable_3 = malloc(nb_pawn*sizeof(int));
}


void free_draughtboard(){


for(int i=0;i<rows-1;i++){

free(maze[i]);

}

printf("Les colonnes de maze sont free\n");

//free(L_1);
//free(L_3);
printf("La réserve des pions est free\n");

free(attaquable_3);
free(attaquable_1);


printf("Reste plus que le maze\n");

free(maze);

}

int id_pawn_on_knowncase(int x,int y,int e){
int value=y*cols+x;
if(e==1){
for(int i=0;i<n_1;i++){
    if(L_1[i]==value){return i;}
}
}else{
    for(int i=0;i<n_3;i++){
    if(L_3[i]==value){return i;}
}

}
printf("La fonction ne marche pas\n");
return -1;
}

void add_attaquable(int x, int y, int e){

    if(e==1){
        a_1++;
        attaquable_1[a_1]=x+y*cols;

    }
        if(e==0){
        a_3++;
        attaquable_3[a_3]=x+y*cols;

    }

}

int is_block(int e){
    //printf("Nous sommes à la %d opérations et c'est à %d de jouer\n",n_operation,e);
    int i;
    int j;

/*for(int i=0;i<20;i++){
        printf("%d ",L_1[i]);
    }printf("\n");


    for(int i=0;i<20;i++){
        printf("%d ",L_3[i]);}
    printf("\n N_1=%d et N_3=%d\n",n_1,n_3);
*/
if(e==1){
    for(int k=0;k<n_1;k++){

    i=(L_1[k]%(cols));///colonne
    j=(L_1[k]-(L_1[k]%(cols)))/cols; //ligne
           row_playable=j;
            col_playable=i;
   if(maze[j][i]==1){                if(i>1&&j<rows-2){
        if(maze[j+1][i-1]==3&&maze[j+2][i-2]==0){
           // printf("Ouf le pion %d en %d ; %d peut manger à gauche\n",k,i,j);
            move_playable=0;
            return 0;

        }
        }
        if(i<cols-2&&j<rows-2){
        if(maze[j+1][i+1]==3&&maze[j+2][i+2]==0){
            move_playable=1;
           
         //  printf("Ouf le pion %d en %d ; %d peut manger à droite\n",k,i,j);
           return 0;
        }
        }
        if(i<cols-1&&j<rows-1){
        if(maze[j+1][i+1]==0){
            move_playable=1;
         //   printf("Ouf le pion %d en %d ; %d peut se déplacer à droite\n",k,i,j);
           return 0;
        }
        }
        if(i>0&&j<rows-1){
        if(maze[j+1][i-1]==0){
            move_playable=0;
        //    printf("Ouf le pion %d en %d ; %d peut se déplacer à gauche \n",k,i,j);
            return 0;
        }
        }}

    }

}
if(e==0){

    for(int k=0;k<n_3;k++){

    i=(L_3[k]%(cols));
    j=(L_3[k]-(L_3[k]%(cols)))/cols;
           row_playable=j;
            col_playable=i;
    if(maze[j][i]==3){
                        if(i>1&&j>1){
        if(maze[j-1][i-1]==1&&maze[j-2][i-2]==0){
           // printf("Ouf le pion en %d ; %d peut manger à gauche ahah\n",i,j);
     
            move_playable=0;
            return 0;
        }
        }
        if(i<cols-2&&j>1){
        if(maze[j-1][i+1]==1&&maze[j-2][i+2]==0){
            move_playable=1;
         //   printf("Ouf le pion en %d ; %d peut manger à droite ahah\n",i,j);
           return 0;
        }
        }
                    if(i>0&&j>0){
        if(maze[j-1][i-1]==0){
            move_playable=0;
          //  printf("Ouf le pion en %d ; %d peut se deplacer ahah\n",i,j);
            return 0;
        }
        }
        if(i<cols-1&&j>0){
        if(maze[j-1][i+1]==0){
            move_playable=1;
           // printf("Ouf le pion en %d ; %d peut se deplacer ahah\n",i,j);
           return 0;
        }
        }
    }
    }
}

return 1;
}
void update_attaquable_move(int x_new,int y_new,int x_old, int y_old,int e){

    //attaquable sous 2 conditions
    //1 ennemis à coté
    //La case derrière l'ennemie est libre

    if(e==1){
        if(x_new>1&&y_new<rows-2){
        if(maze[x_new-1][y_new+1]==3&&maze[x_new-2][y_new+2]==0){
            ////add_attaquable(x_new,y_new,e);
        }
        }
        if(x_new<cols-2&&y_new<rows-2){
        if(maze[x_new+1][y_new+1]==3&&maze[x_new+2][y_new+2]==0){
            //add_attaquable(x_new,y_new,e);
        }
        }
                if(x_new>0&&y_new>0&&x_new<rows-1&&y_new<cols-1){
        if(maze[x_new-1][y_new+1]==3&&maze[x_new+1][y_new-1]==0){
            //add_attaquable(x_new-1,y_new+1,0);
        }
                if(maze[x_new+1][y_new+1]==3&&maze[x_new-1][y_new-1]==0){
            //add_attaquable(x_new+1,y_new+1,0);
        }
        }

if(x_new>x_old){

    if(x_new>1&&y_new<rows-2){
        if(maze[x_old-1][y_old+1]==1&&maze[x_old-2][y_old+2]==3){
            //add_attaquable(x_old-2,y_old-2,0);
        }
    }
}

if(x_new<x_old){
    if(x_new<cols-2&&y_new<rows-2){
        if(maze[x_old+1][y_old+1]==1&&maze[x_old+2][y_old+2]==3){
            //add_attaquable(x_old+2,y_old+2,0);
        }
    }
}
    }


}
void draughtboard_make(){

for(int i=0;i<nb_pawn;i++){
    attaquable_1[i]=-1;
    attaquable_3[i]=-1;
}
a_1=-1;
a_3=-1;
    n_3=nb_pawn;
    n_1=nb_pawn;
     int c=0;
     if(cols==10&&rows==10){
     for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
        
        if(i<4){//Equipe 1
            if(j%2==i%2){
                maze[i][j]=1;
                
                L_1[c]=j+i*rows;
                c++;
            }
            else{
                maze[i][j]=0;
            }
        }
        else if(i>5){//Equipe 0
            if(j%2==i%2){
                maze[i][j]=3;
                
                L_3[c-nb_pawn]=j+i*cols;
                c++;
            }
            else{
                maze[i][j]=0;
            }

        }
        else{
            maze[i][j]=0;
        }

        }
     }
 }


     if(cols==8&&rows==8){
     for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
        
        if(i<4){//Equipe 1
            if(j%2==i%2){
                maze[i][j]=1;
                
                L_1[c]=j+i*rows;
                c++;
            }
            else{
                maze[i][j]=0;
            }
        }
        else if(i>5){//Equipe 0
            if(j%2==i%2){
                maze[i][j]=3;
                
                L_3[c-nb_pawn]=j+i*cols;
                c++;
            }
            else{
                maze[i][j]=0;
            }

        }
        else{
            maze[i][j]=0;
        }

        }
     }
 }
}

void L_render(int e){
if(e==1){
    for(int i=0;i<n_1;i++){
        printf("%d ",L_1[i]);
    }printf("\n");
}
if(e==0){
    for(int i=0;i<n_3;i++){
        printf("%d ",L_3[i]);
    }printf("\n");
}

}
void draughtboard_render(int** D){
     for (int i=rows-1; i>=0; i--) {
         for (int j=0; j< cols; j++){
             printf("%d ", D[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}


void draughtboard_reset(){
     state_row = start_row;
     state_col = start_col;
}

int random_position_with_a_pawn(int e){
    if(e==1){

    return L_1[rand()%n_1];

        }else{
            return L_3[rand()%n_3];
        }
  
}

envOutput draughtboard_step(action a,int col_position,int row_position,int team){

  //  printf("Le bug se situe là dedans !\n");

  //  printf("Right = %d\n",right);
    
   // int sens;
    envOutput stepOut;
    stepOut.combo=0;
    stepOut.end=0;
    stepOut.done=0;
    stepOut.new_col=col_position;
stepOut.new_row=row_position;

//printf("Au tour de la team %d de jouer",team);



//cas des gentils
    if(team==1&&maze[row_position][col_position]==1){
    
    if (a==right){
    
      if(col_position!=cols-1){
        if(maze[row_position+1][col_position+1]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+1+(row_position+1)*cols;
            maze[row_position][col_position]=0;
            col_position=col_position+1;
            row_position=row_position+1;
            maze[row_position][col_position]=1;
            stepOut.end=1;
            tirage.reward=1;
        }
        else{
          //  printf("Impossible de se déplacer la case n'est pas vide !\n");
                                                   if(col_position<cols-2&&row_position<rows-2){
                                            if(maze[row_position+1][col_position+1]==3&&maze[row_position+2][col_position+2]==0){
                                                L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position+2)*cols;
                                                L_3[id_pawn_on_knowncase(col_position+1,row_position+1,0)]=L_3[n_3-1];
                                                n_3--;
                                    maze[row_position][col_position]=0;
                                    maze[row_position+1][col_position+1]=0;
                                                col_position=col_position+2;
                                                row_position=row_position+2;
                                                maze[row_position][col_position]=1;
                                    tirage.reward=1;
                                                stepOut.end=1;
                                                stepOut.combo=1;
                                            }
                                            else{      //     printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
                                     tirage.reward=-1;
                                                    stepOut.end=0;
                                                }   

                                            }
                                        else{
                                       // printf("Trop proche du bord\n");
                                                stepOut.end=0;
                                                tirage.reward=-5;
                                            } 
        }
    }else{
      //  printf("Trop proche du bord\n");
        stepOut.end=0;
        tirage.reward=-5;
      }

    }
    else if (a==left){

    if(col_position!=0){
        
        if(maze[row_position+1][col_position-1]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-1+(row_position+1)*cols;
            maze[row_position][col_position]=0;
            col_position=col_position-1;
            row_position=row_position+1;
            maze[row_position][col_position]=1;
            
tirage.reward=1;
            stepOut.end=1;
        }
        else{
           // printf("Impossible de se déplacer la case n'est pas vide !\n");
                                                        if(col_position>1&&row_position<8){
                                                            if(maze[row_position+1][col_position-1]==3&&maze[row_position+2][col_position-2]==0){
                                                                L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-2+(row_position+2)*cols;
                                                                L_3[id_pawn_on_knowncase(col_position-1,row_position+1,0)]=L_3[n_3-1];
                                                                n_3--;
                                                    maze[row_position][col_position]=0;
                                                    maze[row_position+1][col_position-1]=0;
                                                                col_position=col_position-2;
                                                                row_position=row_position+2;
                                                                maze[row_position][col_position]=1;
                                                    tirage.reward=1;
                                                                stepOut.end=1;
                                                                stepOut.combo=1;
                                                            }
                                                            else{
                                                           //     printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
                                                                    stepOut.end=0;
                                                                    tirage.reward=-1;
                                                                }   

                                                            }
                                                        else{
                                                      //  printf("Trop proche du bord\n");
                                                        tirage.reward=-5;
                                                                stepOut.end=0;
                                                            } 
        }
    }
    else{
   // printf("Trop proche du bord\n");
        stepOut.end=0;
    }  
    }
        else if (a==eat_left){

    if(col_position>1&&row_position<rows-2){
        if(maze[row_position+1][col_position-1]==3&&maze[row_position+2][col_position-2]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-2+(row_position+2)*cols;
            L_3[id_pawn_on_knowncase(col_position-1,row_position+1,0)]=L_3[n_3-1];
            n_3--;
maze[row_position][col_position]=0;
maze[row_position+1][col_position-1]=0;
            col_position=col_position-2;
            row_position=row_position+2;
            maze[row_position][col_position]=1;
tirage.reward=1;
            stepOut.end=1;
            stepOut.combo=1;
        }
        else{
           // printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
                stepOut.end=0;
                tirage.reward=-1;
            }   

        }
    else{
  //  printf("Trop proche du bord\n");
    tirage.reward=-5;
            stepOut.end=0;
        } 
    }
        else if (a==eat_right){

    if(col_position<cols-2&&row_position<rows-2){
        if(maze[row_position+1][col_position+1]==3&&maze[row_position+2][col_position+2]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position+2)*cols;
            L_3[id_pawn_on_knowncase(col_position+1,row_position+1,0)]=L_3[n_3-1];
            n_3--;
maze[row_position][col_position]=0;
maze[row_position+1][col_position+1]=0;
            col_position=col_position+2;
            row_position=row_position+2;
            maze[row_position][col_position]=1;
tirage.reward=1;
            stepOut.end=1;
            stepOut.combo=1;
        }
        else{         //  printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
 tirage.reward=-1;
                stepOut.end=0;
            }   

        }
    else{
  //  printf("Trop proche du bord\n");
            stepOut.end=0;
            tirage.reward=-5;
        } 
    }

if(row_position==rows-1){
stepOut.reward = 10;
stepOut.done = 1;
}
}else{
    if(team==1){//printf("S'il y a un pion sur cette case, il n'est pas de votre équipe\n");
    tirage.reward=-2;}
}












    if(team==0&&maze[row_position][col_position]==3){
        if (a==right){
        
          if(col_position!=cols-1){
            if(maze[row_position-1][col_position+1]==0){
                L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+1+(row_position-1)*cols;
                
                maze[row_position][col_position]=0;
                col_position=col_position+1;
                row_position=row_position-1;
                maze[row_position][col_position]=3;
                stepOut.end=1;
                tirage.reward=1;
            }
            else{
                //printf("Impossible de se déplacer la case n'est pas vide !\n");






            if(col_position<cols-1&&row_position>1){
                if(maze[row_position-1][col_position+1]==1&&maze[row_position-2][col_position+2]==0){
                    L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position-2)*cols;
                    L_1[id_pawn_on_knowncase(col_position+1,row_position-1,0)]=L_1[n_1-1];
                    n_1--;
        maze[row_position][col_position]=0;
        maze[row_position-1][col_position+1]=0;
                    col_position=col_position+2;
                    row_position=row_position-2;
                    maze[row_position][col_position]=3;
        tirage.reward=1;
                    stepOut.end=1;
                }
                else{       //    printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
         tirage.reward=-1;
                        stepOut.end=0;
                    }   

                }
            else{
        //    printf("Trop proche du bord\n");
            tirage.reward=-5;
                    stepOut.end=0;
                } 





                }
            }else{
                stepOut.end=0;
                //printf("Trop proche du bord\n");
                tirage.reward=-5;
              }

            }
            else if (a==left){

            if(col_position!=0){
                if(maze[row_position-1][col_position-1]==0){
                    L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-1+(row_position-1)*cols;
                   // printf("%d\n",maze[row_position-1][cols-1]);
                    maze[row_position][col_position]=0;
                    col_position=col_position-1;
                    row_position=row_position-1;
                    maze[row_position][col_position]=3;
        tirage.reward=1;
                    stepOut.end=1;
                }
                else{//printf("Impossible de se déplacer la case n'est pas vide !\n");
                    





            if(col_position>1&&row_position>1){
                if(maze[row_position-1][col_position-1]==1&&maze[row_position-2][col_position-2]==0){
                    L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-2+(row_position-2)*cols;
                    L_1[id_pawn_on_knowncase(col_position-1,row_position-1,0)]=L_1[n_1-1];
                    n_1--;
        maze[row_position][col_position]=0;
        maze[row_position-1][col_position-1]=0;
                    col_position=col_position-2;
                    row_position=row_position-2;
                    maze[row_position][col_position]=3;
        tirage.reward=1;
                    stepOut.end=1;
                }
                else{          // printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
         tirage.reward=-1;
                        stepOut.end=0;
                    }   

                }
            else{
           // printf("Trop proche du bord\n");
            tirage.reward=-5;
                    stepOut.end=0;
                } 






                }
            }
            else{
            
                stepOut.end=0;
               // printf("Trop proche du bord\n");
                tirage.reward=-5;
            }  
            }
                else if (a==eat_left){

            if(col_position>1&&row_position>1){
                if(maze[row_position-1][col_position-1]==1&&maze[row_position-2][col_position-2]==0){
                    L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-2+(row_position-2)*cols;
                    L_1[id_pawn_on_knowncase(col_position-1,row_position-1,1)]=L_1[n_1-1];
                    n_1--;
        maze[row_position][col_position]=0;
        maze[row_position-1][col_position-1]=0;
                    col_position=col_position-2;
                    row_position=row_position-2;
                    maze[row_position][col_position]=3;
        tirage.reward=1;
                    stepOut.end=1;
                }
                else{
                           //    printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
         tirage.reward=-1;
                    stepOut.end=0;
                }
            }
            else{
         //   printf("Trop proche du bord\n");
            tirage.reward=-5;
                stepOut.end=0;
            } 
            }else if (a==eat_right){

            if(col_position<cols-2&&row_position>1){
                if(maze[row_position-1][col_position+1]==1&&maze[row_position-2][col_position+2]==0){
                    L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position-2)*cols;
                    L_1[id_pawn_on_knowncase(col_position+1,row_position-1,0)]=L_1[n_1-1];
                    n_1--;
        maze[row_position][col_position]=0;
        maze[row_position-1][col_position+1]=0;
                    col_position=col_position+2;
                    row_position=row_position-2;
                    maze[row_position][col_position]=3;
        tirage.reward=1;
                    stepOut.end=1;
                }
                else{       //    printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
         tirage.reward=-1;
                        stepOut.end=0;
                    }   

                }
            else{
           // printf("Trop proche du bord\n");
            tirage.reward=-5;
                    stepOut.end=0;
                } 
            }
            if(row_position==0){
        stepOut.reward = -10;
        stepOut.done = 1;
        }

    }
    else{
        if(team==0){
       // printf("S'il y a un pion sur cette case, il n'est pas de votre équipe\n");
        tirage.reward=-2;
    }
}
//draughtboard_render(maze);

stepOut.choice=a;
if(is_block(team)==1){
    stepOut.done = 1;
    stepOut.end=1;
    stepOut.reward = -9;
}

    //à modifier
    /*if((state_row == goal_row) && (state_col == goal_col)){
       stepOut.reward = 10;
       stepOut.done   = 1;
    }else if(maze[state_row][state_col] == '+'){  
        //printf("Muuuuuuuuuur\n");
    stepOut.reward = reward-10; //permet de lui faire comprendre qu'aller dans un mur c'est pas bien.
    stepOut.done   = done;

    } else{ //printf("Peu mieux faire\n");
            stepOut.reward = reward-0.1; //permet de minimiser
    stepOut.done   = done;
    }
    //stepOut.reward = reward-0.1; //permet de minimiser
    //stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; 
//printf("Ligne : %d Colonne : %d\n",state_row,state_col);*/

  //printf("en fait non !\n");

   return stepOut;
}





