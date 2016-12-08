#include <QCoreApplication>
/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore>
#include <stdio.h>

class PingEvent : public QEvent
{
public:
    PingEvent() : QEvent(QEvent::Type(QEvent::User+2))
        {}
};

class PongEvent : public QEvent
{
public:
    PongEvent() : QEvent(QEvent::Type(QEvent::User+3))
        {}
};

class Pinger : public QState
{
public:
    Pinger(QState *parent)
        : QState(parent) {}

protected:
    virtual void onEntry(QEvent *)
    {
        machine()->postEvent(new PingEvent());
        fprintf(stdout, "ping????\n");
    }
};

class PongTransition : public QAbstractTransition
{
public:
    PongTransition() {}

protected:
    virtual bool eventTest(QEvent *e) {
        return (e->type() == QEvent::User+3);
    }
    virtual void onTransition(QEvent *)
    {
        machine()->postDelayedEvent(new PingEvent(), 500);
        fprintf(stdout, "ping?\n");
    }
};

class PingTransition : public QAbstractTransition
{
public:
    PingTransition() {}

protected:
    virtual bool eventTest(QEvent *e) {
        if (e->type() != QEvent::Type(QEvent::User+2)) // StringEvent
            return false;
        return true;
    }
    virtual void onTransition(QEvent *)
    {
        machine()->postDelayedEvent(new PongEvent(), 500);
        fprintf(stdout, "pong!\n");
    }
};

class StringEvent : public QEvent
{
public:
    StringEvent(const QString &val)
    : QEvent(QEvent::Type(QEvent::User+4)),
      value(val) {}
public:
    QString value;
};

class MyPinger : public QState
{
public:
    MyPinger()
        : QState() {}

protected:
    virtual void onEntry(QEvent *)
    {
        machine()->postEvent(new StringEvent("hello"));
        fprintf(stdout, "hi????\n");
    }
};

class StringTransition : public QAbstractTransition
{
public:
    StringTransition(const QString &value)
        : m_value(value) {}

protected:
    virtual bool eventTest(QEvent *e)
    {
        if (e->type() != QEvent::Type(QEvent::User+4)) // StringEvent
            return false;
        StringEvent *se = static_cast<StringEvent*>(e);
        return (m_value == se->value);
    }

    virtual void onTransition(QEvent *) {}

private:
    QString m_value;
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QStateMachine machine1;
    QState *group = new QState(QState::ParallelStates);
    group->setObjectName("group");

    Pinger *pinger = new Pinger(group);
    pinger->setObjectName("pinger");
    pinger->addTransition(new PongTransition());

    QState *ponger = new QState(group);
    ponger->setObjectName("ponger");
    ponger->addTransition(new PingTransition());

    machine1.addState(group);
    machine1.setInitialState(group);
    machine1.start();

       QStateMachine machine;
       MyPinger *s1 = new MyPinger();
       QState *s2 = new QState();
       QFinalState *done = new QFinalState();

       StringTransition *t1 = new StringTransition("Hello");
       t1->setTargetState(s2);
       s1->addTransition(t1);
       StringTransition *t2 = new StringTransition("world");
       t2->setTargetState(done);
       s2->addTransition(t2);

       machine.addState(s1);
       machine.addState(s2);
       machine.addState(done);
       machine.setInitialState(s1);

       machine.start();

//       s1->machine()->postEvent(new StringEvent("Hello"));

      machine.postEvent(new StringEvent("Hello"));
       machine.postEvent(new StringEvent("world"));


    return app.exec();
}
