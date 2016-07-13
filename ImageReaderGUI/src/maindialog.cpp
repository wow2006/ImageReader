#include "maindialog.h"
#include "ui_maindialog.h"
#include "Decoder.hpp"
#include <iostream>
#include <QFileDialog>
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

    uchar* ptr = nullptr;
    int width = 0, height = 0, channels = 0;

    auto decoder = DecoderFactory::getDecoder(BaseImage::ImageFormat::PNG);
    decoder->Decoder(fileName, ptr, width, height, channels);

    std::cout << fileName << " ("
              << width << ", "
              << height << ")\n";

    QImage image(ptr, width, height, QImage::Format_RGB888);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));

    delete decoder;
    delete[] ptr;
}

void mainDialog::on_saveFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open Image"),
                                                    "/home/fedora/Documents/SourceCode/ImageReader/",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    std::cout << fileName.toStdString() << '\n';
}
