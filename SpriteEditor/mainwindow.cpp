#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFlags>
#include <QGraphicsScene>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(new QColor()) {
    ui->setupUi(this);

    canvasImage = new QImage();
    canvasImage->size().setHeight(800);
    canvasImage->size().setWidth(600);
    canvasPainter = new QPainter();


    // Set up the color selector
    colorSelector = new QColorDialog(parent);
    colorSelector->setOption(QColorDialog::ShowAlphaChannel);
    colorSelector->setOption(QColorDialog::NoButtons);
    colorSelector->setOption(QColorDialog::DontUseNativeDialog);

    // Dock widget is used to place the color selector on the main window
    ui->dockWidget_2->setWidget(colorSelector);
    ui->dockWidget_2->setFloating(false);
    colorSelector->resize(12, 6);
    colorSelector->setVisible(true);

    themes = new Themes();

    p = new QPixmap(700,700);
}

/*
void MainWindow::paintEvent(QPaintEvent *) {
    //set painter to pixmap of current frame
    QPainter * painter = new QPainter(paintedFrames[currentFrameIndex]);

    QColor[][] * currentFrameMap = frames->at(currentFrameIndex);
    //draw every pixel in the pixel
    for(int i = 0; i < canvasSize; i++) {
        for(int j = 0; j < canvasSize; j++) {
            painter->setPen(currentFrameMap[i][j]);
            painter->drawPoint(i, j);
        }
    }
    delete painter;
    ui->canvas = paintedFrames[currentFrameIndex];
}
*/

MainWindow::~MainWindow() {
    delete ui;
    delete canvasImage;
    delete canvasPainter;
    delete themes;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    statusBar()->showMessage(event->pos().x() + ", " + event->pos().y());
    qDebug() << event->pos();
}

void MainWindow::on_actionDark_triggered()
{
    qDebug("Dark triggered");
    statusBar()->showMessage("Dark theme enabled.");
    themes->changeTheme(Themes::DARK);
}

void MainWindow::on_actionLight_triggered()
{
    qDebug("Light triggered");
    statusBar()->showMessage("Light theme enabled");
    themes->changeTheme(Themes::LIGHT);
}




void MainWindow::on_dockWidget_2_visibilityChanged(bool visible)
{

}

void MainWindow::on_actionBlue_triggered()
{
    statusBar()->showMessage("Blue theme enabled");
    themes->changeTheme(Themes::BLUE);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Calculates position for grid.
    xPos = (event->pos().x() / 40) * 40;
    yPos = (event->pos().y() / 40) * 40;

    // Adds the point to the list of points to draw.
    QPoint point = QPoint(xPos, yPos);
    pointsList.push_back(point);

    QPainter painter(p);
    QRect rect = QRect(xPos, yPos, 40, 40);
    painter.drawRect(rect);
    painter.fillRect(rect, Qt::black);
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,700,700,*p);
}







