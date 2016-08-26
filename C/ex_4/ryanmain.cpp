#include <iostream>
#include <functional>

using namespace std;

#include "templatesast.h"

#include "templatesast.cpp" // this is where the eval functions should be

// instantiate the AST template and try it

int add(int x, int y) { return x + y; }

float mult(float x, float y) { return x * y; }

int main(int argc, const char *argv[])
{
    operators<int> intops = {add, 0 };
    
    // new test
    
    Exp<int> *e5 = new Constant<int>(32);
    if (e5->eval(nullptr)==32)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    
    // new test

    ExpList<int> *l = nullptr;
    l = new ExpList<int>(new Constant<int>(30), l);
    l = new ExpList<int>(new Constant<int>(45), l);
    l = new ExpList<int>(new Constant<int>(13), l);
    l = new ExpList<int>(new Constant<int>(17), l);
    l = new ExpList<int>(new Constant<int>(22), l);
    
    Exp<int> *e4 = new OpApp<int>(intops, l);
    if (e4->eval(nullptr)==127)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    // new test
    
  ExpList<int> *l1 = nullptr;
  l1 = new ExpList<int>(new Constant<int>(30), l1);
  l1 = new ExpList<int>(new Constant<int>(12), l1);
  Exp<int> *e = new OpApp<int>(intops, l1);
    if (e->eval(nullptr)==42)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    //new test

  Exp<int> *e1 = new OpApp<int>(intops, nullptr);
  //cout << e1->eval(nullptr) << endl; // should print 0
    
    if (e1->eval(nullptr)==0)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    // new test
    
  operators<float> floatops = { mult, 1.0 };
    
  ExpList<float> *l2 = nullptr;
  l2 = new ExpList<float>(new Constant<float>(.222), l2);
  l2 = new ExpList<float>(new Constant<float>(3.0), l2);
  Exp<float> *e2 = new OpApp<float>(floatops, l2);
  //cout << e2->eval(nullptr) << endl; // should print 0.666 = 1.0 * 3.0 * .222
    
    if (e2->eval(nullptr) == 0.666f)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    // new test
    
    ExpList<int> *l8 = nullptr;
    Exp<int> *e11 = nullptr;
    Exp<int> *e21 = nullptr;
    // test let bind
    l8 = new ExpList<int>(new Constant<int>(8), l8);
    l8 = new ExpList<int>(new Constant<int>(3), l8);
    l8 = new ExpList<int>(new Constant<int>(2), l8);
    e11 = new OpApp<int>(intops, l8);
    
    intops = {mult, 1};
    l8 = nullptr;
    l8 = new ExpList<int>(new Var<int>("x"), l8);
    l8 = new ExpList<int>(new Var<int>("x"), l8);
    l8 = new ExpList<int>(new Var<int>("x"), l8);
    
    Exp<int> *e221 = new OpApp<int>(intops, l8);

    e11 = new Let<int>("x", e11, e221);
    //cout << e11->eval(nullptr) << endl;
    
    if (e11->eval(nullptr)==2197)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    free(l);
    
    // new tests
    
    // test let bind with more than one variables
    
    ExpList<int> *m = nullptr;
    intops = {mult, 1};
    
    l = nullptr;
    m = new ExpList<int>(new Var<int>("z"), m);
    m = new ExpList<int>(new Constant<int>(10), m);
    l = new ExpList<int>(new Let<int>("z", new Constant<int>(2), new OpApp<int>(intops, m)), l);
    l = new ExpList<int>(new Let<int>("y", new Constant<int>(10), new Var<int>("y")), l);
    l = new ExpList<int>(new Constant<int>(5), l);
    l = new ExpList<int>(new Var<int>("x"), l);
    
    intops = {add, 0};

    e1 = new Let<int>("x", new Constant<int>(2), new OpApp<int>(intops, l));
    if (e1->eval(nullptr)==37)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    free(l);
    free(m);
    
    // test let bind when there are different scopes for one variable
    l = nullptr;
    m = nullptr;
    
    floatops = { mult, 1.0 };
    ExpList<float> *mf = nullptr;
    ExpList<float> *lf = nullptr;
    
    mf = new ExpList<float>(new Var<float>("y"), mf);
    mf = new ExpList<float>(new Constant<float>(10.0), mf);
    lf = new ExpList<float>(new Let<float>("y", new Constant<float>(2.0), new OpApp<float>(floatops, mf)), lf);
    lf = new ExpList<float>(new Let<float>("y", new Constant<float>(10.0), new Var<float>("y")), lf);
    lf = new ExpList<float>(new Constant<float>(5.0), lf);
    lf = new ExpList<float>(new Var<float>("y"), lf);
    
    floatops = { add, 0 };
    
    Exp<float> *ef = nullptr;
    
    ef = new Let<float>("y", new Constant<float>(2.0), new OpApp<float>(floatops, lf));
    if (ef->eval(nullptr)==37.0f)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    // test let bind when there are different scopes for one variable
    l = nullptr;
    m = nullptr;
    
    intops = { mult, 1 };
    ExpList<int> *mi = nullptr;
    ExpList<int> *li = nullptr;
    
    mi = new ExpList<int>(new Var<int>("y"), mi);
    mi = new ExpList<int>(new Constant<int>(10), mi);
    li = new ExpList<int>(new Let<int>("y", new Constant<int>(2), new OpApp<int>(intops, mi)), li);
    li = new ExpList<int>(new Let<int>("y", new Constant<int>(10), new Var<int>("y")), li);
    li = new ExpList<int>(new Constant<int>(5), li);
    li = new ExpList<int>(new Var<int>("y"), li);
    
    intops = { add, 0 };
    
    Exp<int> *ei = nullptr;
    
    ei = new Let<int>("y", new Constant<int>(2), new OpApp<int>(intops, li));
    if (ei->eval(nullptr)==37)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;

    // new test
    
    //(= x 2 (+ x 5 1 (= x 10 x) (= x 2 (* 10 x 2 (+ 2 3 (= y 1 (* y 2)))))))
    li = nullptr;
    mi = nullptr;
    //(= y 1 (* y 2))
    li = new ExpList<int>(new Constant<int>(2), li);
    li = new ExpList<int>(new Var<int>("y"), li);
    
    intops = { mult, 1 };
    
    ei = new Let<int>("y", new Constant<int>(1), new OpApp<int>(intops, li));
    //(+ 2 3 e1)
    li = nullptr;
    li = new ExpList<int>(ei, li);
    li = new ExpList<int>(new Constant<int>(3), li);
    li = new ExpList<int>(new Constant<int>(2), li);
    
    intops = { add, 0 };
    
    ei = new OpApp<int>(intops, li);
    //(= x 2 (* 10 x 2 e1))
    li = nullptr;
    li = new ExpList<int>(ei, li);
    li = new ExpList<int>(new Constant<int>(2), li);
    li = new ExpList<int>(new Var<int>("x"), li);
    li = new ExpList<int>(new Constant<int>(10), li);
    
    intops = { mult, 1 };
    
    ei = new OpApp<int>(intops, li);
    
    ei = new Let<int>("x", new Constant<int>(2), ei);
    //(= x 2 (+ x 5 1 (= x 10 x) e1))
    li = nullptr;
    li = new ExpList<int>(ei, li);
    li = new ExpList<int>(new Let<int>("x", new Constant<int>(10), new Var<int>("x")), li);
    li = new ExpList<int>(new Constant<int>(1), li);
    li = new ExpList<int>(new Constant<int>(5), li);
    li = new ExpList<int>(new Var<int>("x"), li);
    
    intops = { add, 0 };

    ei = new OpApp<int>(intops, li);
    ei = new Let<int>("x", new Constant<int>(2), ei);
    if (ei->eval(nullptr)==298)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    
    
    //testing multiplication
    li = nullptr;
    
    intops = { mult, 1 };
    
    li = new ExpList<int>(new Constant<int>(10), li);
    li = new ExpList<int>(new Constant<int>(20), li);
    li = new ExpList<int>(new Constant<int>(30), li);
    li = new ExpList<int>(new Constant<int>(2), li);
    ei = new OpApp<int>(intops, li);
    if (ei->eval(nullptr)==12000)
        cout << "Passed." << endl;
    else
        cout << "Failed." << endl;
    

     
}
