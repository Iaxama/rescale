#include <iostream>
#include <rescale.h>

int main( int argc, char * argv[]) {
    /* initialize yarp network */
    yarp::os::Network yarp;
    if(!yarp.checkNetwork()) {
        std::cout << "Could not connect to YARP" << std::endl;
        return false;
    }
    
    /* create the module */
    RescalingModule rescalingModule;
    
    /* prepare and configure the resource finder */
    yarp::os::ResourceFinder rf;
    rf.setVerbose( true );
//    rf.setDefaultContext( "eventdriven" );
//    rf.setDefaultConfigFile( "vParticleFilter.ini" );
    rf.configure( argc, argv );
    
    return rescalingModule.runModule(rf);
}


yarp::sig::ImageOf<yarp::sig::PixelRgb> ImagePort::getImage(){
    yarp::sig::ImageOf<yarp::sig::PixelRgb> outImg;
    mutex.lock();
    outImg = image;
    imageReady = false;
    mutex.unlock();
    return outImg;
};

void ImagePort::onRead(yarp::sig::ImageOf<yarp::sig::PixelRgb> &inImg){
    mutex.lock();
    image = inImg;
    imageReady = true;
    mutex.unlock();
};

bool RescalingModule::configure(yarp::os::ResourceFinder &rf){
    width = rf.check("width",yarp::os::Value(320)).asInt();
    height = rf.check("height",yarp::os::Value(240)).asInt();
    std::string name = rf.check("name", yarp::os::Value("/rescale")).asString();
    std::cout << "Rescaling to " << width << "x" << height << std::endl;
    this->setName(name.c_str());
    imagePort.open(getName("/img:i"));
    imagePort.useCallback();
    outPort.open(getName("/img:o"));
    return true;
};

bool RescalingModule::interruptModule(){
    imagePort.interrupt();
    outPort.interrupt();
    return true;
};

bool RescalingModule::close(){
    imagePort.close();
    outPort.close();
    return true;
};

double RescalingModule::getPeriod(){
    return 0;
};

bool RescalingModule::updateModule(){
    if (!imagePort.isImageReady())
        return true;
    yarp::sig::ImageOf<yarp::sig::PixelRgb > outImg = imagePort.getImage();
    outImg.copy(outImg, width, height);
    outPort.write(outImg);
    return true;
};