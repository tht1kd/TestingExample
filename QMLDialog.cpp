#include "QMLDialog.h"
#include <QQmlContext>
#include <QQuickView>
#include <iostream>

namespace
{
   constexpr int MAIN_DIALOG_WIDTH = 780;
   constexpr int MAIN_DIALOG_HEIGHT = 480;
}

//TODO: correctly instantiate with different data // DONE!
//TODO: be able to update "numbers" data from CompoundComponent. //DONE!
//TODO: be able to open overlay in QML for changing max. https://doc.qt.io/qt-6/qtqml-cppintegration-interactqmlfromcpp.html //LATER!
//TODO: create productivity section //DONE!
//TODO: Cleaup QML
//TODO: Ajay's request for this story, make runpage, no button clicking. Connect to all old data.
//TODO: finish limit line icon for area series
//TODO: finish line graph compound component sizing

QMLDialog::QMLDialog(QWidget *parent)
    : QDialog(parent)
    , GraphDataTimer(new QTimer(this))
{
    GraphDataTimer->setSingleShot(false);
    GraphDataTimer->setInterval(1000);

    setWindowTitle("Look at These graphs");
    setMinimumSize(MAIN_DIALOG_WIDTH, MAIN_DIALOG_HEIGHT);
    QQuickView* qmlView = new QQuickView();
    qmlView->setResizeMode(QQuickView::SizeRootObjectToView);
    qmlView->setSource(QUrl("qrc:///PFCApp/Resource_Files/QML/AutomationRunpageGraphModule.qml"));
    QMLContainer = QWidget::createWindowContainer(qmlView, this);
    QMLContainer->resize(size());
    qmlView->rootContext()->setContextProperty("pfcData", this);

    connect(GraphDataTimer, &QTimer::timeout, this, &QMLDialog::GraphDataTimeout);
    GraphDataTimer->start(1000);
}

void QMLDialog::GraphDataTimeout()
{
    //Note: Yes this is bad practice, but the point is to show how these can be separated into different slots and updated asynchronously.
    BrokenGrainDataPoint.setX(BrokenGrainDataPoint.x()+1);
    BrokenGrainDataPoint.setY(RandomNumberGenerator(0, 3.0));
    CalculateBrokenGrainMaxValue();
    emit brokenGrainValueChanged();

    GrainLossBackgroundDataValue.setX(GrainLossBackgroundDataValue.x()+1);
    GrainLossBackgroundDataValue.setY(RandomNumberGenerator(0, 1.0));
    CalculateGrainLossMaxValue();
    emit grainLossBackgroundDataValueChanged();

    GrainLossForegroundDataValue.setX(GrainLossForegroundDataValue.x()+1);
    GrainLossForegroundDataValue.setY(RandomNumberGenerator(0, 0.5));
    CalculateGrainLossMaxValue();
    emit grainLossForegroundDataValueChanged();

    ForeignMaterialDataValue.setX(ForeignMaterialDataValue.x()+1);
    ForeignMaterialDataValue.setY(RandomNumberGenerator(0, 0.5));
    CalculateForeignMaterialMaxValue();
    emit foreignMaterialValueChanged();

    ProductivityDataValue.setX(ProductivityDataValue.x()+1);
    ProductivityDataValue.setY((RandomNumberGenerator(0, 50)));
    CalculateProductivityMaxValue();
    emit productivityValueChanged();
}

void QMLDialog::resizeEvent(QResizeEvent *event)
{
    QMLContainer->resize(size());
    QDialog::resizeEvent(event);
}

double QMLDialog::RandomNumberGenerator(const double min, const double max) const
{
    return min + (double)rand() / RAND_MAX * (max-min);
}

void QMLDialog::CalculateBrokenGrainMaxValue()
{
    BrokenGrainMaxValue = qMax(BrokenGrainMaxValue, (double)BrokenGrainDataPoint.y());
}

void QMLDialog::CalculateGrainLossMaxValue()
{
    GrainLossMaxValue = qMax(GrainLossMaxValue, qMax((double)GrainLossBackgroundDataValue.y(), (double)GrainLossForegroundDataValue.y()));
}

void QMLDialog::CalculateForeignMaterialMaxValue()
{
    ForeignMaterialMaxValue = qMax(ForeignMaterialMaxValue, (double)ForeignMaterialDataValue.y());
}

void QMLDialog::CalculateProductivityMaxValue()
{
    ProductivityMaxValue = qMax(ProductivityMaxValue, (double)ProductivityDataValue.y());
}
