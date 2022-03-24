#include "pid_controller.h"
#include <QDebug>

PID_controller::PID_controller(QObject *parent) : QObject(parent)
{
    // a new file is created with the name (houer_minute_second) of creation
    m_file =new QFile(QDateTime::currentDateTime().toString("hh_mm_ss"));
    if(!m_file->open(QIODevice::WriteOnly))
    {
        // if the creation of the file is failed, in console window will appear "Failed"
        qDebug()<<"Failed";
    }
    // create the varible of type pointer on QTextStream varialbe and connect it with file (m_file)
    m_stream=new QTextStream(m_file);
    // inialization of the integrator and differentiator and the filter
    I=new Integrator(0);
    D=new Differentiator(50);
    F1=new Filter(10,0.7);
}

PID_controller::~PID_controller()
{
    // when the controller is deleted the pointers that have been created in the constucter are deleted.
        m_file->close();
        delete m_file;
        delete m_stream;
        delete I;
        delete D;
        qDebug() << qSqrt(averag_error/count); // show the error value of with the equation: E_final=sqrt(sum_for_all_samples((rerference-ouyput)^2)/number_of_samples)
}




void PID_controller::getMessage(QByteArray bytearray)
{
    //the varialbe second is used to calculate the sampling time
    double seconds = 0;

    if (m_lastMeasure.isNull()) {
        m_lastMeasure2= QDateTime::currentDateTime();// we save the first time, at which the controller recieve a message
    } else {
        currentDateTime = QDateTime::currentDateTime();

        seconds = m_lastMeasure.msecsTo(currentDateTime) / 1000.0;//time from the previous to the current time.
    }

    m_lastMeasure = QDateTime::currentDateTime();//save the current time in m_lastMeasure to become previous time for the next sample


    // Here we check the correctance of the recieved message, using the check byte using the fact:
    // for the correct package the sum for all the bits must equal 255.
    quint8 variable=0;
    for (int i=0;i<11;i++)
    {
       variable+= *((quint8*)bytearray.data()+i);
    }
// the message has the following form: two unchanging bytes represent define the message + 4 bytes represent the output + 4 bytes represent the reference + one check byte.
float data1,data2;
memcpy(&data1,bytearray.data()+2,4); // copy the bytes that represent the output in data1 (a varable of type float).
memcpy(&data2,bytearray.data()+6,4); // copy the bytes that represent the reference in data2 (a varable of type float).
if(variable!=255)
{
    //if the message is not correct, we ignore the recived message and use the previous correct values.
    data1=previous_data1;
    data2=previous_data2;
}
else
{
   //if the message is correct, we update the previous recived correct values.
    previous_data1=data1;
    previous_data2=data2;
}
compute(data1,seconds,data2); // start the function to compute the command signal

}

void PID_controller::compute(double value, double seconds, double referenceSignal)
{
    // /////////////////////////// THIS PART IS USED TO CONTROL THE SYSTEM:
    // this variable is to calcualte the time difference from the program start to the current time
    double t=m_lastMeasure2.msecsTo(currentDateTime)/ 1000.0;
    // referenceSignal is the required reference
    // update the value of the accomulative error and the contor of the sample
    error=referenceSignal-value;
    averag_error+=error*error;
    count++;
    // recalculate the error using the filtered output to use it in the controller
    error=referenceSignal-F1->update(value,seconds);
    error=8*error+4.21*I->update(error,seconds)+1.3*D->update(error,seconds); //PID parameters: Kp=8,Ki=4.21,Kd=1.3
    // Satruration
    if(error>200)
        error=200;
    else if(error<-200)
        error=-200;
    emit computed(error);
    *m_stream<<referenceSignal<<" "<<value<<' '<<error<<"\n";

    // ///////////////////////////// THIS PART IS USED FOR THE IDENTIFICATION PORPUSES WITH MATLAB PROGRAM:
    // Please comment the preveous part of this function and uncomment the following part for identification porpuses.
    // Identfication is done using least square method, considering the following linear regression model: dd_y+a1*d_y+a0*y=b0*u
    // Then filtering the sides of the equation with a second order filter to get rid of the derivative operation.

//    referenceSignal=25+25*qSin((m_lastMeasure2.msecsTo(currentDateTime)/ 1000.0)*(m_lastMeasure2.msecsTo(currentDateTime) / 1000.0)*0.05);
//    emit computed(referenceSignal);
//    emit new_ref( referenceSignal);
//    *m_stream<<referenceSignal<<" "<<value<<' '<<referenceSignal<<"\n";

}

