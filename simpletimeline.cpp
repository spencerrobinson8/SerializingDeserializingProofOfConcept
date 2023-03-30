#include "simpletimeline.h"

SimpleTimeline::SimpleTimeline(unsigned int sizeX, unsigned int sizeY, QWidget *parent)
    : QMainWindow(parent)
    , activeLayer(0)
    , activeFrame(0)
    , frameDuration(100)
    , size(sizeX, sizeY)
{


}

SimpleTimeline::~SimpleTimeline(){
    QPixmap* trash;
    while (!frames.empty()) {
        trash = frames.back();
        frames.pop_back();
        delete trash;
    }


}

void SimpleTimeline::addFrame(QPixmap s) {

    frames.push_back(&s);
}

QVector<QPixmap*> SimpleTimeline::getFrames(){
    return frames;
}

//unsigned int simpleTimeline::getActiveLayer(){
//    return activeLayer;
//}
//unsigned int simpleTimeline::getActiveFrame(){
//    return activeFrame;
//}
//unsigned int simpleTimeline::getFrameDuration(){
//    return frameDuration;
//}
unsigned int SimpleTimeline::getSizeX(){
    return size.width();
}
unsigned int SimpleTimeline::getSizeY(){
    return size.height();
}
void SimpleTimeline::setSizeX(int x){
    size.setWidth(x);
}
void SimpleTimeline::setSizeY(int y){
    size.setHeight(y);
}
//bool simpleTimeline::getOnionSkinEnabled(){
//    return onionSkinEnabled;
//}


