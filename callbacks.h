// Ce fichier possède la déclarations de toutes les fonctions défines dans le callbacks.c

#pragma once 
#include <libsx.h>
#include "modele.h"



extern void SaveCB (Widget w, char *string, void *data) ;
extern void GridGame_easyCB (Widget *w,void *grid) ;
extern void GridGame_averageCB (Widget *w, void *grid) ;
extern void GridGame_highCB (Widget *w, void *grid) ;
extern void GridGame_editCB (Widget *w, void *grid) ;
extern void QuitGame(Widget *w);
extern void button_down(Widget *w, int which_button, int x, int y, void *data);
extern void ActionAfterClick(int x, int y, dim d, char *grid, char *MarkedGrid, char *FlagGrid, GameState *G);
extern void EmptyCase(int x, int y, dim d ,char *grid, char *MarkedGrid, char *FlagGrid, GameState *G);
extern void GameOver (char *grid, dim d) ;