//
//  load_image.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    IplImage* img = cvLoadImage( argv[1] );
    cvNamedWindow( "Example1" , CV_WINDOW_AUTOSIZE);
    cvShowImage("Example1", img );
    cvWaitKey(0);
    cvReleaseImage( &img );
    cvDestroyWindow( "Example1" );
}
