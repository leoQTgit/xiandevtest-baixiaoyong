#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>
#include <DWidget>
#include <DMainWindow>
#include <DPushButton>
#include <DLabel>
#include <QVBoxLayout>
#include <DLineEdit>
#include <QLineEdit>
#include <DWidget>
#include <DSpinner>
#include <QStackedWidget>
#include <QClipboard>
#include <QApplication>
#include <QRegExp>
#include <QValidator>
#include <qvalidator.h>
#include <QTimer>
#include "askwindow.h"

DWIDGET_USE_NAMESPACE

class HelpWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HelpWindow(QWidget *parent = nullptr);

    DWidget* initUI_3();
    DWidget* createInputPage();
    DWidget* createConnectPage();
    DWidget* createCancelPage();
    DWidget* createRetryPage();
    DWidget* createDisconnectPage();




signals:
    void cancelSignal();


public slots:
    void sendSlot();

private:
    QStackedWidget* m_phelpWindowStackedWidget;
    QVBoxLayout* helpWindowStackLayout;
//  创建输入界面
    DWidget* widget1;
    QLineEdit* m_line;
    DLabel* m_textLabel;
    DPushButton* m_cancelBtn;
    QVBoxLayout *vLayout;
//　创建连接界面
    DWidget* inputWidget;
    DLineEdit* m_inputLine;
    DLabel* m_strLabel;
    DPushButton* m_connectBtn;
    QVBoxLayout *vLayout2;

//  创建取消界面
    DWidget* connectWidget;
    DSpinner* m_pSpinner;
    DLabel* m_stringLabel;
    DPushButton* m_cancelBtn2;
    QVBoxLayout* vLayout1;
//  创建重试界面
    DWidget* retryWidget;
    DLabel* m_falseLabel;
    DLabel* m_retryLabel;
    DPushButton* m_retryBtn;
    QVBoxLayout* vLayout3;
//  创建成功连接界面
    DWidget* disconnectWidget;
    DLabel* m_disconnectLabel;
    DLabel* m_disstrLabel;
    DPushButton* m_disconnectBtn;
    QVBoxLayout* vLayout4;


    QTimer* timer;




};

#endif // HELPWINDOW_H
