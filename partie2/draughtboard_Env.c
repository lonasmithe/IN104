#include "draughtboard_Env.h"
#include "agent.h"
#include "storage.h"

// Allocation mémoire pour le damier

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


// Fonction pour libérer le damier

void free_draughtboard(){

	for(int i=0;i<rows-1;i++){

	free(maze[i]);

	}

	printf("Les colonnes de maze sont free\n");
	printf("La réserve des pions est free\n");

	free(attaquable_3);
	free(attaquable_1);

	printf("Il ne reste plus que le maze\n");

	free(maze);

}


// Fonction pour retourner l'identifiant d'un pion sur une case

int id_pawn_on_knowncase(int x,int y,int e){

	int value=y*cols+x;
	
	if(e==1){
		
		for(int i=0;i<n_1;i++){
		
    			if(L_1[i]==value){return i;}
	
		}
	
	}
	
	else {
	
    		for(int i=0;i<n_3;i++){
    		
    			if(L_3[i]==value){return i;}
		
		}

	}
	
	printf("La fonction ne marche pas\n");
	
	return -1;
	
}

// Fonction qui ajoute un pion à la liste des pions qui peuvent manger

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


// Fonction pour voir s'il existe un coup à jouer

int is_block(int e){
    
    	int i;
    	int j;


	if(e==1){
    
    		for(int k=0;k<n_1;k++){

    			i=(L_1[k]%(cols)); //colonne
    			j=(L_1[k]-(L_1[k]%(cols)))/cols; //ligne
           		row_playable=j;
            		col_playable=i;
            		
            		
   			if(maze[j][i]==1){                
   			
   				if(i>1&&j<rows-2){
   				
        				if(maze[j+1][i-1]==3&&maze[j+2][i-2]==0){
        				
            					move_playable=0;
            					return 0;

        				}
        				
        			}
        			
        			if(i<cols-2&&j<rows-2){
        		
        				if(maze[j+1][i+1]==3&&maze[j+2][i+2]==0){
        			
            					move_playable=1;
          
           					return 0;
        
        				}
        
        			}
        		
        			if(i<cols-1&&j<rows-1){
        			
        				if(maze[j+1][i+1]==0){
            
            					move_playable=1;
         
           					return 0;
        				}
        				
        			}
        
        			if(i>0&&j<rows-1){
        
        				if(maze[j+1][i-1]==0){
            					
            					move_playable=0;
        
            					return 0;
        				
        				}
        			
        			}
        		
        		}

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
         
            					move_playable=0;
            					
            					return 0;
        				
        				}
        
        			}
        
        			if(i<cols-2&&j>1){
        
        				if(maze[j-1][i+1]==1&&maze[j-2][i+2]==0){
            
            					move_playable=1;
         
           					return 0;
        			
        				}
        		
        			}
                    
                    		if(i>0&&j>0){
        			
        				if(maze[j-1][i-1]==0){
            			
            					move_playable=0;
         
            					return 0;
        			
        				}
        		
        			}
        		
        			if(i<cols-1&&j>0){
        			
        				if(maze[j-1][i+1]==0){
           				
           					move_playable=1;
           
           					return 0;
        			
        				}
        		
        			}
    		
    			}	
    	
    		}

	}

	return 1;
	
}


// Elle ne marche pas

