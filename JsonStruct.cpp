#include <QVector>
#include <QString>
#include <QJsonValue>
struct JsonPixel{
    QVector<int> rgb;
//    QString serialize(){
//        QString json = "[";
//        foreach(int i , rgb){
//            json.push_back(i + ", ");
//        }
//        json.truncate(json.size()-2);
//        json.push_back("]");
//        return json;
//    }

};

struct JsonRow{
    QVector<JsonPixel> pixels;
//    QString serialize(){
//        QString jsonString = "";
//        foreach (JsonPixel pixel, pixels) {
//            jsonString.push_back(pixel.serialize());
//        }
//        return jsonString;
//    }

};

struct JsonFrame{
    QVector<JsonRow> rows;
//    QString serialize(){
//        QString jsonString = "";
//        foreach (JsonRow row, rows) {
//            jsonString.push_back(row.serialize());
//        }
//        return jsonString;
};
