#include "StarRatingWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFormLayout>

StarRatingWidget::StarRatingWidget(QWidget *parent)
    : QWidget(parent), m_rating(0), m_starSize(20, 20), m_maxRating(5)
{
    setMouseTracking(true); // Opcional, para atualizações de hover

    // Encontra todos os QFormLayout dentro do parentWidget
    QList<QFormLayout *> formLayouts = parent->findChildren<QFormLayout *>();

    for(QFormLayout *formLayout : formLayouts) {
        formLayout->addWidget(this);
        // Aqui você pode fazer algo com cada QFormLayout encontrado
    }
}

int StarRatingWidget::rating() const
{
    return m_rating;
}

void StarRatingWidget::setRating(int newRating)
{
    if (m_rating != newRating) {
        m_rating = newRating;
        emit ratingChanged(m_rating);
        update();
    }
}

void StarRatingWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < m_maxRating; ++i) {
        QRect starRect(i * m_starSize.width(), 0, m_starSize.width(), m_starSize.height());
        if (i < m_rating) {
            // Desenhe a estrela preenchida
            painter.drawPixmap(starRect, QPixmap(":/Icons/star_checked.png"));
        } else {
            // Desenhe a estrela vazia
            painter.drawPixmap(starRect, QPixmap(":/Icons/star_unchecked.png"));
        }
    }
}

void StarRatingWidget::mousePressEvent(QMouseEvent *event)
{
    int starWidth = sizeHint().width() / m_maxRating;
    int newRating = event->x() / starWidth + 1;
    setRating(newRating);
}

QSize StarRatingWidget::sizeHint() const
{
    return QSize(m_starSize.width() * m_maxRating, m_starSize.height());
}
