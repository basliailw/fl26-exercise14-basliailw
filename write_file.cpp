// write_file.cpp
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
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Error: cannot open file for writing:" << file.errorString();
    return EXIT_FAILURE;
  }

  // treat the file as consuming a data stream
  QDataStream out(&file);

  // Write a header with a magic number and a version
  out << MAGIC;
  out << VERSION;

  // use a specific streaming format
  out.setVersion(QDataStream::Qt_5_0);
  
  // write some data
  QList<QString> messages;
  messages << "This is a test. This is only a test.")
  out << msg;

  if (out.status() != QDataStream::Ok) {
    qDebug() << "Error: failed while writing data.";
    return EXIT_FAILURE;
  }
  
  // notify the user that we're finished
  qDebug() << "A data stream has been written to a file.";  
  for (const QString &s : messages)
    qDebug() << " " << s;
  
  return EXIT_SUCCESS;
}
