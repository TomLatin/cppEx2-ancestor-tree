#include "FamilyTree.hpp"
using namespace family;

Tree& Tree:: addFather(string nameChild, string nameFather)
{
    return *this;
}

Tree& Tree:: addMother(string nameChild, string nameMother)
{
    return *this;
}


string Tree::relation(string name)
{
    return "true";
}

string Tree:: find(string name)
{
    return "true";
}

void Tree:: display()
{

}

void Tree:: remove(string name)
{

}
