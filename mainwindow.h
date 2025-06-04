#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>//正则表达式

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_address_textChanged();

private:
    Ui::MainWindow *ui;
    QString normalizeKernelAddress(const QString& input) ;
    void showError(const QString& error);
};
#endif // MAINWINDOW_H
