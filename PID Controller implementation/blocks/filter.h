#ifndef FILTER_H
#define FILTER_H
#include "blocks/integrator.h"

class Filter
{
    //the filter, that is used here, is a second order filter of the following dynamic
    // F(s)=wn^2/(s^2+2*xi*wn*s+wn^2)
public:
    // this is the constructor of the filter
    Filter(double Wn,double Xi);
    //the destructor of the filter
    ~Filter();
    //this function is used to update the value of the filter
    double update(double value, double dt);
    //this function is used to set the coefficient (wn) of the filter
    void setWn(double value);
    //this function is used to set the coefficient (xi) of the filter
    void setXi(double value);
    //this function is used to get the output of the filter
    double getValue() const;
    //this function is used to set the output of the filter.
    void setValue(double v1,double v2);

private:
    double wn; //the coefficient (wn) of the filter
    double xi; //the coefficient (xi) of the filter
    double value=0; //this variable is used as the output of the filter.
    Integrator *I1; //this is the first integrator for the filter
    Integrator *I2; // this is the second integrator. it is output is the filter output.
};

#endif // FILTER_H
