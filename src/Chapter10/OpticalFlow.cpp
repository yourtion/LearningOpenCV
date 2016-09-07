//
//  OpticalFlow.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

#define CVX_RED CV_RGB( 0xff, 0x00, 0x00 )
#define CVX_BLUE CV_RGB( 0x00, 0x00, 0xff )
#define CVX_GREEN CV_RGB( 0x00, 0xff, 0x00 )

const int MAX_CORNERS = 500;

int main(int argc, const char * argv[]) {
    
    IplImage* imgA = cvLoadImage( "data/OpticalFlow0.jpg", CV_LOAD_IMAGE_GRAYSCALE );
    IplImage* imgB = cvLoadImage( "data/OpticalFlow1.jpg", CV_LOAD_IMAGE_GRAYSCALE );
    
    CvSize img_sz = cvGetSize( imgA );
    int win_size = 10;
    
    IplImage* imgC = cvLoadImage( "data/OpticalFlow1.jpg", CV_LOAD_IMAGE_UNCHANGED );
    
    IplImage* image_eig = cvCreateImage( img_sz, IPL_DEPTH_32F, 1 );
    IplImage* image_tmp = cvCreateImage( img_sz, IPL_DEPTH_32F, 1 );
    
    int corner_count = MAX_CORNERS;
    CvPoint2D32f* cornersA = new CvPoint2D32f[ MAX_CORNERS ];
    CvPoint2D32f* cornersB = new CvPoint2D32f[ MAX_CORNERS ];
    
    cvGoodFeaturesToTrack( imgA, image_eig, image_tmp, cornersA, &corner_count, 0.01, 5.0, 0, 3, 0, 0.04 );
    
    cvFindCornerSubPix(
                       imgA,
                       cornersA,
                       corner_count,
                       cvSize(win_size, win_size),
                       cvSize(-1, -1),
                       cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20.0, 0.03)
                       );
    
    char features_found[ MAX_CORNERS ];
    float feature_errors[ MAX_CORNERS ];
    
    CvSize pyr_sz = cvSize( imgA->width+8, imgB->height/3 );
    
    IplImage* pyrA = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
    IplImage* pyrB = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
    
    cvCalcOpticalFlowPyrLK(imgA,
                           imgB,
                           pyrA,
                           pyrB,
                           cornersA,
                           cornersB,
                           corner_count,
                           cvSize(win_size, win_size),
                           5,
                           features_found,
                           feature_errors,
                           cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20.0, 0.3),
                           0
                           );
    
    for( int i=0; i<corner_count; i++ ) {
        if( features_found[i]==0|| feature_errors[i]>550 ) {
            printf("Error is %f\n",feature_errors[i]);
            continue;
        }
        CvPoint p0 = cvPoint(
                             cvRound( cornersA[i].x ),
                             cvRound( cornersA[i].y )
                             );
        CvPoint p1 = cvPoint(
                             cvRound( cornersB[i].x ),
                             cvRound( cornersB[i].y )
                             );
        
        cvLine( imgC, p0, p1, CV_RGB(255,0,0),2 );
    }
    cvNamedWindow("ImageA",0);
    cvNamedWindow("ImageB",0);
    cvNamedWindow("LKpyr_OpticalFlow",0);
    cvShowImage("ImageA",imgA);
    cvShowImage("ImageB",imgB);
    cvShowImage("LKpyr_OpticalFlow",imgC);
    cvWaitKey(0);
    
    return 0;

}
