#include "graphWindow.h"
#include "../logic/arrayUtils.h"
#include "graphConstants.h"

GraphWindow::GraphWindow(QWidget *parent): QWidget(parent) {}

void GraphWindow::setMetric(const AppContext* context) {
    freeArrayDouble(valuesMetric);
    copyArray(YEARS_COUNT, context->valuesMetric, &valuesMetric);
    metrics.max = context->metrics.max;
    metrics.median = context->metrics.median;
    metrics.min = context->metrics.min;
}

void GraphWindow::paintEvent(QPaintEvent* event) {
    double padding = (metrics.max - metrics.min) * AXIS_PADDING;
    highOY = HIGH_OFFSET;
    dataHighOY = highOY + DATA_AREA_HIGH_OFFSET;
    startOY = height() - DOWN_OFFSET;
    rightOX = width() - RIGHT_OFFSET;
    startOX = LEFT_OFFSET;
    stepOX = (rightOX - startOX - DATA_AREA_HIGH_OFFSET) / YEARS_COUNT;
    axisMin = metrics.min - padding;
    axisMax = metrics.max + padding;

    QPainter painter(this);
    painter.fillRect(rect(), COLOR_WHITE);

    if (valuesMetric != NULL) {
        paintAxis(&painter);
        paintDesignation(&painter);
        paintValues(&painter);
    }
}

void GraphWindow::paintAxis(QPainter* painter) {
    QPen pen(COLOR_BLACK);
    QFont font = painter->font();
    pen.setWidth(PEN_WIDTH_NORMAL);
    painter->setPen(pen);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawLine(startOX, highOY, startOX, startOY);
    painter->drawLine(startOX, highOY, startOX - ARROW_LEN, highOY + ARROW_HALF_SPAN);
    painter->drawLine(startOX, highOY, startOX + ARROW_LEN, highOY + ARROW_HALF_SPAN);

    font.setPointSize(FONT_SIZE_AXIS);
    painter->setFont(font);
    int countDivision = AXIS_DIVISIONS;
    double stepValues = (axisMax - axisMin) / countDivision;
    for (int i = 1; i < countDivision; i++) {
        double value = axisMin + stepValues * i;
        int pixelOY = getPixelOY(value);

        painter->setPen(pen);
        painter->drawLine(startOX - TICK_LEN, pixelOY, startOX + TICK_LEN, pixelOY);
        painter->drawText(startOX - TICK_TEXT_OFFSET_X, pixelOY + TICK_TEXT_OFFSET_Y,
                          QString::number(value, 'f', ONE));
        painter->setPen(COLOR_GREY);
        painter->drawLine(startOX + TICK_LEN, pixelOY, rightOX, pixelOY);
    }

    painter->setPen(COLOR_BLACK);
    pen.setWidth(PEN_WIDTH_NORMAL);
    painter->setPen(pen);
    painter->drawLine(startOX, startOY, rightOX, startOY);
    painter->drawLine(rightOX, startOY, rightOX - ARROW_HALF_SPAN, startOY - ARROW_LEN);
    painter->drawLine(rightOX, startOY, rightOX - ARROW_HALF_SPAN, startOY + ARROW_LEN);

    font.setPointSize(FONT_SIZE_YEAR);
    painter->setFont(font);
    for (unsigned xi = 1; xi <= YEARS_COUNT; ++xi) {
        int PixelOX = getPixelOX(xi);
        painter->drawLine(PixelOX + YEAR_TICK_OFFSET, startOY - TICK_LEN,
                          PixelOX + YEAR_TICK_OFFSET, startOY + TICK_LEN);
    }

    font.setPointSize(FONT_SIZE_XY);
    painter->setFont(font);
    painter->drawText(startOX + AXIS_OY_LABEL_OFFSET, highOY + AXIS_OY_LABEL_OFFSET, "Y");
    painter->drawText(rightOX, startOY - AXIS_OX_LABEL_OFFSET, "X");
}

