#MAKE SURE YOUR CODE COMPILES WITH THESE FLAGS!
#WARNINGS = NO COMPILE = ZERO!
#also can add to the list of flags if you so desire. At your own risk. 
CFLAGS = -g -Wall -Werror

#add what you need to make HW3 get compiled. IT IS YOUR RESPONSIBILITY TO 
#MAKE SURE EVERYTHING GETS IN THE COMPILATION. 
#Depending on your choice of implementation, change what you need to change. 

#Getting this to work is probably the hardest part of HW3. Use your 
#resources to figure out how this thing works. 
all: Gauntlet

Gauntlet: game.o shop.o heroes.o io.o  
	gcc $^ -g -o Gauntlet

%.o: %.c game.h
	gcc $< -c $(CFLAGS) -o $@

clean:
	rm -f *.o Gauntlet
