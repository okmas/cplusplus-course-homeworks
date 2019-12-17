#include "Tag.h"
#include "IOoperation.h"
#include <iostream>

#define INPUT "input2.txt"

using namespace std;

IOoperation *io;
Tag *doc, *t;

void foo0() {
}

void foo1() {
}

void foo2() {
}

int main()
{
    foo0();foo1();foo2();

    io = new IOoperation();
    doc = io->load(INPUT);
    t = doc->getFirstChild();
    t = t->getFirstChild();
    t = t->getSibling();
    t = t->getSibling();
    t = t->getSibling();
    t->setAttribute("height", 0);
    t = t->getSibling();
    t = t->getFirstChild();
    t->remove();

    t = doc->getFirstChild();
    t = t->getSibling();
    t = t->getFirstChild();
    t = t->getSibling();
    if (t != NULL) cout << "Chyba getSibling()." << endl;

    t = doc->getFirstChild()->getSibling()->getSibling();
    t->setContent("Novy content.");
    io->save("output.txt", doc);

    delete io;

    return 0;
}
