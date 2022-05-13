#include "draughtboard_Env.h"
#include "agent.h"
#include "storage.h"
void alloc_draughtboard(){
     maze = malloc(rows * sizeof(int*));

     for(int i=0; i<rows; i++) {
         maze[i] = malloc(cols * sizeof(int*));
     }
     L_1 = malloc(20*sizeof(int));
     L_3 = malloc(20*sizeof(int));
}


void free_draughtboard(){
for(int i=0;i<cols;i++){

free(maze[i]);
}


free(maze);

}

int id_pawn_on_knowncase(int x,int y,int e){
int value=x*rows+y;
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

void draughtboard_make(){
     int c=0;
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
                
                L_3[c-nb_pawn]=j+i*rows;
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

  //  printf("Right = %d\n",right);
    
   // int sens;
    envOutput stepOut;
    stepOut.combo=0;
    stepOut.end=0;
    stepOut.done=0;
    stepOut.new_col=col_position;
stepOut.new_row=row_position;

printf("Au tour de la team %d de jouer",team);



//cas des gentils
    if(team==1&&maze[row_position][col_position]==1){
    
    if (a==right){
    
      if(col_position!=cols-1){
        if(maze[row_position+1][col_position+1]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+1+(row_position+1)*rows;
            maze[row_position][col_position]=0;
            col_position=col_position+1;
            row_position=row_position+1;
            maze[row_position][col_position]=1;
            stepOut.end=1;
            tirage.reward=1;
        }
        else{
            printf("Impossible de se déplacer la case n'est pas vide !\n");
            stepOut.end=0;
            tirage.reward=-1;
        }
    }else{
        printf("Trop proche du bord\n");
        stepOut.end=0;
        tirage.reward=-5;
      }

    }
    else if (a==left){

    if(col_position!=0){
        
        if(maze[row_position+1][col_position-1]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-1+(row_position+1)*rows;
            maze[row_position][col_position]=0;
            col_position=col_position-1;
            row_position=row_position+1;
            maze[row_position][col_position]=1;
            
tirage.reward=1;
            stepOut.end=1;
        }
        else{
            printf("Impossible de se déplacer la case n'est pas vide !\n");
            stepOut.end=0;
            tirage.reward=-1;
        }
    }
    else{
    printf("Trop proche du bord\n");
        stepOut.end=0;
    }  
    }
        else if (a==eat_left){

    if(col_position>1&&row_position<9){
        if(maze[row_position+1][col_position-1]==3&&maze[row_position+2][col_position-2]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-2+(row_position+2)*rows;
            L_3[id_pawn_on_knowncase(col_position-1,row_position+1,1)]=L_3[n_3];
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
            printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
                stepOut.end=0;
                tirage.reward=-1;
            }   

        }
    else{
    printf("Trop proche du bord\n");
    tirage.reward=-5;
            stepOut.end=0;
        } 
    }
        else if (a==eat_right){

    if(col_position<8&&row_position<9){
        if(maze[row_position+1][col_position+1]==3&&maze[row_position+2][col_position+2]==0){
            L_1[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position+2)*rows;
            L_3[id_pawn_on_knowncase(col_position+1,row_position+1,1)]=L_3[n_3];
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
        else{           printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
 tirage.reward=-1;
                stepOut.end=0;
            }   

        }
    else{
    printf("Trop proche du bord\n");
            stepOut.end=0;
            tirage.reward=-5;
        } 
    }
if(row_position==9){
stepOut.reward = 10;
stepOut.done = 1;
}
}else{
    if(team==1){printf("S'il y a un pion sur cette case, il n'est pas de votre équipe\n");
    tirage.reward=-2;}
}












    if(team==0&&maze[row_position][col_position]==3){
    if (a==right){
    
      if(col_position!=cols-1){
        if(maze[row_position-1][col_position+1]==0){
            L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+1+(row_position-1)*rows;
            
            maze[row_position][col_position]=0;
            col_position=col_position+1;
            row_position=row_position-1;
            maze[row_position][col_position]=3;
            stepOut.end=1;
            tirage.reward=1;
        }
        else{
            printf("Impossible de se déplacer la case n'est pas vide !\n");
            tirage.reward=-1;
            stepOut.end=0;
        }
    }else{
        stepOut.end=0;
        printf("Trop proche du bord\n");
        tirage.reward=-5;
      }

    }
    else if (a==left){

    if(col_position!=0){
        if(maze[row_position-1][col_position-1]==0){
            L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-1+(row_position-1)*rows;
            printf("%d\n",maze[row_position-1][cols-1]);
            maze[row_position][col_position]=0;
            col_position=col_position-1;
            row_position=row_position-1;
            maze[row_position][col_position]=3;
tirage.reward=1;
            stepOut.end=1;
        }
        else{
            printf("Impossible de se déplacer la case n'est pas vide !\n");
            tirage.reward=-1;
            stepOut.end=0;
        }
    }
    else{
    
        stepOut.end=0;
        printf("Trop proche du bord\n");
        tirage.reward=-5;
    }  
    }
        else if (a==eat_left){

    if(col_position>1&&row_position>1){
        if(maze[row_position-1][col_position-1]==1&&maze[row_position-2][col_position-2]==0){
            L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-2+(row_position-2)*rows;
            L_1[id_pawn_on_knowncase(col_position-1,row_position-1,0)]=L_3[n_1];
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
                       printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
 tirage.reward=-1;
            stepOut.end=0;
        }
    }
    else{
    printf("Trop proche du bord\n");
    tirage.reward=-5;
        stepOut.end=0;
    } 
    }else if (a==eat_right){

    if(col_position<8&&row_position>1){
        if(maze[row_position-1][col_position+1]==1&&maze[row_position-2][col_position+2]==0){
            L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position-2)*rows;
            L_1[id_pawn_on_knowncase(col_position+1,row_position-1,0)]=L_1[n_1];
            n_1--;
maze[row_position][col_position]=0;
maze[row_position-1][col_position+1]=0;
            col_position=col_position+2;
            row_position=row_position-2;
            maze[row_position][col_position]=3;
tirage.reward=1;
            stepOut.end=1;
        }
        else{           printf("Impossible de manger soit la case d'arrivé est occupé soit il n'y a rien à manger\n");
 tirage.reward=-1;
                stepOut.end=0;
            }   

        }
    else{
    printf("Trop proche du bord\n");
    tirage.reward=-5;
            stepOut.end=0;
        } 
    }
    if(row_position==0){
stepOut.reward = -10;
stepOut.done = 1;
}
}else{if(team==0){
    printf("S'il y a un pion sur cette case, il n'est pas de votre équipe\n");
    tirage.reward=-2;
}
}

    

stepOut.choice=a;

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

   return stepOut;
}





