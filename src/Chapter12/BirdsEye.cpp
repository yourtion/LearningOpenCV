//
//  BirdsEye.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    const char* default_args[] = {"", "12", "12", "./data/Intrinsics.xml", "./data/Distortion.xml", "./data/birdseye.jpg" };
    if (argc != 6) {
        argc = 6;
        argv = default_args;
    }
    
    int board_w = atoi(argv[1]);
    int board_h = atoi(argv[2]);
    int board_n  = board_w * board_h;
    CvSize board_sz = cvSize( board_w, board_h );
    CvMat* intrinsic = (CvMat*)cvLoad(argv[3]);
    CvMat* distortion = (CvMat*)cvLoad(argv[4]);
    IplImage *image = 0, *gray_image = 0;
    if((image = cvLoadImage(argv[5]))== 0){
        printf("Error: Couldn't load %s\n",argv[5]);
        return -1;
    }
    gray_image = cvCreateImage(cvGetSize(image),8,1);
    cvCvtColor(image, gray_image, CV_BGR2GRAY);
    
    //UNDISTORT OUR IMAGE
    IplImage* mapx = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    IplImage* mapy = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    cvInitUndistortMap( intrinsic, distortion, mapx, mapy );
    IplImage* t = cvCloneImage( image );
    cvRemap( t, image, mapx, mapy );
    
    cvNamedWindow("Checkers");
    CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
    int corner_count = 0;
    int found = cvFindChessboardCorners( image, board_sz, corners, &corner_count, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS );
    if(!found){
        printf("Couldn't aquire checkerboard on %s, only found %d of %d corners\n", argv[5],corner_count,board_n);
        return -1;
    }
    cvFindCornerSubPix(gray_image, corners, corner_count, cvSize(11,11),cvSize(-1,-1), cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1) );
    
    //GET THE IMAGE AND OBJECT POINTS:
    CvPoint2D32f objPts[4], imgPts[4];
    objPts[0].x = 0;
    objPts[0].y = 0;
    objPts[1].x = board_w-1;
    objPts[1].y = 0;
    objPts[2].x = 0;
    objPts[2].y = board_h-1;
    objPts[3].x = board_w-1;
    objPts[3].y = board_h-1;
    imgPts[0] = corners[0];
    imgPts[1] = corners[board_w-1];
    imgPts[2] = corners[(board_h-1)*board_w];
    imgPts[3] = corners[(board_h-1)*board_w + board_w-1];
    
    //DRAW THE POINTS in order: B,G,R,YELLOW
    cvCircle(image,cvPointFrom32f(imgPts[0]),9,CV_RGB(0,0,255),3);
    cvCircle(image,cvPointFrom32f(imgPts[1]),9,CV_RGB(0,255,0),3);
    cvCircle(image,cvPointFrom32f(imgPts[2]),9,CV_RGB(255,0,0),3);
    cvCircle(image,cvPointFrom32f(imgPts[3]),9,CV_RGB(255,255,0),3);
    
    //DRAW THE FOUND CHECKERBOARD
    cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
    cvShowImage( "Checkers", image );
    
    //FIND THE HOMOGRAPHY
    CvMat *H = cvCreateMat( 3, 3, CV_32F);
    cvGetPerspectiveTransform(objPts,imgPts,H);

    //LET THE USER ADJUST THE Z HEIGHT OF THE VIEW
    float Z = 25;
    int key = 0;
    IplImage *birds_image = cvCloneImage(image);
    cvNamedWindow("Birds_Eye");
    while(key != 27) {//escape key stops
        CV_MAT_ELEM(*H,float,2,2) = Z;
        //USE HOMOGRAPHY TO REMAP THE VIEW
        cvWarpPerspective( image,birds_image, H, CV_INTER_LINEAR+CV_WARP_INVERSE_MAP+CV_WARP_FILL_OUTLIERS );
        cvShowImage("Birds_Eye", birds_image);
        key = cvWaitKey();
        if(key == 'u') Z += 0.5;
        if(key == 'd') Z -= 0.5;
    }
    
    cvSave("H.xml",H);
    
    return 0;
    
}
