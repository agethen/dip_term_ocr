CC=g++ 
LN=g++ 
PARAM=-Wall
all:
	$(CC) $(PARAM) -c segmentation.cc
	$(CC) $(PARAM) -c ../include/viewer.cc
	$(CC) $(PARAM) -c ../include/Bitmap.cc
	$(LN) -o segmentation segmentation.o viewer.o Bitmap.o -lGL -lglut
clean:
	rm *.o
