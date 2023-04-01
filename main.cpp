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
#include <QApplication>
#include <QByteArray>

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

void save(SimpleTimeline& t, QString path){

    QJsonObject jTimeline;
    jTimeline["height"] =(int) t.getSizeY();
    jTimeline["width"] = (int)t.getSizeX();
    jTimeline["numberOfFrames"] = (int)t.getFrames().size();
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
    QFile file(path);
    if(file.open(QFile::WriteOnly)){
        file.write(doc.toJson());
    }
    file.close();
}

SimpleTimeline* load(QString path){
    QFile file(path);
    QByteArray jsonData;
    if(file.open(QFile::ReadOnly)){
        jsonData = file.readAll();
    }
    else{
        return nullptr;
    }
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    QJsonObject obj = jsonDocument.object();
    QJsonValue x = obj.value("width");
    QJsonValue y = obj.value("height");
    QJsonValue numOfFrames = obj.value("numberOfFrames");
    SimpleTimeline* st = new SimpleTimeline(x.toInt(),y.toInt());
    QJsonValue frames = obj.value("frames");
    QJsonObject frameObject = frames.toObject();
    QList<QImage> images;
    for(int i = 0; i<numOfFrames.toInt(); i++){
        QString framen = "frame" + QString::number(i);
        QJsonValue row = frameObject.value(framen);
        QImage image(x.toInt(), y.toInt(), QImage::Format_RGB32);
        image.fill(QColor(0,0,0,0));
        QJsonArray pixels = row[0].toArray();
        for(int j = 0; j<y.toInt(); j++){
            QJsonValue pixelRow = pixels[j];
            QString pixelRowString = pixelRow.toString();
            pixelRowString = pixelRowString.remove("]");
            QStringList rowsString =pixelRowString.split("[", Qt::SkipEmptyParts);
            for(int k = 0; k < x.toInt(); k++){

                QStringList pixelString = rowsString[k].split(",");
                int r, g, b, a;
                r=pixelString[0].toInt();
                g=pixelString[1].toInt();
                b=pixelString[2].toInt();
                a=pixelString[3].toInt();
                image.setPixelColor(k,j, QColor(r,g,b,a));
            }
        }
        images.push_back(image);

    }
    foreach(QImage img, images){
        QPixmap* pixmap = new QPixmap(x.toInt(), y.toInt());
        pixmap->convertFromImage(img);
        st->addFrame(pixmap);
    }
    return st;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleTimeline* w = new SimpleTimeline(4, 4);
    QPixmap* frameOne= new QPixmap(":/img/me2.png");
    QPixmap* frameTwo = new QPixmap(":/img/me.png");
    w->addFrame(frameOne);
    w->addFrame(frameTwo);
    w->addFrame(frameOne);
    w->addFrame(frameTwo);
    QString path = QDir::currentPath() + "/JsonFile.ssp";
    save(*w, path);

    SimpleTimeline* s = load(path);
    path = QDir::currentPath() + "/OtherJsonFile.ssp";
    save(*s, path);


    w->show();
    return a.exec();
}
