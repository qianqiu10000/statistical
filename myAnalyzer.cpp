#include "myAnalyzer.h"

#include<QFile>
#include<QDebug>

myAnalyzer::myAnalyzer()
{
    initialize();
}

myAnalyzer::~myAnalyzer()
{

}

int myAnalyzer::codeLines() const
{
    return m_codeLines;
}

int myAnalyzer::microLines() const
{
    return m_microLines;
}

int myAnalyzer::emptyLines() const
{
    return m_emptyLines;
}

int myAnalyzer::annoMultiLines() const
{
    return m_annoMultiLines;
}

int myAnalyzer::annoSingleLines() const
{
    return m_annoSingleLines;
}

bool myAnalyzer::procFile(const QString &name)
{
    initialize();
    QFile file(name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd()) {
            oneLine(file.readLine());
        }

        file.close();
        return true;
    }

    return false;

}

void myAnalyzer::initialize()
{
    m_codeLines = 0;
    m_microLines = 0;
    m_emptyLines = 0;
    m_annoMultiLines = 0;
    m_annoSingleLines = 0;
    m_linePointer = &m_codeLines;

    m_multiFlag = false;
}

void myAnalyzer::oneLine(const QString &line)
{

    QString newline = line.simplified();

    if(!m_multiFlag)                                                                   //多行注释中不需要判断
    {
        if(newline.isEmpty()) {
            m_linePointer = &m_emptyLines;
        }
        else if(newline.startsWith('#')) {                                      //该行是预编译宏
            m_linePointer = &m_microLines;
        }
        else if(newline.startsWith("//")) {                                    //该行是注释
            m_linePointer = &m_annoSingleLines;
        }
        else if(newline.startsWith("/*")) {                                    //注释开始
            m_linePointer = &m_annoMultiLines;
            m_multiFlag = true;
        } else {
            m_linePointer = &m_codeLines;
        }
    }

    (*m_linePointer)++;

    if(m_multiFlag && newline.endsWith("*/"))    {
        m_multiFlag = false;
    }

}
