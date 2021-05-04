#pragma once
#include <vector>
#include <stdexcept>
#include <cmath>

constexpr double pi = 3.14159265359;

class Trajectory {
public:
    struct Point {
        double x;
        double y;
    };
    Trajectory() = default;
    Trajectory(const Trajectory&) = default;
    Trajectory(Trajectory&&) = default;
    Trajectory& operator=(const Trajectory&) = default;
    Trajectory& operator=(Trajectory&&) = default;

    template<typename... Args>
    Trajectory(Args&... args) : bezier_points{args...} {}

    Point getControlPoint(size_t i) {
        return bezier_points[i];
    }

    void setControlPoint(size_t i, Point value) {
        bezier_points[i] = value;
    }

    bool isDone() {
        return t >= 1.0;
    }

    virtual Point getPoint() = 0;
    virtual double getAngle() = 0;

protected:
    std::vector<Point> bezier_points;
    double t{0.0};
};

class Trajectory2D: public Trajectory {
public:
    Trajectory2D(Point p1, Point p2) : Trajectory(p1, p2) {}
    Point getPoint() override {
        Point p;

        p.x = (1-t)*(1-t)*bezier_points[0].x + t*bezier_points[1].x;
        p.y = (1-t)*(1-t)*bezier_points[0].y + t*bezier_points[1].y;

        if (t < 1.0)
            t += 0.01;
        
        return p;
    }

    double getAngle() override {
        return std::atan2(-bezier_points[0].y, -bezier_points[0].x) * 180 / pi;
    }
};

class Trajectory4D: public Trajectory {
public:
    Trajectory4D(Point p1, Point p2, Point p3, Point p4) : Trajectory(p1, p2, p3, p4) {}

    Point getPoint() override {
        Point p;

        p.x = std::pow((1-t), 3)*bezier_points[0].x + 
              3*t*std::pow((1-t), 2)*bezier_points[1].x + 
              3*(1-t)*t*t*bezier_points[2].x + t*t*t*bezier_points[3].x;
        p.y = std::pow((1-t), 3)*bezier_points[0].y + 
              3*t*std::pow((1-t), 2)*bezier_points[1].y + 
              3*(1-t)*t*t*bezier_points[2].y + t*t*t*bezier_points[3].y;
        
        if (t < 1.0)
            t += 0.01;
        
        return p;
    }

    double getAngle() override {
        double u = 3*(bezier_points[3].x*t*t - ((1-t)*(1-t)) * bezier_points[0].x + bezier_points[1].x - 4*t*bezier_points[1].x + 3*(t*t)*bezier_points[1].x + 2*t*bezier_points[2].x - 3*t*t*bezier_points[2].x);
        double v = 3*(bezier_points[3].y*t*t - ((1-t)*(1-t)) * bezier_points[0].y + bezier_points[1].y - 4*t*bezier_points[1].y + 3*(t*t)*bezier_points[1].y + 2*t*bezier_points[2].y - 3*t*t*bezier_points[2].y);
        
        // if (t < 1.0)
        //     t += 0.01;
        return std::atan2(v, u) * 180 / pi;
    }
};

