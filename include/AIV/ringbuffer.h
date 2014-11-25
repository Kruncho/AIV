/**
  * @file ringbuffer.h
  * @author Kruncho (Vincent Rose <vincent.rose95@gmail.com>)
  * @version 1.0
  * @date November 13, 2014
  */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <cv.h>

#define EMPTY 0
#define MARKED 1

/**
 * @brief A ring buffer to keep the last frames
 */

class RingBuffer
{
    public:
        /**
         * @brief Create a buffer with the disired size
         * @param size  the number of frames we want to keep
         */
        RingBuffer(int size);

        /**
          * @brief  delete each frame in the buffer plus the buffer
          */
        ~RingBuffer();

        /**
         * @brief Return the current index from the buffer
         * @return the value of the index
         */
        int getIndex() const {return _index ;}

        /**
         * @brief Return the marker at the current index
         * @return the value of the marker
         */
        int getMarker() const {return _buffer_sample[_index].marker;}

        /**
         * @brief Return the buffer size
         * @return the size
         */
        int getSize() const {return _size;}

        /**
         * @brief Get the frame wanted in the buffer
         * @param index    start from 0 to the minus buffer size
         * @return A pointer to the frame
         */
        cv::Mat getFrameAt(int index);

        /**
         * @brief Add a frame to the buffer
         * @param color_frame The frame adress
         */
        void add(cv::Mat *color_frame);

        /**
         * @brief Buffer initialization
         */
        void initBuffer();

    protected:
        int _size; ///< The buffer size
        int _index; ///< The buffer current index

        /// A structure to list what we keep at each sample
        struct bufferSample
        {
                int marker; ///< To know if the buffer sample is empty or not
                cv::Mat *frame; ///< The frame to keep
        } *_buffer_sample;

};

#endif // RINGBUFFER_H
