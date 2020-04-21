#include "FamilyTree.hpp"
using namespace family;

//************Implementation of the functions of node************

//Default constructor
node::node ()
{
    this->name="";
    this->father= nullptr;
    this->mother=nullptr;
    this->gender='n';
    this->height=0;
}

//Parameters constructor
node::node (string name)
{
    this->name=name;
    this->father=nullptr;
    this->mother=nullptr;
    this->gender='n';
    this->height=0;
}

node::node (string name, char gender)
{
    this->name=name;
    this->father=nullptr;
    this->mother=nullptr;
    this->gender=gender;
    this->height=0;
}

node::node (string name, char gender,int height)
{
    this->name=name;
    this->father=nullptr;
    this->mother=nullptr;
    this->gender=gender;
    this->height=height;
}

//gets&sets
void node::setFather(node * father)
{
    this->father=father;
}

void node::setMother(node * mother)
{
    this->mother=mother;
}

node * node::getFather()
{
    return this->father;
}

node * node::getMother()
{
    return this->mother;
}

string node::getName()
{
    return this->name;
}

int node::getHeight()
{
    return this->height;
}

char node::getGender()
{
    return this->gender;
}

//************Implementation of the functions of Tree************

/**
 * The father will mark the right side of the binary tree.
 * @param nameChild
 * @param nameFather
 * @return Reference to the tree after the change
 */
Tree& Tree:: addFather(string nameChild, string nameFather)
{
    int height=-1;
    node * toAdd=returnNode(nameChild,this->root,height);
    if(toAdd== nullptr)
    {
        throw runtime_error("The "+nameChild +" does not exist in tree");
    }
    else //the name child is in the tree
    {
        if(toAdd->getFather()!= nullptr)
        {
            throw runtime_error("To "+nameChild +" Father's name is already set");
        }
        else
        {
            node * father=new node(nameFather,'m',height);
            toAdd->setFather(father);
        }
    }
    return *this;
}

/**
 *  The father will mark the left side of the binary tree.
 * @param nameChild
 * @param nameMother
 * @return Reference to the tree after the change
 */
Tree& Tree:: addMother(string nameChild, string nameMother)
{
    int height=-1;
    node * toAdd=returnNode(nameChild,this->root,height);
    if(toAdd== nullptr)
    {
        throw runtime_error("The "+nameChild +"does not exist in tree");
    }
    else //the name child is in the tree
    {
        if(toAdd->getMother()!= nullptr)
        {
            throw runtime_error("To "+nameChild +" Mother's name is already set");
        }
        else
        {
            node * mother=new node(nameMother,'f',height);
            toAdd->setMother(mother);
        }
    }
    return *this;
}

/**
 *
 * @param name
 * @return
 */
string Tree::relation(string name)
{
    if(this->root!=NULL && this->root->getName().compare(name)==0) return "me";
    else if (this->root->getMother()!= nullptr && this->root->getMother()->getName().compare(name)==0) return "mother";
    else if (this->root->getFather()!= nullptr && this->root->getFather()->getName().compare(name)==0) return "father";
    else if (this->root->getMother()->getMother()!=nullptr && this->root->getMother()->getMother()->getName().compare(name)==0) return "grandmother";
    else if (this->root->getFather()->getFather()!= nullptr && this->root->getFather()->getFather()->getName().compare(name)==0) return "grandfather";
    else
    {
        int height=0;
        node * ans=returnNode(name,this->root,height);
        if(ans== nullptr)
        {
            return "unrelated";
        }
        else
        {
            int times=ans->getHeight();
            string finaleAns="";
            for (int i = 0; i <times ;i++) {
                finaleAns+="great-";
            }
            if(ans->getGender()=='f')
            {
                finaleAns+="grandmother";
            }
            else
            {
                finaleAns+="grandfather";
            }
            return finaleAns;
        }
    }
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

node* Tree::returnNode(string key,node* ptr,int & height)
{
     if(ptr!= nullptr) //the node we currently working on is not null
     {
//         cout<<"ptr->getName().compare(key) "<<ptr->getName().compare(key)<<"name"<<ptr->getName()<<"\n";
         if (ptr->getName().compare(key)==0) //find the right node
         {
             return ptr;
         }
         else //still not found the right node
         {
           if(ptr->getFather()!= nullptr) //there is still a right tree
           {
               height=height+1;
               return returnNode(key,ptr->getFather(),height);
           }
           if(ptr->getMother()!= nullptr) //there is still a left tree
           {
               height=height+1;
               return returnNode(key,ptr->getMother(),height);
           }
           else if(ptr->getFather()== nullptr && ptr->getMother()== nullptr) //there no one more to check
           {
               return nullptr;
           }
         }
     }
     else
     {
         throw runtime_error("The tree does not exist");
     }

    return nullptr;
}

//************Implementation of the private functions ************
