#include "FamilyTree.hpp"
using namespace family;
#define COUNT 10

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

node::node (string name, char gender='n',int height=0)
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
    int height=0;
    node * toAdd=returnNode(nameChild,this->root,&height);
//    if(nameChild=="Rachel")
//    {
//        cout<<"toAdd->getName(): "<<toAdd->getName();
//    }
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
            node * father=new node(nameFather,'m',height+1);
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
    int height=0;
    node * toAdd=returnNode(nameChild,this->root,&height);
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
            node * mother=new node(nameMother,'f',height+1);
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
    if(this->root!=NULL && this->root->getName()==name) return "me";
    else if (this->root->getMother()!= nullptr && this->root->getMother()->getName()==name) return "mother";
    else if (this->root->getFather()!= nullptr && this->root->getFather()->getName()==name) return "father";
    else if (this->root->getMother()!= nullptr && this->root->getMother()->getMother()!=nullptr && this->root->getMother()->getMother()->getName()==name) return "grandmother";
    else if (this->root->getFather()!= nullptr && this->root->getFather()->getFather()!= nullptr && this->root->getFather()->getFather()->getName()==name) return "grandfather";
    else if (this->root->getFather()!= nullptr && this->root->getFather()->getMother()!=nullptr && this->root->getFather()->getMother()->getName()==name) return "grandmother";
    else if (this->root->getMother()!= nullptr && this->root->getMother()->getFather()!= nullptr && this->root->getMother()->getFather()->getName()==name) return "grandfather";
    else
    {
        int height=0;
        node * ans=returnNode(name,this->root,&height);
        if(name=="Avi")
        {
            cout<<"ans->getHeight()"<<ans->getHeight();
        }
        if(ans== nullptr)
        {
            return "unrelated";
        }
        else
        {
            int times=ans->getHeight();
            times=times-2;

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
    if(name=="me"&&this->root!=NULL) return root->getName();
    else if(name=="mother"&&this->root->getMother()!= nullptr) return this->root->getMother()->getName();
    else if(name=="father"&&this->root->getFather()!= nullptr) return this->root->getFather()->getName();
    string ans="";
    string & finalAns=ans;
    findRecursion(this->root,name,finalAns);
    if(finalAns=="")
    {
        throw runtime_error("not in the tree");
    }
    else
    {
        return finalAns;
    }
}

void  Tree:: findRecursion(node * ptr,string name,string & finalAns)
{
    if(ptr==NULL) return;
    if(ptr->getMother()!=nullptr && ptr->getMother()->getMother()!=nullptr && name=="grandmother")
    {
        finalAns=ptr->getMother()->getMother()->getName();
    }
    else if(ptr->getFather()!=nullptr && ptr->getFather()->getMother()!=nullptr && name=="grandmother")
    {
        finalAns=ptr->getFather()->getMother()->getName();
    }
    else if(ptr->getMother()!=nullptr && ptr->getMother()->getFather()!=nullptr && name=="grandfather")
    {
        finalAns=ptr->getMother()->getFather()->getName();
    }
    else if(ptr->getFather()!=nullptr && ptr->getFather()->getFather()!=nullptr && name=="grandfather")
    {
        finalAns=ptr->getFather()->getFather()->getName();
    }

    if(name!="grandmother" && name!="grandfather" && (name.length()<6 || name.substr(0,6)!="great-"))
    {
        throw runtime_error("relation Illegal");
    }
    if(name!="grandmother" && name!="grandfather")
    {
        findRecursion(ptr->getFather(),name.substr(6), finalAns);
    }
    if(name!="grandmother" && name!="grandfather" && finalAns=="")
    {
        findRecursion(ptr->getMother(),name.substr(6),finalAns);
    }
}

void Tree:: display()
{
    printTree(this->root,0);
}
void printTree(family::node* root,int space){
    if(root==NULL) return;
    space+=COUNT;
    printTree(root->getMother(),space);
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->getName()<<"\n";
    printTree(root->getFather(),space);
}

void Tree:: remove(string name)
{
    if(this->root->getName()==name)
    {
        throw runtime_error("The root of the tree cannot be deleted");
    }
    else
    {
        node * child= nullptr;
        findChild(this->root,name,&child);
        if(child== nullptr)
        {
            throw runtime_error("Does not exist in tree");
        }
        else //find the child that we need to delete is parents
        {
            if(child->getMother()!=nullptr && child->getMother()->getName()==name)
            {
                deleteSubTree(child->getMother());
                child->setMotherNull();
            }
            else if(child->getFather()!=nullptr && child->getFather()->getName()==name)
            {
                deleteSubTree(child->getFather());
                child->setFatherNull();
            }
        }
    }
}

void Tree::findChild(node * ptr,string name,node ** childToUpdate)
{
    if(ptr==NULL) return;
    if( (ptr->getMother()!= nullptr && ptr->getMother()->getName()==name) || (ptr->getFather()!= nullptr && ptr->getFather()->getName()==name) )
    {
        *(childToUpdate)=ptr;
    }
    if(ptr->getFather()!= nullptr)
    {
        findChild(ptr->getFather(),name,childToUpdate);
    }
    if(ptr->getMother()!= nullptr)
    {
        findChild(ptr->getMother(),name,childToUpdate);
    }
}

void Tree::deleteSubTree(node * ptr)
{
    if(ptr!=NULL)
    {
        deleteSubTree(ptr->getMother());
        deleteSubTree(ptr->getFather());
        delete ptr;
    }
}

node* Tree::returnNode(string key,node* ptr,int* height)
{
    if(ptr!= nullptr) //the node we currently working on is not null
    {
        if (ptr->getName()==key) //find the right node
        {
            return ptr;
        }
        else //still not found the right node
        {
            if(ptr->getFather()== nullptr && ptr->getMother()== nullptr) //there no one more to check
            {
                return nullptr;
            }
            else { //at least one of them isnt null

                if (ptr->getFather() != nullptr) //there is still a right tree
                {
                    node * a = returnNode(key, ptr->getFather(), height);
                    if (a!= nullptr)
                    {
                        *(height) = *(height) + 1;
                        return  a;
                    }
                }
                if (ptr->getMother() != nullptr) //there is still a left tree
                {
                    node * b= returnNode(key, ptr->getMother(), height);
                    if (b!= nullptr) {
                        *(height) = *(height) + 1;
                        return  b;
                    }
                }
                return nullptr;
            }
        }
    }
    else
    {
        throw runtime_error("The tree does not exist");
    }

}




