#include <iostream>

using namespace std;

#include "../ball.h"
#include "../inkballscene.h"
#include <QtTest/QtTest>


class BallTest : public QObject
{
    Q_OBJECT
public:
    BallTest();

private slots:
    void testIntersectsSegment1();
    void testIntersectsSegment2();
    void testIntersectsSegment3();
    void testIntersectsSegment4();
    void testIntersectsSegment5();
    void testIntersectsSegment6();
    void testIntersectsSegment7();
    void testIntersectsSegment8();
    void testPointCollision();
    void testSegmentCollision();
    void testSegmentCollision2();
    void testSegmentCollision3();
    void testSegmentCollision4();
    void testSegmentCollision5();
};


BallTest::BallTest() {}


void BallTest::testIntersectsSegment1()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), 0, 1);
    QLineF segment(QPointF(1, 1), QPointF(1, -1));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.intersectsSegment(segment, dist, angle));
    QVERIFY(dist == 1);
    QVERIFY(angle == M_PI);
}

void BallTest::testIntersectsSegment2()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), 0, 1);
    QLineF segment(QPointF(0, 1), QPointF(0, -1));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.intersectsSegment(segment, dist, angle));
    QVERIFY(dist == 0);
    QVERIFY(angle == M_PI);
}

void BallTest::testIntersectsSegment3()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI, 1);
    QLineF segment(QPointF(0, 1), QPointF(0, -1));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.intersectsSegment(segment, dist, angle));
    QVERIFY(dist == 0);
    QCOMPARE(angle, 0);
}

void BallTest::testIntersectsSegment4()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/2, 1);
    QLineF segment(QPointF(-1, 1), QPointF(1, 1));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.intersectsSegment(segment, dist, angle));
    QCOMPARE(dist, 1);
    QCOMPARE(angle, 3*M_PI/2);
}

void BallTest::testIntersectsSegment5()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), 3*M_PI/2, 1);
    QLineF segment(QPointF(-1, -1), QPointF(1, -1));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.intersectsSegment(segment, dist, angle));
    QCOMPARE(dist, 1);
    QCOMPARE(angle, M_PI/2);
}

void BallTest::testIntersectsSegment6()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/2, 8);
    ball.setPos(400, 288);
    QLineF segment(QPointF(400, 745), QPointF(440, 745));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.intersectsSegment(segment, dist, angle));
    QCOMPARE(round(dist), 457);
    QCOMPARE(angle, 3*M_PI/2);
}

void BallTest::testIntersectsSegment7()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/4, 8);
    QLineF segment(QPointF(10, 5), QPointF(10, -5));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(!ball.intersectsSegment(segment, dist, angle));
}

void BallTest::testIntersectsSegment8()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/4, 8);
    QLineF segment(QPointF(10, 10), QPointF(10, -10));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.intersectsSegment(segment, dist, angle));
    QCOMPARE(round(dist), 14);
    QCOMPARE(angle, 3*M_PI/4);
}

void BallTest::testPointCollision()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/4, 8);
    QPointF point(100, 100);
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.doesCollide(point, dist, angle));
    QCOMPARE(round(dist), 14);
    QCOMPARE(angle, 5*M_PI/4);
}

void BallTest::testSegmentCollision()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), 0, 1);
    QLineF segment(QPointF(15, 1), QPointF(15, -1));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.doesCollide(segment, dist, angle));
    QCOMPARE(dist, 0);
    QCOMPARE(angle, M_PI);
}

void BallTest::testSegmentCollision2()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI, 1);
    QLineF segment(QPointF(15, 1), QPointF(15, -1));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(!ball.doesCollide(segment, dist, angle));
}

void BallTest::testSegmentCollision3()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/2, 1);
    QLineF segment(QPointF(-1, 15), QPointF(1, 15));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.doesCollide(segment, dist, angle));
    QCOMPARE(dist, 0);
    QCOMPARE(angle, 3*M_PI/2);
}

void BallTest::testSegmentCollision4()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/2, 1);
    QLineF segment(QPointF(-1, 30), QPointF(1, 30));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.doesCollide(segment, dist, angle));
    QCOMPARE(round(dist), 15);
    QCOMPARE(angle, 3*M_PI/2);
}

void BallTest::testSegmentCollision5()
{
    InkBallScene inkBallScene;
    Ball ball(&inkBallScene, QColor(255, 255, 255), M_PI/2, 8);
    ball.setPos(400, 288);
    QLineF segment(QPointF(400, 745), QPointF(440, 745));
    qreal dist = 1e9;
    qreal angle = 0;
    QVERIFY(ball.doesCollide(segment, dist, angle));
    QCOMPARE(round(dist), 442);
    QCOMPARE(angle, 3*M_PI/2);
}


QTEST_MAIN(BallTest)
#include "balltest.moc"
