/*
El programa recibe un entero indicando la cantidad de puntos que se procesarán, 
en las siguientes lineas el conjunto de puntos (x, y) por renglón ubicados en un plano cartesiano.

La salida del programa será la distancia más corta entre dos puntos.

Autores:
Yusdivia Molina
Daniel Yamamoto
Héctor Noyola

Fecha de modificación: 02/11/2021
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Point.h"

// Liga del vector push_back: https://www.hackerearth.com/practice/notes/standard-template-library/
std::vector<Point*> readConsole() {
    std::vector<Point*> tmp;
    std::string X, Y, size;

    std::cin >> size;

    for (int i = 0; i < std::stoi(size); i++) {
        std::cin >> X >> Y;
        tmp.push_back(new Point(std::stof(X), std::stof(Y))); // Complejidad O(1)
    }
    
    return tmp;
}

// Liga del vector push_back: https://www.hackerearth.com/practice/notes/standard-template-library/
// Liga del min_element: https://stackoverflow.com/questions/3313301/complexity-of-stl-max-element
// Liga del pow: https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/
// Liga del sqrt: https://www.geeksforgeeks.org/square-root-of-an-integer/
// Complejidad O(n^2)
float getMinDist(std::vector<Point*> points) {
    std::vector<float> distMin;
    int reducer = 0;
    for (int i = points.size() - 1; i >= 1; i--) {
        for (int j = 0; j < (points.size() - 1) - reducer; j++) {
            distMin.push_back(sqrtf(pow(points[i]->getX() - points[j]->getX(), 2) + pow(points[i]->getY() - points[j]->getY(), 2))); // Complejidad O(√(n)) + O(log n) + O(1)
        }
        reducer++;
    }

    auto minR = std::min_element(std::begin(distMin), std::end(distMin)); // Complejidad O(n)
    return (float)*minR;
}

// Liga del vector push_back: https://www.hackerearth.com/practice/notes/standard-template-library/
// Liga del sort: https://stackoverflow.com/questions/4484900/what-is-the-time-complexity-of-stdsort-in-the-c-standard-library
// Complejidad O(n) + O(n^2) -> O(n^3)
float geometryLoop(std::vector<Point*> points, float dl, float dr, float dmin, float midX, float midXM, float midXP, float result) {
    while (points.size() > 3) {
        // Ordenamos con respecto X
        std::sort(points.begin(), points.end(), Point::compare_points_by_x_coordinate()); // Complejidad O(n log n)

        // Hacemos las mitades
        std::vector<Point*> pointsLeft;
        for (int i = 0; i < points.size() / 2; i++) {
            pointsLeft.push_back(points[i]); // Complejidad O(1)
        }

        std::vector<Point*> pointsRight;
        for (int i = points.size() / 2; i < points.size(); i++) {
            pointsRight.push_back(points[i]); // Complejidad O(1)
        }

        // Sacamos la menor distancia LEFT
        float dltmp = getMinDist(pointsLeft); // Complejidad O(n^2)
        dl = dltmp < dl ? dltmp : dl;
        // Sacamos la menor distancia RIGHT
        float drtmp = getMinDist(pointsRight); // Complejidad O(n^2)
        dr = drtmp < dr ? drtmp : dr;
        // Sacamos el mínimo entre las dos distancias
        dmin = dl < dr ? dl : dr;
        // Sacamos la mitad de X
        midX = pointsRight[0]->getX();
        // Sacamos la mitad de X menos la distancia mínima
        midXM = midX - dmin;
        // Sacamos la mitad de X más la distancia mínima
        midXP = midX + dmin;

        // Obtenemos los nuevos puntos que se encuentren en el rango de midXM & midXP
        std::vector<Point*> newPoints;
        for (int i = 0; i < points.size(); i++) {
            if (points[i]->getX() >= midXM && points[i]->getX() <= midXP) {
                newPoints.push_back(points[i]); // Complejidad O(1)
            }
        }
        points = newPoints;
    }

    // Recuperamos la menor distancia
    if (points.size() < 2) {
        result = dl < dr ? dl : dr;
    } else if (points.size() <= 3) {
        float tmp = getMinDist(points);
        if (tmp < dl && tmp < dr) result = tmp;
        else result = dl < dr ? dl : dr;
    }

    return result;
}

// Complejidad O(n^3)
float geometrySearch(std::vector<Point*> points) {
    return geometryLoop(points, 1000, 1000, 0, 0, 0, 0, 0); // Complejidad O(n^3)
}

int main() {
    std::vector<Point*> points = readConsole();

    if (points.size() < 2) { std::cout << "Se necesitan al menos dos puntos" << std::endl; } 
    else { std::cout << std::to_string(geometrySearch(points)) << std::endl; } // Complejidad O(n^3)

    return  0;
}