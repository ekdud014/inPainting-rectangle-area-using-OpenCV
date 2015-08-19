#ifndef INPAINTING_H_
#define INPAINTING_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>

using namespace std;
using namespace cv;

class InPaint
{
    public:
        Rect rect_;                     // rectangle
        Mat input_img_;                 // input image
        Mat inpaint_img_;               // inpainted image
        Mat mask_;                      // mask
        const char *input_win_name_;    // input image window name
        const char *output_win_name_;   // output image window name
        // inpainting functions
        void InPainting(char *img_name);       
        // show rectangle area
        void ShowRect(const char *win_name, Mat img, const Rect rect, Scalar color, int thickness, int line_type, int shift);
    private:
        // draw rectangle
        void DrawRect(Mat img, Rect rect, Scalar color, int thickness, int line_type, int shift);
};

void mouse(int event, int x, int y, int flag, void *arg);

#endif
