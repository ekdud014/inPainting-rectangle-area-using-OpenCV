/*------------------------------------------------------------*/
/*  InPainting selected areas on an image using OpenCV        */
/*                                                            */
/* Author: Matrivian                                          */
/* Date: 05/11/2015                                           */
/*------------------------------------------------------------*/

#include "inpainting.h"

int main(int argc, char** argv)
{
    InPaint ipt;
#ifdef INPAINTING
    if (argc == 1)
        cout << "Please Specify the path and name of the image!" << endl;
    else if (argc == 2)
        ipt.InPainting(argv[1]);
    else
        cout << "Too many parameters!" << endl;
#endif

    return 0;
}
