# LearningOpenCV

Source code for Learning OpenCV 

《学习OpenCV》源码，使用 `OpenCV 2.4` 自带 Mac 项目 Xcode 工程。

![ScreenShot](ScreenShot1.png)

## 使用方法

### 下载源码

```sh
git clone https://github.com/yourtion/LearningOpenCV.git
```

### 加入OpenCV

 使用 `HomeBrew` 安装：

```sh
$ brew install opencv
```

安装后 `OpenCV` 位于 `/usr/local/Cellar/opencv/2.4.13/lib`，也就是 Xcode 工程中的 `lib` 的位置。

### 使用Demo

所有源码按照章节放在 `src` 目录下，数据位于 `data` 目录。

Checkout 到对应的 commit 即可运行对应的 Demo。

## 源码列表

- [cameraCapture](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter02/cameraCapture.cpp)
- [imageCannyAndPyrDown](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter02/imageCannyAndPyrDown.cpp)
- [load_image](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter02/load_image.cpp)
- [load_video](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter02/load_video.cpp)
- [load_videoTrackbar](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter02/load_videoTrackbar.cpp)
- [smoothImage](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter02/smoothImage.cpp)
- [videoConver](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter02/videoConver.cpp)
- [AlphaBlend](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter04/AlphaBlend.cpp)
- [FileStorage](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter04/FileStorage.cpp)
- [imageROI](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter04/imageROI.cpp)
- [AffineTransform](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter06/AffineTransform.cpp)
- [PerspectiveTransform](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter06/PerspectiveTransform.cpp)
- [cvHoughCircles](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter06/cvHoughCircles.cpp)
- [drawBoxs](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter06/drawBoxs.cpp)
- [Histogrem-EMD](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter07/Histogrem-EMD.cpp)
- [Histogrem](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter07/Histogrem.cpp)
- [MatchTemplate](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter07/MatchTemplate.cpp)
- [Contours1](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter08/Contours1.cpp)
- [Contours2](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter08/Contours2.cpp)
- [Kalman](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter10/Kalman.cpp)
- [OpticalFlow](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter10/OpticalFlow.cpp)
- [calib](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter11/calib.cpp)
- [calibFromFile](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter11/calibFromFile.cpp)
- [2DLineFitting](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter12/2DLineFitting.cpp)
- [BirdsEye](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter12/BirdsEye.cpp)
- [StereoCalib](https://github.com/yourtion/LearningOpenCV/blob/master/src/Chapter12/StereoCalib.cpp)
