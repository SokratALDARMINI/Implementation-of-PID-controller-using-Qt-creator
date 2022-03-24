#ifndef INTEGRATOR_H
#define INTEGRATOR_H

class Integrator
{
public:
    // The constructor of the integrator
    Integrator(double init=0);
    // This function is used to update the value of the integrator using rectangular integeration method
    double update(double input, double dt);
    // This function is used to get the current value of the integrator
    double getValue() const;
    // Use this function to change the value of the integrator
    void setValue(double v);
private:
    // this private variable is used to save the current value of the integrator
    double value=0;
};
#endif // INTEGRATOR_H
