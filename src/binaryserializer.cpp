#include "binaryserializer.h"

#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QDir>

BinarySerializer::BinarySerializer(const QString &dirPath)
    : m_dirPath(dirPath) { }

void BinarySerializer::save(const Serializable& serializable, const QString& fileName) const
{
    // Qt automatically resolves separators for different OSs
    QDir dir;
    if (!dir.exists(m_dirPath)) {
        dir.mkpath(m_dirPath);
    }

    QFile file(m_dirPath + "/" + fileName);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        std::cerr << "error while opening a file: " << fileName.toStdString() << std::endl;
        return;
    }

    QDataStream dataStream(&file);
    dataStream << serializable.toVariant();

    file.close();
}

void BinarySerializer::load(Serializable& serializable, const QString& fileName) const
{
    // Qt automatically resolves separators for different OSs
    QDir dir;
    if (!dir.exists(m_dirPath)) {
        dir.mkpath(m_dirPath);
    }

    QFile file(m_dirPath + "/" + fileName);
    if (!file.open(QFile::ReadOnly)) {
        std::cerr << "error while opening a file: " << fileName.toStdString() << std::endl;
        return;
    }

    QDataStream dataStream(&file);
    QVariant variant;
    dataStream >> variant;
    serializable.fromVariant(variant);

    file.close();
}
