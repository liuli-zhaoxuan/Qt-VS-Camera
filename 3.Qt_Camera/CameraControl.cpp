#include "CameraControl.h"
#include <QTimer>

Mat myImg;
int initFlag;

static void FrameData_callback(const guide_usb_frame_data_t frame_data) {
	if (frame_data.frame_rgb_data_length > 0)
	{
		Mat testMat(frame_data.frame_height, frame_data.frame_width, CV_8UC3, frame_data.frame_rgb_data);
		//cv::Mat testMat(frame_data.frame_height, frame_data.frame_width, CV_16SC1, frame_data.frame_yuv_data);
		myImg = testMat.clone();
	}
}

static void DeviceConnectStatus_callback(const guide_usb_device_status_e device_status) {
	std::cout << "device_status:" << device_status << std::endl;
}

// 视频流回调函数,设备连接回调函数
OnFrameDataReceivedCB pFrameProc = FrameData_callback;
OnDeviceConnectStatusCB pDevStatus = DeviceConnectStatus_callback;
guide_usb_device_info_t myDev;

CameraControl::CameraControl(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    InitCamera();
	
	timer = new QTimer;

	connect(ui.openBtn, SIGNAL(clicked(bool)), this, SLOT(on_openBtn_clicked()));
	connect(ui.closeBtn, SIGNAL(clicked(bool)), this, SLOT(on_closeBtn_clicked()));
	connect(timer, &QTimer::timeout, this, &CameraControl::timeoutSlot);
	connect(ui.cameraShotBtn, SIGNAL(clicked(bool)), this, SLOT(on_cameraShotBtn_clicked()), Qt::UniqueConnection);
	connect(ui.cameraShotBtn2, SIGNAL(clicked(bool)), this, SLOT(on_cameraShotBtn2_clicked()), Qt::UniqueConnection);
}

CameraControl::~CameraControl()
{}

void CameraControl::InitCamera() {
	initFlag = Initialize();								// SDK 相机初始化

	if (initFlag == -1) {
		ui.MessageLabel->setText("未找到设备");
	}
	else if (initFlag < -1) {
		ui.MessageLabel->setText("设备初始化失败!");
	}
	else {
		ui.MessageLabel->setText("设备初始化成功");
	}

	device_info_list devlist;
	int ret2 = GetDeviceList(&devlist);

	guide_usb_video_mode_e videoMode = YUV;
	//myDev.width = 640;
	//myDev.height = 512;
	myDev.width = 1280;
	myDev.height = 1024;
	myDev.video_mode = videoMode;
	OpenCamera();

}

void CameraControl::Test() {
	ui.MessageLabel->setText("test");
}

void CameraControl::ImgShow() {

	if (initFlag == 1) {
		ui.ConnectStatusLabel->setText("传输中");
		myQImg = QImage((const unsigned char*)(myImg.data), myImg.cols, myImg.rows, QImage::Format_RGB888).copy();
		ui.ViewLabel->setPixmap(QPixmap::fromImage(myQImg.scaled(ui.ViewLabel->size(), Qt::KeepAspectRatio)));
	}
	else
	{
		ui.MessageLabel->setText("相机未初始化");
	}
	
}

void CameraControl::OpenCamera() {
	int ret = OpenStream(&myDev, pFrameProc, pDevStatus);
	//ui.ConnectStatusLabel->setNum(ret);
	ui.ConnectStatusLabel->setText(QString::number(ret));
}

void CameraControl::on_openBtn_clicked() {
	timer->start(1000/ FPS);
	cameraOpened = 1;
}

void CameraControl::on_closeBtn_clicked() {
	if (initFlag == 1) {
		timer->stop();
		ui.ConnectStatusLabel->setText("通道关闭");
		ui.MessageLabel_2->setText("------------");
		cameraOpened = 0;
		ui.ViewLabel->clear();
	}
	else
	{
		ui.MessageLabel->setText("相机未初始化");
	}
}

void CameraControl::timeoutSlot() {
	//定时器操作
	ImgShow();
	if (cameraContinuousShot) ImgSave();
}

void CameraControl::on_cameraShotBtn_clicked() {
	ImgSave();
}

void CameraControl::ImgSave() {

	if (cameraOpened) {
		QDateTime currentDateTime = QDateTime::currentDateTime();
		// 将日期和时间格式化为字符串
		QString currentDateTimeString = currentDateTime.toString("MMd_hhmmss_zzz");
		QString imageName = savePath + "Infrared image" + currentDateTimeString + ".png";

		bool saved = myQImg.save(imageName);
		if (saved) {
			ui.MessageLabel->setText("图像保存成功！");
		}
		else {
			ui.MessageLabel->setText("图像保存失败！");
		}
	}
	else {
		ui.MessageLabel->setText("相机未打开！");
	}
}

void CameraControl::on_cameraShotBtn2_clicked() {
	if (initFlag == 1) {
		if (cameraOpened) {
			cameraContinuousShot = !cameraContinuousShot;
			if (cameraContinuousShot) {
				ui.MessageLabel_2->setText("连续采图ing");
			}
			else ui.MessageLabel_2->setText("------------");
		}
	}
	else
	{
		ui.MessageLabel->setText("相机未初始化");
	}
}