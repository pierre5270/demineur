/*Ce fichier est celui comportant les données utilisées pour l'élaboration 
  de l'application */
#pragma once 


//Dimension de la grille pour un niveau facile
#define M1 8
#define NB_MINE1 10

//Dimension de la grille pour un niveau moyen
#define M2 16
#define NB_MINE2 40

// Dimension de la grille pour un niveau difficile
#define MX3 32
#define MY3 32
#define NB_MINE3 99

//Taux maximal de mines possible sur une grille
#define MINE_RATE_MAX 0.96



//Structure définissant la dimension d'une grille
typedef struct {
    
  unsigned int width ; // la largeur de la grille
  unsigned int height ; // la longueur de la grille
  unsigned int mine_Number ; // Nombre de mine de la grille
}dim ;

typedef struct {

  unsigned int GameResume ; // signalant si une partie est en cours ou pas
  unsigned int EndGame ; // Indiquant si l'on est à la fin du jeu 
  unsigned int OpenException ; // exception d'ouverture pour l'effet générique de la cellule zéro
  unsigned int FlagNumber ; // Désignant le nombre de drapeau disponible pour le joueur
  unsigned long TimeGame ; // Le temps de jeu di joueur

} GameState ;

/* Dimension des 03 modes de jeu standard :
  * Dimension facile
  * Dimension moyenne
  * Dimension grande
*/




/* La variable caractère de type pointeur représentant
  *notre grille
*/

// Fonction attribuant le choix de dimension de la grille
extern dim ChoiceDim(int choice) ;

//Fonction effectuant la comparaison entre 2 dimensions
extern int verif(const dim d1, const dim d2) ;

//Fonction initialisant la dimension de la grille
extern dim InitDim (unsigned int , unsigned int , float ) ;

//Fonction déterminant le nombre de mines de la grille 
extern unsigned int MineNumber(unsigned int , unsigned int , float ) ;

// Renvoie le nombre total de cases de la grille
extern unsigned int NbCase (const dim d ) ;

//Génère une grille vide
extern void grilleVide(char *, const dim ) ;

//Initialise les paramètres de la partie
extern void InitSetting (GameState *G, const dim d) ;

//Affiche les éléments de la grille
extern void afficheGrille(const char *, const dim ) ;

// Attribue aléatoirement des mines sur la grille
extern void grilleDeMine(char *, int ) ; 

// Attribue le nombre de mines proches d'une case
extern char *mineProche(char *, dim ) ;

//Renvoie le timing de jeu du score
extern void ScoreTime(GameState *G, double time) ;

//Récupère le nom du joueur
extern void Username(char *string);
