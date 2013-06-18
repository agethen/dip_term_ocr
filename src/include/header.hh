#ifndef __HEADER_HH__
#define __HEADER_HH__

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#include "Bitmap.hh"
#include "boundary.hh"
#include "viewer.hh"

#include "../Decision/decision_clustering.hh"
#include "../Segmentation/segmentation.hh"

#include "../Features/circularity.hh"
#include "../Features/dummy_feature.hh"
#include "../Features/euler.hh"
#include "../Features/geometry.hh"
#include "../Features/shapeContexts.hh"
#include "../Features/subcomponents.hh"
#include "../Features/BaysLakes.hh"

#include "../Preprocessing/resize.hh"


#ifdef __MACOS__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


#define NUM_BINS 5

using namespace std;

#endif
