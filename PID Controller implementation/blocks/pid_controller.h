#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QFile>
#include "blocks/integrator.h"
#include "blocks/differentiator.h"
#include "blocks/filter.h"

class PID_controller : public QObject
{
    Q_OBJECT
public:
    explicit PID_controller(QObject *parent = nullptr);//the constrctor of PID controller
    ~PID_controller();//the destructor of PID controller

signals:
    void computed(float value); //this signal is emitted when the output of the controller is calculated
    void new_ref(float value); //this signal is emitted to adjust the reference signal of the system when needed
public slots:
   void getMessage(QByteArray bytearray); //this slot is used to handle the recieved message from the control object.
   void compute(double value, double seconds, double referenceSignal); //this slot is used to calculate the output of the filter

private:
    QDateTime m_lastMeasure; // this variable is from type QDateTime and used to save the time of the previous sample.
    QDateTime m_lastMeasure2; // this variable is from type QDateTime and used to save the start time of the process.
    QDateTime currentDateTime; // this variable is from type QDateTime and used to save the current sample time.
    QFile* m_file; // this variable is a pointer on a varible of the type QFile, which used to handle a file.
    QTextStream* m_stream; // this variable is a pointer on a varible of the type QTextStream, which used to read and write on the file.
    float previous_data1=0;// this variable is used to save the previos (correct) recieved output of the control opject.
    float previous_data2=0;// this variable is used to save the previos (correct) recieved reference Signal of the control opject.

    Integrator* I;//integrator is used in the controller
    Differentiator* D;//differentiator is used in the controller
    Filter* F1;//Filter used to filter the output signal befor injecting it in the contoller.
    double error=0;//the current value of the error
    double averag_error=0;//the accumulative squared error
    int count=0; //the number of samples

};

#endif // PID_CONTROLLER_H
