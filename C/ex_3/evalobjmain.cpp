
#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

int main(int argc, const char *argv[])
{
 
ExpList *l2 = nullptr;
l2 = new ExpList(new Var("x"), l2);
l2 = new ExpList(new Var("y"), l2);
l2 = new ExpList(new Var("z"), l2);
Exp *e5 = new OpApp(timesop, l2);
ExpList *l3 = nullptr;
l3 = new ExpList(new Constant(2), l3);
l3 = new ExpList(new Constant(3), l3);
l3 = new ExpList(new Constant(5), l3);
Exp *e4 = new OpApp(plusop, l3);
Exp *e3 = new Let("x",e4, e5);
Exp *e2 = new Let("y",new Constant(5), e3);
Exp *e1 = new Let("z",new Constant(40), e2);

if(e1->eval(nullptr) == 2000)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}

//cout << e1->eval(nullptr) << endl;//should print 2000

ExpList *l4 = nullptr;
l4 = new ExpList(new Var("y"),l4);
l4 = new ExpList(new Let("y",new Constant(10),new Var("y")),l4);
l4 = new ExpList(new Var("y"),l4);
Exp *e7 = new OpApp(plusop,l4);
Exp *e6 = new Let("y",new Constant(2),e7);
//cout << e6->eval(nullptr) << endl;//should print 14

if(e6->eval(nullptr) == 14)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  ExpList *l = nullptr;
  l = new ExpList(new Constant(23), l);
  l = new ExpList(new Constant(42), l);
  l = new ExpList(new Constant(666), l);

  Exp *e = new OpApp(plusop, l);
  //cout << e->eval(nullptr) << endl; // 731

if(e->eval(nullptr) == 731)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  ExpList * l5 = nullptr;
  l5 = new ExpList(new Constant(5), l5);
  l5 = new ExpList(new Constant(3), l5);
  l5 = new ExpList(new Constant(2), l5);
  l5 = new ExpList(new Constant(2), l5);
  Exp * e8 = new OpApp(timesop, l5);
 // cout << e8->eval(nullptr) << endl; // 60

if(e8->eval(nullptr) == 60)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  l5 = nullptr;
  l5 = new ExpList(new Constant(5), l5);
  e8 = new OpApp(timesop, l5);
  //cout << e8->eval(nullptr) << endl; // 5

if(e8->eval(nullptr) == 5)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  l5 = nullptr;
  l5 = new ExpList(new Constant(5), l5);
  l5 = new ExpList(new Constant(2), l5);

  e8 = new OpApp(timesop, l5);
 // cout << e8->eval(nullptr) << endl; // 10

  if(e8->eval(nullptr) == 10)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}

  l5 = nullptr;
  l5 = new ExpList(new Constant(5), l5);
  l5 = new ExpList(new Constant(3), l5);
  l5 = new ExpList(new Constant(2), l5);
  l5 = new ExpList(new Constant(2), l5);
  e8 = new OpApp(plusop, l5);
//  cout << e8->eval(nullptr) << endl; //12

  if(e8->eval(nullptr) == 12)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}

    l5 = nullptr;
  l5 = new ExpList(new Constant(5), l5);
  e8 = new OpApp(plusop, l5);
//  cout << e8->eval(nullptr) << endl; // 5

  if(e8->eval(nullptr) == 5)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}

    l5 = nullptr;
  l5 = new ExpList(new Constant(5), l5);
  l5 = new ExpList(new Constant(2), l5);

  e8 = new OpApp(plusop, l5);
  //cout << e8->eval(nullptr) << endl; // 7

if(e8->eval(nullptr) == 7)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  l5 = nullptr;
  l5 = new ExpList(new Constant(5), l5);
  l5 = new ExpList(new Constant(2), l5);
  l5 = new ExpList(new OpApp(plusop, l5), l5);

  e8 = new OpApp(timesop, l5);
 // cout << e8->eval(nullptr) << endl; // 70

if(e8->eval(nullptr) == 70)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  Constant * c = new Constant(2);
//  cout << c->eval(nullptr) << endl; //2

if(c->eval(nullptr) == 2)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}

  l = nullptr;
  l = new ExpList(new Constant(5), l);
  l = new ExpList(new Constant(3), l);
  l = new ExpList(new Constant(2), l);
  e1 = new OpApp(plusop, l);

  l = nullptr;
  l = new ExpList(new Var("x"), l);
  l = new ExpList(new Var("x"), l);
  l = new ExpList(new Var("x"), l);
  e2 = new OpApp(timesop, l);
  e1 = new Let("x", e1, e2);

  //cout << e1->eval(nullptr) << endl; //1000

if(e1->eval(nullptr) == 1000)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  ExpList * m = nullptr;
  m = new ExpList(new Var("z"), m);
  m = new ExpList(new Constant(10), m);

  l = nullptr;
  l = new ExpList(new Let("z", new Constant(2), new OpApp(timesop, m)), l);
  l = new ExpList(new Let("y", new Constant(10), new Var("y")), l);
  l = new ExpList(new Constant(5), l);
  l = new ExpList(new Var("x"), l);

  e1 = new Let("x", new Constant(2), new OpApp(plusop, l));

  //cout << e1->eval(nullptr) << endl; //37

if(e1->eval(nullptr) == 37)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  l = nullptr;
  e1 = new Constant(2);
  l = new ExpList(new Var("y"), l);
  l = new ExpList(new Let("y", new Constant(10), new Var("y")), l);
  l = new ExpList(new Var("y"), l);
  e2 = new OpApp(plusop, l);
  e1 = new Let("y", e1, e2);

 // cout << e1->eval(nullptr) << endl;

if(e1->eval(nullptr) == 14)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
  m = nullptr;
  m = new ExpList(new Var("x"), m);
  m = new ExpList(new Constant(10), m);

  l = NULL;
  l = new ExpList(new Let("x", new Constant(2), new OpApp(timesop, m)), l);
  l = new ExpList(new Let("x", new Constant(10), new Var("x")), l);
  l = new ExpList(new Constant(5), l);
  l = new ExpList(new Var("x"), l);

  e1 = new Let("x", new Constant(2), new OpApp(plusop, l));

  //cout << e1->eval(nullptr) << endl; //37

if(e1->eval(nullptr) == 37)
{
	cout << "Pass\n";
}
else
{
	cout << "Fail\n";
}
}
