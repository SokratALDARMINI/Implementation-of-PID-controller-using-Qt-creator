#include "differentiator.h"

Differentiator::Differentiator(double n)
{// the value of coefficient (N) is set as needed when the differentiator is created the integrator (I) is created with inital output equal zero
N=n; I=new Integrator(0); }

Differentiator::~Differentiator()
{   //the integrator (I) is deleted
        delete I; }

double Differentiator::update(double input, double dt)
{   //update with integrator value with (input-integrator_output)*N
    //then the integrator input is used as the output of the differentiator
    value=(input-I->getValue())*N;
    I->update(value,dt);
    return value; }

void Differentiator::setValue(double V)
{    //the integrator output is set to V and the differentiator output is set to zero
    value = 0; I->setValue(V);}

double Differentiator::getValue() const
{    //return the output of the differentiator
    return value;}

void Differentiator::setN(double value)
{   // set the coefficient (N)
    N = value;}
