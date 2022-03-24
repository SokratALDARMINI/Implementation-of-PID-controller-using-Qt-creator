#include "integrator.h"

Integrator::Integrator(double init)
{
    //(The constructor)Here we set the value of the integrator
    //equal to the initial value from the user
    value=init;
}
double Integrator::update(double input, double dt)
{
    // we update the value of the integrator using rectanular integration method
   value=value+input*dt;
   return value;
}
double Integrator::getValue() const
{
    // return the current value of the integrator
    return value;
}
void Integrator::setValue(double v)
{
    // Changing the value of the integrator to v
    this->value = v;
}

