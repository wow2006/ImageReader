#include "maindialog.h"
#include "ui_maindialog.h"
#include "Decoder.hpp"
#include "Encoder.hpp"
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
                                                    tr("Image Files (*.png *.jpg *.bmp *tiff)"));
    std::string fileName = _fileName.toStdString();

    _image.open(fileName);
    ptr = _image.get();

    qDebug() << _image.getWidth() << ", " <<  _image.getHeight() << '\n';

    QImage image(_image.get(), _image.getWidth(), _image.getHeight(),
                 // Find Better way to wrap our format with Qt Format
                 QImage::Format_RGBA8888);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void mainDialog::on_saveFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open Image"),
                                                    "/home/fedora/Documents/SourceCode/ImageReader/",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    std::cout << fileName.toStdString() << '\n';

    std::vector<uchar> output;
    std::size_t fileSize = 0;
    auto encoder = Encoder::EncoderInterface::getEncoder(ImageFormat::TIF);
    encoder->encode(_image.get(), _image.getWidth(), _image.getHeight(), _image.getChannels(),
                    output, fileSize);

    std::ofstream filehandler(fileName.toStdString(), std::ofstream::binary);
    filehandler.write(reinterpret_cast<char*>(output.data()), fileSize);
    filehandler.close();
}
