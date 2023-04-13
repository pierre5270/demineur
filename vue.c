// Ce fichier C désigne le programme vu par l'utilisateur

#include <stdio.h>
#include <stdlib.h>
#include "callbacks.h"
#include "modele.h"
#include "vue.h"

Widget Game, Exit;

/* 
  * Antécédent : le nombre d'arguments et le pointeur représentant la grille
  * Conséquent : Renvoie un aspect visuel du programme avec les différents menus
  * Invariant : 
*/
void init_display (int argc, char *argv[], char *grid){

    Widget BEasyMode,BAverageMode,BHighMode,BCustomMode ; 
    Widget Title,EnterName,BValidate, Restart;
    char *player ;
    /*Définition des widgets */
    
    //Entête de fenếtre
    Title = MakeLabel("Demineur ") ;

    //Zone de texte pour nom de joueur et validation
    EnterName = MakeStringEntry ("Entrez votre Nom" ,SCREENVIEW  ,NULL ,NULL) ;
    BValidate = MakeButton (" Ok " , SaveCB , player) ;
    //Restart = MakeButton("Restart", RedisplayCB,NULL) ;

    //Mode de Jeu 
    BEasyMode = MakeButton (" 8 x 8 \n 10 mines " , GridGame_easyCB , grid) ;
    BAverageMode = MakeButton (" 16 x 16 \n 40 mines " , GridGame_averageCB , grid) ;
    BHighMode = MakeButton (" 32 x 32 \n 99 mines " , GridGame_highCB , grid) ;
    BCustomMode = MakeButton (" personnaliser ",GridGame_editCB,NULL) ;

    //Fin de jeu
    Exit = MakeButton("Quitter", QuitGame, NULL);

    /*Positionnement des widgets */
    
    SetWidgetSize(Title, TBOX_X, TBOX_Y) ;
    SetBorderColor(Title, RED) ;


    SetWidgetPos(EnterName, PLACE_UNDER, Title, NO_CARE, NULL) ;
    SetWidgetSize(EnterName, SCREENVIEW, 1.6*TBOX_Y) ;
    SetWidgetPos(BValidate, PLACE_RIGHT, EnterName, PLACE_UNDER,Title) ;
    SetWidgetSize(BValidate, TBOX_X, 1.6*TBOX_Y) ;

    SetWidgetPos(BEasyMode, PLACE_UNDER, EnterName, NO_CARE, NULL) ;
    SetWidgetSize(BEasyMode, TBOX_X, 2*TBOX_Y) ;

    SetWidgetPos(BAverageMode,PLACE_UNDER,EnterName ,PLACE_RIGHT,BEasyMode) ;
    AttachEdge(BAverageMode,LEFT_EDGE,ATTACH_TOP) ;
    SetWidgetSize(BAverageMode, TBOX_X, 2*TBOX_Y) ;

    SetWidgetPos(BHighMode, PLACE_UNDER, EnterName, PLACE_RIGHT, BAverageMode) ;
    SetWidgetSize(BHighMode, TBOX_X, 2*TBOX_Y) ;

    SetWidgetPos(BCustomMode, PLACE_UNDER, EnterName, PLACE_RIGHT, BHighMode) ;
    AttachEdge(BCustomMode,LEFT_EDGE,ATTACH_LEFT) ;
    SetWidgetSize(BCustomMode, TBOX_X, 2*TBOX_Y) ;

    SetWidgetPos(Exit, PLACE_UNDER, EnterName, PLACE_RIGHT, BCustomMode) ;
    SetWidgetSize(Exit, TBOX_X, 2*TBOX_Y) ;

    
    Game = MakeDrawArea(GRID_X,GRID_Y,NULL,NULL);
    SetWidgetPos(Game, PLACE_UNDER, BCustomMode, NO_CARE, NULL) ;
    
    ShowDisplay(); // pour afficher l'interface et son contenu
    SetButtonDownCB(Game,button_down) ;
}

/* 
  * Antécédent : Le pointeur de type caractère et un type dim
  * Conséquent : Renvoie en sortie une grille 
  * Invariant : 
*/
void DrawGrille(char *grid, dim d){

    unsigned int Box = CaseSize (d) ;
    ClearDrawArea();
    SetColor(GetNamedColor("black"));
    for(int i=0 ; i<d.width ; i++){
        for(int j=0 ; j<d.height ;j++){ 
            DrawBox(i*Box, j*Box,Box,Box) ;

        }
    }
}


