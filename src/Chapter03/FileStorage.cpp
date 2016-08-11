//
//  FileStorage.cpp
//  LearningOpenCV
//
//  Created by YourtionGuo on 7/28/16.
//  Copyright © 2016 Yourtion. All rights reserved.
//

#include <iostream>
#include <highgui.h>
#include <cv.h>

int main(int argc, const char * argv[]) {
    CvMat *cmatrix = cvCreateMat(5,5,CV_32FC1);
    float element_3_2 = 7.7;
    *((float*)CV_MAT_ELEM_PTR( *cmatrix, 3,2) ) = element_3_2;
    cvmSet(cmatrix,4,4,0.5000);
    cvSetReal2D(cmatrix,3,3,0.5000);
    
    CvFileStorage* fs1 = cvOpenFileStorage("cfg.xml", 0, CV_STORAGE_WRITE);
    cvWriteInt( fs1, "frame_count", 10 );
    cvStartWriteStruct( fs1, "frame_size", CV_NODE_SEQ );
    cvWriteInt( fs1 , 0, 320 );
    cvWriteInt( fs1 , 0, 200 );
    cvEndWriteStruct( fs1 );
    cvWrite( fs1, "color_cvt_matrix", cmatrix );
    cvReleaseFileStorage( &fs1 );
    
    CvFileStorage* fs2 = cvOpenFileStorage("cfg.xml", 0, CV_STORAGE_READ);
    int frame_count = cvReadIntByName( fs2 , 0, "frame_count");
    CvSeq* s = cvGetFileNodeByName( fs2,0,"frame_size" )->data.seq;
    int frame_width = cvReadInt( (CvFileNode*)cvGetSeqElem(s,0) );
    int frame_height = cvReadInt( (CvFileNode*)cvGetSeqElem(s,1) );
    CvMat* color_cvt_matrix = (CvMat*) cvReadByName( fs2, 0 , "color_cvt_matrix");
    
    printf("color_cvt_matrix: width=%d, height=%d\n",color_cvt_matrix->width, color_cvt_matrix->height );
    printf("frame_count=%d, frame_width=%d, frame_height=%d\n",frame_count,frame_width,frame_height);
    
    cvReleaseFileStorage( &fs2 );
    
    return 0;
}
