#ifndef FACES_H
#define FACES_H

#include <cv.h>
#include <highgui.h>
#include "opencv2/contrib/contrib.hpp"

#include "AIV/ringbuffer.h"

class Faces
{
    public:
        Faces(std::string name, cv::Mat *picture);
    protected:
        //cv::FaceRecognizer _face;
        struct face {
                RingBuffer *_ringBuff;
                std::string _name;
                cv::Mat _picture;
                std::vector<int> _label;
        } _oneFace;


};

#endif // FACES_H
