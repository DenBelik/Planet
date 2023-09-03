#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QImage"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    speedPlanetRotation = 2.5;
    speedAtmosphereRotation = 3.0;
    planetSize = 100;
    atmosphereUpSize = 6;

    starBackground.load("img/star_background.jpg");
    planetTexture.load("img/planet_texture.png");
    planetAlpha.load("img/planet_alpha.png");
    planetShadow.load("img/planet_shadow.png");
    planetLightsTexture.load("img/planet_lights_texture.png");
    planetLightsAlpha.load("img/planet_lights_alpha.png");
    planetAtmosphereTexture.load("img/planet_atmosphere_texture.png");
    planetAtmosphereAlpha.load("img/planet_atmosphere_alpha.png");

    planetAlpha = planetAlpha.scaled(planetSize, planetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planetShadow = planetShadow.scaled(planetSize, planetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planetLightsTexture = planetLightsTexture.scaled(planetTexture.width(), planetTexture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planetLightsAlpha = planetLightsAlpha.scaled(planetSize, planetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planetAtmosphereTexture = planetAtmosphereTexture.scaled(planetTexture.width(), planetTexture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planetAtmosphereAlpha = planetAtmosphereAlpha.scaled(planetSize, planetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    timerCycle = new QTimer;
    connect(timerCycle, SIGNAL(timeout()), this, SLOT(cycle()));
    timerCycle->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {

    QPainter painter(this);

    painter.setViewport(ui->screen->geometry().x(), ui->screen->geometry().y(), ui->screen->geometry().width(), ui->screen->geometry().height());

    starBackground = starBackground.scaled(ui->screen->geometry().width(), ui->screen->geometry().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter.drawImage(0, 0, starBackground);
    painter.save();

    //painter.translate(ui->screen->geometry().width()/2, ui->screen->geometry().height()/2);


    painter.translate(ui->screen->geometry().width()/2, ui->screen->geometry().height()/2);
    painter.rotate(orbitalRotation);

    painter.translate(ui->screen->geometry().width()/5, ui->screen->geometry().height()/5);
    painter.rotate(-orbitalRotation);

    painter.drawImage(-planetSize/2, -planetSize/2, planet);
    painter.drawImage(-(planetSize + atmosphereUpSize)/2, -(planetSize + atmosphereUpSize)/2, planetAtmosphere);
    painter.rotate(orbitalRotation);
    painter.drawImage(-planetSize/2, -planetSize/2, planetShadow);
    painter.rotate(-orbitalRotation);
    painter.drawImage(-planetSize/2, -planetSize/2, planetLights);

    painter.restore();

    QPainter sun(this);
    QPen pen;
    QBrush brush;

    pen.setColor(Qt::yellow);
    pen.setWidth(5);
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);

    sun.setPen(pen);
    sun.setBrush(brush);
    sun.drawEllipse(ui->screen->geometry().width()/2-100, ui->screen->geometry().height()/2-100, 180, 180);


}

void MainWindow::cycle()
{
    planet = planetTexture.copy(planetRotation, 0, planetTexture.height(), planetTexture.height());
    planet = planet.scaled(planetSize, planetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    planetLights = planetLightsTexture.copy(planetRotation, 0, planetLightsTexture.height(), planetLightsTexture.height());
    planetLights = planetLights.scaled(planetSize, planetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    planetAtmosphere = planetAtmosphereTexture.copy(atmosphereRotation, 0, planetAtmosphereTexture.height(), planetAtmosphereTexture.height());
    planetAtmosphere = planetAtmosphere.scaled(planetSize, planetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPainter painter1(&planet);
    painter1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter1.drawImage(0, 0, planetAlpha);

//    QPainter painterTest(&planetLights);

//    painterTest.translate(planetSize/2, planetSize/2);
//    painterTest.rotate(planetRotation);
//    painterTest.drawImage(-planetSize/2, -planetSize/2, planetLightsAlpha);

    QPainter painter2(&planetLights);
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter2.drawImage(0, 0, planetAlpha);
    painter2.translate(planetSize/2, planetSize/2);
    painter2.rotate(orbitalRotation);
    painter2.drawImage(-planetSize/2, -planetSize/2, planetLightsAlpha);

    QPainter painter3(&planetAtmosphere);
    painter3.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter3.drawImage(0, 0, planetAtmosphereAlpha);



    planetRotation += speedPlanetRotation;
    atmosphereRotation += speedAtmosphereRotation;
    orbitalRotation += speedOrbitalRotation;
    if (orbitalRotation >= 360) orbitalRotation = 0;
    if (planetRotation + planetTexture.height() >= planetTexture.width()) planetRotation = 0;
    if (atmosphereRotation + planetAtmosphereTexture.height() >= planetAtmosphereTexture.width()) atmosphereRotation = 0;

    update();
}

