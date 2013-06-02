CC=g++ 
LN=g++ 
PARAM=-Wall
all:
	$(CC) $(PARAM) -c convex.cc
	$(CC) $(PARAM) -c ../include/Bitmap.cc
	$(CC) $(PARAM) -c ../include/viewer.cc
	$(LN) -o convex convex.o Bitmap.o viewer.o -lGL -lglut
clean:
	rm *.o
