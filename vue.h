
#define GRID_X 640
#define GRID_Y 640

#define TBOX_X 40
#define TBOX_Y 20

#define TX 10
#define TY 10
#define SCREENVIEW GRID_X/2

// Cette fonction Renvoie l'affichage de notre programme
extern void init_display (int argc, char *argv[], char *grid) ;

// Designe la grille en fonction de nos dimensions
extern void DrawGrille(char *grid, dim d) ;