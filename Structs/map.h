#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include "PCKEngine/PCKEngine.h"
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include <QTextItem>

struct GameMapInfo
{
public:
    QString MapName;
    QString MapPath;
    QList<PCKFileEntry> MapFragments;
};


class CliqueLabel : public QLabel {
    Q_OBJECT

public:
    explicit CliqueLabel(QWidget *parent = nullptr) : QLabel(parent) {
        // Permitir eventos de clique com o mouse
        setMouseTracking(true);
    }

protected:

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            // Obter a posição do clique
            QPoint pos = event->pos();

            // Desenhar um ponto na posição do clique
            QImage image(pixmap()->size(), QImage::Format_ARGB32_Premultiplied);
            QPainter painter(&image);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.drawPixmap(0, 0, *pixmap());
            painter.setPen(QPen(Qt::red)); // Definir a cor do ponto
            painter.drawText(pos.x() - 3, pos.y() + 3, "•");

            // Atualizar a imagem do QLabel
            setPixmap(QPixmap::fromImage(image));

            // Chamar a implementação base (opcional, dependendo do comportamento desejado)
            QLabel::mousePressEvent(event);
        }
    }
};

#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QCursor>

class EventFilter : public QObject {
protected:
    bool shiftPressed = false;
    bool directionDetermined = false;
    bool moveHorizontal = false;
    bool moveVertical = false; // Correção: declaração adequada da variável
    QPoint lastMousePos;

    bool eventFilter(QObject *obj, QEvent *event) override {
        switch (event->type()) {
        case QEvent::KeyPress: {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Shift) {
                shiftPressed = true;
                directionDetermined = false;
                moveHorizontal = false;
                moveVertical = false; // Resetando a direção do movimento
                lastMousePos = QCursor::pos(); // Armazena a posição inicial do cursor
                return true;
            }
            break;
        }
        case QEvent::KeyRelease: {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Shift) {
                shiftPressed = false;
                return true;
            }
            break;
        }
        case QEvent::MouseMove: {
            if (shiftPressed) {
                if (!directionDetermined) {
                    // Determina a direção com base no primeiro movimento significativo
                    QPoint currentPos = QCursor::pos();
                    QPoint moveDirection = currentPos - lastMousePos;
                    if (abs(moveDirection.x()) > abs(moveDirection.y())) {
                        moveHorizontal = true;
                        moveVertical = false;
                    } else {
                        moveVertical = true;
                        moveHorizontal = false;
                    }
                    directionDetermined = true;
                }

                QPoint newPos = QCursor::pos();
                if (moveHorizontal) {
                    newPos.setY(lastMousePos.y());
                } else if (moveVertical) {
                    newPos.setX(lastMousePos.x());
                }

                QCursor::setPos(newPos); // Move o cursor para a nova posição
                return true; // Indica que o evento foi tratado
            }
            break;
        }
        default:
            break;
        }
        return QObject::eventFilter(obj, event);
    }
};

#endif // MAP_H
