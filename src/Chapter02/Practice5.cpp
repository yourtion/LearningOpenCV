//
//  main.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

int g_slider_size =  2;

IplImage* doPyrDown (IplImage* in, int filter = IPL_GAUSSIAN_5x5 ) {
    assert( in->width%2 == 0 && in->height%2 == 0 );
    IplImage *out = cvCreateImage( cvSize( in->width/2, in->height/2 ), in->depth, in->nChannels);
    cvPyrDown( in, out );
    return ( out );
}

int main(int argc, const char * argv[]) {
    CvCapture* capture = cvCreateCameraCapture(0);
    cvNamedWindow("Practice", CV_WINDOW_AUTOSIZE);
    cvCreateTrackbar("Position", "Practice", &g_slider_size, 6);
    IplImage* frame;
    while (1) {
        frame = cvQueryFrame( capture );
        if (!frame) break;
        for ( int i = 0; i<g_slider_size; i++) {
            frame = doPyrDown(frame);
        }
        cvShowImage( "Practice", frame );
        char c = cvWaitKey(33);
        if ( c == 27 ) break;
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Practice" );
}
