#include "qformulalinkwidget.h"

QFormulaLinkWidget::QFormulaLinkWidget(QString lbl, QWidget* dst) {
    this->m_Label = lbl;
    this->m_pDestinationLayout = dst;
}

QString QFormulaLinkWidget::getLabelText() {
    return m_Label;
}

QWidget* QFormulaLinkWidget::getDestination() {
    return m_pDestinationLayout;
}
