//
// Created by explore on 2021/8/31.
//

#include "mylabel.h"
#include <QPen>
#include<QPainter>

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{
    this->lineStartPoint = QPoint(0,0);
    this->lineEndPoint = QPoint(0,0);
    this->lineColor = QColor(Qt::white);
    this->lineSize = 3;
}

//绘制线条
void MyLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);//必须有，才能让背景图片显示出来
    QPainter painter(this);
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(lineSize);
    painter.setPen(pen);
    painter.drawLine(lineStartPoint,lineEndPoint);
}

//鼠标按下
void MyLabel::mousePressEvent(QMouseEvent *e)
{
    Is_finish = false;
    lineStartPoint = e->pos();
    lineEndPoint = e->pos();
    //在图片上绘制
    isPressed = true;
}

//鼠标移动
void MyLabel::mouseMoveEvent(QMouseEvent *e)
{
    if(isPressed)
    {
        lineEndPoint=e->pos();
        update();
    }
}

//鼠标抬起
void MyLabel::mouseReleaseEvent(QMouseEvent *e)
{
    Is_finish = true;
    isPressed=false;
    update();
}

void MyLabel::setLineColor(const QColor lineColor)
{
    this->lineColor = lineColor;
}

void MyLabel::setLineSize(const int lineSize)
{
    this->lineSize = lineSize;
}

QPoint MyLabel::getStartPoint()
{
    return lineStartPoint;
}

QPoint MyLabel::getEndPoint()
{
    return lineEndPoint;
}

void MyLabel::clear()
{
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
    update();
}