void update_attaquable_move(int x_new,int y_new,int x_old, int y_old,int e){

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

// Fonction qui configurer le damier

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
        
        			if(i<4){
        			
            				//Equipe 1
            				if(j%2==i%2){
                				
                				maze[i][j]=1;
                
                				L_1[c]=j+i*rows;
                				c++;
            				}
            				
            				else{
                				
                				maze[i][j]=0;
            				
            				}
       			
       			}
       		
       		 	else if(i>5){
       		 
       		 		//Equipe 0
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
        
        			if(i==2){
            				
            				//Equipe 1
            				if(j%2==i%2){
                				
                				maze[i][j]=1;
                
                				L_1[c]=j+i*rows;
                				c++;
            				}
            				
            				else{
                			
                				maze[i][j]=0;
            				
            				}
        			}
        			
        			else if(i==5){
        			
        				//Equipe 0
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
      	
      	if(cols==4&&rows==8){
     		
     		for(int i=0;i<rows;i++){
        		
        		for(int j=0;j<cols;j++){
        
        			if(i<2){
        				
        				//Equipe 1
            				if(j%2==i%2){
                				
                				maze[i][j]=1;
                
                				L_1[c]=j+i*rows;
                				c++;
            				}
            			
            				else{
                			
                				maze[i][j]=0;
            				}
        			
        			}
        			
        			else if(i>5){
        				
        				//Equipe 0
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

// Elle affiche la liste des pions sur le damier


void L_render(int e){
		
	if(e==1){
    			
    		for(int i=0;i<n_1;i++){
        			
        		printf("%d ",L_1[i]);
    		
    		}
    			
    		printf("\n");
		
	}
		
	if(e==0){
    			
    		for(int i=0;i<n_3;i++){
        			
        		printf("%d ",L_3[i]);
    		
    		}
    			
    		printf("\n");
		
	}

}


// Fonction qui affiche le damier

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

// Fonction qui retourne un endroit où il y a un pion

int random_position_with_a_pawn(int e){
    
    	if(e==1){

   		return L_1[rand()%n_1];

        }
        
        else{
        
            	return L_3[rand()%n_3];
        
        }
  
}

// Fonction qui retourne le coup joué s'il était possible

envOutput draughtboard_step(action a,int col_position,int row_position,int team){

    	envOutput stepOut;
    	stepOut.combo=0;
    	stepOut.end=0;
    	stepOut.done=0;
    	stepOut.new_col=col_position;
	stepOut.new_row=row_position;


	// Equipe avec apprentissage par renforcement
	
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
                                    		tirage.reward=4;
                                              stepOut.end=1;
                                              stepOut.combo=1;
                                              
                                     	}
                                                                              
                                     	else{      
                                     		
                                     		tirage.reward=-1;
                                          	stepOut.end=0;
                                      
                                  	}   

                          	}
                               
                               else{
                                       stepOut.end=0;
                                       tirage.reward=-5;
                                       
                               }
                                
        		}
    		}
    		
    		else{
    		
			stepOut.end=0;
        		tirage.reward=-5;
      		
      		}

    	}
   	
   	else if (a==left){

    		if(col_position!=0&&row_position<rows-1){
        
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
		          			tirage.reward=4;
		                            	stepOut.end=1;
		                  		stepOut.combo=1;
                  
                  			}
                  		
                               	else{
                                                           
		         			stepOut.end=0;
	   					tirage.reward=-1;
                       	
                       		}   

              			}
                                                        
             			else{
                                                      
		       		tirage.reward=-5;
		      			stepOut.end=0;
                                                            
                    		} 
                    	
        		}
        		
    		}
    	
	    	else{
	   
			stepOut.end=0;
	    	
	    	}  
	}


	if(row_position==rows-1){
		
		stepOut.reward = 1000;
		stepOut.done = 1;
	
	}
	
	}
	
	else{
    		
    		if(team==1){
    			
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
					tirage.reward=5;
            			
            			}
            		
            		else{
              
            			if(col_position<cols-1&&row_position>1){
            	    			
            	    			if(maze[row_position-1][col_position+1]==1&&maze[row_position-2][col_position+2]==0){
						    
						    L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position-2)*cols;
						    L_1[id_pawn_on_knowncase(col_position+1,row_position-1,1)]=L_1[n_1-1];
						    n_1--;
						    maze[row_position][col_position]=0;
					            maze[row_position-1][col_position+1]=0;
						    col_position=col_position+2;
						    row_position=row_position-2;
						    maze[row_position][col_position]=3;
					            tirage.reward=5;
						    stepOut.end=1;
                			
                			}
                		
                			else{ 
         				
		 				tirage.reward=-1;
		                		stepOut.end=0;
                    		
                    			}   
      	
                		}
            		
            			else{
       
		    			tirage.reward=-5;
		            		stepOut.end=0;
                	
                		} 


                	}
            	
            	}
            	
            	else{
                	
                	stepOut.end=0;
                
                	tirage.reward=-5;
              	}

  	}
        
        else if (a==left){

            	if(col_position!=0){
                	
                	if(maze[row_position-1][col_position-1]==0){
                    
		            L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position-1+(row_position-1)*cols;
		           
				    maze[row_position][col_position]=0;
				    col_position=col_position-1;
				    row_position=row_position-1;
				    maze[row_position][col_position]=3;
				tirage.reward=1;
		            	stepOut.end=1;
                	}
                	
                	else{

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
         					
         					tirage.reward=-1;
                        			stepOut.end=0;
                    			}   

                		}
            
            			else{
          
            				tirage.reward=-5;
                   			 stepOut.end=0;
                		} 
                	
                	}
            
            	}
            	
            	else{
		    
		        stepOut.end=0;
		       
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
				           
			 tirage.reward=-1;
				    stepOut.end=0;
				    
                	}
                
            	}
            	
            	else{
         
		    tirage.reward=-5;
		        stepOut.end=0;
		        
            	} 
            	
            }
     	else if (a==eat_right){

            	if(col_position<cols-2&&row_position>1){
                	if(maze[row_position-1][col_position+1]==1&&maze[row_position-2][col_position+2]==0){
				    L_3[id_pawn_on_knowncase(col_position,row_position,team)]=col_position+2+(row_position-2)*cols;
				    L_1[id_pawn_on_knowncase(col_position+1,row_position-1,1)]=L_1[n_1-1];
				    n_1--;
			maze[row_position][col_position]=0;
			maze[row_position-1][col_position+1]=0;
				    col_position=col_position+2;
				    row_position=row_position-2;
				    maze[row_position][col_position]=3;
			tirage.reward=1;
				    stepOut.end=1;
                	}
                	
                	else{     
                	 
         			tirage.reward=-1;
                        	stepOut.end=0;
                        	
                    	}   

                }
            	
            	else{
           
            		tirage.reward=-5;
                    	stepOut.end=0;
                
                } 
            
   	}
   	
   	
        if(row_position==0){
		
		stepOut.reward = -1000;
		stepOut.done = 1;
		
        }

    	}
    	
    	else{
        	
        	if(team==0){
       
        		tirage.reward=-2;
        		
    		}

	}


	stepOut.choice=a;

if(n_3<=0){
       stepOut.done = 1;
    stepOut.end=1;
    stepOut.reward = 100; 
}
if(n_1<=0){
       stepOut.done = 0;
    stepOut.end=1;
    stepOut.reward = -100; 
}
if(is_block(team)==1){
    stepOut.done = 1;
    stepOut.end=1;
    stepOut.reward = -9;
}
if(n_1<=0){
    stepOut.done = 1;
    stepOut.end=1;
    stepOut.reward = -1000;
}if(n_3<=0){
    stepOut.done = 1;
    stepOut.end=1;
    stepOut.reward = 1000;
}


return stepOut;

}