// Faire le traitement de données ici 
// Attention : pas d'appel de fonction de libsx dans le callbacks 
void ActionAfterClick(int x, int y, dim d, char *grid, char *MarkedGrid, char *FlagGrid, GameState *G){
    
    //afficheGrille(grid, d) ;
    int rang=0;
    char *value=calloc(1,sizeof(char));
    //printf("x:%d y:%d",x,y);

    //Cas ou grille 12x12

    if(verif(ChoiceDim(1),d)){
        for(int i=0 ; i<GRID_Y; i=i+8*TY){
            for(int j=0 ; j<GRID_X; j=j+8*TX){
                if((x>=i)&&(x<i+8*TX)){
                    if((y>=j)&&(y<j+8*TY)){
                        *value = *(grid+rang) ;
                        printf("%c %c \n",*value,*(MarkedGrid+rang) ) ;
                        if(*value == 'M' && (G->OpenException == 0)){
                            SetColor(GetNamedColor("red")) ;
            
                            GameOver(grid,d) ;
                            GetOkay("Game Over !!") ;
                            free(grid);
                            free(MarkedGrid);
                            free(FlagGrid);
                            
                        }
                        if(*value!= 'M' && *value != '0' ){
                            SetColor(GetNamedColor("gray")) ;
                            DrawFilledBox(i+2*TX,j+2*TX,4*TX,4*TY) ;
                            DrawText(value, (2*i+8*TX)/2, (2*j+8*TY)/2);
                            *(MarkedGrid+rang) = '1' ;
                            
                        }
                        if((*value == '0') && (*(MarkedGrid+rang) == '0')){
                            *(MarkedGrid+rang) = '1' ;
                            G->OpenException = 1 ;
                            SetColor(GetNamedColor("gray")) ;
                            DrawFilledBox(i+2*TX,j+2*TX,4*TX,4*TY) ;
                            DrawText("", (2*i+8*TY)/2, (2*j+8*TX)/2);
                            EmptyCase(x,y,d,grid,MarkedGrid,FlagGrid, &G) ;
                            G->OpenException = 0 ;
                        }
                        
                    }

                }
                rang++ ;
            }
        }
    }

    //Cas ou grille 16x16
    if(verif(ChoiceDim(2),d)){
        for(int i=0 ; i<GRID_Y; i=i+4*TY){
            for(int j=0 ; j<GRID_X; j=j+4*TX){
                if((x>=i)&&(x<i+4*TX)){
                    if((y>=j)&&(y<j+4*TY)){
                        *value=*(grid+rang);
                        if(*value == 'M' && (G->OpenException == 0)){
                            SetColor(GetNamedColor("red")) ;
                            
                            GameOver(grid,d) ;
                            GetOkay("Game Over !!") ;
                            free(grid);
                            free(MarkedGrid);
                            free(FlagGrid);

                        }
                        if(*value!= 'M' && *value != '0'){
                            SetColor(GetNamedColor("gray")) ;
                            DrawFilledBox(i+TX,j+TX,2*TX,2*TY) ;
                            DrawText(value, (2*i+4*TX)/2, (2*j+4*TY)/2);
                            *(MarkedGrid+rang) = '1' ;
                        }
                        if((*value == '0') && (*(MarkedGrid+rang) == '0') ){
                            *(MarkedGrid+rang) = '1' ;
                            G->OpenException = 1 ;
                            SetColor(GetNamedColor("gray")) ;
                            DrawFilledBox(i+TX,j+TX,2*TX,2*TY) ;
                            DrawText(value, (2*i+4*TX)/2, (2*j+4*TY)/2);
                            EmptyCase(x,y,d,grid,MarkedGrid,FlagGrid, &G) ;
                            G->OpenException = 0 ;
                        }
                    }
                }
                rang++;
            }
        }
    }


    //Cas ou grille 32x32
    if(verif(ChoiceDim(3),d)){
        for(int i=0 ; i<GRID_Y; i=i+2*TY){
            for(int j=0 ; j<GRID_X; j=j+2*TX){ 
                if((x>=i)&&(x<i+2*TX)){
                    if((y>=j)&&(y<j+2*TY)){
                        *value=*(grid+rang);
                        if(*value == 'M' && (G->OpenException == 0)){
                            SetColor(GetNamedColor("red")) ;
                            DrawFilledBox(i+TX/2,j+TX/2,TX,TY) ;
                            GameOver(grid, d) ;
                            GetOkay("Game Over !!") ;
                            free(grid);
                            free(MarkedGrid);
                            free(FlagGrid);

                        }
                        if(*value!= 'M' && *value != '0'){
                            //SetColor(GetNamedColor("gray")) ;
                            DrawFilledBox(i+TX/2,j+TX/2,TX,TY) ;
                            DrawText(value, (2*i+2*TX)/2, (2*j+2*TY)/2);
                            
                        }
                        if((*value == '0') && (*(MarkedGrid+rang) == '0') ){
                            *(MarkedGrid+rang) = '1' ;
                            G->OpenException = 1 ;
                            SetColor(GetNamedColor("gray")) ;
                            
                            DrawText(value, (2*i+2*TX)/2, (2*j+2*TY)/2);
                            EmptyCase(x,y,d,grid,MarkedGrid,FlagGrid, &G) ;
                            G->OpenException = 0 ;
                        }
                    }
                }
                rang++;
            }
        }
    }

    
    free(value); 
} 



