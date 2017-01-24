#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <cassert>

using namespace std;

// to mial byc przyklad dla sprawdzenia TClonesArray ale nie dziala zaden przyklad z TClonesArray w klasie EventClass
// jezeli zapisuje i odczytuje z pliku

void writeData()
{
  // Create simple data
  ParamClass* a = new ParamClass ("Alpha", 1);
  a->simpleField = 101;

  EventClass* eve = 0;

  // Fill tree with events
  eve = new EventClass (a, 1);

  // Set TRef using my function
  eve->setTRef(*a);
  ParamClass *b = eve->getTRef();
  std::cout << "b->GetId() " << b->GetId() << std::endl;

  // Set TRef using my function (vector)
  ParamClass* c = new ParamClass ("C", 1);
  eve->addTRefKB(*c);
  ParamClass *d = eve->getTRef();
  std::cout << "d->GetId() " << d->GetId() << std::endl;

  /*ponizsze metody zakomentowane w EventClass
  eve->AddCh(*a);
  b = eve->getfScintillators(0);
  std::cout << "b->GetId() " << b->GetId() << std::endl;
  */
}

int main (int argc, char** argv) 
{
  writeData();
  return 0;
}
