#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H
#include "blocks/integrator.h"

class Differentiator
{
    //the differentiator is implemented in the same way by which Matlab implement
    //the continuous differentiator with dynamic equation (D(s)=s*N/(N+s))
public:
    Differentiator(double n);// The constructor of the differentiator
    ~Differentiator();//this function is the destructor of the differentiator
    // This function update the value of the differentiator using rectangular differentiator method
    double update(double input, double dt);
    // this function used to set the coefficient (N)
    void setN(double value);
    // This function to get the current value of the differentiator
    double getValue() const;
    //this function used to set the integrator value that is used in the differentiator (and reset the output to zero)
    void setValue(double value);
private:
    double N; // this private variable is used to implement the differentiator with filter (as in matlab)
    double value=0; // this variable is used to save the output of the differentiator
    Integrator *I; // this integrator is used to implement the differentiator with filter (as in matlab)
};

#endif // DIFFERENTIATOR_H
