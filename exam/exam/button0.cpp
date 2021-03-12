#include "button0.h"

void button0::Analysis()
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)==false) return;

    QString name="";
    QString func="";
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        if (str[0]=='f' && str[1]=='u' && str[2]=='n' && str[3]=='c' && str[4]==' ')
        {
            if (name!="" && func!="")
            {
                node *n=new node(name,func);
                List.push_front(*n);
                name="";
                func="";
            }
            for (int i=5;i<str.length()-1;++i) name.append(str[i]);
            continue;
        }
        func.append(str);
    }
    node *n=new node(name,func);
    List.push_front(*n);



    //现在开始读取main的内容
    call("main",0);

}

void button0::call(QString func, int depth)
{

    QString word="";//记录要输出的字符
    for (int i=0;i<depth;i++)
    {word.append('|');word.append(' ');word.append(' ');word.append(' ');}
    word.append(func);
    write(word);
    if (func=="finish" ) return;

    list<node>::iterator iter=List.begin();
    while (iter->name!=func) iter++;
    int i=0;
    while (iter->function[i]!='\0')
    {
        if (iter->function[i+4]=='\0') return;
        if (iter->function[i]=='/' && iter->function[i+1]=='/')
        {
            while (iter->function[i]!='\0' && iter->function[i]!='\n') ++i;
            i++;
        }
        if (iter->function[i]=='c' && iter->function[i+1]=='a' && iter->function[i+2]=='l' && iter->function[i+3]=='l' && iter->function[i+4]==' ')
        {
         QString funct="";
         int j;//跳过空格
         for (j=i+5;iter->function[j]!='\n';j++) funct.append(iter->function[j]);
         call(funct,depth+1);
        }
        ++i;
    }


}
