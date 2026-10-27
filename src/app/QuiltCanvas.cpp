#include "QuiltCanvas.h"


QuiltCanvas::QuiltCanvas(const Args& args)
    : QGraphicsScene{quiltBorderRect(args.quiltWidthIn, args.quiltHeightIn), args.parent}
    , tileScaleIn_{args.tileScaleIn}
    , quiltSizePx_{toPx(args.quiltWidthIn, args.quiltHeightIn)}
{

}

void QuiltCanvas::updateBoundaries()
{
    setSceneRect(quiltBorderRect(quiltSizePx_));
}
