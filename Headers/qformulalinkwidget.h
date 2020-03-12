#ifndef QFORMULALINKWIDGET_H
#define QFORMULALINKWIDGET_H

#include <QWidget>

class QFormulaLinkWidget {
public:
    explicit QFormulaLinkWidget(QString lbl, QWidget* dst);

    QString getLabelText();
    QWidget* getDestination();
private:
    QString m_Label;
    QWidget* m_pDestinationLayout;
};

#endif // QFORMULALINKWIDGET_H
