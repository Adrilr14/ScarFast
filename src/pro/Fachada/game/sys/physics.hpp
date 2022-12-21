#pragma once

class Physics_t {
private:
    double x {0.0};
    double z {0.0};
    double velx {0.0};
    double velz {0.0};
public:
    Physics_t(){};
    Physics_t(double xvalue, double zvalue, double vx, double vz) 
    : x(xvalue), z(zvalue), velx(vx), velz(vz) {};

    ~Physics_t() {};
};