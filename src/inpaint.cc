#include "inpainting.h"

// draw rectangle
void InPaint::DrawRect(Mat img, Rect rect, Scalar color=Scalar(255,0,0), int thickness=2, int line_type=8, int shift=0)
{
    Point pt1 = Point(rect.x, rect.y);
    Point pt2 = Point(rect.x+rect.width, rect.y+rect.height);
    rectangle(img, pt1, pt2, color, thickness, line_type, shift);
}

// show rectangle without showing the intermediate rectangles
void InPaint::ShowRect(const char *win_name, Mat img, const Rect rect, Scalar color=Scalar(255,0,0), int thickness=2, int line_type=8, int shift=0)
{
    Mat clone_img;
    img.copyTo(clone_img);
    InPaint::DrawRect(clone_img, rect, color, thickness, line_type, shift);
    imshow(win_name, clone_img);
    clone_img.release();
}

// mouse activities
void mouse(int event, int x, int y, int flag, void *arg)
{
    InPaint *fig = (InPaint*) arg;

    if (event == CV_EVENT_LBUTTONDOWN)
    {
        fig->rect_.x = x;
        fig->rect_.y = y;
    }
    else if(event == CV_EVENT_MOUSEMOVE && flag & CV_EVENT_FLAG_LBUTTON)
    {
        fig->rect_.width = abs(fig->rect_.x - x);
        fig->rect_.height = abs(fig->rect_.y - y);
        if (fig->rect_.x > 0 && fig->rect_.y > 0)
            fig->ShowRect(fig->input_win_name_, fig->input_img_, fig->rect_);
    }
    else if(event == CV_EVENT_LBUTTONUP)
    {
        Point **pts = new Point *[1];
        pts[0] = new Point[4];
        pts[0][0] = Point(fig->rect_.x, fig->rect_.y);
        pts[0][1] = Point(fig->rect_.x, fig->rect_.y+fig->rect_.height);
        pts[0][2] = Point(fig->rect_.x+fig->rect_.width, fig->rect_.y+fig->rect_.height);
        pts[0][3] = Point(fig->rect_.x+fig->rect_.width, fig->rect_.y);
        const Point* points[1] = {pts[0]};
        int npts[1] = {4};
        polylines(fig->mask_, points, npts, 1, true, Scalar(255,0,0));
        fillPoly(fig->mask_, points, npts, 1, Scalar(255,0,0));
        delete [] pts[0];
        delete [] pts;
        // set the rectangle to default values after clicking
        fig->rect_ = Rect(-1,-1,0,0);
    }
}

//inpainting function
void InPaint::InPainting(char* img_name)
{
    InPaint fig;
    Mat input_img = imread(img_name, -1);
    if (!input_img.data)
    {
        cout << "Could NOT read the image!" << endl;
        exit(-1);
    }
    // initialization
    input_img.copyTo(fig.input_img_);
    fig.input_img_.copyTo(fig.inpaint_img_);
    fig.input_win_name_ = "Original Image";
    fig.output_win_name_ = "InPainted Image";
    fig.rect_ = Rect(-1,-1,0,0);
    fig.mask_ = Mat::zeros(fig.input_img_.size(), CV_8UC1);
    namedWindow(fig.input_win_name_, 1);
    imshow(fig.input_win_name_, input_img);
    setMouseCallback(fig.input_win_name_, mouse, (InPaint*)&fig);
    namedWindow(fig.output_win_name_, 1);
    const char *out_img_name = "inpainted.jpg";

    while(1)
    {
        imshow(fig.output_win_name_, fig.inpaint_img_);
        int key = waitKey(1) & 255;
        if (key == 27)
            break;
        // Press 'i' or space to inpaint
        else if (key == 'i' || key == ' ')
        {
            inpaint(fig.input_img_, fig.mask_, fig.inpaint_img_, 2, INPAINT_NS);
            //inpaint(fig.input_img_, fig.mask_, fig.inpaint_img_, 2, INPAINT_TELEA);
            imshow(fig.output_win_name_, fig.inpaint_img_);
        }
        // Press 'r' to restore image
        else if (key == 'r')
        {
            fig.mask_ = Scalar::all(0);
            fig.input_img_.copyTo(fig.inpaint_img_);
            imshow(fig.output_win_name_, fig.inpaint_img_);
        }
        // save image
        imwrite(out_img_name, fig.inpaint_img_);
    }
    // release all the memory
    input_img.release();
}
