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

int main(int argc, const char * argv[]) {
    
    CvPoint2D32f srcQuad[4], dstQuad[4];
    CvMat* warp_matrix = cvCreateMat(3, 3, CV_32FC1);
    IplImage *src, *dst;
    
    if (argc == 2 && ((src = cvLoadImage(argv[1], 1)) != 0)) {
        dst = cvCloneImage( src );
        dst->origin = src->origin;
        cvZero( dst );
        
        // warp matrix
        srcQuad[0].x = 0;
        srcQuad[0].y = 0;
        srcQuad[1].x = src->width - 1;
        srcQuad[1].y = 0;
        srcQuad[2].x = 0;
        srcQuad[2].y = src->height - 1;
        srcQuad[3].x = src->width - 1;
        srcQuad[3].y = src->height - 1;
        
        dstQuad[0].x = src->width * 0.005;
        dstQuad[0].y = src->height * 0.33;
        dstQuad[1].x = src->width * 0.9;
        dstQuad[1].y = src->height * 0.25;
        dstQuad[2].x = src->width * 0.2;
        dstQuad[2].y = src->height * 0.7;
        dstQuad[3].x = src->width * 0.8;
        dstQuad[3].y = src->height * 0.9;
        
        cvGetPerspectiveTransform( srcQuad, dstQuad, warp_matrix );
        cvWarpPerspective( src, dst, warp_matrix );
        
        
        cvNamedWindow( "Perspective_Transform", 1 );
        cvShowImage( "Perspective_Transform" , dst );
        
        cvWaitKey();
        
        cvReleaseImage( &dst );

    }
    
    cvReleaseMat( &warp_matrix );
    
    return 0;
}
