//
//  Kalman.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

#define CVX_DONT_CARE -1

#define CVX_CAMERA  0
#define CVX_AVI     1

#define CVX_RED     CV_RGB(0xff,0x00,0x00)
#define CVX_GREEN   CV_RGB(0x00,0xff,0x00)
#define CVX_BLUE    CV_RGB(0x00,0x00,0xff)

#define CVX_CYAN    CV_RGB(0x00,0xff,0xff)
#define CVX_MAGENTA CV_RGB(0xff,0x00,0xff)
#define CVX_YELLOW  CV_RGB(0xff,0xff,0x00)

#define CVX_WHITE   CV_RGB(0xff,0xff,0xff)
#define CVX_BLACK   CV_RGB(0x00,0x00,0x00)
#define CVX_GRAY50  CV_RGB(0x88,0x88,0x88)

typedef struct {
    float x;
    float y;
    float width;
    float height;
}
CvxRect32f;

CV_INLINE  CvxRect32f  cvxRect32f(float x, float y, float width, float height) {
    CvxRect32f r;
    
    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;
    
    return r;
}
CvScalar cvx_hsv2rgb( CvScalar hsv ) {
    
    // H is given on [0, 180]. S and V are given on [0, 255].
    // RGB are each returned on [0, 255].
    //
    float h = hsv.val[0]/30.0f;
    float s = hsv.val[1]/255.0f;
    float v = hsv.val[2]/255.0f;
    while( h>6.0f ) h-=6.0f;
    while( h<0.0f ) h+=6.0f;
    float m, n, f;
    int i;
    
    CvScalar rgb;
    
    i = floor(h);
    f = h - i;
    if ( !(i&1) ) f = 1 - f; // if i is even
    m = v * (1 - s);
    n = v * (1 - s * f);
    switch (i) {
        case 6:
        case 0: rgb = CV_RGB(v, n, m); break;
        case 1: rgb = CV_RGB(n, v, m); break;
        case 2: rgb = CV_RGB(m, v, n); break;
        case 3: rgb = CV_RGB(m, n, v); break;
        case 4: rgb = CV_RGB(n, m, v); break;
        case 5: rgb = CV_RGB(v, m, n); break;
    }
    
    rgb.val[0] *= 255.0f;
    rgb.val[1] *= 255.0f;
    rgb.val[2] *= 255.0f;
    
    return rgb;
}

#define phi2xy(mat)                                                  \
cvPoint( cvRound(img->width/2 + img->width/3*cos(mat->data.fl[0])),\
cvRound( img->height/2 - img->width/3*sin(mat->data.fl[0])) )

int main(int argc, const char * argv[]) {
    
    cvNamedWindow( "Kalman", 1 );
    CvRandState rng;
    cvRandInit( &rng, 0, 1, -1, CV_RAND_UNI );
    
    IplImage* img = cvCreateImage( cvSize(500,500), 8, 3 );
    CvKalman* kalman = cvCreateKalman( 2, 1, 0 );

    CvMat* x_k = cvCreateMat( 2, 1, CV_32FC1 );
    cvRandSetRange( &rng, 0, 0.1, 0 );
    rng.disttype = CV_RAND_NORMAL;
    cvRand( &rng, x_k );
    
    // process noise
    CvMat* w_k = cvCreateMat( 2, 1, CV_32FC1 );
    
    // measurements, only one parameter for angle
    CvMat* z_k = cvCreateMat( 1, 1, CV_32FC1 );
    cvZero( z_k );
    
    const float F[] = { 1, 1, 0, 1 };
    memcpy( kalman->transition_matrix->data.fl, F, sizeof(F));
    // Initialize other Kalman filter parameters.
    cvSetIdentity( kalman->measurement_matrix,    cvRealScalar(1) );
    cvSetIdentity( kalman->process_noise_cov,     cvRealScalar(1e-5) );
    cvSetIdentity( kalman->measurement_noise_cov, cvRealScalar(1e-1) );
    cvSetIdentity( kalman->error_cov_post,        cvRealScalar(1));
    
    // choose random initial state
    cvRand( &rng, kalman->state_post );
    
    while( 1 ) {
        // predict point position
        const CvMat* y_k = cvKalmanPredict( kalman, 0 );
        
        // generate measurement (z_k)
        cvRandSetRange( &rng, 0, sqrt(kalman->measurement_noise_cov->data.fl[0]), 0 );
        cvRand( &rng, z_k );
        cvMatMulAdd( kalman->measurement_matrix, x_k, z_k, z_k );
        // plot points (eg convert to planar co-ordinates and draw)
        cvZero( img );
        cvCircle( img, phi2xy(z_k), 4, CVX_YELLOW );   // observed state
        cvCircle( img, phi2xy(y_k), 4, CVX_WHITE, 2 ); // "predicted" state
        cvCircle( img, phi2xy(x_k), 4, CVX_RED );      // real state
        cvShowImage( "Kalman", img );
        // adjust Kalman filter state
        cvKalmanCorrect( kalman, z_k );
        
        cvRandSetRange( &rng, 0, sqrt(kalman->process_noise_cov->data.fl[0]), 0 );
        cvRand( &rng, w_k );
        cvMatMulAdd( kalman->transition_matrix, x_k, w_k, x_k );
        
        // exit if user hits 'Esc'
        if( cvWaitKey( 100 ) == 27 ) break;
    }
    
    return 0;
}
