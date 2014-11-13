#include "AIV/ai.h"

AI::AI()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video cam" << std::endl;
        EXIT_FAILURE;
    }

    _cols = cap.get(CV_CAP_PROP_FRAME_WIDTH); /* get the width of frames of the video */
    _rows = cap.get(CV_CAP_PROP_FRAME_HEIGHT); /* get the height of frames of the video */
    _fps = cap.get(CV_CAP_PROP_FPS); /* Not working for some unknown reasons*/

    std::cout << "Frame size : " << _cols << " x " << _rows << std::endl;
    std::cout << "FPS : " << _fps << std::endl;

    _window_title = "I'm Watching You";

    cv::namedWindow(_window_title, CV_WINDOW_AUTOSIZE);

    bool first_frame = true; /* To do just in the first loop */
    bool show = true;

    _count = 0;

    _buffer = new RingBuffer(128);

    while (1)
    {
        cap >> _current_color_frame;

        cvtColor(_current_color_frame, _current_gray_frame, CV_BGR2GRAY);

        if (first_frame)
        {
            first_frame = false;
            _prev_gray_frame = _current_gray_frame;
        }

        this->process();

        if(show)
            cv::imshow(_window_title, _current_color_frame); //show the frame

        if (cv::waitKey(30) == 27) // 27 = 'esc' button
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }

        this->updateFrames();

        _count++;
    }
}

AI::~AI()
{
    delete _buffer;
}

void AI::process()
{
    _buffer->add(&_current_color_frame);
}

void AI::updateFrames()
{
    _prev_gray_frame = _current_gray_frame;
    _prev_color_frame = _current_color_frame;
}


