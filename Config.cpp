/*
 * Config.cpp
 *
 */

#include <opencv2/highgui/highgui.hpp>

#include "Config.h"

Config::Config() :
        _rotationDegrees(-90), _ocrMaxDist(5e5), _digitMinHeight(0.04f), _digitMaxHeight(0.075f
                ), _digitYAlignment(10), _cannyThreshold1(160), _cannyThreshold2(
                255), _trainingDataFilename("trainctr.yml") {
}

void Config::saveConfig() {
    cv::FileStorage fs("config.yml", cv::FileStorage::WRITE);
    fs << "rotationDegrees" << _rotationDegrees;
    fs << "cannyThreshold1" << _cannyThreshold1;
    fs << "cannyThreshold2" << _cannyThreshold2;
    fs << "digitMinHeight" << _digitMinHeight;
    fs << "digitMaxHeight" << _digitMaxHeight;
    fs << "digitYAlignment" << _digitYAlignment;
    fs << "ocrMaxDist" << _ocrMaxDist;
    fs << "trainingDataFilename" << _trainingDataFilename;
    fs.release();
}

void Config::loadConfig() {
    cv::FileStorage fs("config.yml", cv::FileStorage::READ);
    if (fs.isOpened()) {
        fs["rotationDegrees"] >> _rotationDegrees;
        fs["cannyThreshold1"] >> _cannyThreshold1;
        fs["cannyThreshold2"] >> _cannyThreshold2;
        fs["digitMinHeight"] >> _digitMinHeight;
        fs["digitMaxHeight"] >> _digitMaxHeight;
        fs["digitYAlignment"] >> _digitYAlignment;
        fs["ocrMaxDist"] >> _ocrMaxDist;
        fs["trainingDataFilename"] >> _trainingDataFilename;
        fs.release();
    } else {
        // no config file - create an initial one with default values
        saveConfig();
    }
}

