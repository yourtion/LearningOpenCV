//
//  drawBoxs.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

void my_mous_callback( int evetnt, int x, int y, int flag, void* param );

CvRect box;
bool drawing_box = false;

void draw_box( IplImage* img, CvRect rect ) {
    cvRectangle(
        img ,
        cvPoint(rect.x, rect.y),
        cvPoint(rect.x+rect.width, rect.y+rect.height),
        cvScalar(0x00, 0x00, 0xff) // Red
    );
}

int main(int argc, const char * argv[]) {
    
    box = cvRect(-1, -1, 0, 0);
    IplImage* image = cvCreateImage( cvSize(200, 200), IPL_DEPTH_8U, 3 );
    cvZero( image );
    IplImage* temp = cvCloneImage( image );
    
    cvNamedWindow( "Box Example" );
    
    cvSetMouseCallback( "Box Example", my_mous_callback, (void *) image );
    
    while (1) {
        cvCopyImage( image, temp );
        
        if (drawing_box) draw_box( temp, box );
        cvShowImage( "Box Example", temp );
        
        if ( cvWaitKey(15) == 27) break;
        
    }
    
    cvReleaseImage( &image );
    cvReleaseImage( &temp );
    cvDestroyWindow( "Box Example" );
    
    return 0;
}

void my_mous_callback( int evetnt, int x, int y, int flag, void* param ) {
    
    IplImage* image = (IplImage *) param;
    
    switch (evetnt) {
        case CV_EVENT_MOUSEMOVE:
            if ( drawing_box ) {
                box.width = x-box.x;
                box.height = y-box.y;
            }
            break;
        case CV_EVENT_LBUTTONDOWN:
            drawing_box = true;
            box = cvRect(x, y, 0, 0);
            break;
        case CV_EVENT_LBUTTONUP:
            drawing_box = false;
            if (box.width<0) {
                box.x += box.width;
                box.width *= -1;
            }
            if (box.height<0) {
                box.y += box.height;
                box.height *= -1;
            }
            draw_box(image, box);
            break;
        default:
            break;
    }
    
}
