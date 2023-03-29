#ifndef SIMPLETIMELINE_H
#define SIMPLETIMELINE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SimpleTimeline; }
QT_END_NAMESPACE

class SimpleTimeline : public QMainWindow
{
    Q_OBJECT

public:
    SimpleTimeline(QWidget *parent = nullptr);
    ~SimpleTimeline();
    SimpleTimeline(unsigned int sizeX, unsigned int sizeY, QWidget* parent = nullptr);

      QList<QPixmap*> getFrames();
      unsigned int getActiveLayer();
      unsigned int getActiveFrame();
      unsigned int getFrameDuration();
      unsigned int getSizeX();
      unsigned int getSizeY();
      void addFrame(QPixmap s);
//    bool getOnionSkinEnabled();

private:
    Ui::SimpleTimeline *ui;
    QList<QPixmap*> frames;
    unsigned int activeLayer;
    unsigned int activeFrame;
    unsigned int frameDuration;
    QSize size;
};
#endif // SIMPLETIMELINE_H
