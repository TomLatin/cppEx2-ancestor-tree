#include "FamilyTree.hpp"
using namespace family;
#define COUNT 10

//************Implementation of the functions of node class************

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

//************Implementation of the functions of Tree class************

/**
 * A shell method whose job is to add father to the child
 * The father will mark the right side.
 * @param nameChild
 * @param nameFather
 * @return Reference to the tree after the change
 */
Tree& Tree:: addFather(string nameChild, string nameFather)
{
    addMotherOrFather(nameChild,nameFather,"father",this->root);
    return *this;
}

/**
 * A shell method whose job is to add mother to the child
 *  The father will mark the left side
 * @param nameChild
 * @param nameMother
 * @return Reference to the tree after the change
 */
Tree& Tree:: addMother(string nameChild, string nameMother)
{
    addMotherOrFather(nameChild,nameMother,"mother",this->root);
    return *this;
}

/**
 *A method whose job is to find the right node and then add another node to it.
  The method adds a father or mother according to whichParent parameter
 * @param nameChild
 * @param nameParent
 * @param whichParent
 * @param root
 */
void Tree::addMotherOrFather(string nameChild, string nameParent, string whichParent,node * root)
{
    int height=0;
    node * toAdd=returnNode(nameChild,root,&height);
    if(toAdd== nullptr)
    {
        throw runtime_error("The "+nameChild +"does not exist in tree");
    }
    else //the name child is in the tree
    {
        if(whichParent=="mother")
        {
            if(toAdd->getMother()!= nullptr)
            {
                throw runtime_error("To "+nameChild +" Mother's name is already set");
            }
            else
            {
                node * mother=new node(nameParent,'f',height+1);
                toAdd->setMother(mother);
            }
        }
        else //whichParent=="father"
        {
            if(toAdd->getFather()!= nullptr)
            {
                throw runtime_error("To "+nameChild +" Father's name is already set");
            }
            else
            {
                node * father=new node(nameParent,'m',height+1);
                toAdd->setFather(father);
            }
        }
    }
}

/**
 *Accepting someone's name in the tree, returning their relationship to you.
 * For example: father, mother, grandmother, great-grandfather, great-great-grandmother ...
 * If he is not in the tree, return unrelated.
 * @param name
 * @return Family relation
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
    else //need to add "great-" x times
    {
        int height=0;
        node * ans=returnNode(name,this->root,&height); //To know how many times the word "great-" should be added, we need to know the height of the node
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

/**
 * An inverse relation function, accepts a string that specifies a relation, and returns the person's name from the tree
 * that maintains this relation.
   If it does not exist, the function throws an error.
 * @param name
 * @return
 */
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

//help function to: string Tree:: find(string name)
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

//this method taken from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void Tree:: display()
{
    printTree(this->root,0);
}

//this method taken from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void Tree:: printTree(family::node* root,int space){
    if(root==NULL) return;
    space+=COUNT;
    printTree(root->getMother(),space);
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->getName()<<"\n";
    printTree(root->getFather(),space);
}

/**
 * Gets the name of someone who is in the tree, and deletes it and all its parents from the tree.
 * @param name
 */
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

//help function to: void Tree:: remove(string name)
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

//help function to: void Tree:: remove(string name)
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
            else { //at least one of them isn't null

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




