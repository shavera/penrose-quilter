#include "QuiltView.h"

#include <QKeyEventTransition>
#include <QState>
#include <QStateMachine>

QPointer<QStateMachine> QuiltView::configureStateMachine(QuiltView* view)
{
  QPointer<QStateMachine> qsm{new QStateMachine{view}};
  qsm->setObjectName("quiltViewStateMachine");

  auto* initialState = new QState{};
  initialState->setObjectName("initialState");
  auto* ready = new QState{};
  ready->setObjectName("ready");
  auto* dragPan = new QState{};
  dragPan->setObjectName("dragPan");
  auto* bandSelect = new QState{};
  bandSelect->setObjectName("bandSelect");

  initialState->addTransition(ready);

  view->setDragMode(QGraphicsView::NoDrag);

  QObject::connect(dragPan, &QState::entered, [view] {
    qDebug() << "Enter dragPan";
    view->setDragMode(QGraphicsView::ScrollHandDrag);
  });
  QObject::connect(dragPan, &QState::exited, [view] {
    qDebug() << "Exit dragPan";
    view->setDragMode(QGraphicsView::NoDrag);
  });

  QObject::connect(bandSelect, &QState::entered, [view] {
    qDebug() << "Enter bandSelect";
    view->setDragMode(QGraphicsView::RubberBandDrag);
  });
  QObject::connect(bandSelect, &QState::exited, [view] {
    qDebug() << "Exit bandSelect";
    view->setDragMode(QGraphicsView::NoDrag);
  });

  auto* pressAlt{new QKeyEventTransition(view, QEvent::KeyPress, Qt::Key_Alt)};
  pressAlt->setObjectName("pressAlt");
  pressAlt->setTargetState(dragPan);
  ready->addTransition(pressAlt);

  auto* releaseAlt{new QKeyEventTransition(view, QEvent::KeyRelease, Qt::Key_Alt)};
  releaseAlt->setObjectName("releaseAlt");
  releaseAlt->setTargetState(ready);
  dragPan->addTransition(releaseAlt);

  auto* pressShift{new QKeyEventTransition(view, QEvent::KeyPress, Qt::Key_Shift)};
  pressShift->setObjectName("pressShift");
  pressShift->setTargetState(bandSelect);
  ready->addTransition(pressShift);

  auto* releaseShift{new QKeyEventTransition(view, QEvent::KeyRelease, Qt::Key_Shift)};
  releaseShift->setObjectName("releaseShift");
  releaseShift->setTargetState(ready);
  bandSelect->addTransition(releaseShift);

  qsm->addState(initialState);
  qsm->addState(ready);
  qsm->addState(dragPan);
  qsm->addState(bandSelect);

  qsm->setInitialState(initialState);

  qsm->start();

  return qsm;
}