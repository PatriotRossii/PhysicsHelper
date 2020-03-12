#include "qformulaswindow.h"

QFormulasWindow::QFormulasWindow(QWidget* parent): QWidget(parent) {
    SetupGui();
}

void QFormulasWindow::SetupGui() {
    m_pMainVBL = new QVBoxLayout();
    setLayout(m_pMainVBL);
}
