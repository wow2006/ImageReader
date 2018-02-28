// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "maindialog.h"
#include "ui_maindialog.h"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QString>

mainDialog::mainDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::mainDialog) {
  ui->setupUi(this);
}

mainDialog::~mainDialog() { delete ui; }

void mainDialog::on_openFileButton_clicked() {
  QString _fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "/home/fedora/Documents/SourceCode/ImageReader/",
      tr("Image Files (*.png *.jpg *.bmp *tiff)"));
  std::string fileName = _fileName.toStdString();

  _image.open(fileName);
  ptr = _image.get();
  if (ptr == nullptr) {
    qDebug() << "Error reading Image";
    return;
  }

  qDebug() << _image.getWidth() << ", " << _image.getHeight() << '\n';

  QImage image(ptr, _image.getWidth(), _image.getHeight(),
               // Find Better way to wrap our format with Qt Format
               QImage::Format_RGB888);

  if (image.isNull()) {
    qDebug() << "Error reading Image";
    return;
  }

  ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void mainDialog::on_saveFileButton_clicked() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Open Image"), "/home/fedora/Documents/SourceCode/ImageReader/",
      tr("Image Files (*.png *.jpg *.bmp)"));
  std::cout << fileName.toStdString() << '\n';

  _image.save(fileName.toStdString());
}
