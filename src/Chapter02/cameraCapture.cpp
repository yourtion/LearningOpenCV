//
//  main.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>

int main(int argc, const char * argv[]) {
    CvCapture* capture = cvCreateCameraCapture(0);
    cvNamedWindow("Example5", CV_WINDOW_AUTOSIZE);
    IplImage* frame;
    while (1) {
        frame = cvQueryFrame( capture );
        if (!frame) break;
        cvShowImage( "Example5", frame );
        char c = cvWaitKey(33);
        if ( c == 27 ) break;
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Example5" );
}
