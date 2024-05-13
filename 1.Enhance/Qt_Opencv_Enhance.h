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

    // ���з���
    void initMainWindow();
    void imgShow();
    void imgProc(float con, int bri);

    // ȫ�ֱ���
    Mat myImg;          // ����ͼƬ��������������úʹ���
    QImage myQImg;      // ����ͼƬ����תΪ�ļ����̻�����ʾ��
private:
    Ui::Qt_Opencv_EnhanceClass ui;

private slots:
    void contrast_slider_Moved(int position);
    void contrast_slider_valueChanged(int value);
    void brightness_slider_Moved(int position);
    void brightness_slider_valueChanged(int value);
    void pushbtn();
};

