CC = g++
CCFLAGS = -g

main: main.o Board.o GameTime.o Pointer.o Map.o Item.o Snake.o SnakeGame.o
	$(CC) $(CCFLAGS) -o main main.o Board.o GameTime.o Map.o Pointer.o Item.o Snake.o SnakeGame.o -lncurses

clean:
	rm -f *.o

%.o : %.cpp %.hpp
	$(CC) $(CCFLAGS) -c $<

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $<

% : %.cpp
	$(CC) $(CCFLAGS) -o $<

