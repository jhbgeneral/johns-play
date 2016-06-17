#include <QString>
#include <QDebug>
#include <QVector>
#include <QVectorIterator>

void printPrevNext(QVectorIterator<QString *> vi);

void testIterators()
{
    QVector <QString *> stringVector;
    QVectorIterator <QString *> stringVectorIterator(stringVector);

    QString first = QString("First String");
    QString second = QString("Second String");
    QString third = QString("Third String");
    stringVector.append(&first);
    stringVector.append(&second);
    stringVector.append(&third);

    stringVectorIterator = QVectorIterator<QString *> (stringVector);

    qDebug() << "stringVector.size() =" << stringVector.size();

    while (stringVectorIterator.hasNext())
    {
        printPrevNext(stringVectorIterator);

        QString *str;
        str = stringVectorIterator.peekNext();
        qDebug() << "*str, from peekNext() =" << *str;
        str = stringVectorIterator.next();
        qDebug() << "*str,     from next() =" << *str;
    }

    printPrevNext(stringVectorIterator);
}

void printPrevNext(QVectorIterator <QString *> vi)
{
    qDebug() << "hasPrevious() =" << vi.hasPrevious();
    qDebug() << "hasNext()     =" << vi.hasNext();
}
