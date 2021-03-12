#include "running.h"
using namespace std;

running::running()
{
    isInputing=false;
    Inputnum="";
}

void running::getInput(QString word)
{
    if (isInputing==false) return;//如果不是input环节，返回

    this->loop.exit();
    this->Inputnum=word.remove(0,10);//"pls input "一共十个
    isInputing=false;
    setExpisInputing(false);

}

bool running::isNodeExist(QString key0)
{
    list<Node>::iterator iter=List.begin();
    while (iter!=List.end())
    {
        if (iter->key == key0) return true;
        else iter++;
    }

    return false;
}

int running::NodeValue(QString key0)
{
    list<Node>::iterator iter=List.begin();
    while (iter!=List.end())
    {
        if (iter->key == key0) return iter->value;
        else iter++;
    }

    return -1;
}

bool running::isExpressionValid(QString expression)
{
    int i=0;
    while (expression[i]!='\0')
    {
        if (expression[i]==' ') ++i;
        else if (expression[i]>='a' && expression[i]<='z') ++i;
        else if (expression[i]>='A' && expression[i]<='Z') ++i;
        else if (expression[i]>='0' && expression[i]<='9') ++i;
        else if (expression[i]=='+' || expression[i]=='-' ||
                 expression[i]=='*' || expression[i]=='/' ||
                 expression[i]=='(' || expression[i]==')' ||
                 expression[i]=='_' || expression[i]=='=') ++i;
        else return false;
    }

    return true;
}

