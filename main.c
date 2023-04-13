#include <libsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "vue.h"
#include "modele.h"


int main(int argc ,char *argv[]){

    /*if (argc!=2){
        fprintf(stderr, "Usage : %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *in;
    if( (in=fopen(argv[1], "w")) == NULL){
        perror(argv[1]);
        exit(errno);
    }

    fwrite(string, 1, sizeof(string), in);

    fclose(in); */

    if(OpenDisplay(argc,argv)== 0){
        fprintf(stderr,"Can't open display\n");
        return EXIT_FAILURE ;
    }
    char *grid ;
    init_display(argc,argv,grid) ;
    ShowDisplay() ;
    MainLoop() ;
    return EXIT_SUCCESS ;

}