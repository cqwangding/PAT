#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>

class config
{
public:
    config();
    ~config();
    bool openfile(QString filename);
    bool savefile(QString filename);
    void closefile();
    QString getvalue(QString node);
private:
    QFile XMLfile;
    QDomDocument document;
    QDomElement root;
};

#endif // CONFIG_H
