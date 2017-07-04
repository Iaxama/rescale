//
// Created by miacono on 03/07/17.
//

#ifndef RESCALE_RESCALE_H
#define RESCALE_RESCALE_H

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

class ImagePort : public yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > {

private:
    yarp::sig::ImageOf<yarp::sig::PixelRgb> image;
    yarp::os::Mutex mutex;
    bool imageReady;
public:
    
    ImagePort() : imageReady(false) {};
    virtual void onRead(yarp::sig::ImageOf<yarp::sig::PixelRgb> &inImg);
    yarp::sig::ImageOf<yarp::sig::PixelRgb> getImage();
    bool isImageReady() { return imageReady;};
};


class RescalingModule : public yarp::os::RFModule {

private:
    int width;
    int height;
    ImagePort imagePort;
    yarp::os::Port outPort;
public:

    virtual bool configure(yarp::os::ResourceFinder &rf);
    virtual bool interruptModule();
    virtual bool close();
    virtual double getPeriod();
    virtual bool updateModule();
};

#endif //RESCALE_RESCALE_H
