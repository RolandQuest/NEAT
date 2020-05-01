#include "Pole1.h"

#include <map>
#include <math.h>

double Pole1::x = 0.0;
double Pole1::x_Dot = 0.0;
double Pole1::theta = 0.0;
double Pole1::theta_Dot = 0.0;

const double Pole1::GRAVITY = 9.8;
const double Pole1::MASSCART = 1.0;
const double Pole1::MASSPOLE = 0.1;
const double Pole1::TOTAL_MASS = (MASSPOLE + MASSCART);
const double Pole1::LENGTH = 0.5;     /* actually half the pole's length */
const double Pole1::POLEMASS_LENGTH = (MASSPOLE * LENGTH);
const double Pole1::FORCE_MAG = 10.0;
const double Pole1::TAU = 0.02;   /* seconds between state updates */
const double Pole1::FOURTHIRDS = 1.3333333333333;
const double Pole1::twelve_degrees = 0.2094384;

double Pole1::Evaluate(std::mt19937& rng, neat::Network* net) {

    Initialize(rng);

    int maxSteps = 100000;
    int steps = 0;

    std::map<int, double> inputArray =
    {
        { 1, 0.0 },
        { 2, 0.0 },
        { 3, 0.0 },
        { 4, 0.0 },
    };

    std::map<int, double> outputArray =
    {
        { 5, 0.0 },
        { 6, 0.0 }
    };

    //if (false)
    {
        inputArray[1] = (x + 2.4) / 4.8; ;
        inputArray[2] = (x_Dot + .75) / 1.5;
        inputArray[3] = (theta + twelve_degrees) / .41;
        inputArray[4] = (theta_Dot + 1.0) / 2.0;
        net->Initialize(inputArray, outputArray);
    }

    while (++steps < maxSteps)
    {
        inputArray[1] = (x + 2.4) / 4.8;
        inputArray[2] = (x_Dot + .75) / 1.5;
        inputArray[3] = (theta + twelve_degrees) / .41;
        inputArray[4] = (theta_Dot + 1.0) / 2.0;

        net->SetInput(inputArray);
        net->Activate();
        net->GetOutput(outputArray);

        if (outputArray[5] > outputArray[6]) {
            AdjustCart(0);
        }
        else {
            AdjustCart(1);
        }

        if (!IsStable())
        {
            break;
        }

    }

    return steps;
}

void Pole1::Initialize(std::mt19937& rng) {

    std::uniform_int_distribution<int> temp(1, 24000);

    x = (temp(rng) % 4800) / 1000.0 - 2.4;
    x_Dot = (temp(rng) % 2000) / 1000.0 - 1;
    theta = (temp(rng) % 400) / 1000.0 - .2;
    theta_Dot = (temp(rng) % 3000) / 1000.0 - 1.5;
}

bool Pole1::IsStable() {
    return !(x < -2.4 || x > 2.4 || theta < -twelve_degrees || theta > twelve_degrees);
}

void Pole1::AdjustCart(int action) {

    double xacc, thetaacc, force, costheta, sintheta, temp;

    force = (action > 0) ? FORCE_MAG : -FORCE_MAG;
    costheta = cos(theta);
    sintheta = sin(theta);

    temp = (force + POLEMASS_LENGTH * theta_Dot * theta_Dot * sintheta)
        / TOTAL_MASS;

    thetaacc = (GRAVITY * sintheta - costheta * temp)
        / (LENGTH * (FOURTHIRDS - MASSPOLE * costheta * costheta
            / TOTAL_MASS));

    xacc = temp - POLEMASS_LENGTH * thetaacc * costheta / TOTAL_MASS;

    /*** Update the four state variables, using Euler's method. ***/

    x += TAU * x_Dot;
    x_Dot += TAU * xacc;
    theta += TAU * theta_Dot;
    theta_Dot += TAU * thetaacc;
}

