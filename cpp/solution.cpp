#include "solution.hpp"


using RT = Robot::robotType;

std::map<std::pair<RT, RT>, std::function<bool(const Robot&, const Robot&)>> collisionType = {
    {{RT::RECTANGLE, RT::RECTANGLE}, // 1, 1
        [](const Robot& robotA, const Robot& robotB) {
            return rectangleOnRectangle(static_cast<const RectangularRobot&>(robotA), static_cast<const RectangularRobot&>(robotB));
        }},
    {{RT::RECTANGLE, RT::CIRCLE}, // 1, 2
        [](const Robot& robotA, const Robot& robotB) {
            return rectangleOnCircle(static_cast<const RectangularRobot&>(robotA), static_cast<const CircularRobot&>(robotB));
        }},
    {{RT::CIRCLE, RT::CIRCLE}, // 2, 2
        [](const Robot& robotA, const Robot& robotB) {
            return circleOnCircle(static_cast<const CircularRobot&>(robotA), static_cast<const CircularRobot&>(robotB));
        }},
};

double getDistance(const Robot& a, const Robot& b) {
    double distanceX = b.getCenterX() - a.getCenterX();
    double distanceY = b.getCenterY() - a.getCenterY();
    distanceX = distanceX * distanceX;
    distanceY = distanceY * distanceY;
    return sqrt(distanceX + distanceY);     
}

double getDistance(double x1, double y1, double x2, double y2) {
    double distanceX = x2 - x1;
    double distanceY = y2 - y1;
    distanceX = distanceX * distanceX;
    distanceY = distanceY * distanceY;
    return sqrt(distanceX + distanceY);
}

// Take the combined radius of two circles and compare that value to the distance between the two centers. The only way the distance
// can be less is if the circles overlap each other and therefore collide.

bool circleOnCircle(const CircularRobot& a, const CircularRobot& b) {
    double distance = getDistance(a, b);
    double combinedRadius = a.getRadius() + b.getRadius();

    if (combinedRadius > distance) {
        return true;        
    }
    else {
        return false;
    }
}

 
// First, the function checks if the center of rectangle B lies within rectangle A. If that flags true, then we know they collide.

// Otherwise, we can check if B's sides are within the bounds of Rectangle A's sides. If one vertical and horizontal side from B lie
// A, then we can also flag a collision.

bool rectangleOnRectangle(const RectangularRobot& a, const RectangularRobot& b) {

    bool xCondition = false;
    bool yCondition = false;

    double a_LEFT = a.getCenterX() - (a.getWidth() / 2);
    double a_RIGHT = a.getCenterX() + (a.getWidth() / 2);
    double BOTTOM = a.getCenterY() - (a.getLength() / 2);
    double a_TOP = a.getCenterY() + (a.getLength() / 2);

    double b_LEFT = b.getCenterX() - (b.getWidth() / 2);
    double b_RIGHT = b.getCenterX() + (b.getWidth() / 2);
    double b_BOTTOM = b.getCenterY() - (b.getLength() / 2);
    double b_TOP = b.getCenterY() + (b.getLength() / 2);
    
    if (((b.getCenterX() > a_LEFT) && (b.getCenterX() < a_RIGHT)) && ((b.getCenterY() > BOTTOM) && (b.getCenterY() < a_TOP))) {
        return true;
    } 

    if (((b_LEFT > a_LEFT) && (b_LEFT < a_RIGHT)) || ((b_RIGHT > a_LEFT) && (b_RIGHT < a_RIGHT))) {
        xCondition = true;
    }
    if (((b_BOTTOM > BOTTOM) && (b_BOTTOM < a_TOP)) || ((b_TOP > BOTTOM) && (b_TOP < a_TOP))) {
        yCondition = true;
    }
    if (xCondition && yCondition) {
        return true;
    } else {
        return false;
    }
}

