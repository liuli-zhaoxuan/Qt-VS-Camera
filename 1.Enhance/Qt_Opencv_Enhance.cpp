#include "Qt_Opencv_Enhance.h"

Qt_Opencv_Enhance::Qt_Opencv_Enhance(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initMainWindow();

    connect(ui.contrast_slider, SIGNAL(sliderMoved(int)), this, SLOT(contrast_slider_Moved(int)));
    connect(ui.contrast_slider, SIGNAL(valueChanged(int)), this, SLOT(contrast_slider_valueChanged(int)));
    connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(pushbtn()));
    connect(ui.brightness_slider, SIGNAL(sliderMoved(int)), this, SLOT(brightness_slider_Moved(int)));
    connect(ui.contrast_slider, SIGNAL(valueChanged(int)), this, SLOT(contrast_slider_valueChanged(int)));
}

Qt_Opencv_Enhance::~Qt_Opencv_Enhance()
{}

// ��ʼ��
void Qt_Opencv_Enhance::initMainWindow()
{
    QString imgPath = "D:/Project_2/15.Camera_QT/QTproject/1.Enhance/1.jpeg";
    //Mat imgData = imread(imgPath.toLatin1().data());                        // ��ȡͼƬ���ݣ�.data()����ָ����QStringתΪlatin�ַ��ĵ�ַ
    Mat imgData = imread(imgPath.toStdString());
    //cvtColor(imgData, imgData, COLOR_BGR2BGRA);                             // ͼƬ��ʽת��
    myImg = imgData;
    myQImg = QImage((const unsigned char*)(imgData.data), imgData.cols, imgData.rows, QImage::Format_BGR888);
    
    imgShow();
}


// ��Qt��������ʾͼƬ
void Qt_Opencv_Enhance::imgShow()
{
    ui.viewLabel->setPixmap(QPixmap::fromImage(myQImg.scaled(ui.viewLabel->size(), Qt::KeepAspectRatio)));
}

// ͼ����
void Qt_Opencv_Enhance::imgProc(float con, int bri)
{
    Mat imgSrc = myImg;
    Mat imgDst = Mat::zeros(imgSrc.size(), imgSrc.type());                  // ��ʼ���ɿյ�����������
    imgSrc.convertTo(imgDst, -1, con, bri);
    myQImg = QImage((const unsigned char*)(imgDst.data), imgDst.cols, imgDst.rows, QImage::Format_RGB888);
    
    imgShow();

}

void Qt_Opencv_Enhance::contrast_slider_Moved(int position)
{
    imgProc(position / 33.3, 0);
    ui.label->setText("done 1");
}

void Qt_Opencv_Enhance::contrast_slider_valueChanged(int value)
{
    imgProc(value / 33.3, 0);
}

void Qt_Opencv_Enhance::brightness_slider_Moved(int position)
{
    imgProc(1.0, position);
    ui.label->setText("done 2");
}

void Qt_Opencv_Enhance::brightness_slider_valueChanged(int value)
{
    imgProc(1.0, value);
}

void Qt_Opencv_Enhance::pushbtn()
{
    ui.label->setText("Hello");
}