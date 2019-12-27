#include "askwindow.h"
#include <QDebug>

AskWindow::AskWindow(QWidget *parent) : QWidget(parent)
{
    createCancelPage();
    createCopyPage();
    createCopyPastPage();

    m_suggestButton = new DSuggestButton;
    m_suggestButton->setText("cancel");
    m_pStackedWidget = new QStackedWidget;
    m_pStackedWidget->addWidget(widget);
    m_pStackedWidget->addWidget(copyWidget);
    m_pStackedWidget->addWidget(copyPastWidget);
    m_pStackedWidget->setCurrentWidget(widget);
    mainVLayout = new QVBoxLayout;
    mainVLayout->addWidget(m_pStackedWidget);
    mainVLayout->addWidget(m_suggestButton, 0, Qt::AlignCenter);
    setLayout(mainVLayout);
   connect(m_suggestButton,&DSuggestButton::clicked,this,&AskWindow::sendSlot);
   m_pTimer = new QTimer;
   connect(m_pTimer,&QTimer::timeout,
           [=]()
   {
        if(m_pTimer->isActive())
            m_pTimer->stop();
        m_suggestButton->setText("copy");
        m_pStackedWidget->setCurrentWidget(copyWidget);
        setClipboard();

   });
}

DWidget* AskWindow::createCopyPastPage()
{

    // 验证码
    copyPastWidget = new DWidget;
    QFont v_font("宋体",10,QFont::Thin,true);
    v_font.setLetterSpacing(QFont::AbsoluteSpacing,5 );
    m_textLabel2 =new DLabel(copyPastWidget);
    m_textLabel2->setFont(v_font);
    m_textLabel2->setText(tr("Successfully copied "));
    m_textLabel2->setAlignment(Qt::AlignCenter);


    //　加载文字
    QString text = QString(tr("\t waiting for connection, please wait..."
                             "\r\n this interface will be automatically hidden\r\n "
                              "to the taskbar after successful connection"));
    QFont str_font("宋体",8,QFont::Thin,true);
    m_stringLabel2 =new DLabel(text,copyPastWidget);
    m_stringLabel2->setFont(str_font);
    m_stringLabel2->setAlignment(Qt::AlignCenter);

    //　加载按钮
  //  m_copyPastBtn = new DPushButton(tr("cancel"),copyPastWidget);


    //添加控件
    vLayout3 =new QVBoxLayout;
    vLayout3->addWidget(m_textLabel2, 0, Qt::AlignCenter);
    vLayout3->addWidget(m_stringLabel2, 0, Qt::AlignCenter);
  //  vLayout3->addWidget(m_copyPastBtn, 0, Qt::AlignCenter);

    copyPastWidget->setLayout(vLayout3);
    return copyPastWidget;

}

DWidget* AskWindow::createCopyPage()
{
    // 验证码
    copyWidget = new DWidget;
    QFont font("宋体",14,QFont::Thin,true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,15 );
    m_textLabel1 =new DLabel(copyWidget);
    m_textLabel1->setFont(font);
    m_textLabel1->setAlignment(Qt::AlignCenter);
    int num=getRandomNumber(0,999999);
    QString str = QString::number(num);
    strNum=str;
    m_textLabel1->setText(str);

    //　加载文字
    QString text = QString(tr("To start sharing your desktop, put the above verification code \r\n"
                              "Provided to personnel assisting you after they input \n verification code"
                              ", your Shared drawing will begin immediately"));
    QFont s_font("宋体",8,QFont::Thin,true);
    m_stringLabel1 =new DLabel(text,copyWidget);
    m_stringLabel1->setFont(s_font);
    m_stringLabel1->setAlignment(Qt::AlignCenter);

    //　加载按钮
   // m_copyBtn = new DPushButton(tr("copy"),copyWidget);


    //添加控件
    vLayout2 =new QVBoxLayout;
    vLayout2->addWidget(m_textLabel1, 0, Qt::AlignCenter);
    vLayout2->addWidget(m_stringLabel1, 0, Qt::AlignCenter);
   // vLayout2->addWidget(m_copyBtn, 0, Qt::AlignCenter);

    copyWidget->setLayout(vLayout2);
    return copyWidget;

}


DWidget* AskWindow::createCancelPage()
{    
//     加载动态图标
    widget = new DWidget;
    m_pSpinner =new DSpinner(widget);
    m_pSpinner->setFixedSize(32,32);
    m_pSpinner->start();

//    　加载文字
    QString text = QString(tr("Request verification code is being generated, please wait..."));
    m_stringLabel =new DLabel(text,widget);
    QFont s_font("宋体",8,QFont::Thin,true);
    m_stringLabel->setFont(s_font);

//  　加载按钮
   // m_cancelBtn = new DPushButton(tr("cancel"),widget);
 //   connect(m_cancelBtn,&DPushButton::clicked,this,&AskWindow::sendSlot);


//    添加控件
    vLayout =new QVBoxLayout;
    vLayout->addWidget(m_pSpinner, 0, Qt::AlignCenter);
    vLayout->addWidget(m_stringLabel, 0, Qt::AlignCenter);
    //vLayout->addWidget(m_cancelBtn, 0, Qt::AlignCenter);

    widget->setLayout(vLayout);

    return widget;
}



void AskWindow::sendSlot()
{
    if(m_pTimer->isActive())
        m_pTimer->stop();

    qDebug()<<"========"<<m_suggestButton->text();
    if((m_suggestButton->text() == "cancel") || (m_suggestButton->text() == "back"))
    {
         qDebug()<<"2222";
         m_suggestButton->setText("cancel");
        m_pStackedWidget->setCurrentWidget(widget);
        emit backMainWindow();
    }
    if(m_suggestButton->text() == "copy")
    {
        qDebug()<<"11111111";
        m_suggestButton->setText("back");
        m_pStackedWidget->setCurrentWidget(copyPastWidget);
    }

}

int AskWindow::getRandomNumber(int min,int max)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    int num = qrand()%(max-min);
    QString str=QString::number(num);
    if(str.length()!=6){
        getRandomNumber(0,1000000);
    }

//    qDebug()<<num+min;

    return num;
}



void AskWindow::setClipboard()
{
    board = QApplication::clipboard();
    board->setText(m_textLabel1->text());
}

void AskWindow::getClipboard()
{
    board = QApplication::clipboard();
    QString str = board->text();

}
