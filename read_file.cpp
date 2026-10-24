// read_file.cpp
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>

#include <cstdlib>

#include "file_header.h"

int main(int argc, char *argv[])
{
  QFile file("temp.dat");
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Error: cannot open file for reading:" << file.errorString();
    return EXIT_FAILURE;
  }
  QDataStream in(&file);

  // Read and check the header
  quint32 magic;
  in >> magic;
  if (magic != MAGIC){
    qDebug() << "Error: unexpected format.";
    return EXIT_FAILURE;
  }

  // Read the version
  qint32 version;
  in >> version;
  if(version != VERSION){
    qDebug() << "Error: unsupported file version.";
    return EXIT_FAILURE;
  }

  // use the same encoding format
  in.setVersion(QDataStream::Qt_5_0);

  // Read the data
  QList<QString> msg;
  in >> msg;

  if (in.status() != QDataStream::Ok) {
    qDebug() << "Error: file is truncated or corrupt.";
    return EXIT_FAILURE;
  }

  qDebug() << "Read " << msg.size() << "strings from a file: ";
  for (const QString &s : msg)
    qDebug() << " " << s;
  
  return EXIT_SUCCESS;
}
