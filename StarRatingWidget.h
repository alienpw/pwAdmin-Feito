#ifndef STARRATINGWIDGET_H
#define STARRATINGWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class StarRatingWidget : public QWidget {
    Q_OBJECT

public:
    StarRatingWidget(QWidget *parent = nullptr) : QWidget(parent), rating(-1), maxRating(5) {
        setMouseTracking(true);
    }

    void setRating(int newRating) {
        if (rating != newRating) {
            rating = newRating;
            emit ratingChanged(rating);
            update();
        }
    }

    int getRating() const {
        return rating;
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap starFilled(":/Icons/star-checked.png"); // Caminho para a imagem preenchida no recurso
        QPixmap starOutline(":/Icons/star-unchecked.png"); // Caminho para a imagem contornada no recurso

        for (int i = 0; i < maxRating; ++i) {
            if (i < rating) {
                // Desenha a estrela preenchida
                painter.drawPixmap(5 + i * 16, 0, 16, 16, starFilled);
            } else {
                // Desenha a estrela contornada
                painter.drawPixmap(5 + i * 16, 0, 16, 16, starOutline);
            }
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        int newRating = event->pos().x() / 10 + 1;
        if (newRating != rating && newRating <= maxRating) {
            setRating(newRating);
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        setRating(event->pos().x() / 10 + 1);
    }

signals:
    void ratingChanged(int newRating);

private:
    int rating;
    int maxRating;
};


#endif // STARRATINGWIDGET_H
