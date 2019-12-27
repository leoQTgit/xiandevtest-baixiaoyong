#include "helpwindow.h"
#include <QDebug>

HelpWindow::HelpWindow(QWidget *parent) : QWidget(parent)
{
    createInputPage();

    connect(m_line,&QLineEdit::textChanged,[=](){
        QString str=m_line->text();
        int len = str.length();  

      if(len==6){
            m_cancelBtn->setText("connect");
            QString text = QString(tr("Please enter the captcha provided to you \r\n"
                                      "by the person you want to help at the top,\r\n"
                                      "When finished, click the link to start \r\n "
                                      "to assist each other"));
            m_textLabel =new DLabel(text);
        }


    });

    connect(m_cancelBtn,&DPushButton::clicked,[=](){
       QString cancelBtnStr=m_cancelBtn->text();
       QString lineStr=m_line->text();


       if((cancelBtnStr.contains("connect",Qt::CaseSensitive))){
         m_phelpWindowStackedWidget->setCurrentWidget(connectWidget);
         QClipboard* board = QApplication::clipboard();
         QString strNum = board->text();

         timer = new QTimer;
         timer->start(5000);
            qDebug()<<strNum<<lineStr;
         connect(timer,&QTimer::timeout,[=](){
             if(strNum.contains(lineStr,Qt::CaseSensitive)){
               m_phelpWindowStackedWidget->setCurrentWidget(disconnectWidget);
               timer->stop();
             }else {
                m_phelpWindowStackedWidget->setCurrentWidget(retryWidget);
                timer->stop();
                }

         });

       }else {
        connect(m_cancelBtn,&DPushButton::clicked,this,&HelpWindow::sendSlot);
}
    });
    connect(m_disconnectBtn,&DPushButton::clicked,[=](){
        emit sendSlot();
    });
}
//  创建成功连接界面
DWidget* HelpWindow::createDisconnectPage()
{
 //     状态现实
    disconnectWidget = new DWidget;
    m_disconnectLabel =new DLabel(disconnectWidget);
    m_disconnectLabel->setText(tr("You are doing remote assistance"));
    m_disconnectLabel->setAlignment(Qt::AlignCenter);
    QFont v_font("宋体",10,QFont::Thin,true);
    v_font.setLetterSpacing(QFont::AbsoluteSpacing,3);
    m_disconnectLabel->setFont(v_font);


 //    　加载文字
    QFont font("宋体",8,QFont::Thin,true);
    QString text = QString(tr("There is already a connection session.\r\n"
                              "If you want to establish a new connection,\r\n"
                              " disconnect first..."));
    m_disstrLabel =new DLabel(text,disconnectWidget);
    m_disstrLabel->setFont(font);

 //  　加载按钮
    m_disconnectBtn = new DPushButton(tr("disconnect"),disconnectWidget);
 //    connect(m_retryBtn,&DPushButton::clicked,this,&HelpWindow::sendSlot);


 //    添加控件
    vLayout4 =new QVBoxLayout;
    vLayout4->addWidget(m_disconnectLabel, 0, Qt::AlignCenter);
    vLayout4->addWidget(m_disstrLabel, 0, Qt::AlignCenter);
    vLayout4->addWidget(m_disconnectBtn, 0, Qt::AlignCenter);

    disconnectWidget->setLayout(vLayout4);
    return disconnectWidget;
}
//  创建重试界面
DWidget* HelpWindow::createRetryPage()
{
 //     加载动态图标
    retryWidget = new DWidget;
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::darkYellow);
    QFont s_font("宋体",18,QFont::Thin,true);
    m_falseLabel =new DLabel(retryWidget);
    m_falseLabel->setFont(s_font);
    m_falseLabel->setText(tr("connection fails"));
    m_falseLabel->setPalette(pa);
    m_falseLabel->setAlignment(Qt::AlignCenter);



 //    　加载文字
    QString text = QString(tr("The network connection state is not very stable,\r\n"
                              " click the retry button to try again"));
    m_retryLabel =new DLabel(text,retryWidget);
    QFont font("宋体",8,QFont::Thin,true);
    m_retryLabel->setFont(font);
    m_retryLabel->setAlignment(Qt::AlignCenter);

 //  　加载按钮
    m_retryBtn = new DPushButton(tr("retry"),retryWidget);
    connect(m_retryBtn,&DPushButton::clicked,this,&HelpWindow::sendSlot);


 //    添加控件
    vLayout3 =new QVBoxLayout;
    vLayout3->addWidget(m_falseLabel, 0, Qt::AlignCenter);
    vLayout3->addWidget(m_retryLabel, 0, Qt::AlignCenter);
    vLayout3->addWidget(m_retryBtn, 0, Qt::AlignCenter);

    retryWidget->setLayout(vLayout3);
    return retryWidget;
}

