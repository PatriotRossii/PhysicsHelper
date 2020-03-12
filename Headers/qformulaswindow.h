#ifndef QFORMULASWINDOW_H
#define QFORMULASWINDOW_H

#include <QtWidgets>
#include "qformulalinkwidget.h"
#include "qformulawindowexample.h"

class QFormulasWindow: public QWidget {
    Q_OBJECT
public:
    QFormulasWindow(QWidget* parent = nullptr);
private:
    QVBoxLayout* m_pMainVBL;
private:
    void SetupGui();
};

#endif // QFORMULASWINDOW_H
