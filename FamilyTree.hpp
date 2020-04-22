#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace family {
    class node
    {
    private:
        node* father;
        node* mother;
        string name;
        char gender;
        int height;
    public:
        node ();
        node (string name);
        node (string name, char gender);
        node(string name, char gender,int height);

        ~node()
        {
            void setFatherNull();
            void setMotherNull();
        }

        void setFatherNull()
        {
            this->father=nullptr;
        }
        void setMotherNull()
        {
            this->mother=nullptr;
        }

        void setFather(node * father);
        void setMother(node * mother);

        node * getFather();
        node * getMother();
        string getName();
        char getGender();
        int getHeight();
    }; //end class node

    class Tree {
    private:
        node* root;
    public:
        Tree (string name)
        {
            this->root=new node(name);
        }
        ~Tree()
        {
            delete root;
        }
        Tree& addFather(string nameChild, string nameFather);

        Tree& addMother(string nameChild, string nameMother);

        string relation(string name);

        string find(string name);

        void display();

        void remove(string name);

        node * getRoot();

    private:
        node * returnNode(string key,node * ptr,int & height);
        void  findRecursion(node * ptr,string name,string & finalAns);
        void findChild(node * ptr,string name,node ** childToUpdate);
        void deleteSubTree(node * ptr);

    }; //end class Tree
} //end namespace family







