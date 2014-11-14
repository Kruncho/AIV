#include "AIV/ai.h"

AI::AI()
{
    _cap = cv::VideoCapture(0);

    if (!_cap.isOpened())
    {
        std::cout << "Cannot open the video cam" << std::endl;
        EXIT_FAILURE;
    }

    _cols = _cap.get(CV_CAP_PROP_FRAME_WIDTH); /* get the width of frames of the video */
    _rows = _cap.get(CV_CAP_PROP_FRAME_HEIGHT); /* get the height of frames of the video */
    _fps = _cap.get(CV_CAP_PROP_FPS); /* Not working for some unknown reasons*/

    std::cout << "Frame size : " << _cols << " x " << _rows << std::endl;
    std::cout << "FPS : " << _fps << std::endl;

    _window_title = "I'm Watching You";

    cv::namedWindow(_window_title, CV_WINDOW_AUTOSIZE);

    _frame_counter = 0;

    _ringBuffer = new RingBuffer(8);

    std::cout << "Wait for " << _ringBuffer->getSize() << " samples." << std::endl;

    _thread_dumpSamples = boost::thread(&AI::dumpSamples, this);

    while (1)
    {

    }
}

AI::~AI()
{
    delete _ringBuffer;
}

void AI::dumpSamples()
{
    const bool show = true;

    while(1)
    {
        _cap >> _color_frame;

        _ringBuffer->add(&_color_frame);
        _frame_counter++;

        if(_ringBuffer->getMarker() == EMPTY) /* Fill the buffer */
            continue;

        cvtColor(_color_frame, _gray_frame, CV_BGR2GRAY);

        process();

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

void AI::process()
{

}



