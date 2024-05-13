#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_Opencv_Enhance.h"
#include <opencv2/opencv.hpp>

using namespace cv;

class Qt_Opencv_Enhance : public QMainWindow
{
    Q_OBJECT

public:
    Qt_Opencv_Enhance(QWidget *parent = nullptr);
    ~Qt_Opencv_Enhance();

    // 公有方法
    void initMainWindow();
    void imgShow();
    void imgProc(float con, int bri);

    // 全局变量
    Mat myImg;          // 缓存图片（供程序代码引用和处理）
    QImage myQImg;      // 保存图片（可转为文件存盘或者显示）
private:
    Ui::Qt_Opencv_EnhanceClass ui;

private slots:
    void contrast_slider_Moved(int position);
    void contrast_slider_valueChanged(int value);
    void brightness_slider_Moved(int position);
    void brightness_slider_valueChanged(int value);
    void pushbtn();
};

