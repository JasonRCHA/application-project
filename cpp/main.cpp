#include "solution.hpp" // modify solution.hpp to include everything necessary

#include <cstdio>

// Method to display two objects' names and whether they're colliding
void printIsColliding(const std::string& obj1, const std::string& obj2, bool status) {
    printf("%s is %scolliding with %s\n", obj1.c_str(), status ? "" : "not ", obj2.c_str());
}

int main() {
    // Define circular robots
    CircularRobot c1( 12.5,  -2.5,  2.0);
    CircularRobot c2(  1.5,  14.5,  4.0);
    CircularRobot c3(  2.5, -22.5, 20.0);
    CircularRobot c4(-13.2,  -0.8,  0.5);

    // Define rectangular robots
    
    RectangularRobot r1( -5.0,  5.0,  5.5, 13.0);
    RectangularRobot r2( 12.5,  7.5,  2.0, 16.2);
    RectangularRobot r3(-15.5,  6.5,  4.0, 14.0);
    RectangularRobot r4(  2.5,  4.5,  5.0,  9.0);
    RectangularRobot r5( -7.5, 20.5, 10.0,  4.0);
    RectangularRobot r6(-10.0,  4.5,  7.0,  3.0);

    // Perform collision checks
    printIsColliding("c1", "r2", isColliding(c1, r2)); // CORRECT
    printIsColliding("c1", "c3", isColliding(c1, c3)); // CORRECT
    printIsColliding("r1", "c2", isColliding(r1, c2)); // CORRECT
    printIsColliding("r1", "r5", isColliding(r1, r5)); // CORRECT
    printIsColliding("r1", "r6", isColliding(r1, r6)); // CORRECT
    printIsColliding("c2", "r5", isColliding(c2, r5)); // CORRECT
    printIsColliding("c4", "r5", isColliding(c4, r3)); // CORRECT
    printIsColliding("r3", "r5", isColliding(r3, r6)); // CORRECT

    return 0;   
}