/* 

First, we check if the circle collides with the corners of the rectangle by comparing the distance between the center of
the circle to each corner of the rectangle. If any of them are smaller than the radius, we flag true.

Otherwise, give the rectangle an expanded boundary, adding on the radius of the circle to the length and width of the rectangle
and checking if the circle still lies within the bounds, if yes, we flag for a collision.

The reason check the corners first is because a circle can afford to get closer to a corner of a rectangle before a collision.

*/

bool rectangleOnCircle(const RectangularRobot& a, const CircularRobot& b) {
    double a_LEFT = a.getCenterX() - (a.getWidth() / 2); // LEFT
    double a_RIGHT = a.getCenterX() + (a.getWidth() / 2); //RIGHT
    double a_BOTTOM = a.getCenterY() - (a.getLength() / 2); // BOTTOM
    double a_TOP = a.getCenterY() + (a.getLength() / 2); // TOP

    // std::cout<<"WIDTH: "<<a.getWidth()<<std::endl;
    // std::cout<<"LENGTH: "<<a.getLength()<<std::endl;

    // std::cout<<a_LEFT<<std::endl;
    // std::cout<<a_RIGHT<<std::endl;
    // std::cout<<a_BOTTOM<<std::endl;
    // std::cout<<a_TOP<<std::endl;
    
    double shortestDistance;
    double check;

    shortestDistance = getDistance(b.getCenterX(), b.getCenterY(), a_LEFT, a_BOTTOM);

    // std::cout<<"CHECK START "<<shortestDistance<<std::endl;

    check = getDistance(b.getCenterX(), b.getCenterY(), a_LEFT, a_TOP);
    if (check < shortestDistance) {
        shortestDistance = check;
    }

    // std::cout<<"CHECK 2 "<<shortestDistance<<std::endl;

    check = getDistance(b.getCenterX(), b.getCenterY(), a_RIGHT, a_BOTTOM); // HERE

    // std::cout<<b.getCenterX()<<std::endl;
    // std::cout<<b.getCenterY()<<std::endl;
    // std::cout<<a_RIGHT<<std::endl;
    // std::cout<<a_BOTTOM<<std::endl;

    if (check < shortestDistance) {
        shortestDistance = check;
    }

    // std::cout<<"CHECK 3 "<<shortestDistance<<std::endl;

    check = getDistance(b.getCenterX(), b.getCenterY(), a_RIGHT, a_TOP);

    if (check < shortestDistance) {
        shortestDistance = check;
    }

    // std::cout<<"CHECK 4 "<<shortestDistance<<std::endl;

    // std::cout<<shortestDistance<<" "<<b.getRadius()<<std::endl;

    if (shortestDistance < b.getRadius()) {
        // std::cout<<"THE CORNER COLLISION WAS FLAGGED."<<std::endl;
        return true;
    }

    if (((b.getCenterX() > a_LEFT) && (b.getCenterX() < a_RIGHT)) || ((b.getCenterY() > a_BOTTOM) && (b.getCenterY() < a_TOP))) {
        if (((b.getCenterX() > a_LEFT-b.getRadius()) && (b.getCenterX() < a_RIGHT+b.getRadius())) && ((b.getCenterY() > a_BOTTOM-b.getRadius()) && (b.getCenterY() < a_TOP+b.getRadius()))) {
            std::cout<<"THE SIDE COLLISION WAS FLAGGED."<<std::endl;
            return true;
        }
    }
    return false;
}

bool isColliding (const Robot& a, const Robot& b) {
    auto typeA = a.getType();
    auto typeB = b.getType();
    
    if (typeA > typeB) { // This makes it so that the highest value will always be second in the map
        auto selector = collisionType.find({typeB, typeA});
            if (selector != collisionType.end()) {
            return selector->second(b, a);   
            }

    }
    else {
        auto selector = collisionType.find({typeA, typeB});
            if (selector != collisionType.end()) {
            return selector->second(a, b);   
            }
    }

    return true;
}