void running::run(QMap<int,node> mapp)
{
    this->mapp=mapp;

    QMap<int,node>::Iterator iter1=mapp.begin();

    while (iter1!=mapp.cend())//当mapp中还有节点的时候,先检查程序有无错误
    {
        switch(iter1.value().s)
        {
         case 0://REM
             break;

         case 1://LET
         {
             if (isExpressionValid(iter1.value().movement) == false) {validfailed();return;}
             else
             {
                 bool valid ;
                 valid= let_func(iter1.value().movement);
                 if (valid==false)
                 {
                     validfailed();

                     mapp.clear();
                     List.clear();
                     numlist.clear();//数字列表
                     oplist.clear();//操作符列表
                     Inputnum="";

                     return;
                 }
             }
             break;
         }

         case 2://PRINT
         {

            if (isExpressionValid(iter1.value().movement) == false)
            {
                validfailed();

                mapp.clear();
                List.clear();
                numlist.clear();//数字列表
                oplist.clear();//操作符列表
                Inputnum="";

                return;
            }
            else
            {
                bool valid ;
                int a;
                valid=value_of(a,iter1.value().movement);
                if (valid==false)
                {
                    validfailed();

                    mapp.clear();
                    List.clear();
                    numlist.clear();//数字列表
                    oplist.clear();//操作符列表

                    return;
                }
                else writeToConsole(QString::number(a));
            }
            break;
         }

         case 3://INPUT
         {
            if (iter1.value().movement[0]=='\0')
            {
                validfailed();

                mapp.clear();
                List.clear();
                numlist.clear();//数字列表
                oplist.clear();//操作符列表
                Inputnum="";

                return;
            }

            //先检查变量命名是否合格

            int i=0;
            while(iter1.value().movement[i]!='\0')
            {
                if (!((iter1.value().movement[i].toLower()>='a' && iter1.value().movement[i].toLower()<='z') || (iter1.value().movement[i]=='_')))
                {
                    validfailed();

                    mapp.clear();
                    List.clear();
                    numlist.clear();//数字列表
                    oplist.clear();//操作符列表
                    Inputnum="";

                    return;
                }

                else i++;

            }

            writeToConsole("pls input ");
            isInputing=true;//表明正在输入
            setExpisInputing(true);
            loop.exec();

            i=0;
            while (Inputnum[i]!='\0')
            {
                if (Inputnum[i]<'0' || Inputnum[i]>'9')
                {
                        validfailed();

                        mapp.clear();
                        List.clear();
                        numlist.clear();//数字列表
                        oplist.clear();//操作符列表
                        Inputnum="";

                        return;
                }
                i++;
            }


            if (List.empty()==true)
            {
                Node *node=new Node(iter1.value().movement,Inputnum.toInt());
                List.push_front(*node);
            }

            else
            {
                list<Node>::iterator iter2=List.begin();//定义一个新的迭代器iter2,来寻找iter1要input的变量
                QString key = " ";
                do
                {

                    if (iter2==List.end())//如果没有就push一个进去
                    {
                        Node *node=new Node(iter1.value().movement,Inputnum.toInt());
                        List.push_front(*node);
                        break;
                    }

                    key = iter2->key;
                    if (key == iter1.value().movement)
                    {
                        iter2->value=Inputnum.toInt();//赋值为input的数值
                        break;
                    }
                    iter2++;
                }while (key != iter1.value().movement);
            }


            Inputnum="";

            break;
         }

         case 4://GOTO
         {
            QMap<int,node>::Iterator iter0=mapp.begin();//定义一个新的迭代器iter0,来寻找iter1要跳转的行号
            QString key = "";
            do
            {

                if (iter0==mapp.end())
                {
                    validfailed();

                    mapp.clear();
                    List.clear();
                    numlist.clear();//数字列表
                    oplist.clear();//操作符列表
                    Inputnum="";
                    return;
                }

                key = QString::number(iter0.key());
                if (key == iter1.value().movement)
                {
                    iter1=iter0;
                    iter1--;//因为switch结束后会iter1++
                    break;
                }
                iter0++;
            }while (key != iter1.value().movement);

            break;
         }

         case 5://IF
         {
             int des;//跳转的行数
             bool isTrue,valid;
             valid=if_func(isTrue,des,iter1.value().movement);
             if (valid==false)
             {
                 validfailed();

                 mapp.clear();
                 List.clear();
                 numlist.clear();//数字列表
                 oplist.clear();//操作符列表

                 return;
             }

             if (isTrue==false) break;
             else//goto des
             {
                 QMap<int,node>::Iterator iter0=mapp.begin();//定义一个新的迭代器iter0,来寻找des要跳转的行号
                 int key =0;
                 do
                 {

                     if (iter0==mapp.end())
                     {
                         validfailed();
                         mapp.clear();
                         List.clear();
                         numlist.clear();//数字列表
                         oplist.clear();//操作符列表

                         return;
                     }

                     key = iter0.key();
                     if (key == des)
                     {
                         iter1=iter0;
                         iter1--;//因为switch结束后会iter1++
                         break;
                     }
                     iter0++;
                 }while (key != des);
             }

             break;
         }

         case 6://END
             int i=0;
             if (iter1.value().movement[i]!='\0')
             {
                 validfailed();
                 mapp.clear();
                 List.clear();
                 numlist.clear();//数字列表
                 oplist.clear();//操作符列表

             }
             return;
        }

        iter1++;
    }

    //全部执行完之后清空表达式双栈，list和map保留
    numlist.clear();//数字列表
    oplist.clear();//操作符列表
    Inputnum="";
    return;
}

