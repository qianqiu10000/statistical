#ifndef MYANALYZER_H
#define MYANALYZER_H


class QString;
class myAnalyzer
{
public:
    myAnalyzer();
    virtual ~myAnalyzer();

    int codeLines()const;
    int microLines()const;
    int emptyLines()const;
    int annoMultiLines()const;
    int annoSingleLines()const;
    bool procFile(const QString &name);

private:
    int *m_linePointer;
    int m_codeLines;
    int m_microLines;
    int m_emptyLines;
    int m_annoMultiLines;
    int m_annoSingleLines;

    bool m_multiFlag;
private:
    void initialize();
    void oneLine(const QString &line);
};

#endif // MYANALYZER_H
