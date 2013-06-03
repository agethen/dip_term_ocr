CC=g++ 
LN=g++ 
PARAM=-Wall
all:
	$(CC) $(PARAM) -c main.cc
	$(CC) $(PARAM) -c Segmentation/segmentation.cc
	$(CC) $(PARAM) -c Features/dummy_feature.cc
	$(CC) $(PARAM) -c Features/euler.cc
	$(CC) $(PARAM) -c Decision/decision_clustering.cc
	$(CC) $(PARAM) -c include/viewer.cc
	$(CC) $(PARAM) -c include/Bitmap.cc
	$(LN) -o main main.o segmentation.o dummy_feature.o euler.o decision_clustering.o viewer.o Bitmap.o -lGL -lglut
clean:
	rm *.o
