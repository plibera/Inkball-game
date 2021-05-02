#ifndef INKBALLVIEW_H
#define INKBALLVIEW_H

#include <QGraphicsView>
#include <QTimer>
#include "inkballscene.h"

class InkBallView : public QGraphicsView
{
    QTimer timer;
public:
    InkBallView(InkBallScene* inkBallScene);
};

#endif // INKBALLVIEW_H
