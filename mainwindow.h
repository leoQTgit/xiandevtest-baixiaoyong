#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DToolButton>
#include <DLabel>
#include <DWidget>
#include <QVBoxLayout>
#include <QLayout>
#include <QStackedWidget>
#include <QTimer>
#include <QImage>
#include <QHBoxLayout>
#include <DTitlebar>

#include "askwindow.h"
#include "helpwindow.h"




DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void initUI_1();
    DWidget* createHostPage();
    void signalAndSlot();
    void  setTitleBar(const QString& path,const QString& name);





signals:

public slots:

     void subWindowSignalSlot();
     void on_askbtn_click();
     void on_toHelp_click();


private:
    QStackedWidget* hostStackWidget;
    QVBoxLayout* hostLayout;

    DWidget* widget;
    DLabel* m_iconLabel;
    DLabel* m_textLabel;
    DToolButton* m_askBtn;
    DToolButton* m_toHelpBtn;
    QVBoxLayout* vLayout;

    QHBoxLayout* hLayout;
    DWidget* titleBatWidget;
    QImage* image;
    DLabel* askIcon;
    DLabel* helpIcon;
    DTitlebar* TitleBar;


    AskWindow *askWindow;
    HelpWindow *helpWindow;


    QTimer *myTimer2;

};

#endif // MAINWINDOW_H