bool running::let_func(QString movement)//现在只有合法字符,如果不对直接return false
{
    if (movement[0]=='\0') return false;//先判断

    QString variable="";
    int constant=0;
    int i=0;
    int type=-1;//记录上一个位置的字符的类型，0表示正常数，1表示正变量，2表示操作符,3表示负常数,4表示负变量,-1表示空格

    while (movement[i] != '=')
    {
        if (movement[i]=='\0') return false;
        i++;//找到等号之后的表达式
    }

    i++;
    while (movement[i]!='\0')
    {
        if (movement[i]==' ')
        {
            ++i;
            type=-1;
            constant=0;
            variable="";
            continue;
        }//variable和constant全部置零

        else if ((movement[i].toLower()>='a' && movement[i].toLower()<='z') || movement[i]=='_' || type==1 || type==4)
        {
            if (type!=4) type=1;//如果不是负变量，就定义为正变量
            variable.append(movement[i]);
            if (movement[i+1]=='+' || movement[i+1]=='-' || movement[i+1]=='*' || movement[i+1]=='/' ||movement[i+1]=='(' || movement[i+1]==')' || movement[i+1]==' ')
             //如果下一个字符是操作符或空格，进栈，variable置零
            {
                   if (isNodeExist(variable)==false) return false;
                   else
                   {
                       if (type==4)
                       {
                           numnode *n=new numnode(NodeValue(variable)*(-1));
                           numlist.push_front(*n);
                       }

                       else if (type==1)
                       {
                           numnode *n=new numnode(NodeValue(variable));
                           numlist.push_front(*n);
                       }
                       else return false;
                       variable="";
                       type=2;
                   }

            }
            ++i;
        }

        else if (movement[i]>='0' && movement[i]<='9' && type!=1 && type!=4)//如果是数字,且前一个不是变量中字符
        {
            if ((movement[i+1].toLower()>='a' && movement[i+1].toLower()<='z') || movement[i+1]=='_')//如果下一个字符是变量名
            {
                if (type==4) continue;
                else type=1;
                continue;
            }

            constant*=10;//如果前一个字符也是常量中字符
            if (type!=3) type=0;//如果不是负常数，就定义为正常数

            constant += (movement[i].toLatin1()-'0');

            if (movement[i+1]<'0' || movement[i+1]>'9')
            {
                if (type==0)
                {
                    numnode *n=new numnode(constant);
                    numlist.push_front(*n);
                }
                else if (type==3)
                {
                    numnode *n=new numnode(constant*(-1));
                    numlist.push_front(*n);
                }
                else return false;
                constant=0;
            }//下一个字符不是数字(空格或操作符)，进栈

            ++i;
            continue;
        }

        else if (movement[i]=='+' || movement[i]=='-' ||movement[i]=='*' || movement[i]=='/' ||movement[i]=='(' || movement[i]==')')
        //如果是操作符
        {
            if (movement[i]=='-' && (movement[i-1]=='=' || movement[i-1]=='(' || (movement[i-1]==' ' && (movement[i-2]=='=' || movement[i-2]=='(') )))
            {
                if (movement[i+1]>='0' && movement[i+1]<='9') type=3;//负常数
                else if ((movement[i+1].toLower()>='a' && movement[i+1].toLower()<='z') || movement[i+1]=='_') type=4;//负变量
                else return false;
                ++i;
                continue;
            }

            type=2;
            bool canpush;
            if (movement[i]=='*' && movement[i+1]=='*')//如果是乘方
            {
                canpush=pushop('^');
                if (canpush==false) return false;
                i+=2;
            }
            else
            {
                canpush=pushop(movement[i].toLatin1());
                if (canpush==false) return false;
                ++i;
            }

            continue;
        }


    }

    //下面要把双栈中未执行的运算全部执行
    if (variable!="")
    {
        if (isNodeExist(variable)==false) return false;
        else
        {
            numnode *n=new numnode (NodeValue(variable));
            numlist.push_front(*n);
            variable="";
        }
    }


    while(oplist.empty()==false)
    {
        if (numlist.empty()==true) return false;


        if (oplist.begin()->s == '+')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(b->x+a->x,'+',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '-')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(b->x-a->x,'-',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '*')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(b->x*a->x,'*',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '/')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(b->x/a->x,'/',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '^')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(mi(b->x,a->x),'^',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '(') return false;

    }

    if (oplist.empty()==false) return false;
    if (numlist.empty()==true) return false;

    i=0;
    variable="";
    while (movement[i]!=' ' && movement[i]!='=') {variable.append(movement[i]);++i;}
    if (movement[i]==' ' && movement[i+1]!='=') return false;//确保=前只有一个变量

    Node *node=new Node(variable,numlist.begin()->x);
    numlist.pop_front();
    if (numlist.empty()==false) return false;

    list<Node>::iterator iter=List.begin();
    while (iter!=List.end())
    {
        if (iter->key==variable)
        {
            List.erase(iter);//将已有的变量移除
            break;
        }
        iter++;
    }
    List.push_front(*node);

    return true;


}

