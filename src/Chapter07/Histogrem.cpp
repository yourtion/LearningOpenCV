//
//  Histogrem.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

int main(int argc, const char * argv[]) {
    
    IplImage *src;
    
    if (argc == 2 && ((src = cvLoadImage(argv[1], 1)) != 0)) {
        
        // HSV image and decompose into separate planes
        
        IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
        cvCvtColor( src, hsv, CV_BGR2HSV);
        
        
        IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
        IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
        IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
        IplImage* planes[] = { h_plane, s_plane };
        cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );
        
        // Build the histogram amd compute
        int h_bins = 30, s_bins = 32;
        CvHistogram* hist;
        {
            int hist_size[] = { h_bins, s_bins };
            float h_ranges[] = { 0, 180 };
            float s_ranges[] = { 0, 255 };
            float* ranges[] = { h_ranges, s_ranges };
            hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
        }
        cvCalcHist( planes, hist, 0, 0 );
        cvNormalizeHist( hist, 1.0 );
        
        // create image to visualize
        int scale = 10;
        IplImage* hist_img = cvCreateImage( cvSize(h_bins*scale, s_bins*scale), 8, 3);
        cvZero( hist_img );
        
        float max_value = 0;
        cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );
        for ( int h = 0; h < h_bins; h ++ ) {
            for ( int s = 0; s < s_bins ; s++ ) {
                float bin_val = cvQueryHistValue_2D( hist, h, s );
                int intensity = cvRound( bin_val * 255 / max_value );
                cvRectangle(hist_img,
                            cvPoint( h*scale, s*scale ),
                            cvPoint( (h+1)*scale-1, (s+1)*scale-1 ),
                            CV_RGB(intensity, intensity, intensity),
                            CV_FILLED
                            );
            }
        }
        cvNamedWindow( "Source", 1 );
        cvShowImage( "Source", src );
        
        cvNamedWindow( "H-S Histogrem", 1 );
        cvShowImage( "H-S Histogrem", hist_img);
        
        cvWaitKey();
        
        cvReleaseImage( &src );
        cvReleaseImage( &hist_img );
        cvReleaseHist( &hist );
        
    }
    
    return 0;
}
