#pragma once

#include <string>
#include <array>
#include <map>
#include <functional>
#include <utility>
#include <cmath>
#include <iostream>

// --------------- Robot Main Class ---------------

class Robot {

    public:

        // robotType is an enum set used to run a quick check on subclass type without having to specifically compare pointers
        // Each subclass gets its own int, and will be constant once constructed, if you're adding more shapes, expand enum
        enum class robotType {
            NONE = 0,
            RECTANGLE = 1,
            CIRCLE = 2,
        };

    protected:

        double centerX;
        double centerY;
        const robotType type;
    
    public: 
            //In practice, a parent class robot shouldn't ever be constucted
            Robot(double x, double y) : centerX(x), centerY(y), type(robotType::NONE) {}

            Robot(double x, double y, robotType t) : centerX(x), centerY(y), type(t) {}

    double getCenterX() const {
        return centerX;
    }

    double getCenterY() const {
        return centerY;
    }

    robotType getType() const {
        return type;
    }
};

// ------------ CircularRobot Subclass ------------

class CircularRobot : public Robot {
    private:
        double radius;

    public: CircularRobot(double x, double y, double r) : Robot(x, y, robotType::CIRCLE), radius(r) {}

    double getRadius() const {
        return radius;
    }
};

// ---------- RectangularRobot Subclass -----------

class RectangularRobot : public Robot {
    private:
        double length;
        double width;

    public: RectangularRobot(double x, double y, double l, double w) : Robot(x, y, robotType::RECTANGLE), width(w), length(l) {}

    double getLength() const {
        return length;
    }

    double getWidth() const {
        return width;
    }
};

/* isColliding FUNCTION

   I haven't looked up an eloquent solution to this problem, so a majority of this can be disregarded if there's a neat geometrical
   solution that can work for circles, rectangles, and any other potential shapes. Assuming there isn't- this is what I have.

   isColliding will pull the robotType from a and b, and the pair of types will be ran into a map to assign
   the specific mathematical function needed for the job. The function will also quickly swap the position of the robots in the
   parameters to make sure the smallest ID is first so that future add ons don't require every potential combination be met.

*/

double getDistance(const Robot& a, const Robot& b); // This version grabs the distance between the center of two robots, rather than two generic points
double getDistance(double x1, double y1, double x2, double y2);

bool isColliding(const Robot& a, const Robot& b); // The big daddy itself

// Math functions for each unique type of collision, if you're adding more shapes, add unique collisions here.
// Unique descriptions and walkthroughs for each function lies in the solution.cpp file
bool circleOnCircle(const CircularRobot& a, const CircularRobot& b); 
bool rectangleOnRectangle(const RectangularRobot& a, const RectangularRobot& b);
bool rectangleOnCircle(const RectangularRobot& a, const CircularRobot& b);