bool running::pushop(char op)
{
    opnode *opp=new opnode(op);
    switch (op)
    {
    case '+':case'-':
    {
        while (oplist.empty()==false)
        {
            if (oplist.begin()->s == '+')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x+a->x,'+',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '-')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x-a->x,'-',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '*')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x*a->x,'*',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '/')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x/a->x,'/',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '^')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(mi(b->x,a->x),'^',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '(') break;
        }
        oplist.push_front(*opp);
        break;
    }

    case '*':case'/':
    {
        while (oplist.empty()==false)
        {
            if (oplist.begin()->s == '+') break;
            else if (oplist.begin()->s == '-') break;
            else if (oplist.begin()->s == '*')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x*a->x,'*',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '/')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x/a->x,'/',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '^')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(mi(b->x,a->x),'^',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '(') break;
        }
        oplist.push_front(*opp);
        break;
    }

    case '(': oplist.push_front(*opp);break;
    case ')':
    {
        while (oplist.empty()==false)
        {
            if (oplist.begin()->s == '+')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x+a->x,'+',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '-')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x-a->x,'-',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '*')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x*a->x,'*',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '/')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(b->x/a->x,'/',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '^')
            {
                oplist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *a=new numnode(numlist.begin()->x);
                numlist.pop_front();
                if (numlist.empty()==true) return false;
                numnode *b=new numnode(numlist.begin()->x);
                numlist.pop_front();
                numnode* n=new numnode(mi(b->x,a->x),'^',b,a);
                numlist.push_front(*n);
            }
            else if (oplist.begin()->s == '(') {oplist.pop_front();break;}
        }
        break;
    }

    case '^': oplist.push_front(*opp);break;

    default:break;
    }

    return true;
}

bool running::if_func(bool &isTrue,int &des,QString movement)
{
    if (movement[0]=='\0') return false;//先判断

    int index=0;//index是比教育语句的结尾
    while (true)
    {
        if (movement[index]==' ' && movement[index+1].toLower()=='t' && movement[index+2].toLower()=='h' && movement[index+3].toLower()=='e' && movement[index+4].toLower()=='n' && movement[index+5]==' ') break;
        else if (movement[index]=='\0') return false;
        else ++index;
    }

    int temp=index+6;//跳到N后面的空格的下一个元素
    int dest=0;
    while (movement[temp]!='\0')
    {
        dest*=10;
        if (movement[temp].toLatin1()>='0' && movement[temp].toLatin1()<='9') dest+=(movement[temp].toLatin1()-'0');
        else return false;
        ++temp;
    }

    int i=0;
    QString left="";
    QString right="";
    char op;
    while (true)
    {
        if (movement[i]=='=' || movement[i]=='>' || movement[i]=='<') break;
        else if (i>=index) return false;//格式不对
        left.append(movement[i]);
        i++;
    }
    op=movement[i].toLatin1();
    i++;
    while (i<index)
    {
        if (movement[i]=='=' || movement[i]=='>' || movement[i]=='<') break;
        right.append(movement[i]);
        i++;
    }
    if (left.contains('=') || right.contains('=') || isExpressionValid(left)==false || isExpressionValid(right)==false) return false;
    //如果左式或右式中有非法字符或=，则报错

    int a=0,b=0;
    bool valid1,valid2;
    valid1=value_of(a,left);
    valid2=value_of(b,right);
    if (valid1==false || valid2==false) return false;

    switch (op)
    {
    case '=':
    {
        isTrue=(a==b)?true:false;
        break;
    }

    case '<':
    {
        isTrue=(a<b)?true:false;
        break;
    }

    case '>':
    {
        isTrue=(a>b)?true:false;
        break;
    }
    default:break;
    }

    des=dest;//如果全程没有return false，再把dest的值赋给des

    return true;

}

