#include "AIV/ai.h"

AI::AI()
{
    const bool show = true;

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

    _frame_counter = 0;

    _buffer = new RingBuffer(64);

    std::cout << "Wait for " << _buffer->getSize() << " samples." << std::endl;

    while (1)
    {
        cap >> _color_frame;

        _buffer->add(&_color_frame);
        _frame_counter++;

        if(_buffer->getMarker() == EMPTY) /* Fill the buffer */
            continue;

        cvtColor(_color_frame, _gray_frame, CV_BGR2GRAY);

        this->process();

        if(show)
            cv::imshow(_window_title, _color_frame); //show the frame

        if (cv::waitKey(30) == 27) // 27 = 'esc' button
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }
        std::cout << _frame_counter << std::endl;
    }
}

AI::~AI()
{
    delete _buffer;
}

void AI::process()
{

}



