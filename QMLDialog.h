#pragma once

#include <QDialog>
#include <QTimer>
#include <QPointF>

class QMLDialog : public QDialog
{
    Q_OBJECT

    Q_PROPERTY(QPointF brokenGrainValue READ GetBrokenGrainValueValue NOTIFY brokenGrainValueChanged)
    Q_PROPERTY(QPointF grainLossBackgroundDataValue READ GetGrainLossBackgroundDataValue NOTIFY grainLossBackgroundDataValueChanged)
    Q_PROPERTY(QPointF grainLossForegroundDataValue READ GetGrainLossForegroundDataValue NOTIFY grainLossForegroundDataValueChanged)
    Q_PROPERTY(double grainLossMaxValue READ GetGrainLossMaxValue CONSTANT)
    Q_PROPERTY(double brokenGrainMaxValue READ GetBrokenGrainMaxValue CONSTANT)
    Q_PROPERTY(QPointF foreignMaterialValue READ GetForeignMaterialValue NOTIFY foreignMaterialValueChanged)
    Q_PROPERTY(double foreignMaterialMaxValue READ GetForeignMaterialMaxValue CONSTANT)
    Q_PROPERTY(QPointF productivityValue READ GetProductivityValue NOTIFY productivityValueChanged)
    Q_PROPERTY(double productivityMaxValue READ GetProductivityMaxValue CONSTANT)

public:
    QMLDialog(QWidget *parent = nullptr);
    ~QMLDialog() = default;

    QPointF GetBrokenGrainValueValue() const { return BrokenGrainDataPoint;}
    double GetBrokenGrainMaxValue() const {return BrokenGrainMaxValue;}

    QPointF GetGrainLossBackgroundDataValue() const {return GrainLossBackgroundDataValue;}
    QPointF GetGrainLossForegroundDataValue() const {return GrainLossForegroundDataValue;}
    double GetGrainLossMaxValue() const {return GrainLossMaxValue;}

    QPointF GetForeignMaterialValue() const {return ForeignMaterialDataValue;}
    double GetForeignMaterialMaxValue() const {return ForeignMaterialMaxValue;}

    QPointF GetProductivityValue() const { return ProductivityDataValue;}
    double GetProductivityMaxValue() const {return ProductivityMaxValue;}

signals:
    void grainLossBackgroundDataValueChanged();
    void grainLossForegroundDataValueChanged();
    void foreignMaterialValueChanged();
    void areaSeriesTwoLowerValueChanged();
    void brokenGrainValueChanged();
    void productivityValueMaxChanged();
    void productivityValueChanged();

private slots:
    void GraphDataTimeout();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    double RandomNumberGenerator(const double min, const double max) const;
    void CalculateBrokenGrainMaxValue();
    void CalculateGrainLossMaxValue();
    void CalculateForeignMaterialMaxValue();
    void CalculateProductivityMaxValue();

    QTimer* GraphDataTimer;
    QWidget* QMLContainer = nullptr;
    QPointF BrokenGrainDataPoint;
    double BrokenGrainMaxValue = 1.2;
    QPointF GrainLossBackgroundDataValue;
    QPointF GrainLossForegroundDataValue;
    double GrainLossMaxValue = 1.2;
    QPointF ForeignMaterialDataValue;
    double ForeignMaterialMaxValue = 1.2;
    QPointF ProductivityDataValue;
    double ProductivityMaxValue = 1.2;
};