void GraphWindow::paintDesignation(QPainter* painter) {
    QPen pen(COLOR_RED);
    painter->setBrush(COLOR_RED);
    painter->setPen(pen);
    painter->drawRect(rightOX - RECT_OFFSET_X, highOY - RECT_OFFSET_Y_MAX,
                      RECT_WIDTH, RECT_HEIGHT);

    pen.setColor(COLOR_GREEN);
    painter->setBrush(COLOR_GREEN);
    painter->setPen(pen);
    painter->drawRect(rightOX - RECT_OFFSET_X, highOY - RECT_OFFSET_Y_MEDIAN,
                      RECT_WIDTH, RECT_HEIGHT);

    pen.setColor(COLOR_BLUE);
    painter->setBrush(COLOR_BLUE);
    painter->setPen(pen);
    painter->drawRect(rightOX - RECT_OFFSET_X, highOY - RECT_OFFSET_Y_MIN,
                      RECT_WIDTH, RECT_HEIGHT);

    pen.setColor(COLOR_BLACK);
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSize(FONT_SIZE_LABEL);
    painter->setFont(font);
    painter->drawText(rightOX - TEXT_OFFSET_X_MAX, highOY - TEXT_OFFSET_Y_MAX, "Max-");
    painter->drawText(rightOX - TEXT_OFFSET_X_MEDIAN, highOY - TEXT_OFFSET_Y_MEDIAN, "Median-");
    painter->drawText(rightOX - TEXT_OFFSET_X_MIN, highOY - TEXT_OFFSET_Y_MIN, "Min-");

    painter->drawText(rightOX - DESCRIPTION_OFFSET_X, highOY - DESCRIPTION_OFFSET_Y, "Y - metric values");
    painter->drawText(rightOX - DESCRIPTION_OFFSET_X, highOY - DESCRIPTION_OFFSET_Y_SECOND, "X - years");

    font.setPointSize(FONT_SIZE_TITLE);
    painter->setFont(font);
    painter->drawText(startOX, highOY - TITLE_OFFSET_Y, "Metrics chart");
}

void GraphWindow::paintValues(QPainter* painter) {
    QPen pen(COLOR_BLACK);
    painter->setBrush(COLOR_BLACK);
    pen.setWidth(PEN_WIDTH_THICK);
    painter->setPen(pen);

    for (unsigned xi = 1; xi < YEARS_COUNT; ++xi) {
        int startPixelOY = getPixelOY(valuesMetric[xi - 1]);
        int endPixelOY = getPixelOY(valuesMetric[xi]);
        int startPixelOX = getPixelOX(xi);
        int endPixelOX = getPixelOX(xi + 1);

        painter->drawLine(startPixelOX + YEAR_TICK_OFFSET, startPixelOY,
                          endPixelOX + YEAR_TICK_OFFSET, endPixelOY);
        painter->drawEllipse(startPixelOX + POINT_RADIUS,
                             startPixelOY - (POINT_RADIUS / TWO),
                             POINT_RADIUS, POINT_RADIUS);
        painter->drawEllipse(endPixelOX + POINT_RADIUS,
                             endPixelOY - (POINT_RADIUS / TWO),
                             POINT_RADIUS, POINT_RADIUS);
    }

    painter->setPen(COLOR_RED);
    double maxOY = getPixelOY(metrics.max);
    painter->drawLine(startOX, maxOY, rightOX, maxOY);

    painter->setPen(COLOR_GREEN);
    double medianOY = getPixelOY(metrics.median);
    painter->drawLine(startOX, medianOY, rightOX, medianOY);

    painter->setPen(COLOR_BLUE);
    double minOY = getPixelOY(metrics.min);
    painter->drawLine(startOX, minOY, rightOX, minOY);
}

int GraphWindow::getPixelOY(double value) {
    return startOY - (int) qRound((value - axisMin) / (axisMax - axisMin) * (startOY - dataHighOY));
}

int GraphWindow::getPixelOX(int value) {
    return startOX + stepOX * value;
}

void GraphWindow::clearGraph() {
    freeArrayDouble(valuesMetric);
    valuesMetric = NULL;

    metrics.max = 0;
    metrics.median = 0;
    metrics.min = 0;
    update();
}

GraphWindow::~GraphWindow() {
    freeArrayDouble(valuesMetric);
}
