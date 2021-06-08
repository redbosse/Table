#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QColorDialog>
#include <QImage>
#include <QCursor>

#include <vector>


#include "customscene.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    void closeEvent(QCloseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


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
    QImage renderImage(size_t index);
    void reloadCustomCursor();


    QCursor custom_cursor;

    QImage standart_cursor;
    QImage cleaner_cursor;
    QImage circle_cursor;
    QImage line_cursor;
    QImage rectangle_cursor;


private slots:
     void slotTimer();
     void setColor();
     void resizePen(int value);
     void clearScene();
     void nextScene();
     void prevScene();
     void saveInImage();
     void saveInImages();
     void saveInPDF();
     void Checked(int index);
     void verification();
     void Cleaner();
     void SetBackgroundColor();
     void CleanerVariant();
};

#endif // MAINWINDOW_H
