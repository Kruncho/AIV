#include "AIV/ringbuffer.h"

RingBuffer::RingBuffer(int size)
{
    _buffer_sample = new bufferSample[size];
    _size = size;

    this->initBuffer();
}

RingBuffer::~RingBuffer()
{
    for(int i = 0; i < _size; i++)
        delete _buffer_sample[i].frame;

    delete[] _buffer_sample;
}

void RingBuffer::add(cv::Mat *color_frame)
{
    *_buffer_sample[_index].frame = *color_frame;
    _buffer_sample[_index].marker = MARKED;
    _index = (_index + 1) % _size;

    //std::cout << _index << std::endl;
}

cv::Mat *RingBuffer::getFrameAt(int index)
{
    if( _buffer_sample[(_index + index) % _size].marker == MARKED)
        return _buffer_sample[(_index + index) % _size].frame;
    else
    {
        std::cout << "The buffer sample don't exists yet" << std::endl;
        return NULL;
    }
}

void RingBuffer::initBuffer()
{
    _index = 0;

    for(int i = 0; i < _size; i++)
    {
        _buffer_sample[i].frame = new cv::Mat;
        _buffer_sample[i].marker = EMPTY;
    }
}
