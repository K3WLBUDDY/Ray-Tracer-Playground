#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include<QTextEdit>

class TextEdit:public QTextEdit
{
    Q_OBJECT

public:
    explicit TextEdit(const QString *plainText, QWidget *parent = 0);
};

#endif // TEXTEDIT_H