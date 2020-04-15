#pragma once
#include <iostream>
#include <string>
using namespace std;

class node{
private:
    node* father;
    node* mother;
    string privateName;
    string lastName;
public:
    node (string privateName)
    {
        this->privateName=privateName;
        this->lastName="";
        this->father=NULL;
        this->mother=NULL;
    }
    node (string lastName, string privateName)
    {
        this->privateName=privateName;
        this->lastName=lastName;
        this->father=NULL;
        this->mother=NULL;
    }

    void setFather(node * father);
    void setMother(node * mother);
    void setPrivateName(string newPrivateName);
    void setLastName(string newLastName);

    node * getFather();
    node * getMother();
    string getPrivateName();
    string getLastName();
};

namespace family {

    class Tree {
    private:
        node* root;
    public:
        Tree (string name)
        {
            this->root=new node(name);
        }
        Tree& addFather(string nameChild, string nameFather);

        Tree& addMother(string nameChild, string nameMother);

        string relation(string name);

        string find(string name);

        void display();

        void remove(string name);

    };
}

