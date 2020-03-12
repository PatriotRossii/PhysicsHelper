#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("PhysicsHelper"));

    m_pSettings = new QSettings();
    m_pMainTab = new QTabWidget();

    m_pFormulasWindow = new QFormulasWindow();
    m_pMainTab->addTab(m_pFormulasWindow, tr("Formulas"));

    m_pFormulasMenu = new QMenu("Формулы");
    m_formulas = {
        {"Кинематика", {new QFormulaLinkWidget("Sum",
                            new QFormulaWindowExample({QPair<QString, TYPE>("First argument", TYPE::INTEGER), QPair<QString, TYPE>("Second argument", TYPE::INTEGER)}, [](std::vector<std::variant<int, double, QString>> arguments) -> QString {
                                if(std::holds_alternative<int>(arguments[0]) && std::holds_alternative<int>(arguments[1])) {
                                    return QString::number(std::get<int>(arguments[0]) + std::get<int>(arguments[1]));
                                }
                                return QString("Error");
                            })
                        )}
        }
    };

    for(auto it = m_formulas.cbegin(); it != m_formulas.end(); ++it) {
        QMenu* newMenu = new QMenu(it.key());
        for(auto y: it.value()) {
            newMenu->addAction(y->getLabelText(), [this, dst=y->getDestination(), lbl=y->getLabelText()]() {
               this->changeWindow(dst, lbl);
            });
        }
        m_pFormulasMenu->addMenu(newMenu);
    }

    menuBar()->addMenu(m_pFormulasMenu);

    setCentralWidget(m_pMainTab);
    setMinimumSize(640, 480);
    LoadSettings();
}

MainWindow::~MainWindow() {
    SaveSettings();
}

void MainWindow::SaveSettings() {
    m_pSettings->beginGroup("MainWindow");

    m_pSettings->setValue("width", this->width());
    m_pSettings->setValue("height", this->height());
    m_pSettings->setValue("posX", this->x());
    m_pSettings->setValue("posY", this->y());

    m_pSettings->endGroup();
}

void MainWindow::LoadSettings()
{
    QScreen* p_Screen = QGuiApplication::screens().first();
    QRect rect = p_Screen->geometry();

    int width, height, posX, posY, startX, startY;

    width  = m_pSettings->value("MainWindow/width", rect.width()/2).toInt();
    height = m_pSettings->value("MainWindow/height", rect.height()/1.6).toInt();

    startX = rect.center().x() - (width/2);
    startY = rect.center().y() - (height/2);

    posX   = m_pSettings->value("MainWindow/posX", startX).toInt();
    posY   = m_pSettings->value("MainWindow/posY", startY).toInt();

    setGeometry(posX, posY, width, height);
}

void MainWindow::changeWindow(QWidget* dst, QString title) {
    m_pMainTab->addTab(dst, title);
    m_pMainTab->setCurrentWidget(dst);
}
