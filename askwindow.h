#ifndef ASKWINDOW_H
#define ASKWINDOW_H

#include <DMainWindow>
#include <DPushButton>
#include <DLabel>
#include <DWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QStackedWidget>
#include <DSpinner>
#include <QTime>
#include <QApplication>
#include <QClipboard>
#include <DSuggestButton>





DWIDGET_USE_NAMESPACE

static QString  strNum="";

class AskWindow : public DWidget
{
    Q_OBJECT
public:
    explicit AskWindow(QWidget *parent = nullptr);


   DWidget* createCancelPage();
   DWidget* createCopyPage();
   DWidget* createCopyPastPage();

   void toCopyPage();
   void toCopyPastPage();



    int getRandomNumber(int min,int max);
    void setClipboard();
    void getClipboard();


signals:
    void cancelSignal();

public slots:
    void sendSlot();


private:
    QStackedWidget* m_pStackedWidget;
    QVBoxLayout* mainVLayout;

    DWidget* widget;
    QVBoxLayout* vLayout;
    DSpinner* m_pSpinner;
    DLabel* m_stringLabel;
    DPushButton* m_cancelBtn;


    DWidget* copyWidget;
    DLabel* m_textLabel1;
    DLabel* m_stringLabel1;
    DPushButton* m_copyBtn;
    QVBoxLayout* vLayout2;

    DWidget* copyPastWidget;
    DLabel* m_textLabel2;
    DLabel* m_stringLabel2;
    DPushButton* m_copyPastBtn;
    QVBoxLayout* vLayout3;


    QClipboard *board;

    DSuggestButton *m_suggestButton;
//////////////////////////////////
public:
    QTimer *m_pTimer;
 signals:
    void backMainWindow();


};

#endif // ASKWINDOW_H
