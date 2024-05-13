#include "OpencvFilter.h"

OpencvFilter::OpencvFilter(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    InitMainWindow();

    connect(ui.kernelSlider, SIGNAL(sliderMoved(int)), this, SLOT(kernelslider_Moved(int)));
    connect(ui.kernelSlider, SIGNAL(valueChanged(int)), this, SLOT(kernelslider_Valuechaged(int)));
    connect(ui.saveAsBtn, SIGNAL(clicked(bool)), this, SLOT(on_saveAsbtn_clicked()));
}

OpencvFilter::~OpencvFilter()
{}

void OpencvFilter::InitMainWindow()
{
    QString imgPath = "D:/Project_2/15.Camera_QT/QTproject/2.Filter/mm.jpg";
    Mat imgData = imread(imgPath.toStdString());
    myImg = imgData;
    cvtColor(imgData, imgData, COLOR_BGR2RGB);
    myBlurQImg = QImage((const unsigned char*)(imgData.data), imgData.cols, imgData.rows, QImage::Format_RGB888);
    myGaussianQImg = myBlurQImg;
    myMedianQImg = myBlurQImg;
    myBilateralQImg = myBlurQImg;
    imgShow();

}

void OpencvFilter::imgProc(int kernel)
{
    Mat imgSrc = myImg;
    Mat imgDst1 = imgSrc.clone();
    for(int i = 1; i < kernel; i = i+2)
    {
        blur(imgSrc, imgDst1, Size(i, i), Point(-1, -1));
    }
    myBlurQImg = QImage((const unsigned char*)(imgDst1.data), imgDst1.cols, imgDst1.rows, QImage::Format_RGB888);

    Mat imgDst2 = imgSrc.clone();
    for (int i = 1; i < kernel; i = i + 2)
    {
        GaussianBlur(imgSrc, imgDst2, Size(i, i), 0, 0);
    }
    myGaussianQImg = QImage((const unsigned char*)(imgDst2.data), imgDst2.cols, imgDst2.rows, QImage::Format_RGB888);

    Mat imgDst3 = imgSrc.clone();
    for (int i = 1; i < kernel; i = i + 2)
    {
        medianBlur(imgSrc, imgDst3, i);
    }
    myMedianQImg = QImage((const unsigned char*)(imgDst3.data), imgDst3.cols, imgDst3.rows, QImage::Format_RGB888);

    Mat imgDst4= imgSrc.clone();
    for (int i = 1; i < kernel; i = i + 2)
    {
        bilateralFilter(imgSrc, imgDst4, i, i*2, i/2);
    }
    myBilateralQImg = QImage((const unsigned char*)(imgDst4.data), imgDst4.cols, imgDst4.rows, QImage::Format_RGB888);
    
    imgShow();
}

void OpencvFilter::imgShow()
{
    ui.blurViewLabel->setPixmap(QPixmap::fromImage(myBlurQImg.scaled(ui.blurViewLabel->size(), Qt::KeepAspectRatio)));  // 显示均值滤波
    ui.gaussianViewLabel->setPixmap(QPixmap::fromImage(myGaussianQImg.scaled(ui.gaussianViewLabel->size(), Qt::KeepAspectRatio)));  // 显示均值滤波
    ui.mediaViewLabel->setPixmap(QPixmap::fromImage(myMedianQImg.scaled(ui.mediaViewLabel->size(), Qt::KeepAspectRatio)));  // 显示均值滤波
    ui.bilateralViewLabel->setPixmap(QPixmap::fromImage(myBilateralQImg.scaled(ui.bilateralViewLabel->size(), Qt::KeepAspectRatio)));  // 显示均值滤波
}

void OpencvFilter::kernelslider_Moved(int position)
{
    imgProc(position);
}

void OpencvFilter::kernelslider_Valuechaged(int value)
{
    imgProc(value);
}

void OpencvFilter::on_saveAsbtn_clicked() 
{
    QString filename = QFileDialog::getSaveFileName(this, tr("保存图片"), "kaola", tr("图片文件(*.png *.jpg *.jpeg *.bmp)"));
    QScreen* screen = QGuiApplication::primaryScreen();
    if(ui.blurRadioBtn->isChecked())
        screen->grabWindow(ui.blurViewLabel->winId()).save(filename);
    if (ui.gaussianRadioBtn->isChecked())
        screen->grabWindow(ui.gaussianViewLabel->winId()).save(filename);
    if (ui.medianRadioBtn->isChecked())
        screen->grabWindow(ui.mediaViewLabel->winId()).save(filename);
    if (ui.bilateralRadioBtn->isChecked())
        screen->grabWindow(ui.bilateralViewLabel->winId()).save(filename);
}