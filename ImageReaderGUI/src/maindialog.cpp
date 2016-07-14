#include "maindialog.h"
#include "ui_maindialog.h"
#include "Decoder.hpp"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QString>

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::on_openFileButton_clicked()
{
    QString _fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    "/home/fedora/Documents/SourceCode/ImageReader/",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    std::string fileName = _fileName.toStdString();

    BaseImage _image(fileName);

    qDebug() << _image.getWidth() << ", " <<  _image.getHeight() << '\n';

    QImage image(_image.get(), _image.getWidth(), _image.getHeight(),
                 (_image.getChannels() == 3) ? QImage::Format_RGB888 : QImage::Format_Grayscale8);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void mainDialog::on_saveFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open Image"),
                                                    "/home/fedora/Documents/SourceCode/ImageReader/",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    std::cout << fileName.toStdString() << '\n';
}
