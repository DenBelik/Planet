#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timerCycle;
    int orbitalRadius = 300;
    int planetSize;
    int atmosphereUpSize;
    double speedPlanetRotation;
    double orbitalRotation;
    double speedOrbitalRotation = 0.6;
    double planetRotation =0;
    double speedAtmosphereRotation;
    double atmosphereRotation = 0;


    QImage starBackground;
    QImage planetTexture;
    QImage planetAlpha;
    QImage planet;
    QImage planetShadow;
    QImage planetLightsTexture;
    QImage planetLightsAlpha;
    QImage planetLights;
    QImage planetAtmosphereTexture;
    QImage planetAtmosphereAlpha;
    QImage planetAtmosphere;

private:
    Ui::MainWindow *ui;

private slots:
    void paintEvent(QPaintEvent *event);
    void cycle();
};
#endif // MAINWINDOW_H
