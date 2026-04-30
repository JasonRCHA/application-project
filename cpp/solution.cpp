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
    double distanceX = b.getCenterX() - a.getCenterY();
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

bool rectangleOnRectangle(const RectangularRobot& a, const RectangularRobot& b) {

    bool xCondition = false;
    bool yCondition = false;

    double a_x1 = a.getCenterX() - (a.getWidth() / 2);
    double a_x2 = a.getCenterX() + (a.getWidth() / 2);
    double a_y1 = a.getCenterY() - (a.getLength() / 2);
    double a_y2 = a.getCenterY() + (a.getLength() / 2);

    double b_x1 = b.getCenterX() - (b.getWidth() / 2);
    double b_x2 = b.getCenterX() + (b.getWidth() / 2);
    double b_y1 = b.getCenterY() - (b.getLength() / 2);
    double b_y2 = b.getCenterY() + (b.getLength() / 2);
    
    if (((b.getCenterX() > a_x1) && (b.getCenterX() < a_x2)) && ((b.getCenterY() > a_y1) && (b.getCenterY() < a_y2))) {
        return true;
    } 

    if (((b_x1 > a_x1) && (b_x1 < a_x2)) || ((b_x2 > a_x1) && (b_x2 < a_x2))) {
        xCondition = true;
    }
    if (((b_y1 > a_y1) && (b_y1 < a_y2)) || ((b_y2 > a_y1) && (b_y2 < a_y2))) {
        yCondition = true;
    }
    if (xCondition && yCondition) {
        return true;
    } else {
        return false;
    }
}

bool rectangleOnCircle(const RectangularRobot& a, const CircularRobot& b) {
    double a_x1 = a.getCenterX() - (a.getWidth() / 2); // LEFT
    double a_x2 = a.getCenterX() + (a.getWidth() / 2); //RIGHT
    double a_y1 = a.getCenterY() - (a.getLength() / 2); // BOTTOM
    double a_y2 = a.getCenterY() + (a.getLength() / 2); // TOP
    
    double shortestDistance;
    double check;

    shortestDistance = getDistance(b.getCenterX(), b.getCenterY(), a_x1, a_y1);

    check = getDistance(b.getCenterX(), b.getCenterY(), a_x1, a_y2);
    if (check < shortestDistance) {
        shortestDistance = check;
    }

    check = getDistance(b.getCenterX(), b.getCenterY(), a_x2, a_y1);
    if (check < shortestDistance) {
        shortestDistance = check;
    }

    check = getDistance(b.getCenterX(), b.getCenterY(), a_x2, a_y2);
    if (check < shortestDistance) {
        shortestDistance = check;
    }

    if (shortestDistance < b.getRadius()) {
        return true;
    }

    if (((b.getCenterX() > a_x1-b.getRadius()) && (b.getCenterX() < a_x2+b.getRadius())) && ((b.getCenterY() > a_y1-b.getRadius()) && (b.getCenterY() < a_y2+b.getRadius()))) {
        return true;
    }
    return false;
}

bool isColliding (const Robot& a, const Robot& b) {
    auto typeA = a.getType();
    auto typeB = b.getType();
    
    if (typeA > typeB) { // This makes it so that the highest value will always be second in the map
        auto it = collisionType.find({typeB, typeA});
            if (it != collisionType.end()) {
            return it->second(b, a);   
            }

    }
    else {
        auto it = collisionType.find({typeA, typeB});
            if (it != collisionType.end()) {
            return it->second(a, b);   
            }
    }

    return true;
}
