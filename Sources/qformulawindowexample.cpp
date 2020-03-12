#include "qformulawindowexample.h"

#define lambdaType std::function<QString(std::vector<std::variant<int, double, QString>>)>

QFormulaWindowExample::QFormulaWindowExample(std::initializer_list<QPair<QString, TYPE>> list, lambdaType lambda, QWidget* parent): QWidget(parent) {
    this->m_typesData = std::move(list);
    this->m_lambda = lambda;

    this->m_pMainLayout = new QVBoxLayout();

    for(const QPair<QString, TYPE>& x: list) {
        QHBoxLayout* argument = new QHBoxLayout();

        QLabel* label = new QLabel(x.first);
        QLineEdit* lineEdit = new QLineEdit();

        argument->addWidget(label);
        argument->addWidget(lineEdit);

        QObject::connect(lineEdit, &QLineEdit::editingFinished, this, &QFormulaWindowExample::check, Qt::AutoConnection);
        this->m_pMainLayout->addLayout(argument);
    }

    this->m_pResult = new QHBoxLayout();
    this->m_pResultLbl = new QLabel("Result:");
    this->m_pResultEdt = new QLineEdit();

    this->m_pMainLayout->addStretch(1);

    m_pResult->addWidget(m_pResultLbl);
    m_pResult->addWidget(m_pResultEdt);

    m_pMainLayout->addLayout(m_pResult);

    setLayout(m_pMainLayout);
    QObject::connect(this, &QFormulaWindowExample::printResult, this, &QFormulaWindowExample::writeResult, Qt::AutoConnection);
}

void QFormulaWindowExample::check() {
    QList<QLineEdit*> lineEdits = this->m_pMainLayout->findChildren<QLineEdit*>();
    for(QList<QLineEdit*>::iterator it = lineEdits.begin(); it != lineEdits.end() - 1; ++it) {
        if((*it)->text().isEmpty()) {
            return;
        }
    }
    emit this->printResult(lineEdits);
}

void QFormulaWindowExample::writeResult(QList<QLineEdit*> list) {
    std::vector<std::variant<int, double, QString>> arguments;
    arguments.reserve(list.size() - 1);
    for(unsigned int i = 0; i < list.size(); ++i) {
        auto it = m_typesData.begin() + i;
        if(it->second == TYPE::INTEGER) {
            arguments.push_back(std::variant<int, double, QString>(list[i]->text().toInt()));
        } else if(it->second == TYPE::DOUBLE) {
            arguments.push_back(std::variant<int, double, QString>(list[i]->text().toDouble()));
        } else if(it->second == TYPE::STRING) {
            arguments.push_back(std::variant<int, double, QString>(list[i]->text()));
        }
    }
    this->m_pResultLbl->setText(this->m_lambda(arguments));
}
