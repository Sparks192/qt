/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qtest.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

//TESTED_FILES=

class tst_QGraphicsItem : public QObject
{
    Q_OBJECT

public:
    tst_QGraphicsItem();
    virtual ~tst_QGraphicsItem();

public slots:
    void init();
    void cleanup();

private slots:
    void setParentItem();
    void setParentItem_deep();
    void setParentItem_deep_reversed();
    void deleteItemWithManyChildren();
    void setPos_data();
    void setPos();
    void setTransform_data();
    void setTransform();
    void rotate();
    void scale();
    void shear();
    void translate();
    void setRotation();
};

tst_QGraphicsItem::tst_QGraphicsItem()
{
}

tst_QGraphicsItem::~tst_QGraphicsItem()
{
}

void tst_QGraphicsItem::init()
{
}

void tst_QGraphicsItem::cleanup()
{
}

void tst_QGraphicsItem::setParentItem()
{
    QBENCHMARK {
        QGraphicsRectItem rect;
        QGraphicsRectItem *childRect = new QGraphicsRectItem;
        childRect->setParentItem(&rect);
    }
}

void tst_QGraphicsItem::setParentItem_deep()
{
    QBENCHMARK {
        QGraphicsRectItem rect;
        QGraphicsRectItem *lastRect = &rect;
        for (int i = 0; i < 10; ++i) {
            QGraphicsRectItem *childRect = new QGraphicsRectItem;
            childRect->setParentItem(lastRect);
            lastRect = childRect;
        }
        QGraphicsItem *first = rect.children().first();
        first->setParentItem(0);
    }
}

void tst_QGraphicsItem::setParentItem_deep_reversed()
{
    QBENCHMARK {
        QGraphicsRectItem *lastRect = new QGraphicsRectItem;
        for (int i = 0; i < 100; ++i) {
            QGraphicsRectItem *parentRect = new QGraphicsRectItem;
            lastRect->setParentItem(parentRect);
            lastRect = parentRect;
        }
        delete lastRect;
    }
}

void tst_QGraphicsItem::deleteItemWithManyChildren()
{
    QBENCHMARK {
        QGraphicsRectItem *rect = new QGraphicsRectItem;
        for (int i = 0; i < 1000; ++i)
            new QGraphicsRectItem(rect);
        delete rect;
    }
}

void tst_QGraphicsItem::setPos_data()
{
    QTest::addColumn<QPointF>("pos");

    QTest::newRow("0, 0") << QPointF(0, 0);
    QTest::newRow("10, 10") << QPointF(10, 10);
    QTest::newRow("-10, -10") << QPointF(-10, -10);
}

void tst_QGraphicsItem::setPos()
{
    QFETCH(QPointF, pos);

    QGraphicsScene scene;
    QGraphicsRectItem *rect = scene.addRect(QRectF(0, 0, 100, 100));

    QBENCHMARK {
        rect->setPos(10, 10);
        rect->transform(); // prevent lazy optimizing
    }
}

void tst_QGraphicsItem::setTransform_data()
{
    QTest::addColumn<QTransform>("transform");

    QTest::newRow("id") << QTransform();
    QTest::newRow("rotate 45z") << QTransform().rotate(45);
    QTest::newRow("scale 2x2") << QTransform().scale(2, 2);
    QTest::newRow("translate 100, 100") << QTransform().translate(100, 100);
    QTest::newRow("rotate 45x 45y 45z") << QTransform().rotate(45, Qt::XAxis)
        .rotate(45, Qt::YAxis).rotate(45, Qt::ZAxis);
}

void tst_QGraphicsItem::setTransform()
{
    QFETCH(QTransform, transform);

    QGraphicsScene scene;
    QGraphicsRectItem *item = scene.addRect(QRectF(0, 0, 100, 100));

    QBENCHMARK {
        item->setTransform(transform);
        item->transform(); // prevent lazy optimizing
    }
}

void tst_QGraphicsItem::rotate()
{
    QGraphicsScene scene;
    QGraphicsItem *item = scene.addRect(QRectF(0, 0, 100, 100));

    QBENCHMARK {
        item->rotate(45);
        item->transform(); // prevent lazy optimizing
    }
}

void tst_QGraphicsItem::scale()
{
    QGraphicsScene scene;
    QGraphicsItem *item = scene.addRect(QRectF(0, 0, 100, 100));

    QBENCHMARK {
        item->scale(2, 2);
        item->transform(); // prevent lazy optimizing
    }
}

void tst_QGraphicsItem::shear()
{
    QGraphicsScene scene;
    QGraphicsItem *item = scene.addRect(QRectF(0, 0, 100, 100));

    QBENCHMARK {
        item->shear(1.5, 1.5);
        item->transform(); // prevent lazy optimizing
    }
}

void tst_QGraphicsItem::translate()
{
    QGraphicsScene scene;
    QGraphicsItem *item = scene.addRect(QRectF(0, 0, 100, 100));

    QBENCHMARK {
        item->translate(100, 100);
        item->transform(); // prevent lazy optimizing
    }
}

void tst_QGraphicsItem::setRotation()
{
    QGraphicsScene scene;
    QGraphicsItem *item = scene.addRect(QRectF(0, 0, 100, 100));

    QBENCHMARK {
        item->setRotation(45);
        item->transform(); // prevent lazy optimizing
    }
}

QTEST_MAIN(tst_QGraphicsItem)
#include "tst_qgraphicsitem.moc"
