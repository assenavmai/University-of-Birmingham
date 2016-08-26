#include <iostream>
#include <functional>

using namespace std;

#include "templatesast.h" 

#include "templatesast.cpp" // this is where the eval functions should be

// instantiate the AST template and try it

int add(int x, int y) { return x + y; }
int mint(int x, int y) { return x * y; }

int sub(int x, int y) { return x - y; }

float mult(float x, float y) { return x * y; }
float fadd(float x, float y) { return x + y; }

string addStr(string x, string y, string z) { return x; }

int main(int argc, const char *argv[])
{

  ExpList<int> *l = nullptr;
  Exp<int> * e1 = nullptr;
  Exp<int> *e2 = nullptr;
  operators<int> op1 = {add, 0};
  operators<int> op2 = {mint, 1};


  //test let bind
  l = new ExpList<int>(new Constant<int>(5), l);
  l = new ExpList<int>(new Constant<int>(3), l);
  l = new ExpList<int>(new Constant<int>(2), l);
  e1 = new OpApp<int>(op1, l);


  l = nullptr;
  l = new ExpList<int>(new Var<int>("x"), l);
  l = new ExpList<int>(new Var<int>("x"), l);
  l = new ExpList<int>(new Var<int>("x"), l);
  e2 = new OpApp<int>(op2, l);
  e1 = new Let<int>("x", e1, e2);

  if(e1->eval(nullptr) == 1000)
    cout << "Pass\n";
  else
    cout << "False\n";

  l = nullptr;
  l = new ExpList<int>(new Constant<int>(5), l);
  l = new ExpList<int>(new Constant<int>(3), l);

  operators<int> oper = {sub, 0};

  e2 = new OpApp<int>(oper, l);
  cout << e2->eval(nullptr) << endl;

  l = nullptr;
  l = new ExpList<int>(new Constant<int>(5), l);
  l = new ExpList<int>(new Constant<int>(3), l);
  l = new ExpList<int>(new Constant<int>(2), l);
  e1 = new OpApp<int>(op1, l);

  l = nullptr;
  l = new ExpList<int>(new Var<int>("x"), l);
  l = new ExpList<int>(new Var<int>("x"), l);
  


  // testing vars with floats
  /*ExpList<float> *l2 = nullptr;
  Exp<float> *e3 = nullptr;
  Exp<float> *e4 = nullptr;

  operators<float> op3 = {fadd, 0.00000000};
  l2 = new ExpList<float>(new Constant<float>(0.1), l2);
  l2 = new ExpList<float>(new Constant<float>(0.1), l2);
  l2 = new ExpList<float>(new Constant<float>(0.1), l2);
  e3 = new OpApp<float>(op3, l2);

  operators<float> op4 = {mult, 1.00000000};
  l2 = nullptr;
  l2 = new ExpList<float>(new Var<float>("x"), l2);
  l2 = new ExpList<float>(new Var<float>("x"), l2);
  l2 = new ExpList<float>(new Var<float>("x"), l2);
  e4 = new OpApp<float>(op4, l2);

  e3 = new Let<float>("x", e3, e4);

  cout << e3->eval(nullptr) << endl;
  if(e3->eval(nullptr) == 0.027)
    cout << "Pass\n";
  else
    cout << "Fail\n";*/



  //operators<int> op5 = {sub, }
}