//  创建取消界面
DWidget* HelpWindow::createCancelPage()
{
//     加载动态图标
    connectWidget = new DWidget;
    m_pSpinner =new DSpinner(connectWidget);
    m_pSpinner->setFixedSize(32,32);
    m_pSpinner->start();

//    　加载文字
    QString text = QString(tr("Request verification code is being generated, please wait..."));
    m_stringLabel =new DLabel(text,connectWidget);
    QFont s_font("宋体",8,QFont::Thin,true);
    m_stringLabel->setFont(s_font);

//  　加载按钮
    m_cancelBtn2 = new DPushButton(tr("cancel"),connectWidget);
    connect(m_cancelBtn2,&DPushButton::clicked,this,&HelpWindow::sendSlot);


//    添加控件
    vLayout1 =new QVBoxLayout;
    vLayout1->addWidget(m_pSpinner, 0, Qt::AlignCenter);
    vLayout1->addWidget(m_stringLabel, 0, Qt::AlignCenter);
    vLayout1->addWidget(m_cancelBtn2, 0, Qt::AlignCenter);

    connectWidget->setLayout(vLayout1);
    return connectWidget;
}
 //　创建连接界面
DWidget* HelpWindow::createConnectPage()
{

 //     加载输入框
    inputWidget = new DWidget;
    m_inputLine =new DLineEdit(inputWidget);
    m_inputLine->setText(m_line->text());
    m_inputLine->setFixedSize(this->width()/3,this->height()/6);
    QFont font("宋体",14,QFont::Thin,true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,15 );
    m_inputLine->setFont(font);


 //    　加载文字
    QString text = QString(tr("Please enter the captcha provided to you \r\n"
                              "by the person you want to help at the top,\r\n"
                              "When finished, click the link to start \r\n "
                              "to assist each other"));
    m_strLabel =new DLabel(text,inputWidget);
    QFont s_font("宋体",8,QFont::Thin,true);
    m_strLabel->setFont(s_font);


 //    　加载按钮
     m_connectBtn = new DPushButton(tr("connect"),inputWidget);

 //    添加控件
    vLayout2 =new QVBoxLayout;
    vLayout2->addWidget(m_inputLine, 0, Qt::AlignCenter);
    vLayout2->addWidget(m_strLabel, 0, Qt::AlignCenter);
    vLayout2->addWidget(m_connectBtn, 0, Qt::AlignCenter);


    inputWidget->setLayout(vLayout2);
    return inputWidget;


}

//  创建输入界面
DWidget* HelpWindow::createInputPage()
{


//     加载输入框
    widget1 = new DWidget;
    m_line =new QLineEdit(widget1);
    m_line->setFixedSize(this->width()/3,this->height()/7);
    QFont font("宋体",14,QFont::Thin,true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,15 );
    m_line->setFont(font);
    m_line->setFocus();
    m_line->setCursorPosition(m_line->text().size()/2);
    m_line->setAlignment(Qt::AlignCenter);
    QRegExp regx("[0-9]{6}");
    QValidator *validator = new QRegExpValidator(regx, m_line );
    m_line->setValidator( validator );



//    　加载文字
    QString text = QString(tr("Please enter the item you want to \r\n"
                              "help The verification code provided \r\n "
                              "to you by the person,When finished, \r\n"
                              " click the link to start to assist each other"));
    m_textLabel =new DLabel(text,widget1);
    QFont s_font("宋体",8,QFont::Thin,true);
    m_textLabel->setFont(s_font);


//    　加载按钮
     m_cancelBtn = new DPushButton(tr("cancel"),widget1);


//    添加控件
    vLayout =new QVBoxLayout;
    vLayout->addWidget(m_line, 0, Qt::AlignCenter);
    vLayout->addWidget(m_textLabel, 0, Qt::AlignCenter);
    vLayout->addWidget(m_cancelBtn, 0, Qt::AlignCenter);
    widget1->setLayout(vLayout);

    m_phelpWindowStackedWidget = new QStackedWidget;
    m_phelpWindowStackedWidget->addWidget(widget1);
    m_phelpWindowStackedWidget->addWidget(createConnectPage());
    m_phelpWindowStackedWidget->addWidget(createCancelPage());
    m_phelpWindowStackedWidget->addWidget(createRetryPage());
    m_phelpWindowStackedWidget->addWidget(createDisconnectPage());

    helpWindowStackLayout = new QVBoxLayout;
    helpWindowStackLayout->addWidget(m_phelpWindowStackedWidget);
    setLayout(helpWindowStackLayout);

    return widget1;

}
void HelpWindow::sendSlot()
{
    emit cancelSignal();

}
