#include "Tiles.h"

#include <numbers>


QList<QPointF> Rhomb::generatePoints(const double narrowAngleDeg, const double lengthScaleIn)
{

    constexpr double pi = std::numbers::pi;

    const auto lengthScalePx = toPx(lengthScaleIn);

    const auto narrowAngleRad = narrowAngleDeg * pi / 180.0;
    const auto xOffset = lengthScalePx * cos(narrowAngleRad);
    const auto yOffset = lengthScalePx * sin(narrowAngleRad);

    return {
        QPointF{0,0},
        QPointF{lengthScalePx, 0},
        QPointF{lengthScalePx + xOffset, yOffset},
        QPointF{xOffset, yOffset},
        QPointF{0,0}
    };
}