bool running::value_of(int &num,QString movement)//求一个表达式的值,存在a中
{
    if (movement[0]=='\0') return false;//先判断

    QString variable="";
    int constant=0;
    int i=0;
    int type=-1;//记录上一个位置的字符的类型，0表示正常数，1表示正变量，2表示操作符,3表示负常数,4表示负变量,-1表示空格

    while (movement[i]!='\0')
    {
        if (movement[i]==' ')
        {
            ++i;
            type=-1;
            constant=0;
            variable="";
            continue;
        }//variable和constant全部置零

        else if ((movement[i].toLower()>='a' && movement[i].toLower()<='z') || movement[i]=='_' || type==1 || type==4)
        {
            if (type!=4) type=1;//如果不是负变量，就定义为正变量
            variable.append(movement[i]);
            if (movement[i+1]=='+' || movement[i+1]=='-' || movement[i+1]=='*' || movement[i+1]=='/' ||movement[i+1]=='(' || movement[i+1]==')' || movement[i+1]==' ')
             //如果下一个字符是操作符或空格，进栈，variable置零
            {
                   if (isNodeExist(variable)==false) return false;
                   else
                   {
                       if (type==4)
                       {
                           numnode *n=new numnode(NodeValue(variable)*(-1));
                           numlist.push_front(*n);
                       }

                       else if (type==1)
                       {
                           numnode *n=new numnode(NodeValue(variable));
                           numlist.push_front(*n);
                       }
                       else return false;
                       variable="";
                       type=2;
                   }

            }
            ++i;
        }

        else if (movement[i]>='0' && movement[i]<='9' && type!=1 && type!=4)//如果是数字,且前一个不是变量中字符
        {
            if ((movement[i+1].toLower()>='a' && movement[i+1].toLower()<='z') || movement[i+1]=='_')//如果下一个字符是变量名
            {
                if (type==4) continue;
                else type=1;
                continue;
            }

            constant*=10;//如果前一个字符也是常量中字符
            if (type!=3) type=0;//如果不是负常数，就定义为正常数

            constant += (movement[i].toLatin1()-'0');

            if (movement[i+1]<'0' || movement[i+1]>'9')
            {
                if (type==0)
                {
                    numnode *n=new numnode(constant);
                    numlist.push_front(*n);
                }
                else if (type==3)
                {
                    numnode *n=new numnode(constant*(-1));
                    numlist.push_front(*n);
                }
                else return false;
                constant=0;
            }//下一个字符不是数字(空格或操作符)，进栈

            ++i;
            continue;
        }

        else if (movement[i]=='+' || movement[i]=='-' ||movement[i]=='*' || movement[i]=='/' ||movement[i]=='(' || movement[i]==')')
        //如果是操作符
        {
            if (movement[i]=='-' && (movement[i-1]=='=' || movement[i-1]=='(' || (movement[i-1]==' ' && (movement[i-2]=='=' || movement[i-2]=='(') )))
            {
                if (movement[i+1]>='0' && movement[i+1]<='9') type=3;//负常数
                else if ((movement[i+1].toLower()>='a' && movement[i+1].toLower()<='z') || movement[i+1]=='_') type=4;//负变量
                else return false;
                ++i;
                continue;
            }

            type=2;
            bool canpush;
            if (movement[i]=='*' && movement[i+1]=='*')//如果是乘方
            {
                canpush=pushop('^');
                if (canpush==false) return false;
                i+=2;
            }
            else
            {
                canpush=pushop(movement[i].toLatin1());
                if (canpush==false) return false;
                ++i;
            }

            continue;
        }


    }

    //下面要把双栈中未执行的运算全部执行
    if (variable!="")
    {
        if (isNodeExist(variable)==false) return false;
        else
        {
            numnode *n=new numnode (NodeValue(variable));
            numlist.push_front(*n);
            variable="";
        }
    }


    while(oplist.empty()==false)
    {
        if (numlist.empty()==true) return false;


        if (oplist.begin()->s == '+')
        {
             oplist.pop_front();
             if (numlist.empty()==true) return false;
             numnode *a=new numnode(numlist.begin()->x);
             numlist.pop_front();
             if (numlist.empty()==true) return false;
             numnode *b=new numnode(numlist.begin()->x);
             numlist.pop_front();
             numnode* n=new numnode(b->x+a->x,'+',b,a);
             numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '-')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(b->x-a->x,'-',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '*')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(b->x*a->x,'*',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '/')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(b->x/a->x,'/',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '^')
        {
            oplist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *a=new numnode(numlist.begin()->x);
            numlist.pop_front();
            if (numlist.empty()==true) return false;
            numnode *b=new numnode(numlist.begin()->x);
            numlist.pop_front();
            numnode* n=new numnode(mi(b->x,a->x),'^',b,a);
            numlist.push_front(*n);
        }
        else if (oplist.begin()->s == '(') return false;

    }

    if (oplist.empty()==false) return false;
    if (numlist.empty()==true) return false;

    int temp=numlist.begin()->x;
    numlist.pop_front();
    if (numlist.empty()==false) return false;
    else num=temp;

    return true;
}

