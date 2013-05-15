CC=g++ 
LN=g++ 
PARAM=-Wall
all:
	$(CC) $(PARAM) -c convex.cc
	$(CC) $(PARAM) -c Bitmap.cc
	$(LN) -o convex convex.o Bitmap.o -lGL -lglut
clean:
	rm *.o
