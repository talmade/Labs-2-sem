#include "surfaceWidget.h"

#define PROJECTION_SCALE 10.0
#define ISOMETRIC_DEPTH_FACTOR 0.5

SurfaceWidget::SurfaceWidget(QWidget *parent)
    : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
}

void SurfaceWidget::projectPoint(const Point3D* point, double* screenX, double* screenY) {
    double centerX = width() / 2.0;
    double centerY = height() / 2.0;
    *screenX = centerX + (point->x - point->z) * PROJECTION_SCALE;
    *screenY = centerY - point->y * PROJECTION_SCALE + (point->x + point->z) * PROJECTION_SCALE * ISOMETRIC_DEPTH_FACTOR;
}

void SurfaceWidget::drawEdges(AppContext* context) {
    int rows = context->scene.rows;
    int cols = context->scene.columns;
    Point3D* points = context->scene.transformedPoints;
    QPen pen(Qt::white);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double x1, y1, x2, y2;
            projectPoint(&points[i * cols + j], &x1, &y1);

            if (j + 1 < cols) {
                projectPoint(&points[i * cols + j + 1], &x2, &y2);
                scene->addLine(x1, y1, x2, y2, pen);
            }

            if (i + 1 < rows) {
                projectPoint(&points[(i + 1) * cols + j], &x2, &y2);
                scene->addLine(x1, y1, x2, y2, pen);
            }
        }
    }
}

void SurfaceWidget::render(AppContext* context) {
    scene->clear();
    if (context->scene.transformedPoints != NULL)
        drawEdges(context);
}
