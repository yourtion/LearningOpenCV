//
//  MatchTemplate.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    IplImage *src, *templ, *ftmp[6];
    int i;
    
    if (argc == 3 && ((src = cvLoadImage(argv[1], 1)) != 0) && ((templ = cvLoadImage(argv[2], 1)) != 0)) {
        // Allocate output images
        int i_width = src->width - templ->width + 1;
        int i_height = src->height - templ->height + 1;
        for ( i = 0; i < 6; i++ ) {
            ftmp[i] = cvCreateImage( cvSize(i_width, i_height), 32, 1 );
        }
        // Do template matching
        for ( i = 0; i < 6; i++) {
            cvMatchTemplate( src, templ, ftmp[i], i );
            cvNormalize( ftmp[i], ftmp[i], 1, 0, CV_MINMAX );
        }
        
        //DISPLAY
        cvNamedWindow( "Template", 0 );
        cvShowImage(   "Template", templ );
        cvNamedWindow( "Image", 0 );
        cvShowImage(   "Image", src );
        
        cvNamedWindow( "SQDIFF", 0 );
        cvShowImage(   "SQDIFF", ftmp[0] );
        
        cvNamedWindow( "SQDIFF_NORMED", 0 );
        cvShowImage(   "SQDIFF_NORMED", ftmp[1] );
        
        cvNamedWindow( "CCORR", 0 );
        cvShowImage(   "CCORR", ftmp[2] );
        
        cvNamedWindow( "CCORR_NORMED", 0 );
        cvShowImage(   "CCORR_NORMED", ftmp[3] );
        
        cvNamedWindow( "CCOEFF", 0 );
        cvShowImage(   "CCOEFF", ftmp[4] );
        
        cvNamedWindow( "CCOEFF_NORMED", 0 );
        cvShowImage(   "CCOEFF_NORMED", ftmp[5] );
        
        cvWaitKey();

    }
    
    return 0;
}
