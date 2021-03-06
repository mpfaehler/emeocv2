/*
 * ImageInput.h
 *
 */

#ifndef IMAGEINPUT_H_
#define IMAGEINPUT_H_

#include <ctime>
#include <string>
#include <list>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Directory.h"

class ImageInput {
public:
    virtual ~ImageInput();

    virtual bool nextImage() = 0;

    virtual cv::Mat & getImage();
    virtual time_t getTime();
    virtual void setOutputDir(const std::string & outDir);
    virtual void saveImage();

protected:
    cv::Mat _img;
    time_t _time;
    std::string _outDir;
};

class DirectoryInput: public ImageInput {
public:
    DirectoryInput(const Directory & directory);

    virtual bool nextImage();
	std::string getCurrentFilename();
private:
    Directory _directory;
    std::list<std::string>::const_iterator _itFilename;
    std::list<std::string> _filenameList;
	tm readExifCreatedDate(const std::string fullpath);
	tm readFilenameDate(const std::string filename);
	std::string _curFilename;
};

class CameraInput: public ImageInput {
public:
    CameraInput(int device);

    virtual bool nextImage();

private:
    cv::VideoCapture _capture;
};

class CLIImageInput: public ImageInput {
public:
    CLIImageInput(const std::string command, const std::string temporaryPath);	
    virtual bool nextImage();

private:
    std::string command;
    std::string temporaryPath;
};


#endif /* IMAGEINPUT_H_ */
