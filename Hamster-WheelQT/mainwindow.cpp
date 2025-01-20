#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    loadPropertyEditorPanel();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadPropertyEditorPanel() {
    QUiLoader loader;

    QFile file(":/panels/propertyeditorpanel.ui");
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << "Failed to open file:" << file.errorString();
        qWarning() << "File path:" << file.fileName();
        return;
    }

    QWidget* propertyEditorPanel = loader.load(&file, this); // Load the UI file
    file.close();

    if (!propertyEditorPanel) {
        qWarning("Failed to load propertyeditorpanel.ui");
        return;
    }

    QDockWidget* dockWidget = new QDockWidget("dockWidgetName", this);
    dockWidget->setWidget(propertyEditorPanel);
    dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);

    this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}
