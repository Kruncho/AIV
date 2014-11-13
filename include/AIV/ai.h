/**
  * @file ai.h
  * @author Kruncho (Vincent Rose <vincent.rose95@gmail.com>)
  * @version 1.0
  * @date November 13, 2014
  */

#ifndef AI_H
#define AI_H

#include <cv.h>
#include <highgui.h>

#include "AIV/ringbuffer.h"

/**
 * @class AI
 * @brief
 */
class AI
{
    public:
        /**
         * @brief Contain the main loop
         */
        AI();

        /**
          * @brief Delete the buffer
          */
        ~AI();

        /**
         * @brief Main process
         */
        void process();

    protected:
        RingBuffer *_buffer; ///< The ring buffer to store the frames

        double _cols; ///< Nb colums
        double _rows; ///< Nb rows
        double _fps; ///< frame rate

        std::string _window_title; ///< the name that apears in the window

        cv::Mat _color_frame;
        cv::Mat _gray_frame;

        int _count; ///< Frames counter

};

#endif // AI_H
