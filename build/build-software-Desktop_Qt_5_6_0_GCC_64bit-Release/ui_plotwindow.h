/********************************************************************************
** Form generated from reading UI file 'plotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWINDOW_H
#define UI_PLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QToolButton *openFile;
    QLabel *info;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_8;
    QPushButton *nextFrame;
    QPushButton *computeOne;
    QPushButton *Compute;
    QPushButton *prevFrame;
    QPushButton *animate;
    QPushButton *goodReg;
    QPushButton *badReg;
    QFrame *line_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *BFA;
    QRadioButton *SAA;
    QRadioButton *FA;
    QRadioButton *CFA;
    QVBoxLayout *verticalLayout_10;
    QRadioButton *SOMA;
    QRadioButton *ABC;
    QRadioButton *ES;
    QFrame *line_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *NMI;
    QRadioButton *NED;
    QRadioButton *NCD;
    QRadioButton *NCC;
    QFrame *line_6;
    QFrame *line_7;
    QGroupBox *visuals;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *channelsRadio;
    QRadioButton *checkerboardRadio;
    QCheckBox *showRoi;
    QFrame *line_9;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_12;
    QRadioButton *tofirstFrame;
    QRadioButton *toprevFrame;
    QFrame *line_10;
    QVBoxLayout *verticalLayout_13;
    QLabel *transfom;
    QLabel *criteria;
    QFrame *line_8;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_5;
    QSlider *transImage;
    QSpacerItem *horizontalSpacer;
    Plot *histo;
    QSpacerItem *horizontalSpacer_3;
    Plot *label;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QToolButton *toolButton;
    QLabel *label_2;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *PlotWindow)
    {
        if (PlotWindow->objectName().isEmpty())
            PlotWindow->setObjectName(QStringLiteral("PlotWindow"));
        PlotWindow->resize(1366, 768);
        PlotWindow->setMinimumSize(QSize(1366, 768));
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/avmediaplayer.png"), QSize(), QIcon::Normal, QIcon::Off);
        PlotWindow->setWindowIcon(icon);
        PlotWindow->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        centralWidget = new QWidget(PlotWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 50);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));

        verticalLayout_7->addLayout(verticalLayout_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(6, 6, 6, -1);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        openFile = new QToolButton(centralWidget);
        openFile->setObjectName(QStringLiteral("openFile"));
        openFile->setMinimumSize(QSize(40, 40));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setKerning(true);
        openFile->setFont(font);
        openFile->setCursor(QCursor(Qt::PointingHandCursor));
        openFile->setFocusPolicy(Qt::NoFocus);
        openFile->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/img/lc_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFile->setIcon(icon1);
        openFile->setIconSize(QSize(40, 40));
        openFile->setToolButtonStyle(Qt::ToolButtonIconOnly);
        openFile->setArrowType(Qt::NoArrow);

        verticalLayout_5->addWidget(openFile, 0, Qt::AlignHCenter);

        info = new QLabel(centralWidget);
        info->setObjectName(QStringLiteral("info"));
        info->setAutoFillBackground(false);
        info->setFrameShape(QFrame::NoFrame);
        info->setFrameShadow(QFrame::Plain);
        info->setTextFormat(Qt::PlainText);
        info->setWordWrap(true);
        info->setMargin(5);

        verticalLayout_5->addWidget(info);


        horizontalLayout_4->addLayout(verticalLayout_5);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShadow(QFrame::Plain);
        line_4->setFrameShape(QFrame::VLine);

        horizontalLayout_4->addWidget(line_4);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetMaximumSize);
        nextFrame = new QPushButton(centralWidget);
        nextFrame->setObjectName(QStringLiteral("nextFrame"));
        nextFrame->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nextFrame->sizePolicy().hasHeightForWidth());
        nextFrame->setSizePolicy(sizePolicy);
        nextFrame->setMinimumSize(QSize(155, 20));
        nextFrame->setMaximumSize(QSize(16777215, 16777215));
        nextFrame->setFocusPolicy(Qt::NoFocus);
        nextFrame->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"padding-top: 2px;\n"
"padding-bottom: 2px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;\n"
"text-align: left;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/img/lc_nextrecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextFrame->setIcon(icon2);
        nextFrame->setIconSize(QSize(24, 24));
        nextFrame->setAutoRepeatDelay(304);
        nextFrame->setAutoDefault(false);
        nextFrame->setFlat(false);

        verticalLayout_8->addWidget(nextFrame, 0, Qt::AlignLeft);

        computeOne = new QPushButton(centralWidget);
        computeOne->setObjectName(QStringLiteral("computeOne"));
        sizePolicy.setHeightForWidth(computeOne->sizePolicy().hasHeightForWidth());
        computeOne->setSizePolicy(sizePolicy);
        computeOne->setMinimumSize(QSize(155, 20));
        computeOne->setMaximumSize(QSize(16777215, 16777215));
        computeOne->setFocusPolicy(Qt::NoFocus);
        computeOne->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"padding-top: 2px;\n"
"padding-bottom: 2px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;\n"
"text-align: left;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/img/lc_reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        computeOne->setIcon(icon3);
        computeOne->setIconSize(QSize(24, 24));

        verticalLayout_8->addWidget(computeOne);

        Compute = new QPushButton(centralWidget);
        Compute->setObjectName(QStringLiteral("Compute"));
        sizePolicy.setHeightForWidth(Compute->sizePolicy().hasHeightForWidth());
        Compute->setSizePolicy(sizePolicy);
        Compute->setMinimumSize(QSize(155, 20));
        Compute->setMaximumSize(QSize(16777215, 16777215));
        Compute->setFocusPolicy(Qt::NoFocus);
        Compute->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"padding-top: 2px;\n"
"padding-bottom: 2px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;\n"
"text-align: left;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/img/runbasic.png"), QSize(), QIcon::Normal, QIcon::Off);
        Compute->setIcon(icon4);
        Compute->setIconSize(QSize(24, 24));

        verticalLayout_8->addWidget(Compute, 0, Qt::AlignLeft);

        prevFrame = new QPushButton(centralWidget);
        prevFrame->setObjectName(QStringLiteral("prevFrame"));
        sizePolicy.setHeightForWidth(prevFrame->sizePolicy().hasHeightForWidth());
        prevFrame->setSizePolicy(sizePolicy);
        prevFrame->setMinimumSize(QSize(155, 20));
        prevFrame->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setStyleStrategy(QFont::PreferDefault);
        prevFrame->setFont(font1);
        prevFrame->setFocusPolicy(Qt::NoFocus);
        prevFrame->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"padding-top: 2px;\n"
"padding-bottom: 2px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;\n"
"text-align: left;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/img/lc_prevrecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevFrame->setIcon(icon5);
        prevFrame->setIconSize(QSize(24, 24));

        verticalLayout_8->addWidget(prevFrame, 0, Qt::AlignLeft);

        animate = new QPushButton(centralWidget);
        animate->setObjectName(QStringLiteral("animate"));
        animate->setMinimumSize(QSize(0, 20));
        animate->setMaximumSize(QSize(16777215, 16777215));
        animate->setFocusPolicy(Qt::NoFocus);
        animate->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"padding-top: 2px;\n"
"padding-bottom: 2px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;\n"
"text-align: left;"));
        animate->setIcon(icon);
        animate->setIconSize(QSize(24, 24));

        verticalLayout_8->addWidget(animate);

        goodReg = new QPushButton(centralWidget);
        goodReg->setObjectName(QStringLiteral("goodReg"));
        goodReg->setMinimumSize(QSize(0, 20));
        goodReg->setMaximumSize(QSize(16777215, 16777215));
        goodReg->setFocusPolicy(Qt::NoFocus);
        goodReg->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"padding-top: 2px;\n"
"padding-bottom: 2px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;\n"
"text-align: left;"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/img/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        goodReg->setIcon(icon6);
        goodReg->setIconSize(QSize(24, 24));

        verticalLayout_8->addWidget(goodReg);

        badReg = new QPushButton(centralWidget);
        badReg->setObjectName(QStringLiteral("badReg"));
        badReg->setFocusPolicy(Qt::NoFocus);
        badReg->setStyleSheet(QLatin1String("margin-left: 5px;\n"
"margin-right: 5px;\n"
"padding: 5px;\n"
"padding-top: 2px;\n"
"padding-bottom: 2px;\n"
"border-radius: 5%;\n"
"border: 1px solid darkgray;\n"
"text-align: left;"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/img/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        badReg->setIcon(icon7);
        badReg->setIconSize(QSize(24, 24));

        verticalLayout_8->addWidget(badReg);


        horizontalLayout_4->addLayout(verticalLayout_8);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShadow(QFrame::Plain);
        line_3->setMidLineWidth(1);
        line_3->setFrameShape(QFrame::VLine);

        horizontalLayout_4->addWidget(line_3);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        BFA = new QRadioButton(groupBox_2);
        BFA->setObjectName(QStringLiteral("BFA"));
        BFA->setFocusPolicy(Qt::NoFocus);
        BFA->setChecked(true);

        verticalLayout_9->addWidget(BFA);

        SAA = new QRadioButton(groupBox_2);
        SAA->setObjectName(QStringLiteral("SAA"));
        SAA->setFocusPolicy(Qt::NoFocus);

        verticalLayout_9->addWidget(SAA);

        FA = new QRadioButton(groupBox_2);
        FA->setObjectName(QStringLiteral("FA"));
        FA->setFocusPolicy(Qt::NoFocus);

        verticalLayout_9->addWidget(FA);

        CFA = new QRadioButton(groupBox_2);
        CFA->setObjectName(QStringLiteral("CFA"));
        CFA->setMaximumSize(QSize(16777215, 16777215));
        CFA->setFocusPolicy(Qt::NoFocus);

        verticalLayout_9->addWidget(CFA);


        horizontalLayout->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        SOMA = new QRadioButton(groupBox_2);
        SOMA->setObjectName(QStringLiteral("SOMA"));
        SOMA->setMaximumSize(QSize(16777215, 16777215));
        SOMA->setFocusPolicy(Qt::NoFocus);

        verticalLayout_10->addWidget(SOMA);

        ABC = new QRadioButton(groupBox_2);
        ABC->setObjectName(QStringLiteral("ABC"));
        ABC->setMaximumSize(QSize(16777215, 16777215));
        ABC->setFocusPolicy(Qt::NoFocus);

        verticalLayout_10->addWidget(ABC);

        ES = new QRadioButton(groupBox_2);
        ES->setObjectName(QStringLiteral("ES"));
        ES->setFocusPolicy(Qt::NoFocus);

        verticalLayout_10->addWidget(ES);


        horizontalLayout->addLayout(verticalLayout_10);


        horizontalLayout_4->addWidget(groupBox_2);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setMidLineWidth(1);
        line_2->setFrameShape(QFrame::VLine);

        horizontalLayout_4->addWidget(line_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setCheckable(false);
        verticalLayout_11 = new QVBoxLayout(groupBox);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        NMI = new QRadioButton(groupBox);
        NMI->setObjectName(QStringLiteral("NMI"));
        NMI->setFocusPolicy(Qt::NoFocus);
        NMI->setChecked(true);

        verticalLayout_11->addWidget(NMI);

        NED = new QRadioButton(groupBox);
        NED->setObjectName(QStringLiteral("NED"));
        NED->setFocusPolicy(Qt::NoFocus);

        verticalLayout_11->addWidget(NED);

        NCD = new QRadioButton(groupBox);
        NCD->setObjectName(QStringLiteral("NCD"));
        NCD->setFocusPolicy(Qt::NoFocus);

        verticalLayout_11->addWidget(NCD);

        NCC = new QRadioButton(groupBox);
        NCC->setObjectName(QStringLiteral("NCC"));
        NCC->setFocusPolicy(Qt::NoFocus);

        verticalLayout_11->addWidget(NCC);


        horizontalLayout_4->addWidget(groupBox);

        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_6);

        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShadow(QFrame::Plain);
        line_7->setFrameShape(QFrame::VLine);

        horizontalLayout_4->addWidget(line_7);

        visuals = new QGroupBox(centralWidget);
        visuals->setObjectName(QStringLiteral("visuals"));
        verticalLayout_6 = new QVBoxLayout(visuals);
        verticalLayout_6->setSpacing(5);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 5, 0, 5);
        channelsRadio = new QRadioButton(visuals);
        buttonGroup = new QButtonGroup(PlotWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(channelsRadio);
        channelsRadio->setObjectName(QStringLiteral("channelsRadio"));
        channelsRadio->setFocusPolicy(Qt::NoFocus);
        channelsRadio->setChecked(true);

        verticalLayout_6->addWidget(channelsRadio);

        checkerboardRadio = new QRadioButton(visuals);
        buttonGroup->addButton(checkerboardRadio);
        checkerboardRadio->setObjectName(QStringLiteral("checkerboardRadio"));
        checkerboardRadio->setFocusPolicy(Qt::NoFocus);
        checkerboardRadio->setChecked(false);

        verticalLayout_6->addWidget(checkerboardRadio);

        showRoi = new QCheckBox(visuals);
        showRoi->setObjectName(QStringLiteral("showRoi"));
        showRoi->setFocusPolicy(Qt::NoFocus);
        showRoi->setChecked(true);

        verticalLayout_6->addWidget(showRoi);


        horizontalLayout_4->addWidget(visuals);

        line_9 = new QFrame(centralWidget);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setFrameShadow(QFrame::Plain);
        line_9->setFrameShape(QFrame::VLine);

        horizontalLayout_4->addWidget(line_9);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_12 = new QVBoxLayout(groupBox_3);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        tofirstFrame = new QRadioButton(groupBox_3);
        tofirstFrame->setObjectName(QStringLiteral("tofirstFrame"));
        tofirstFrame->setFocusPolicy(Qt::NoFocus);
        tofirstFrame->setChecked(true);

        verticalLayout_12->addWidget(tofirstFrame);

        toprevFrame = new QRadioButton(groupBox_3);
        toprevFrame->setObjectName(QStringLiteral("toprevFrame"));
        toprevFrame->setFocusPolicy(Qt::NoFocus);

        verticalLayout_12->addWidget(toprevFrame);


        horizontalLayout_4->addWidget(groupBox_3);

        line_10 = new QFrame(centralWidget);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setFrameShadow(QFrame::Plain);
        line_10->setFrameShape(QFrame::VLine);

        horizontalLayout_4->addWidget(line_10);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        transfom = new QLabel(centralWidget);
        transfom->setObjectName(QStringLiteral("transfom"));
        transfom->setMargin(5);

        verticalLayout_13->addWidget(transfom);

        criteria = new QLabel(centralWidget);
        criteria->setObjectName(QStringLiteral("criteria"));
        criteria->setMinimumSize(QSize(0, 45));
        criteria->setMaximumSize(QSize(16777215, 45));
        criteria->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        criteria->setWordWrap(true);
        criteria->setMargin(5);

        verticalLayout_13->addWidget(criteria);


        horizontalLayout_4->addLayout(verticalLayout_13);

        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_8);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_4);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setFrameShape(QFrame::HLine);

        verticalLayout_7->addWidget(line_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        transImage = new QSlider(centralWidget);
        transImage->setObjectName(QStringLiteral("transImage"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(transImage->sizePolicy().hasHeightForWidth());
        transImage->setSizePolicy(sizePolicy1);
        transImage->setMinimumSize(QSize(1, 200));
        transImage->setMaximumSize(QSize(16777215, 16777215));
        transImage->setFocusPolicy(Qt::NoFocus);
        transImage->setMinimum(1);
        transImage->setMaximum(255);
        transImage->setOrientation(Qt::Vertical);

        horizontalLayout_5->addWidget(transImage);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        histo = new Plot(centralWidget);
        histo->setObjectName(QStringLiteral("histo"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(histo->sizePolicy().hasHeightForWidth());
        histo->setSizePolicy(sizePolicy2);
        histo->setMinimumSize(QSize(1, 1));
        histo->setMaximumSize(QSize(9999, 9999));
        histo->setFrameShape(QFrame::NoFrame);
        histo->setFrameShadow(QFrame::Plain);
        histo->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(histo);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        label = new Plot(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(1, 1));
        label->setMaximumSize(QSize(9999, 9999));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_7->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(verticalLayout_7);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/img/qt.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon8);
        toolButton->setIconSize(QSize(32, 32));

        horizontalLayout_2->addWidget(toolButton);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_2);

        PlotWindow->setCentralWidget(centralWidget);

        retranslateUi(PlotWindow);

        nextFrame->setDefault(false);


        QMetaObject::connectSlotsByName(PlotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlotWindow)
    {
        PlotWindow->setWindowTitle(QApplication::translate("PlotWindow", "PlotWindow", 0));
        openFile->setText(QApplication::translate("PlotWindow", "Open File", 0));
        info->setText(QString());
        nextFrame->setText(QApplication::translate("PlotWindow", "Compute Next", 0));
        computeOne->setText(QApplication::translate("PlotWindow", "Compute Again", 0));
        Compute->setText(QApplication::translate("PlotWindow", "Compute All", 0));
        prevFrame->setText(QApplication::translate("PlotWindow", "Prev Frame", 0));
        animate->setText(QApplication::translate("PlotWindow", "Animate To End", 0));
        goodReg->setText(QApplication::translate("PlotWindow", "Well Registered", 0));
        badReg->setText(QApplication::translate("PlotWindow", "Bad Registered", 0));
        groupBox_2->setTitle(QApplication::translate("PlotWindow", "Method                                                           ", 0));
        BFA->setText(QApplication::translate("PlotWindow", "Brute Force", 0));
        SAA->setText(QApplication::translate("PlotWindow", "Simulated Anealing", 0));
        FA->setText(QApplication::translate("PlotWindow", "Fireflies", 0));
        CFA->setText(QApplication::translate("PlotWindow", "Chaotic firely", 0));
        SOMA->setText(QApplication::translate("PlotWindow", "SOMA", 0));
        ABC->setText(QApplication::translate("PlotWindow", "A. Bee Colony", 0));
        ES->setText(QApplication::translate("PlotWindow", "Evolution Str.", 0));
        groupBox->setTitle(QApplication::translate("PlotWindow", "Criteria of Similarity", 0));
        NMI->setText(QApplication::translate("PlotWindow", "Mutual Information", 0));
        NED->setText(QApplication::translate("PlotWindow", "Euclidean Distance", 0));
        NCD->setText(QApplication::translate("PlotWindow", "Cosine Distance", 0));
        NCC->setText(QApplication::translate("PlotWindow", "Cross Corelation", 0));
        visuals->setTitle(QApplication::translate("PlotWindow", "Visualisation", 0));
        channelsRadio->setText(QApplication::translate("PlotWindow", "Channels", 0));
        checkerboardRadio->setText(QApplication::translate("PlotWindow", "Checkerboard", 0));
        showRoi->setText(QApplication::translate("PlotWindow", "Show ROI", 0));
        groupBox_3->setTitle(QApplication::translate("PlotWindow", "Compare with", 0));
        tofirstFrame->setText(QApplication::translate("PlotWindow", "First frame", 0));
        toprevFrame->setText(QApplication::translate("PlotWindow", "Previous Frame", 0));
        transfom->setText(QString());
        criteria->setText(QApplication::translate("PlotWindow", "Criteria:	-\n"
"Similarity", 0));
        histo->setText(QString());
        label->setText(QString());
        label_3->setText(QApplication::translate("PlotWindow", "Powered by", 0));
        toolButton->setText(QApplication::translate("PlotWindow", "PushButton", 0));
        label_2->setText(QApplication::translate("PlotWindow", "Created by Michal Karzel", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotWindow: public Ui_PlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWINDOW_H
