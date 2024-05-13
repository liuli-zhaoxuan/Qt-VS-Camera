#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpencvFilter.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>                              // ÎÄ¼þ¶Ô»°¿ò
#include <QScreen>                                  // QT½ØÆÁ¿ò

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
    QImage myBlurQImg;                      // ±£´æ¾ùÖµÂË²¨Í¼Æ¬
private:
    Ui::OpencvFilterClass ui;
    Mat myImg;                              // »º´æÍ¼Æ¬

    QImage myGaussianQImg;                  // ±£´æ¸ßË¹ÂË²¨Í¼Æ¬
    QImage myMedianQImg;                    // ±£´æÖÐÖµÂË²¨Í¼Æ¬
    QImage myBilateralQImg;                 // ±£´æË«±ßÂË²¨Í¼Æ¬

private slots:
    void kernelslider_Moved(int position);
    void kernelslider_Valuechaged(int value);
    void on_saveAsbtn_clicked();
};
