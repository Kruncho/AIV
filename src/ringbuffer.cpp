#include "AIV/ringbuffer.h"

RingBuffer::RingBuffer(int size)
{
    _buffer = new buffer[size];
    _size = size;

    this->initBuffer();
}

RingBuffer::~RingBuffer()
{
    for(int i = 0; i < _size; i++)
        delete _buffer[i].frame;

    delete _buffer;
}

void RingBuffer::add(cv::Mat *color_frame)
{
    *_buffer[_index].frame = *color_frame;
    _buffer[_index].marker = MARKED;
    _index = (_index + 1) % _size;

    std::cout << _index << std::endl;
}

void RingBuffer::initBuffer()
{
    _index = 0;

    for(int i = 0; i < _size; i++)
    {
        _buffer[i].frame = new cv::Mat;
        _buffer[i].marker = EMPTY;
    }
}
