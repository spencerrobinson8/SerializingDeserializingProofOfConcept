#include "simpletimeline.h"
#include "ui_simpletimeline.h"

SimpleTimeline::SimpleTimeline(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimpleTimeline)
{
    ui->setupUi(this);
}



SimpleTimeline::SimpleTimeline(unsigned int sizeX, unsigned int sizeY, QWidget *parent)
    : QMainWindow(parent)
    , activeLayer(0)
    , activeFrame(0)
    , frameDuration(100)
    , size(sizeX, sizeY)
{


}

SimpleTimeline::~SimpleTimeline(){
    delete ui;
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
//bool simpleTimeline::getOnionSkinEnabled(){
//    return onionSkinEnabled;
//}


