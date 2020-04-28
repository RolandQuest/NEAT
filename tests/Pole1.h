#ifndef POLE1_H
#define POLE1_H

#include <random>

#include "net/Network.h"

class Pole1
{

public:

    static double Evaluate(std::mt19937& rng, neat::Network* net);

private:

    static void Initialize(std::mt19937& rng);
    static void AdjustCart(int action);
    static bool IsStable();

    static double x;
    static double x_Dot;
    static double theta;
    static double theta_Dot;

    static const double GRAVITY;
    static const double MASSCART;
    static const double MASSPOLE;
    static const double TOTAL_MASS;
    static const double LENGTH;     /* actually half the pole's length */
    static const double POLEMASS_LENGTH;
    static const double FORCE_MAG;
    static const double TAU;   /* seconds between state updates */
    static const double FOURTHIRDS;
    static const double twelve_degrees;

};

#endif