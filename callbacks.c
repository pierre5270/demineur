#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "callbacks.h"
#include "modele.h"
#include "vue.h"

// le pointeur représentant notre grille
char *g;

// Le pointeur représentant les cases cochées durant le jeu
// Ainsi on aura un 1 à la position cochée et 0 sinon
char *MarkedGrid ;

// Le pointeur représentant les cases sur lesquels on a mis des drapeaux
char *FlagGrid ;

//Dimensions de la grille
dim d;

// Type Gamestate pour les paramètres de jeu
GameState *G ;

/* 
  * Antécédent : Un widget et une donnée void
  * Conséquent : Renvoie l'affichage de la grille de jeu du mode facile
  * Invariant : 
*/
void GridGame_easyCB(Widget * w, void *grid ){
    d = ChoiceDim(1) ;
    grid  = malloc(NbCase(d)*sizeof(char)) ;
    MarkedGrid = malloc(NbCase(d)*sizeof(char)) ;
    FlagGrid = malloc(NbCase(d)*sizeof(char)) ;
    InitSetting(&G, d) ;
    grilleVide(grid, d) ;
    grilleVide(MarkedGrid, d) ;
    grilleVide(FlagGrid, d) ;
    grilleDeMine(grid, d.mine_Number) ;
    g=mineProche(grid, d) ;
    DrawGrille(grid, d) ;
    
}

/* 
  * Antécédent : Un widget et une donnée void
  * Conséquent : Renvoie l'affichage de la grille de jeu du mode moyen
  * Invariant : 
*/
void GridGame_averageCB(Widget * w, void *grid ){
    d = ChoiceDim(2) ;
    grid  = malloc(NbCase(d)*sizeof(char)) ;
    MarkedGrid = malloc(NbCase(d)*sizeof(char)) ;
    FlagGrid = malloc(NbCase(d)*sizeof(char)) ;
    InitSetting(&G, d) ;
    grilleVide(grid, d) ;
    grilleVide(MarkedGrid, d) ;
    grilleVide(FlagGrid, d) ;
    grilleDeMine(grid, d.mine_Number) ;
    g=mineProche(grid, d) ;
    DrawGrille(grid, d) ;

}

/* 
  * Antécédent : Un widget et une donnée void
  * Conséquent : Renvoie l'affichage de la grille de jeu du mode difficile
  * Invariant : 
*/
void GridGame_highCB(Widget * w, void *grid ){
    d = ChoiceDim(3) ;
    grid  = malloc(NbCase(d)*sizeof(char)) ;
    MarkedGrid = malloc(NbCase(d)*sizeof(char)) ;
    FlagGrid = malloc(NbCase(d)*sizeof(char)) ;
    InitSetting(&G, d) ;
    grilleVide(grid, d) ;
    grilleVide(MarkedGrid, d) ;
    grilleVide(FlagGrid, d) ;
    grilleDeMine(grid, d.mine_Number) ;
    g=mineProche(grid, d) ;
    DrawGrille(grid, d) ;
}

/* 
  * Antécédent : Un widget et une donnée void
  * Conséquent : Renvoie l'affichage de la grille de jeu du mode personnalisable
  * Invariant : 
*/
void GridGame_editCB (Widget *w, void *grid){
    d = ChoiceDim(1) ;
    grid  = malloc(NbCase(d)*sizeof(char)) ;
    MarkedGrid = malloc(NbCase(d)*sizeof(char)) ;
    FlagGrid = malloc(NbCase(d)*sizeof(char)) ;
    InitSetting(&G, d) ;
    grilleVide(grid, d) ;
    grilleVide(MarkedGrid, d) ;
    grilleVide(FlagGrid, d) ;
    grilleDeMine(grid, d.mine_Number) ;
    g=mineProche(grid, d) ;
    DrawGrille(grid, d) ;
    GetOkay("Ce mode de jeu est en cours de developpement - Mode Facile Active") ;
}

/* 
  * Antécédent : Un widget
  * Conséquent : Permet de quitter la fenêtre de jeu
  * Invariant : 
*/
void QuitGame(Widget *w){
    //Fin de programme 
    CloseWindow();
}

/* 
  * Antécédent : Un widget, trois entiers dont l'un désignant le clic
  02 déterminants des coordonnées et une donnée
  * Conséquent : lance l'affichage de la case en fonction du lieu du clic 
  * Invariant : 
*/
void button_down(Widget *w, int which_button, int x, int y, void *data){
    printf("You clicked button %d at (%d,%d)\n", which_button, x,y);

    if(which_button == 1){
        SetColor(GetNamedColor("black")) ;
        ActionAfterClick(x,y,d,g,MarkedGrid,FlagGrid,&G) ;
    }
}

/* 
  * Antécédent : Un pointeur sur caractère et un type dimension
  * Conséquent : Renvoie sur l'affichage de la grille de jeu les mines 
  * Invariant : 
*/
void GameOver (char *grid, dim d){

    int rang = 0 ;
    int count = 0 ;
    char *value=calloc(1,sizeof(char));
    unsigned int Box = CaseSize (d) ;
    SetColor(GetNamedColor("red")) ; // Attribuons une couleur vive aux mines
    for(int i=0 ; i<GRID_Y; i=i+Box){
        for(int j=0 ; j<GRID_X; j=j+Box){
            *value=*(grid+rang);
            if(*value== 'M'){

                DrawFilledBox(0.25*Box+i, 0.25*Box+j, 0.5*Box, 0.5*Box) ;
                DrawText(value,(2*i+Box)/2, (2*j+Box)/2) ;
                count ++ ;
                }
            rang++ ;
            }
        }
}

/* 
  * Antécédent : Tous les paramètres du programme
  * Conséquent : Effectue l'affichage récurrentielle de toutes les cases n'ayant pas un M autour de celle 
  * qui possède une case vide
  * Invariant : 
*/

void EmptyCase(int x, int y, dim d ,char *grid, char *MarkedGrid, char *FlagGrid, GameState *G){

    unsigned int Box = CaseSize (d) ;

    if(x>=Box) {

        ActionAfterClick(x-Box, y, d, grid, MarkedGrid, FlagGrid, &G); 
    }
    if(x>=Box && y>=Box){
    
        ActionAfterClick(x-Box, y-Box, d, grid, MarkedGrid, FlagGrid, &G);
    }
    if(y>=Box) {
    
        ActionAfterClick(x, y-Box, d, grid, MarkedGrid, FlagGrid, &G);
    }
    if(y>=Box && x<GRID_X-Box) {
    
        ActionAfterClick(x+Box, y-Box, d, grid, MarkedGrid, FlagGrid, &G);
    }
    if(x<GRID_X -Box) {
    
        ActionAfterClick(x+Box, y, d, grid, MarkedGrid, FlagGrid, &G);
    }
    if(x<GRID_X - Box && y<GRID_Y - Box) {
    
        ActionAfterClick(x+Box, x+Box, d, grid, MarkedGrid, FlagGrid, &G);
    }
    if(y<GRID_Y-Box) {
    
        ActionAfterClick(x, y+Box, d, grid, MarkedGrid, FlagGrid, &G);
    }
    if(x>=Box && y<GRID_Y-Box) {
    
        ActionAfterClick(x-Box, y+Box, d, grid, MarkedGrid, FlagGrid, &G);
    }


}


//Récupère le nom de l'utilisateur dans un fichier 
void SaveCB(Widget w, char *string, void *data){
    
}


