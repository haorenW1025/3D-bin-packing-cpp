#ifndef SPHERE_H
#define SPHERE_H

class Sphere
{
public:
    Sphere(double r):radius(r){}
    ~Sphere(){};
    Sphere(const Sphere& s):radius(s.radius){}
    float get_r() {return radius; }
    float get_x() {return x; }
    float get_y() {return y; }
    float get_z() {return z; }
    void set_x(float a) {x=a;}
    void set_y(float b) {y=b;}
    void set_z(float c) {z=c;}
private:
    double radius;
    float x;
    float y;
    float z;
};

#endif /* SPHERE_H */
