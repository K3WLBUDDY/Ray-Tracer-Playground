#include <QtWidgets>
#include "textedit.h"

TextEdit::TextEdit(const QString *plainText, QWidget *parent):QTextEdit(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}
