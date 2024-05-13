#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpencvFilter.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>                              // �ļ��Ի���
#include <QScreen>                                  // QT������

using namespace cv;

class OpencvFilter : public QMainWindow
{
    Q_OBJECT

public:
    OpencvFilter(QWidget *parent = nullptr);
    ~OpencvFilter();

    void InitMainWindow();
    void imgProc(int kernel);
    void imgShow();
    QImage myBlurQImg;                      // �����ֵ�˲�ͼƬ
private:
    Ui::OpencvFilterClass ui;
    Mat myImg;                              // ����ͼƬ

    QImage myGaussianQImg;                  // �����˹�˲�ͼƬ
    QImage myMedianQImg;                    // ������ֵ�˲�ͼƬ
    QImage myBilateralQImg;                 // ����˫���˲�ͼƬ

private slots:
    void kernelslider_Moved(int position);
    void kernelslider_Valuechaged(int value);
    void on_saveAsbtn_clicked();
};
