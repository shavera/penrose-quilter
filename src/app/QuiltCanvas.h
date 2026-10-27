#pragma once

#include "Tiles.h"

#include <QGraphicsScene>

class QuiltCanvas : public QGraphicsScene{
public:
    struct Args{
        double tileScaleIn;
        double quiltWidthIn;
        double quiltHeightIn;
        QObject* parent;
    };

    explicit QuiltCanvas(const Args& args);
    // QuiltCanvas(double tileScaleIn, double quiltWidthIn, double quiltHeightIn, QObject* parent = nullptr);

    void addTile(const Tile& tile){
        addPolygon(tile);
    }

    void setTileScale(double tileScaleIn){
        tileScaleIn_ = tileScaleIn;
        updateBoundaries();
    }
    void setQuiltWidth(double quiltWidthIn){
        quiltSizePx_.setWidth(toPx(quiltWidthIn));
        updateBoundaries();
    }
    void setQuiltHeight(double quiltHeightIn){
        quiltSizePx_.setHeight(toPx(quiltHeightIn));
        updateBoundaries();
    }

private:
    void updateBoundaries();

    static QRectF quiltBorderRect(const QSizeF& size){
        const auto topLeft = QPointF{-size.width()/2, -size.height()/2};
        return {topLeft, size};
    }

    static QRectF quiltBorderRect(const double widthIn, const double heightIn){
        return quiltBorderRect(toPx(widthIn, heightIn));
    }

    double tileScaleIn_;
    QSizeF quiltSizePx_;
};
