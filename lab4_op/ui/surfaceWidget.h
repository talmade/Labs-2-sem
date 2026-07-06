#ifndef SURFACEWIDGET_H
#define SURFACEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "../logic/appContext.h"

class SurfaceWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit SurfaceWidget(QWidget* parent = nullptr);
public:
    void render(AppContext* context);
private:
    QGraphicsScene* scene;
    void drawEdges(AppContext* context);
    void projectPoint(const Point3D* point, double* screenX, double* screenY);
};

#endif // SURFACEWIDGET_H
