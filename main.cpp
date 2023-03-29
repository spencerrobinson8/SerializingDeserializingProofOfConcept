#include "simpletimeline.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include <QDir>
#include <QVector>
#include <QDebug>
#include "JsonStruct.cpp"

void save(SimpleTimeline& t){

    QJsonObject jTimeline;
    jTimeline["height"] =(int) t.getSizeY();
    jTimeline["width"] = (int)t.getSizeX();
    jTimeline["numberOfFrames"] = (int)t.getFrames().size();
    QList<QRgb> list;
    int n = 0;
    QJsonArray arr2;
    QJsonArray arr;
    JsonPixel pixel;
    JsonFrame frame;
    JsonRow row;
    foreach(QPixmap* p, t.getFrames()) {
        QImage image = p->toImage();
        for(int x = 0; x < image.width(); x++) {

            for(int y = 0; y < image.height(); y++){
                pixel.rgb.push_back(image.pixelColor(x,y).red());
                pixel.rgb.push_back(image.pixelColor(x,y).green());
                pixel.rgb.push_back(image.pixelColor(x,y).blue());
                pixel.rgb.push_back(image.pixelColor(x,y).alpha());
                row.pixels.push_back(pixel);
            }
            frame.rows.push_back(row);
        }
        jTimeline["frame" + n] = "frame.serialize()";
        n++;
    }


    QJsonDocument doc( jTimeline );
    QFile file("JsonFile.ssp");
    if(file.open(QFile::WriteOnly)){
        file.write(doc.toJson());
    }
    file.close();
}

void load(){

}
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleTimeline w = new SimpleTimeline(64, 64);
    w.addFrame(QPixmap(":/img/me2"));
//    timeline->addFrame();
    save(w);
    load();
    w.show();
    return a.exec();
}
