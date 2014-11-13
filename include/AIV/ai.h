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

        /**
         * @brief Save the color and the gray current frames for one more loop
         */
        void updateFrames();

    protected:
        RingBuffer *_buffer;

        double _cols; ///< Nb colums
        double _rows; ///< Nb rows
        double _fps; ///< frame rate

        std::string _window_title; ///< the name that apears in the window

        cv::Mat _prev_color_frame; ///<
        cv::Mat _prev_gray_frame;
        cv::Mat _current_color_frame;
        cv::Mat _current_gray_frame;

        int _count; ///< Frames counter

};

#endif // AI_H
