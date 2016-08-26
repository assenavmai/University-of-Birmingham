#include <iostream>
#include <functional>

using namespace std;

#include "templatesast.h" 

#include "templatesast.cpp" // this is where the eval functions should be

// instantiate the AST template and try it

int iadd(int x, int y) { return x + y; }
int mint(int x, int y) { return x * y; }
int isub(int x, int y) { return x - y; }

float mult(float x, float y) { return x * y; }
float fadd(float x, float y) { return x + y; }
float fsub(float x, float y) { return x + y; }

int main(int argc, const char *argv[])
{
  ExpList<int> *l = nullptr;
  ExpList<int> *m = nullptr;
  Exp<int> *e1 = nullptr;
  Exp<int> *e2 = nullptr;

  operators<int> intadd = {iadd, 0};
  operators<int> intmult = {mint, 0};
  operators<int> intsub = {isub, 0};



  //test minus

  l = new ExpList<int>(new Constant<int>(10), l);
  l = new ExpList<int>(new Constant<int>(2), l);
  l = new ExpList<int>(new Constant<int>(1), l);
  e1 = new OpApp<int>(intsub, l);
  if(e1->eval(nullptr) == 9)
    cout << "Passed." << endl;
  else
    cout << "Failed." << endl;
}