//
//  imageROI
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

// ./LearningOpenCV 0.jpg 10 10 500 300 100

int main(int argc, const char * argv[]) {
    IplImage* src;
    if( argc == 7 && ((src = cvLoadImage(argv[1],1)) != 0)) {
        int x = atoi(argv[2]);
        int y = atoi(argv[3]);
        int width = atoi(argv[4]);
        int height = atoi(argv[5]);
        int add = atoi(argv[6]);
        cvSetImageROI(src, cvRect(x, y, width, height));
        cvAddS(src, cvScalar(add), src);
        cvResetImageROI(src);
        cvNamedWindow( "ROI_Add", 1 );
        cvShowImage( "ROI_Add", src );
        cvWaitKey();
    }
    return 0;
}
