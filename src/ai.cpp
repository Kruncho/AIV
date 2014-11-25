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

    //std::cout << "Frame size : " << _cols << " x " << _rows << std::endl;
    //std::cout << "FPS : " << _fps << std::endl;

    _window_title = "I'm Watching You";

    cv::namedWindow(_window_title, CV_WINDOW_AUTOSIZE);

    _frame_counter = 0;
    _end_prog = false;
    _ringBuffer =  new RingBuffer(8);

    //std::cout << "Wait for " << _ringBuffer->getSize() << " samples." << std::endl;

    _thread_videoStream = boost::thread(&AI::videoStream, this);

    while (!_end_prog)
    {
        std::system("clear");
        process();
    }

    _thread_videoStream.join();

}

AI::~AI()
{
    delete _ringBuffer;
}

void AI::videoStream()
{
    const bool show = true;

    while(!_end_prog)
    {
        _cap >> _color_frame;

        if(show)
            cv::imshow(_window_title, _color_frame); //show the frame

        if (cv::waitKey(30) == 27) // 27 = 'esc' button
        {
            std::cout << "esc key is pressed by user" << std::endl;
            _end_prog = true;
            break;
        }

        _frame_counter++;
    }
}

void AI::process()
{
    std::string answer = "N";
    std::string name = "";

    while(answer != "y")
    {
        std::cout << "Are you the main user of this software ? [y/N] ";
        std::getline(std::cin, answer);

        if(answer != "y")
            std::cout << "Then you're not allowed to used this software." << std::endl;
        else
            std::cout << "You will be identified." << std::endl;
    }

    answer = "N";

    while(answer != "y")
    {
        std::cout << "Tape your name so we can set you as the main user : ";
        std::getline(std::cin, name);

        std::cout << "Is \"" << name << "\" correct ? [y/N] ";
        std::getline(std::cin, answer);
    }

    _ringBuffer->add(&_color_frame);

    cv::Mat picture = _ringBuffer->getFrameAt(-1);

    Faces *face = new Faces(name, &picture);

    cv::imshow("Face", picture);

    std::getline(std::cin, name);

    delete face;

    _end_prog = true;


}



