#include "simpletimeline.h"
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

struct JsonPixel{
    QVector<int> rgb;
    QString serialize(){
        QString json = "[";
        QJsonArray arr;
        foreach(int i , rgb){
            QString number = QString::number(i);
            json.push_back(number + ", ");
            arr.push_back(i);
        }
        json.truncate(json.size()-2);
        json.push_back("]");
        return json;
    }

};

struct JsonRow{
    QVector<JsonPixel> pixels;
    QJsonValue serialize(){
        QString jsonString = "";
        foreach (JsonPixel pixel, pixels) {
            jsonString.push_back(pixel.serialize());
        }
        return jsonString;
    }

};

struct JsonFrame{
    QVector<JsonRow> rows;
    QJsonArray serialize(){
        QJsonArray jsonString;
        foreach (JsonRow row, rows) {
            jsonString.push_back(row.serialize());
        }
        return jsonString;
    }
};

struct JsonFrames{
    QVector<JsonFrame> frames;
    QJsonObject serialize(){
        QString frameString;

        QJsonObject obj;
        int number = 0;
        foreach (JsonFrame frame, frames) {
            QJsonArray arr;
            QString numberS = QString::number(number);
            frameString = "frame" + numberS;
            number++;
            arr.push_back(frame.serialize());
            obj[frameString] = arr;
        }

        return obj;
    }
};

void save(SimpleTimeline& t){

    QJsonObject jTimeline;
    jTimeline["height"] =(int) t.getSizeY();
    jTimeline["width"] = (int)t.getSizeX();
    jTimeline["numberOfFrames"] = (int)t.getFrames().size();
    //JsonPixel pixel;
//    JsonFrame frame;
    //JsonRow row;
    JsonFrames frames;
    foreach(QPixmap* p, t.getFrames()) {
        QImage image = p->toImage();
        JsonFrame frame;
        for(int x = 0; x < (int) t.getSizeX(); x++) {
            JsonRow row;


            for(int y = 0; y < (int)t.getSizeY(); y++){
                JsonPixel pixel;
                pixel.rgb.push_back(image.pixelColor(x,y).red());
                pixel.rgb.push_back(image.pixelColor(x,y).green());
                pixel.rgb.push_back(image.pixelColor(x,y).blue());
                pixel.rgb.push_back(image.pixelColor(x,y).alpha());
                row.pixels.push_back(pixel);
            }
            frame.rows.push_back(row);

        }
        frames.frames.push_back(frame);

    }
    jTimeline["frames"] = frames.serialize();


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
    SimpleTimeline* w = new SimpleTimeline(4, 4);
    w->addFrame(QPixmap(":/img/me2.png"));
    w->addFrame(QPixmap(":/img/me.png"));
    save(*w);
    load();

    w->show();
    return a.exec();
}
