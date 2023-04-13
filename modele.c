/*
 * Author: Pierre SIGNING && Vincent De Sousa
 * Creation date: 4-june-2022 12:53
 * Last file update: 
*/

/* Ce fichier contient l'implémentation des fonctions appelées dans le fichier
  * data.h
  */

#include <assert.h>
#include <time.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "modele.h"
#include "vue.h"
#include "time.h"

/* Antécédent : un entier représentant le choix
  * Conséquent : Renvoie une dimension correspondante
  * Invariant : l'entier entré
  */

dim ChoiceDim(int choice){
    dim d ;
    if(choice ==1){
      d.width = M1 ;
      d.height = M1 ;
      d.mine_Number = NB_MINE1 ;
    } 
    if(choice ==2){
      d.width = M2 ;
      d.height = M2 ;
      d.mine_Number = NB_MINE2 ;
    } 
    if(choice ==3){
      d.width = MX3 ;
      d.height = MY3 ;
      d.mine_Number = NB_MINE3 ;
    } 
    return d ;
}


/* 
  * Antécédent : deux entiers non sigridnés et un flottant
  * Conséquent : Renvoie une dimension correspondante
  * Invariant : 
*/
unsigned int MineNumber(unsigned int width, unsigned int height, float mine_rate){
  
  return width*height*mine_rate ;
}


/* Antécédent : deux entiers non sigridnés et un flottant
  * Conséquent : Renvoie une dimension correspondante
  * Invariant : 
  */
dim InitDim (unsigned int width, unsigned int height, float mine_rate){
    assert((mine_rate<=0.96) && (mine_rate > 0)) ;
    assert((width>=8 && width<=60)&&(width>=8 && width<=60)) ;
    dim d ;
    d.width = width ;
    d.height = height ;
    d.mine_Number = MineNumber(width, height, mine_rate) ;
    return d ;
}

/* 
  * Antécédent : Une type Gamestate et un type dimension
  * Conséquent : Initialise les paramètres de jeu
  * Invariant : 
*/
void InitSetting (GameState *G, const dim d){

  G -> EndGame = 0 ; // Désigne la fin du jeu
  G -> OpenException = 0 ; // Désigne le décochage automatique dans le cas d'un zéro
  G ->FlagNumber = d.mine_Number ; // le nombre de drapeau disponible pour le joueur
  G ->TimeGame = 0; // Temps de jeu
}

/* 
  * Antécédent : un type Gamestate et un double
  * Conséquent : Initialise le temps de jeu du joueur
  * Invariant : 
*/
void ScoreTime(GameState *G, double time){
  G ->TimeGame = time ;
}


/* 
  * Antécédent : deux type dimensions
  * Conséquent : Renvoie un TRUE (1) si les 2 variables sont égales
  * Invariant : d1 et d2
*/
int verif(const dim d1, const dim d2) {

  if(d1.width == d2.width) {
    if(d1.height == d2.height) {
      if(d1.mine_Number == d2.mine_Number) {
        return 1 ;
      }
    }
  }
  else{ 
    return 0;
  }
}

// Antécédent : une variable de type dimension 
// Rôle : Renvoie le nombre de cellule dans la grille
unsigned int NbCase (const dim d){
  
  return (d.height) * (d.width) ;
}


//Antécedent : grille allouer dynamiquement et dimensions définies par l'utilisateur
//Rôle : initialise une grille vide (pleine de 0) à l'aide d'un pointeur sur caractère
void grilleVide(char *grid, const dim d){

    for(int i=0; i<=NbCase(d); i++){
        *(grid+i)='0';
    }
}


//Antécedent : dimensions définies et grille de jeu réalisé
//Rôle : affiche sur la sortie standard le contenue de la gridrille
void afficheGrille(const char *grid, const dim d){
  for(int i=0; i<d.width; i++){
    for(int j=0; j<d.height; j++){
      printf("%c  ",*(grid+i*d.width+j));
    }
    printf("\n");
  }
  printf("\n\n");
}

//Antécedent : dimensions définies et grille vide initialisée
//Rôle : initialise les emplacements aléatoire des bombes sur la gridrille
void grilleDeMine(char *grid, const int nb_m){
  int k=0, rang;
    
  while(k!=nb_m+1){
    rang=rand()%(strlen(grid)-1); 
    printf("rang: %d\n",rang);
    *(grid+rang)='M';
    k++;
  }

}

