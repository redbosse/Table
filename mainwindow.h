#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QColorDialog>
#include <QImage>
#include <vector>

#include "customscene.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer* timer;

    vector<customScene*> scene;

    size_t sceneId = 0;

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent * event);
    customScene* Scene(){
        return  scene.at(sceneId);
    }


private slots:
     void slotTimer();
     void setColor();
     void resizePen(int value);
     void clearScene();
     void nextScene();
     void prevScene();
     void saveInImage();
};

#endif // MAINWINDOW_H
