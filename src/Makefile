CC=g++ 
LN=g++ 
PARAM=-Wall
all:
	$(CC) $(PARAM) -c main.cc
	$(CC) $(PARAM) -c Segmentation/segmentation.cc
	$(CC) $(PARAM) -c Preprocessing/resize.cc
	$(CC) $(PARAM) -c Features/circularity.cc
	$(CC) $(PARAM) -c Features/dummy_feature.cc
	$(CC) $(PARAM) -c Features/euler.cc	
	$(CC) $(PARAM) -c Features/geometry.cc
	$(CC) $(PARAM) -c Features/shapeContexts.cc
	$(CC) $(PARAM) -c Features/subcomponents.cc
	$(CC) $(PARAM) -c Decision/decision_clustering.cc
	$(CC) $(PARAM) -c include/viewer.cc
	$(CC) $(PARAM) -c include/boundary.cc
	$(CC) $(PARAM) -c include/Bitmap.cc
	$(LN) -o main main.o segmentation.o resize.o circularity.o dummy_feature.o euler.o geometry.o shapeContexts.o subcomponents.o decision_clustering.o viewer.o boundary.o Bitmap.o -lGL -lglut
apple:
	$(CC) $(PARAM) -c main.cc
	$(CC) $(PARAM) -c Segmentation/segmentation.cc
	$(CC) $(PARAM) -c Preprocessing/resize.cc
	$(CC) $(PARAM) -c Features/circularity.cc
	$(CC) $(PARAM) -c Features/dummy_feature.cc
	$(CC) $(PARAM) -c Features/euler.cc	
	$(CC) $(PARAM) -c Features/geometry.cc
	$(CC) $(PARAM) -c Features/shapeContexts.cc
	$(CC) $(PARAM) -c Features/subcomponents.cc
	$(CC) $(PARAM) -c Decision/decision_clustering.cc
	$(CC) $(PARAM) -c include/viewer.cc
	$(CC) $(PARAM) -c include/boundary.cc
	$(CC) $(PARAM) -c include/Bitmap.cc
	$(LN) -o main main.o segmentation.o resize.o circularity.o dummy_feature.o euler.o geometry.o shapeContexts.o subcomponents.o decision_clustering.o viewer.o boundary.o Bitmap.o -framework GLUT -framework OpenGL

clean:
	rm *.o
