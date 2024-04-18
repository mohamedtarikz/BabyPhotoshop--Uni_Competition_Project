/********************************************************************************
** Form generated from reading UI file 'photoshop.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHOTOSHOP_H
#define UI_PHOTOSHOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *filters;
    QGridLayout *gridLayout;
    QPushButton *wano_day;
    QPushButton *black_an_white;
    QPushButton *pixel_image;
    QPushButton *rotate;
    QPushButton *InferaRed;
    QPushButton *oil_painted;
    QPushButton *cropImage;
    QPushButton *gray_scale;
    QPushButton *wanoTv;
    QPushButton *flip_ver;
    QPushButton *skewButton;
    QPushButton *frame_image;
    QPushButton *flip_hori;
    QPushButton *channed_swaped;
    QPushButton *editBrightness;
    QPushButton *blurButton;
    QPushButton *megre_Image;
    QPushButton *wanoNight;
    QPushButton *resize_image;
    QPushButton *detected_image;
    QPushButton *invert_image;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QLabel *image_label;
    QSlider *brightness;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QPushButton *insert_image;
    QPushButton *clear_image;
    QPushButton *save_image;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1198, 552);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"					background-image: url(:/background.jpg) no-repeat center;\n"
"                    background-position: center;\n"
"                    background-size: 100%;\n"
"                    background-repeat: no-repeat;\n"
"                    background-clip: border-box;\n"
"                    background-origin: padding-box;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        filters = new QFrame(centralwidget);
        filters->setObjectName("filters");
        filters->setMaximumSize(QSize(16777215, 120));
        filters->setFrameShape(QFrame::StyledPanel);
        filters->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(filters);
        gridLayout->setObjectName("gridLayout");
        wano_day = new QPushButton(filters);
        wano_day->setObjectName("wano_day");
        wano_day->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/wano day.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/wano day_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/wano day_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(wano_day, 2, 6, 1, 1);

        black_an_white = new QPushButton(filters);
        black_an_white->setObjectName("black_an_white");
        black_an_white->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/Black and white.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/Black and white_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/Black and white_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(black_an_white, 0, 1, 1, 1);

        pixel_image = new QPushButton(filters);
        pixel_image->setObjectName("pixel_image");
        pixel_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/pixelate.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/pixelate_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/pixelate_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(pixel_image, 2, 10, 1, 1);

        rotate = new QPushButton(filters);
        rotate->setObjectName("rotate");
        rotate->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/rotate.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/rotate_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/rotate_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(rotate, 0, 6, 1, 1);

        InferaRed = new QPushButton(filters);
        InferaRed->setObjectName("InferaRed");
        InferaRed->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/infera red.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/infera red_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/infera red_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(InferaRed, 2, 9, 1, 1);

        oil_painted = new QPushButton(filters);
        oil_painted->setObjectName("oil_painted");
        oil_painted->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/oil paint.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/oil paint_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/oil paint_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(oil_painted, 2, 8, 1, 1);

        cropImage = new QPushButton(filters);
        cropImage->setObjectName("cropImage");
        cropImage->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/crop.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/crop_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/crop_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(cropImage, 0, 9, 1, 1);

        gray_scale = new QPushButton(filters);
        gray_scale->setObjectName("gray_scale");
        gray_scale->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/grey scale.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/grey scale_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/grey scale_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(gray_scale, 0, 0, 1, 1);

        wanoTv = new QPushButton(filters);
        wanoTv->setObjectName("wanoTv");
        wanoTv->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/wano tv.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/wano tv_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/wano tv_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(wanoTv, 2, 5, 1, 1);

        flip_ver = new QPushButton(filters);
        flip_ver->setObjectName("flip_ver");
        flip_ver->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/flip v.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/flip v_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/flip v_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(flip_ver, 2, 1, 1, 1);

        skewButton = new QPushButton(filters);
        skewButton->setObjectName("skewButton");
        skewButton->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/skew.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/skew_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/skew_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));
        skewButton->setAutoDefault(false);
        skewButton->setFlat(false);

        gridLayout->addWidget(skewButton, 0, 11, 1, 1);

        frame_image = new QPushButton(filters);
        frame_image->setObjectName("frame_image");
        frame_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/frame.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/frame_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/frame_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(frame_image, 0, 8, 1, 1);

        flip_hori = new QPushButton(filters);
        flip_hori->setObjectName("flip_hori");
        flip_hori->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/flip h.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/flip h_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/flip h_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(flip_hori, 2, 0, 1, 1);

        channed_swaped = new QPushButton(filters);
        channed_swaped->setObjectName("channed_swaped");
        channed_swaped->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/color swap.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/color swap_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/color swap_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"	position: absolute;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(channed_swaped, 2, 11, 1, 1);

        editBrightness = new QPushButton(filters);
        editBrightness->setObjectName("editBrightness");
        editBrightness->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/brightness.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/brightness_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/brightness_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(editBrightness, 2, 12, 1, 1);

        blurButton = new QPushButton(filters);
        blurButton->setObjectName("blurButton");
        blurButton->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/blur.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/blur_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/blur_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));
        blurButton->setIconSize(QSize(80, 20));
        blurButton->setFlat(false);

        gridLayout->addWidget(blurButton, 0, 12, 1, 1);

        megre_Image = new QPushButton(filters);
        megre_Image->setObjectName("megre_Image");
        megre_Image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/Merge.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/Merge_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/Merge_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(megre_Image, 0, 13, 1, 1);

        wanoNight = new QPushButton(filters);
        wanoNight->setObjectName("wanoNight");
        wanoNight->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/wano night.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/wano night_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/wano night_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(wanoNight, 2, 3, 1, 1);

        resize_image = new QPushButton(filters);
        resize_image->setObjectName("resize_image");
        resize_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/resize.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/resize_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/resize_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(resize_image, 0, 10, 1, 1);

        detected_image = new QPushButton(filters);
        detected_image->setObjectName("detected_image");
        detected_image->setMinimumSize(QSize(100, 50));
        detected_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/detect edge.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/detect edge_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/detect edge_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(detected_image, 0, 3, 1, 1);

        invert_image = new QPushButton(filters);
        invert_image->setObjectName("invert_image");
        invert_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/invert colors.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/invert colors_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/invert colors_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout->addWidget(invert_image, 0, 5, 1, 1);


        verticalLayout->addWidget(filters, 0, Qt::AlignHCenter);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName("horizontalLayout");
        image_label = new QLabel(frame_2);
        image_label->setObjectName("image_label");
        image_label->setEnabled(true);
        image_label->setMinimumSize(QSize(850, 250));
        image_label->setMaximumSize(QSize(16777215, 16777215));
        image_label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	image: url(:/insert_Banner.png);\n"
"}"));
        image_label->setScaledContents(true);
        image_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(image_label, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(frame_2);

        brightness = new QSlider(centralwidget);
        brightness->setObjectName("brightness");
        brightness->setMinimumSize(QSize(200, 0));
        brightness->setMaximumSize(QSize(16777215, 16777215));
        brightness->setMouseTracking(false);
        brightness->setMinimum(5);
        brightness->setMaximum(100);
        brightness->setSingleStep(5);
        brightness->setPageStep(5);
        brightness->setOrientation(Qt::Horizontal);
        brightness->setTickPosition(QSlider::NoTicks);

        verticalLayout->addWidget(brightness, 0, Qt::AlignHCenter);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 60));
        frame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"}"));
        frame->setFrameShape(QFrame::NoFrame);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setVerticalSpacing(0);
        insert_image = new QPushButton(frame);
        insert_image->setObjectName("insert_image");
        insert_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/insert.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/insert_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/insert_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"	position: absolute;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout_2->addWidget(insert_image, 0, 0, 1, 1);

        clear_image = new QPushButton(frame);
        clear_image->setObjectName("clear_image");
        clear_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/clear.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/clear_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/clear_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout_2->addWidget(clear_image, 0, 1, 1, 1);

        save_image = new QPushButton(frame);
        save_image->setObjectName("save_image");
        save_image->setStyleSheet(QString::fromUtf8("/* Normal state */\n"
