#pragma once
#pragma execution_character_set("UTF-8")

#include <QtWidgets/QMainWindow>
#include "ui_CameraControl.h"
#include <opencv2/opencv.hpp>
#include "GuideUSBLiveStream.h"
#include <QDateTime>
#include <QFileDialog>                              // 文件对话框
#include <QScreen>                                  // QT截屏框

#define FPS  50

using namespace cv;
class CameraControl : public QMainWindow
{
    Q_OBJECT

public:
    CameraControl(QWidget *parent = nullptr);
    ~CameraControl();

    void InitCamera();
    void Test();
    void OpenCamera();
    void ImgShow();
    void ImgSave();

    QImage myQImg;
    QTimer* timer;
    QString savePath = "D:/Data/Infrared data2/";

private:
    Ui::CameraControlClass ui;
    bool cameraOpened;
    bool cameraContinuousShot = 0;

private slots:
    void on_openBtn_clicked();
    void on_closeBtn_clicked();
    void timeoutSlot();
    void on_cameraShotBtn_clicked();
    void on_cameraShotBtn2_clicked();

};

