#ifndef __RESIZE_HH__
#define __RESIZE_HH__

#include "../include/Bitmap.hh"

/* Resize image located in bitmap (overwrites old image) to a resolution of target_w * target_h pixels */
/* Note: No interpolation is used! */
void resizeImage( cBitmap * bitmap, int target_w, int target_h );
#endif
