#include "config.h"

config::config()
{

}

config::~config()
{

}

bool config::openfile(QString filename)
{
    XMLfile.setFileName(filename);
    if (!XMLfile.open(QIODevice::ReadOnly | QIODevice::Truncate | QIODevice::Text))
        return false;
    else{
        document.setContent(&XMLfile);
        root=document.documentElement();
        if(root.tagName()!= "PAT_CONFIGURATION"){
            closefile();
            return false;
        }
    }
    return true;
}

bool config::savefile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
         return false;
    QTextStream out(&file);
    out<<document.toString();
    file.close();
    return true;
}

void config::closefile()
{
    XMLfile.close();
}

QString config::getvalue(QString node)
{
    int separator;
    QDomElement elem=root;
    while(!node.isEmpty())
    {
        separator=node.indexOf(',');
        if(separator!=-1)
        {
            elem=elem.firstChildElement(node.left(separator));
            node=node.right(node.length()-separator-1);
        }
        else
            return elem.attribute(node);
    }
    return "";
}

