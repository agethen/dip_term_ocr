CC=g++ 
LN=g++ 
PARAM=-Wall -g
all:
	$(CC) $(PARAM) -c main.cc
	$(CC) $(PARAM) -c Segmentation/segmentation.cc
	$(CC) $(PARAM) -c Preprocessing/resize.cc
	$(CC) $(PARAM) -c Features/circularity.cc
	$(CC) $(PARAM) -c Features/dummy_feature.cc
	$(CC) $(PARAM) -c Features/euler.cc	
	$(CC) $(PARAM) -c Features/geometry.cc
	$(CC) $(PARAM) -c Features/shapeContexts.cc
	$(CC) $(PARAM) -c Decision/decision_clustering.cc
	$(CC) $(PARAM) -c include/viewer.cc
	$(CC) $(PARAM) -c include/Bitmap.cc
	$(LN) -o main main.o segmentation.o resize.o circularity.o dummy_feature.o euler.o geometry.o shapeContexts.o decision_clustering.o viewer.o Bitmap.o -lGL -lglut
clean:
	rm *.o
