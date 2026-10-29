#include "ViewStateMachine.h"

#include <QKeyEventTransition>

ViewStateMachine::ViewStateMachine(QuiltView *quiltView)
    : view_{quiltView}
    , initialState_{new QState{}}
    , dragPan_{new QState{}}
    , bandSelect_{new QState{}}
    , pressAlt_{new QKeyEventTransition(view_, QEvent::KeyPress, Qt::Key_Alt)}
    , releaseAlt_{new QKeyEventTransition(view_, QEvent::KeyRelease, Qt::Key_Alt)}
    , pressShift_{new QKeyEventTransition(view_, QEvent::KeyPress, Qt::Key_Shift)}
    , releaseShift_{new QKeyEventTransition(view_, QEvent::KeyRelease, Qt::Key_Shift)}
{
    QObject::connect(initialState_, &QState::entered, [this]{
        this->view_->setDragMode(QGraphicsView::NoDrag);
    });

    QObject::connect(dragPan_, &QState::entered, [this]{
        this->view_->setDragMode(QGraphicsView::ScrollHandDrag);
    });

    QObject::connect(bandSelect_, &QState::entered, [this]{
        this->view_->setDragMode(QGraphicsView::RubberBandDrag);
    });

    pressAlt_->setTargetState(dragPan_);
    initialState_->addTransition(pressAlt_);

    releaseAlt_->setTargetState(initialState_);
    dragPan_->addTransition(releaseAlt_);

    pressShift_->setTargetState(bandSelect_);
    initialState_->addTransition(pressShift_);

    releaseShift_->setTargetState(initialState_);
    bandSelect_->addTransition(releaseShift_);

    machine_.addState(initialState_);
    machine_.addState(dragPan_);
    machine_.addState(bandSelect_);

    machine_.setInitialState(initialState_);

    machine_.start();
}
