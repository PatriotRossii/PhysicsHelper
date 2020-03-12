#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include <stdexcept>

#include "qformulaswindow.h"
#include "global.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QTabWidget* m_pMainTab;
    QFormulasWindow* m_pFormulasWindow;

    QMenu* m_pFormulasMenu;
    QMap<QString, QList<QFormulaLinkWidget*>> m_formulas;

    QSettings* m_pSettings;
private:
    void SaveSettings();
    void LoadSettings();
    void changeWindow(QWidget* dst, QString title);
};

#endif // MAINWINDOW_H
