#include "filter.h"

Filter::Filter(double Wn,double Xi)
{ //the value of the coefficients (xi,wn) are seted and the integrators are created
wn=Wn; xi=Xi; I1= new Integrator(0); I2= new Integrator(0); }

Filter::~Filter()
{//the integrators are deleted
    delete I1; delete I2;}

double Filter::update(double input, double dt)
{   // First we update the output of the first integrator when we recieve a new input
    // then we update the output of the second integrator
    // the output of the second integrator is the filter output (value)
    I1->update(wn*wn*input-wn*wn*I2->getValue()-2*xi*wn*I1->getValue(),dt);
    value=I2->update(I1->getValue(),dt);
    return value;}

void Filter::setWn(double value)
{   // it is used to set coefficient (wn)
    wn = value; }

void Filter::setXi(double value)
{   // it is used to set coefficient (xi)
    xi = value; }

double Filter::getValue() const
{   // it is used to get the value of the filter's output
    return value; }

void Filter::setValue(double v1,double v2)
{   // it is used to reset the filter output (while making the first ingtegrator ouput equal zero)
    value = v2; I2->setValue(v2);   I1->setValue(v1); }
