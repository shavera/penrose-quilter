#pragma once

#include <QPolygonF>

static constexpr double kPixToInScale{64.0};

static double toPx(const double in){
    return in*kPixToInScale;
}

static QSizeF toPx(const double widthIn, const double heightIn){
    return {toPx(widthIn), toPx(heightIn)};
}

class Tile : public QPolygonF{
protected:
    Tile(QList<QPointF> points)
        : QPolygonF{std::move(points)}
    {}
};

class Rhomb : public Tile{
public:
    static QList<QPointF> generatePoints(double narrowAngleDeg, double lengthScaleIn);

protected:
    Rhomb(double narrowAngleDeg, double lengthScaleIn)
        : Tile{generatePoints(narrowAngleDeg, lengthScaleIn)}
    {}
};

class ThinRhomb : public Rhomb{
public:
    static constexpr double kNarrowAngleDeg{36.0};
    explicit ThinRhomb(double lengthScaleIn)
        : Rhomb{kNarrowAngleDeg, lengthScaleIn}
    {}
};

class WideRhomb : public Rhomb{
public:
    static constexpr double kNarrowAngleDeg{72.0};
    explicit WideRhomb(double lengthScaleIn)
        : Rhomb{kNarrowAngleDeg, lengthScaleIn}
    {}
};
