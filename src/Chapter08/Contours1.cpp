//
//  Contours.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

IplImage* g_image = NULL;
IplImage* g_gray = NULL;
int g_thresh = 100;
CvMemStorage* g_storage = NULL;

void on_trackbar(int) {
    if ( g_storage == NULL ) {
        g_gray = cvCreateImage( cvGetSize(g_image), 8, 1);
        g_storage = cvCreateMemStorage( 0 );
    } else {
        cvClearMemStorage( g_storage );
    }
    CvSeq* contours = 0;
    cvCvtColor( g_image, g_gray, CV_BGR2GRAY );
    cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_BINARY );
    cvFindContours( g_gray, g_storage, &contours );
    cvSetZero( g_gray );
    if ( contours ) {
        cvDrawContours( g_gray, contours, cvScalarAll(255), cvScalarAll(255), 100);
        cvShowImage( "Contours", g_gray );
    }
}

int main(int argc, const char * argv[]) {
    
    if (argc == 2 && ((g_image = cvLoadImage(argv[1], 1)) != 0)) {
        cvNamedWindow( "Contours" );
        cvCreateTrackbar( "Threshold", "Contours", &g_thresh, 100,on_trackbar );
        on_trackbar(0);
        
        cvWaitKey();

        cvReleaseImage( &g_image );
        cvReleaseImage( &g_gray );
        cvReleaseMemStorage( &g_storage );
        cvDestroyWindow( "Contours" );

    }
    
    return 0;
}
