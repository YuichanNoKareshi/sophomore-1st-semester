#include "expression.h"

expression::expression()
{
    isInputing=false;
}

void expression::setisInputing(bool is)
{
    isInputing=is;
}

void expression::getExpression(QString expression)
{
    if (isInputing==true) return;//如果是input环节，返回
    expression = expression.simplified();

    int i=0;
    int key=0;//行号

    QString command="";
    enum command c=command::HELP;
    if ( (expression[i]>='a' && expression[i]<='z') || (expression[i]>='A' && expression[i]<='Z') )//如果expression的第一个元素就是字母的话说明有可能是command，否则就不可能
    {
        while (true)
        {
            if ( (expression[i]>='a' && expression[i]<='z') || (expression[i]>='A' && expression[i]<='Z') )
            {
                command.append(expression[i]);
                i++;
                continue;
            }
            else if (expression[i]=='\0' || expression[i]==' ') break;
            else return;
        }

        if (command.toUpper()=="RUN") c=command::RUN;
        else if (command.toUpper()=="LIST") c=command::LIST;
        else if (command.toUpper()=="CLEAR") c=command::CLEAR;
        else if (command.toUpper()=="HELP") c=command::HELP;
        else if (command.toUpper()=="QUIT") c=command::QUIT;
        else if (command.toUpper()=="LET") c=command::LET1;
        else if (command.toUpper()=="PRINT") c=command::PRINT1;
        else if (command.toUpper()=="INPUT") c=command::INPUT1;
        else {writeToConsole("Unknown command!");return;}

        switch(c)
        {
        case 0://RUN
        {
            if (valid.empty()==false)//表达式有错，报错
            {

                writeToConsole("Input error!");
                map.clear();
                valid.clear();
            }
            else run(map);

            break;
        }

        case 1://LIST
        {
            QMap<int,QString>::iterator j;
            if (listmap.empty()==true) writeToConsole("There is nothing.");
            else
                for(j=listmap.begin(); j!=listmap.end(); j++)
                {
                    writeToConsole( j.value() );
                }
            break;
        }

        case 2://CLEAR
        {
            map.clear();
            writeToConsole("Date cleared.");
            break;
        }

        case 3://HELP
        {
            writeToConsole("This is a BASIC interpreter which will interpreter your input into a C++ program.");
            writeToConsole("We support +-*/() operators with signed integers (at least 32-bit) in expressions.");
            writeToConsole("We also support comparision operators (><=) in IF conditions.");
            break;
        }

        case 4://QUIT
        {
            quit();
            break;
        }

        case 5://LET
        case 6://PRINT
        case 7://INPUT
        {
            i++;//跳过该空格
            QString movement1="";
            while (true)
            {
                if (expression[i]!='\0')
                {

                    movement1.append(expression[i]);
                    i++;
                    continue;
                }
                else break;
            }
            com(c,movement1);
        }
        }

        return;
    }


//是command的情况结束--------------------------------------------------------------------------------------------------
//以下是statement的情况------------------------------------------------------------------------------------------------

    while (true)
    {
        if (expression[i]>='0' && expression[i]<='9') {i++;continue;}//i记录行号的位数
        else if (expression[i]==' ' || expression[i]=='\0') break;
        else {writeToConsole("Unknown command!");return;}
    }
    for (int j=0; j<i; j++)
    {
        key*=10;
        key+=expression[j].unicode()-'0';
    }//得到行号

    valid.remove(key);
    if (expression[i]=='\0') //如果只有一个行号，则删除该行
    {
        if (map.contains(key)==true && listmap.contains(key)) {map.remove(key);listmap.remove(key);}
        else if (map.contains(key)==false) valid.push_front(key);
    }


    i++;//跳过该空格

    QString statement="";
    enum statement s=statement::REM;//node中的s(statement)
    while (true)
    {
        if ( (expression[i]>='a' && expression[i]<='z') || (expression[i]>='A' && expression[i]<='Z') )
        {
            statement.append(expression[i]);
            i++;
            continue;
        }
        else if (expression[i]==' ' || expression[i]=='\0') break;
        else {valid.push_front(key);return;}//记录第key行有错
    }
    if (statement.toLower()=="rem") s=statement::REM;
    else if (statement.toLower()=="let") s=statement::LET;
    else if (statement.toLower()=="print") s=statement::PRINT;
    else if (statement.toLower()=="input") s=statement::INPUT;
    else if (statement.toLower()=="goto") s=statement::GOTO;
    else if (statement.toLower()=="if") s=statement::IF;
    else if (statement.toLower()=="end") s=statement::END;
    else {valid.push_front(key);return;}

    QString movement="";//node中的movement

    switch(s)
    {
    case 1:case 2:case 3:case 4:case 5:case 6://REM、IF、LET、INPUT、GOTO、END,把后面的全记录
    {
        i++;//跳过该空格
        while (true)
        {
            if (expression[i]!='\0')
            {
                movement.append(expression[i]);
                i++;
                continue;
            }
            else break;
        }
        break;
    }

    case 0://REM,不记录
    {
        break;
    }

    }


    node Node(s,movement);
    if (map.contains(key)) map.remove(key);
    map.insert(key,Node);

    QString expression1="";
    QString str = QString::number(key);
    expression1.append(str);
    expression1.append(" ");
    expression1.append(statement);
    expression1.append(" ");
    expression1.append(movement);
    if (listmap.contains(key)) listmap.remove(key);
    listmap.insert(key,expression1);

}

void expression::validfailed()
{
    writeToConsole("Input error!");
}
