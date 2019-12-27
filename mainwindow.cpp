#include "mainwindow.h"


#define TIME (2*1000)

MainWindow::MainWindow(QWidget *parent) : DMainWindow(parent)
{
    //createHostPage();
    myTimer2 =new QTimer;

    initUI_1();
    signalAndSlot();
    titleBatWidget=nullptr;
    TitleBar=this->titlebar();

    connect(askWindow, &AskWindow::backMainWindow, this,
            [=]()
    {
        hostStackWidget->setCurrentWidget(widget);
    });
    connect(helpWindow, &HelpWindow::cancelSignal, this,
            [=]()
    {
        hostStackWidget->setCurrentWidget(widget);
    });

}

void MainWindow::initUI_1()
{
    hostLayout = new QVBoxLayout;
    hostStackWidget = new QStackedWidget(this);
    askWindow = new AskWindow;
    helpWindow = new HelpWindow;
    setCentralWidget(hostStackWidget);

    createHostPage();
    hostStackWidget->addWidget(widget);
    hostStackWidget->addWidget(askWindow);
    hostStackWidget->addWidget(helpWindow);
    hostStackWidget->setCurrentWidget(widget);



}

DWidget* MainWindow::createHostPage()
{

    widget = new DWidget;
 //   setCentralWidget(widget);
   // 加载图表
   m_iconLabel =new DLabel(widget);
   QString path = QString(":/images//95233.png");
   QPixmap pxm;
   pxm.load(path);
   m_iconLabel->setPixmap(pxm);
   m_iconLabel->setAlignment(Qt::AlignCenter);

   //　加载文字
   QString text = QString(tr("This is a remote assistance application\r\n "
                             "developed by deepin's team,\r\n"
                             "If you have trouble using \r\n, "
                             "or if someone turns to you for help,\r\n"
                             "Please click I want to help or help someone \r\n"));
   QFont font("宋体",8,QFont::Thin,true);
   m_textLabel =new DLabel(widget);
   m_textLabel->setFont(font);
   m_textLabel->setText(text);
   m_textLabel->setAlignment(Qt::AlignCenter);


   //　加载按钮
    QSize size(30,20);
    QPixmap icon1(":/images/add-to-favorite.png");
    QPixmap icon2(":/images/add-green-button.png");
    m_askBtn = new DToolButton(widget);
    m_askBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_askBtn->setFont(font);
    m_askBtn->setText(tr("For Help"));
    m_askBtn->setIcon(icon1);
    m_askBtn->setFixedSize(size.width()+140,size.height()+20);


    m_toHelpBtn = new DToolButton(widget);
    m_toHelpBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toHelpBtn->setFont(font);
    m_toHelpBtn->setText(tr("Help Other"));
    m_toHelpBtn->setIcon(icon2);
    m_toHelpBtn->setFixedSize(size.width()+140,size.height()+20);

   //添加控件
   vLayout =new QVBoxLayout;
   vLayout->addWidget(m_iconLabel);
   vLayout->addStretch(0);
   vLayout->addWidget(m_textLabel);
   vLayout->addStretch(0);
   vLayout->addWidget(m_askBtn,0,Qt::AlignCenter);
   vLayout->addWidget(m_toHelpBtn,0,Qt::AlignCenter);

   widget->setLayout(vLayout);
   return widget;

}

void MainWindow::signalAndSlot()
{


    connect(m_askBtn,&DToolButton::clicked,[=](){
             setTitleBar(":/images/add-to-favorite.png",tr("我要求助"));
             hostStackWidget->setCurrentWidget(askWindow);
              //myTimer2->start(2000);
             askWindow->m_pTimer->start(TIME);

            });
    connect(m_toHelpBtn,&DToolButton::clicked,[=](){
            setTitleBar(":/images/add-green-button.png",tr("帮助别人"));
             hostStackWidget->setCurrentWidget(helpWindow);

            });
    connect(askWindow,&AskWindow::cancelSignal,this,&MainWindow::subWindowSignalSlot);
    connect(helpWindow,&HelpWindow::cancelSignal,this,&MainWindow::subWindowSignalSlot);
}

void MainWindow::subWindowSignalSlot()
{

    hostStackWidget->setCurrentWidget(widget);

}

void MainWindow::on_askbtn_click()
{

    hostStackWidget->setCurrentWidget(askWindow);

}

void MainWindow::on_toHelp_click()
{
    hostStackWidget->setCurrentWidget(helpWindow);

}

void  MainWindow::setTitleBar(const QString& path,const QString& name)
{
    image= new QImage;
    askIcon = new DLabel(this);
    askIcon-> setPixmap(QPixmap :: fromImage(* image));
    askIcon-> setScaledContents(true);
    askIcon-> setFixedSize(18,18);

    helpIcon = new DLabel(this);

    hLayout = new QHBoxLayout();
    hLayout-> addStretch(0);
    hLayout-> addWidget(askIcon,0,Qt::AlignCenter);
    hLayout-> addWidget(helpIcon,0,Qt::AlignCenter);

    titleBatWidget = new DWidget(this);
    titleBatWidget-> setLayout(hLayout);
    TitleBar->setCustomWidget(titleBatWidget);

    askIcon-> setPixmap(QPixmap(path));
    helpIcon-> setText(name );
}


