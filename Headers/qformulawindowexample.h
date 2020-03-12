#ifndef QFORMULAWINDOWEXAMPLE_H
#define QFORMULAWINDOWEXAMPLE_H

#include <QtWidgets>
#include <vector>
#include <utility>

#include "global.h"

#define lambdaType std::function<QString(std::vector<std::variant<int, double, QString>>)>

class QFormulaWindowExample: public QWidget {
    Q_OBJECT
public:
    QFormulaWindowExample(std::initializer_list<QPair<QString, TYPE>>, lambdaType lambda, QWidget* parent = nullptr);
private:
    QVBoxLayout* m_pMainLayout;

    QHBoxLayout* m_pResult;

    QLabel* m_pResultLbl;
    QLineEdit* m_pResultEdt;

    std::initializer_list<QPair<QString, TYPE>> m_typesData;
    lambdaType m_lambda;
signals:
    void printResult(QList<QLineEdit*>);
public slots:
    void check();
    void writeResult(QList<QLineEdit*> lineEdits);
};

#endif // QFORMULAWINDOWEXAMPLE_H
