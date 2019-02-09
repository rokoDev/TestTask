#include <iostream>
using namespace std;

/*!
 \file
 \brief This is short
 description of Rectangle class
 
 This is long description of rectangle class
 */

class Rectangle {
    int width;///this is rectangle's width
    int height;///this is rectangle's height
public:
    
    /*!
     Set rectangle's width and height
     \param[in] w new rectangle's width
     \param[in] h new rectangle's height
     */
    void set_values (int w,int h);
    
    /*!
     Calculate and then returns rectangle's square
     \return rectangle's square
     */
    int area();
};
