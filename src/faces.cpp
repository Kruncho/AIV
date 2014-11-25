#include "AIV/faces.h"

Faces::Faces(std::string name, cv::Mat *picture)
{
    _name = name;
    _picture = *picture;
    cv::FaceRecognizer *face = cv::createFisherFaceRecognizer();
    face->train(_picture, _label);
}
