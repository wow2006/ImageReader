#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "ImageReader.hpp"

namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

private slots:
    void on_openFileButton_clicked();

    void on_saveFileButton_clicked();

private:
    Ui::mainDialog *ui;
    unsigned char* ptr = nullptr;
    BaseImage _image;
};

#endif // MAINDIALOG_H
