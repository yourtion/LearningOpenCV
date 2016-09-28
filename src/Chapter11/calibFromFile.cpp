//
//  calibFromFile.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>

int n_boards = 0; //Will be set by input list
const int board_dt = 10;
int board_w;
int board_h;

int main(int argc, char* argv[]) {
    
    board_w = 12;
    board_h = 12;
    int board_n  = board_w * board_h;
    CvSize board_sz = cvSize( board_w, board_h );
    FILE *fptr = fopen("./data/chessboards.txt","r");
    char names[2048];

    while(fscanf(fptr,"%s ",names)==1){
        n_boards++;
    }
    rewind(fptr);
    
    cvNamedWindow( "Calibration" );
    CvMat* image_points      = cvCreateMat(n_boards*board_n,2,CV_32FC1);
    CvMat* object_points     = cvCreateMat(n_boards*board_n,3,CV_32FC1);
    CvMat* point_counts      = cvCreateMat(n_boards,1,CV_32SC1);
    CvMat* intrinsic_matrix  = cvCreateMat(3,3,CV_32FC1);
    CvMat* distortion_coeffs = cvCreateMat(4,1,CV_32FC1);
    
    
    IplImage* image = 0;// = cvQueryFrame( capture );
    IplImage* gray_image = 0; //for subpixel
    CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
    int corner_count;
    int successes = 0;
    int step;
    
    for( int frame=0; frame<n_boards; frame++ ) {
        fscanf(fptr,"%s ",names);
        
        if(image){
            cvReleaseImage(&image);
            image = 0;
        }
        image = cvLoadImage( names);
        if(gray_image == 0  && image) //We'll need this for subpixel accurate stuff
            gray_image = cvCreateImage(cvGetSize(image),8,1);
        
        if(!image)
            printf("null image\n");
        
        int found = cvFindChessboardCorners(
                                            image,
                                            board_sz,
                                            corners,
                                            &corner_count,
                                            CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
                                            );
        
        cvCvtColor(image, gray_image, CV_BGR2GRAY);
        cvFindCornerSubPix(gray_image, corners, corner_count,
                           cvSize(11,11),cvSize(-1,-1), cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
        
        cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
        cvShowImage( "Calibration", image );
        
        if( corner_count == board_n ) {
            step = successes*board_n;
            printf("Found = %d for %s\n",found,names);
            for( int i=step, j=0; j<board_n; ++i,++j ) {
                CV_MAT_ELEM(*image_points, float,i,0) = corners[j].x;
                CV_MAT_ELEM(*image_points, float,i,1) = corners[j].y;
                CV_MAT_ELEM(*object_points,float,i,0) = j/board_w;
                CV_MAT_ELEM(*object_points,float,i,1) = j%board_w;
                CV_MAT_ELEM(*object_points,float,i,2) = 0.0f;
                
            }
            //        CV_MAT_ELEM(*point_counts, int,0,successes) = board_n;
            CV_MAT_ELEM(*point_counts, int,successes,0) = board_n;
            successes++;
        }
        
        int c = cvWaitKey(15);
        if(c == 'p') {
            c = 0;
            while(c != 'p' && c != 27){
                c = cvWaitKey(250);
            }
        }
        if(c == 27)
            return 0;
    }
    printf("successes = %d, n_boards=%d\n",successes,n_boards);

    CvMat* object_points2     = cvCreateMat(successes*board_n,3,CV_32FC1);
    CvMat* image_points2      = cvCreateMat(successes*board_n,2,CV_32FC1);
    CvMat* point_counts2      = cvCreateMat(successes,1,CV_32SC1);

    for(int i = 0; i<successes*board_n; ++i){
        CV_MAT_ELEM(*image_points2, float,i,0) 	=	CV_MAT_ELEM(*image_points, float,i,0);
        CV_MAT_ELEM(*image_points2, float,i,1) 	= 	CV_MAT_ELEM(*image_points, float,i,1);
        CV_MAT_ELEM(*object_points2,float,i,0) = CV_MAT_ELEM(*object_points,float,i,0) ;
        CV_MAT_ELEM(*object_points2,float,i,1) = CV_MAT_ELEM(*object_points,float,i,1) ;
        CV_MAT_ELEM(*object_points2,float,i,2) = CV_MAT_ELEM(*object_points,float,i,2) ;
        
    }
    for(int i=0; i<successes; ++i){
        CV_MAT_ELEM(*point_counts2,int,i, 0) = CV_MAT_ELEM(*point_counts, int,i,0);
    }
    cvReleaseMat(&object_points);
    cvReleaseMat(&image_points);
    cvReleaseMat(&point_counts);
    

    CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
    CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
    printf("cvCalibrateCamera2\n");
    cvCalibrateCamera2(
                       object_points2,
                       image_points2,
                       point_counts2,
                       cvGetSize( image ),
                       intrinsic_matrix,
                       distortion_coeffs,
                       NULL,
                       NULL,
                       0
                       );
    // Save our work
    cvSave("Intrinsics.xml",intrinsic_matrix);
    cvSave("Distortion.xml",distortion_coeffs);
    // Load test
    CvMat *intrinsic = (CvMat*)cvLoad("Intrinsics.xml");
    CvMat *distortion = (CvMat*)cvLoad("Distortion.xml");
    
    IplImage* mapx = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    IplImage* mapy = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    printf("cvInitUndistortMap\n");
    cvInitUndistortMap(
                       intrinsic,
                       distortion,
                       mapx,
                       mapy
                       );

    rewind(fptr);
    cvNamedWindow( "Undistort" );
    printf("\n\nPress any key to step through the images, ESC to quit\n\n");
    while(fscanf(fptr,"%s ",names)==1){
        if(image){
            cvReleaseImage(&image);
            image = 0;
        }
        image = cvLoadImage( names);
        IplImage *t = cvCloneImage(image);
        cvShowImage( "Calibration", image );
        cvRemap( t, image, mapx, mapy );
        cvReleaseImage(&t);

        cvShowImage("Undistort", image);
        if((cvWaitKey()&0x7F) == 27) break;
    }
    
    return 0;
}

