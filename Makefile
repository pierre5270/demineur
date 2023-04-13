CC = gcc 
EXEC= Demineur 
#on creer une variable pour gcc comme cela si un jour on souhaite 
#changer de compilateur, on aura tous simplement qu'à modifier le contenu 
#de la variables



all : $(EXEC)

Demineur : main.o modele.o callbacks.o vue.o
	$(CC) -Wall -g -lsx -o $(EXEC) main.o modele.o callbacks.o vue.o
	

main.o : main.c
	$(CC) -Wall -g -lsx -o main.o -c main.c 


vue.o : vue.c
	$(CC) -Wall -g -lsx -o vue.o -c vue.c 

callbacks.o : callbacks.c 
	$(CC) -Wall -g -lsx -o callbacks.o -c callbacks.c


modele.o : modele.c
	$(CC) -Wall -g -lsx -o modele.o -c modele.c 

clean:
	rm -rf *-o   

mrproper: clean 
	rm -rf Demineur

#Variables spéciales  
#$@ vaut le nom de la cible
#$c nom de la premiere dépendance
#$^ liste de dépendance
#$? liste de dépendances plus récentes que la cible
#$* nom fichier, sans extensio