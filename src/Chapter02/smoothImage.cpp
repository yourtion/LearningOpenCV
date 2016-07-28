//
//  smoothImage.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <cv.h>
#include <highgui.h>


int main(int argc, const char * argv[]) {
    
    IplImage* image = cvLoadImage( argv[1] );

    cvNamedWindow( "Example4-in" );
    cvNamedWindow( "Example4-out" );
    
    cvShowImage( "Example4-in",  image);
    
    IplImage* out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
    
    cvSmooth(image, out, 3, 3);
    
    cvShowImage( "Example4-out",  out);
    
    cvReleaseImage( &out );
    cvWaitKey(0);
    cvDestroyWindow("Example4-in");
    cvDestroyWindow("Example4-out");
}
