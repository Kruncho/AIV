#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <cv.h>

#define EMPTY 0
#define MARKED 1

class RingBuffer
{
    public:
        RingBuffer(int size);
        ~RingBuffer();
        void add(cv::Mat *color_frame);
        void initBuffer();

    protected:
        int _size;
        int _index;

        struct buffer
        {
                int marker;
                cv::Mat *frame;
        } *_buffer;

};

#endif // RINGBUFFER_H
