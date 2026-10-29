#pragma once

#include "QuiltView.h"

#include <QPointer>
#include <QStateMachine>

class QKeyEventTransition;

class ViewStateMachine
{
public:
    explicit ViewStateMachine(QuiltView* quiltView);

    ~ViewStateMachine() = default;

private:
    QPointer<QuiltView> view_;

    QStateMachine machine_;

    QState* initialState_;
    QState* dragPan_;
    QState* bandSelect_;

    QKeyEventTransition* pressAlt_;
    QKeyEventTransition* releaseAlt_;

    QKeyEventTransition* pressShift_;
    QKeyEventTransition* releaseShift_;
};
