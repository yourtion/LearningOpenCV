//
//  imageCannyAndPyrDown.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <cv.h>
#include <highgui.h>

IplImage* doPyrDown (IplImage* in, int filter = IPL_GAUSSIAN_5x5 ) {
    assert( in->width%2 == 0 && in->height%2 == 0 );
    IplImage *out = cvCreateImage( cvSize( in->width/2, in->height/2 ), in->depth, in->nChannels);
    cvPyrDown( in, out );
    return ( out );
}

IplImage* doCanny (IplImage* in, double lowThresh, double highThresh, double aperture ) {
//    if (in->nChannels != 1) return (0);
    IplImage* out = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 1);
    cvCanny( in, out, lowThresh, highThresh, aperture);
    return ( out );
}


int main(int argc, const char * argv[]) {
    
    const char* path = argv[1];
    
    if (path == NULL) path = "icon2.png";
    
    IplImage* image = cvLoadImage( path );

    cvNamedWindow( "Example4-in" );
    cvNamedWindow( "Example4-out" );
    
    cvShowImage( "Example4-in",  image);
    
    IplImage* out = doPyrDown(image);
    out = doCanny(out, 10, 100, 3);
    
    cvShowImage( "Example4-out",  out);
    
    cvReleaseImage( &out );
    cvWaitKey(0);
    cvDestroyWindow("Example4-in");
    cvDestroyWindow("Example4-out");
}