//Antécedent : dimensions définies et grille de bombe initialisée
//Rôle : initialise autour des emplacements des bombes les coefficients de proximité
char *mineProche(char *grid, const dim d){

    unsigned int taille = NbCase(d) ;
    for(int i=0; i<=taille; i++){
        if(*(grid+i)=='M'){
            //Partie gridauche de la gridrille
            if((i%d.width)==0){

                //Case en haut à gridauche de la gridrille
                if(i==0){
                    //(condition) ? instruction si vrai : instruction si faux
                    if (*(grid+i+1)!='M') (*(grid+i+1))++ ; 
                    if (*(grid+i+d.width)!='M') (*(grid+i+d.width))++ ;
                    if (*(grid+i+d.width+1)!='M') (*(grid+i+d.width+1))++ ;
                }

                //Case en bas à gridauche de la gridrille
                else if(i==taille-d.width){
                    
                    if (*(grid+i-d.width)!='M') (*(grid+i-d.width))++ ;
                    if (*(grid+i-d.width+1)!='M') (*(grid+i-d.width+1))++ ;
                    if (*(grid+i+1)!='M') (*(grid+i+1))++ ;
                }

                //Le reste des cases à gridauche de la gridrille
                else{
                    if (*(grid+i-d.width)!='M') (*(grid+i-d.width))++ ;
                    if (*(grid+i-d.width+1)!='M') (*(grid+i-d.width+1))++ ;
                    if (*(grid+i+1)!='M') (*(grid+i+1))++ ;
                    if (*(grid+i+d.width)!='M') (*(grid+i+d.width))++ ;
                    if (*(grid+i+d.width+1)!='M') (*(grid+i+d.width+1))++ ;
                }
            }

            //Partie droite de la gridrille
            else if(((i%(d.width))==d.width-1)){

                //Case en haut à droite de la gridrille
                if(i==d.width-1){
                    if (*(grid+i-1)!='M') (*(grid+i-1))++ ;
                    if (*(grid+i+d.width-1)!='M') (*(grid+i+d.width-1))++ ;
                    if (*(grid+i+d.width)!='M') (*(grid+i+d.width))++ ;
                }

                //Case en bas à droite de la gridrille
                else if(i==NbCase(d)-1){
                    if (*(grid+i-d.width-1)!='M') (*(grid+i-d.width-1))++ ;
                    if (*(grid+i-d.width)!='M') (*(grid+i-d.width))++ ;
                    if (*(grid+i-1)!='M') (*(grid+i-1))++ ;
                }

                //Le reste des cases à droite de la gridrille
                else{
                    if (*(grid+i-d.width-1)!='M') (*(grid+i-d.width-1))++ ;
                    if (*(grid+i-d.width)!='M') (*(grid+i-d.width))++ ;
                    if (*(grid+i-1)!='M') (*(grid+i-1))++ ;
                    if (*(grid+i+d.width-1)!='M') (*(grid+i+d.width-1))++ ;
                    if (*(grid+i+d.width)!='M') (*(grid+i+d.width))++ ;
                }

            }

            //Partie supérieur de la gridrille sans les coins
            else if(i>=1 && i<=d.width){
                if (*(grid+i-1)!='M') (*(grid+i-1))++ ;
                if (*(grid+i+1)!='M') (*(grid+i+1))++ ;
                if (*(grid+i+d.width-1)!='M') (*(grid+i+d.width-1))++ ;
                if (*(grid+i+d.width)!='M') (*(grid+i+d.width))++ ;
                if (*(grid+i+d.width+1)!='M') (*(grid+i+d.width+1))++ ;
            }

            //Partie inférieur de la gridrille sans les coins
            else if(i>=NbCase(d)-d.width+1 && i<=NbCase(d)-2){
                if (*(grid+i-d.width-1)!='M') (*(grid+i-d.width-1))++ ;
                if (*(grid+i-d.width)!='M') (*(grid+i-d.width))++ ;
                if (*(grid+i-d.width+1)!='M') (*(grid+i-d.width+1))++ ;
                if (*(grid+i-1)!='M') (*(grid+i-1))++ ;
                if (*(grid+i+1)!='M') (*(grid+i+1))++ ;
            }

            //Partie centrale de la gridrille
            else{
                if (*(grid+i-d.width-1)!='M') (*(grid+i-d.width-1))++ ;
                if (*(grid+i-d.width)!='M') (*(grid+i-d.width))++ ;
                if (*(grid+i-d.width+1)!='M') (*(grid+i-d.width+1))++ ;
                if (*(grid+i-1)!='M') (*(grid+i-1))++ ;
                if (*(grid+i+1)!='M') (*(grid+i+1))++ ;
                if (*(grid+i+d.width-1)!='M') (*(grid+i+d.width-1))++ ;
                if (*(grid+i+d.width)!='M') (*(grid+i+d.width))++ ;
                if (*(grid+i+d.width+1)!='M') (*(grid+i+d.width+1))++ ;
            }
        }
    }
    return grid;
}


//Antécédent : Grille de mines avec les coefficients initialisée
//Rôle : Créer une deuxième grille qu'on va superposer avec libsx
/*void couvrirCase(char *grid2, const dim d){
    for(int i=0; i<NbCase(d)+1; i++){
        *(grid2+i)='|';
    }
}*/


void Username(char *string){
    return string;
}

unsigned int CaseSize (const dim d){
  if(verif(d, ChoiceDim(1))) return 8*TX ;
  if(verif(d, ChoiceDim(2))) return 4*TX ;
  if(verif(d, ChoiceDim(3))) return 2*TX ;
}
