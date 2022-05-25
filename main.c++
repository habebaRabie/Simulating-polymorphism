#include<iostream>
using namespace std;

#define PI 3.14159265

struct ShapeVtable;

//base class
struct Shape
{
    ShapeVtable* vtable;
};

struct ShapeVtable
{
    double (*GetArea)(Shape*);
    void (*PrintInfo)(Shape*);
};

double GetArea(Shape* shape)
{
    return shape->vtable->GetArea(shape);
}

void PrintInfo(Shape* shape)
{
    shape->vtable->PrintInfo(shape);
}

struct Circle
{
    Shape parent;
    double radius;
};

//calculate area of circle
double CircleArea(Circle* circle)
{
    return PI * circle->radius * circle->radius;
}

//print info of circle
void CirclePrintInfo(Circle* circle) 
{
    cout << "Circle radius= " << circle->radius << endl;
}

//create vtable for circle
ShapeVtable circleVtable =
{
    (double(*)(Shape*))CircleArea,
    (void(*)(Shape*))CirclePrintInfo
};

//initialize circle and set its vtable
void CircleInitialize(Circle* circle, double radius)
{
    circle->parent.vtable = &circleVtable;
    circle->radius = radius;
}

struct Rectangle
{
    Shape parent;
    double width;
    double height;
};

//calculate area of rectangle
double RectangleArea(Rectangle* rectangle)
{
    return rectangle->width * rectangle->height;
}

//print info of rectangle
void RectanglePrintInfo(Rectangle* rectangle)
{
    cout << "Rectangle width= " << rectangle->width << " height= " << rectangle->height << endl;
}

//create vtable for rectangle
ShapeVtable rectangleVtable =
{
    (double(*)(Shape*))RectangleArea,
    (void(*)(Shape*))RectanglePrintInfo
};

//initialize rectangle and set its vtable
void RectangleInitialize(Rectangle* rectangle, double width, double height)
{
    rectangle->parent.vtable = &rectangleVtable;
    rectangle->width = width;
    rectangle->height = height;
}

struct Ellipse
{
    Shape parent;
    double radius1;
    double radius2;
};

//calculate area of ellipse
double EllipseArea(Ellipse* ellipse)
{
    return PI * ellipse->radius1 * ellipse->radius2;
}

//print info of ellipse
void EllipsePrintInfo(Ellipse* ellipse)
{
    cout << "Ellipse r1= " << ellipse->radius1 << " r2= " << ellipse->radius2 << endl;
}

//create vtable for ellipse
ShapeVtable ellipseVtable =
{
    (double(*)(Shape*))EllipseArea,
    (void(*)(Shape*))EllipsePrintInfo
};

//initialize ellipse and set its vtable
void EllipseInitialize(Ellipse* ellipse, double radius1, double radius2)
{
    ellipse->parent.vtable = &ellipseVtable;
    ellipse->radius1 = radius1;
    ellipse->radius2 = radius2;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10
    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5
    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12
    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;
    shapes[1]=(Shape*)&rectangle ;
    shapes[2]=(Shape*)&ellipse ;
    double total_area=0;
    int i;
    for(i=0; i<3; i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout<<total_area<<endl; // check if the value is correct
    return 0;
}