"QPushButton {\n"
"    min-width: 50px; \n"
"    min-height: 25px; \n"
"    max-width: 300px; \n"
"   	max-height: 150px; \n"
"    height: 50%;\n"
"	width:100%;\n"
"    border-radius: 20px;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"	background-color: transparent;\n"
"	image: url(:/buttons/normal/save.png);\n"
"	background: none;\n"
"	border: none;\n"
"	background-repeat: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	image: url(:/buttons/hover/save_hover.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	image: url(:/buttons/pressed/save_pressed.png);\n"
"}\n"
"\n"
"QPushButton .icon {\n"
"    width: 100%;\n"
"    height: 100%;\n"
"}\n"
"\n"
"QPushButton .text {\n"
"    font-size: 10px;\n"
"    margin-left: 5px;\n"
"}\n"
"\n"
"/* Hovering state */\n"
"QPushButton:hover .icon {\n"
"\n"
"}\n"
"\n"
"QPushButton:hover .text {\n"
"\n"
"}\n"
""));

        gridLayout_2->addWidget(save_image, 0, 2, 1, 1);


        verticalLayout->addWidget(frame, 0, Qt::AlignHCenter);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1198, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        skewButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        wano_day->setText(QString());
        black_an_white->setText(QString());
        pixel_image->setText(QString());
        rotate->setText(QString());
        InferaRed->setText(QString());
        oil_painted->setText(QString());
        cropImage->setText(QString());
        gray_scale->setText(QString());
        wanoTv->setText(QString());
        flip_ver->setText(QString());
        skewButton->setText(QString());
        frame_image->setText(QString());
        flip_hori->setText(QString());
        channed_swaped->setText(QString());
        editBrightness->setText(QString());
        blurButton->setText(QString());
        megre_Image->setText(QString());
        wanoNight->setText(QString());
        resize_image->setText(QString());
        detected_image->setText(QString());
        invert_image->setText(QString());
        image_label->setText(QString());
        insert_image->setText(QString());
        save_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHOTOSHOP_H