int running::mi(int a,int b)
{
    int temp=1;
    if (b==0) return 1;
    if (b<0)
        for (int i=-1;i>=b;--i)
            temp = temp / a;

    for (int i=1;i<=b;++i)//乘以b次
        temp = temp * a;
    return temp;
}

void running::com(int c,QString movement)
{
    switch (c)
    {
    case 5://LET
    {
        if (isExpressionValid(movement) == false) {writeToConsole("Unknown command!");return;}
        else
        {
            bool valid ;
            valid= let_func(movement);
            if (valid==false)
            {
                writeToConsole("Unknown command!");

                numlist.clear();//数字列表
                oplist.clear();//操作符列表
                Inputnum="";

                return;
            }
        }
        break;
    }
    case 6://PRINT
    {
        if (isExpressionValid(movement) == false)
        {
            writeToConsole("Unknown command!");

            numlist.clear();//数字列表
            oplist.clear();//操作符列表
            Inputnum="";

            return;
        }
        else
        {
            bool valid ;
            int a;
            valid=value_of(a,movement);
            if (valid==false)
            {
                writeToConsole("Unknown command!");

                numlist.clear();//数字列表
                oplist.clear();//操作符列表

                return;
            }
            else writeToConsole(QString::number(a));
        }
        break;
    }
    case 7://INPUT
    {
       if (movement[0]=='\0')
       {
           writeToConsole("Unknown command!");

           numlist.clear();//数字列表
           oplist.clear();//操作符列表
           Inputnum="";

           return;
       }

       //先检查变量命名是否合格

       int i=0;
       while(movement[i]!='\0')
       {
           if (!((movement[i].toLower()>='a' && movement[i].toLower()<='z') || (movement[i]=='_')))
           {
               writeToConsole("Unknown command!");

               numlist.clear();//数字列表
               oplist.clear();//操作符列表
               Inputnum="";

               return;
           }

           else i++;

       }

       writeToConsole("pls input ");
       isInputing=true;//表明正在输入
       setExpisInputing(true);
       loop.exec();

       i=0;
       while (Inputnum[i]!='\0')
       {
           if (Inputnum[i]<'0' || Inputnum[i]>'9')
           {
                   writeToConsole("Unknown command!");

                   numlist.clear();//数字列表
                   oplist.clear();//操作符列表
                   Inputnum="";

                   return;
           }
           i++;
       }


       if (List.empty()==true)
       {
           Node *node=new Node(movement,Inputnum.toInt());
           List.push_front(*node);
       }

       else
       {
           list<Node>::iterator iter2=List.begin();//定义一个新的迭代器iter2,来寻找iter1要input的变量
           QString key = " ";
           do
           {

               if (iter2==List.end())//如果没有就push一个进去
               {
                   Node *node=new Node(movement,Inputnum.toInt());
                   List.push_front(*node);
                   break;
               }

               key = iter2->key;
               if (key == movement)
               {
                   iter2->value=Inputnum.toInt();//赋值为input的数值
                   break;
               }
               iter2++;
           }while (key != movement);
       }


       Inputnum="";

       break;
    }
    default:break;
    }
    return;
}
