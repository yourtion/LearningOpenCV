//
//  AlphaBlend
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

// ./LearningOpenCV 0.jpg 1.jpg 100 100 100 100 0.1 2

int main(int argc, const char * argv[]) {
    IplImage *src1, *src2;
    if( argc == 9 && ((src1 = cvLoadImage(argv[1],1)) != 0) && ((src2 = cvLoadImage(argv[2],1)) != 0)) {
        int x = atoi(argv[3]);
        int y = atoi(argv[4]);
        int width = atoi(argv[5]);
        int height = atoi(argv[6]);
        double alpha = atoi(argv[7]);
        double beta = atoi(argv[8]);
        
        cvSetImageROI(src1, cvRect(x, y, width, height));
        cvSetImageROI(src2, cvRect(0, 0, width, height));
        cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
        cvResetImageROI(src1);
        cvNamedWindow( "Alpha_blend", 1 );
        cvShowImage( "Alpha_blend", src1 );
        cvWaitKey();
    }
    return 0;
}
