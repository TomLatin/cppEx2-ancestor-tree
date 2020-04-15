#include "FamilyTree.hpp"
#include "doctest.h"
using namespace std;
using namespace family;

/**
 * Sketch of the tree:
                                                  ******** tom *********
                                           /                                        \
                                         /                                           \
                                       tehila                                          haviv
                                    /         \                                 /               \
                                  /            \                              /                  \
                              shara           yitzhac                       rachel              moshe
                             /  \               /  \                        /     \               / \
                           /     \            /     \                     /        \            /    \
                      latipa   zachi       galit     oded                or         odi       hana    david
 *                    / \        /\         /\        /\                 /\         / \        /\       /\
 *                  /    \     /   \      /   \     /   \              /   \      /    \     /   \    /   \
 *             yafa   itay  noa  elior  car  eli  rose  eliyahu     yeal  joni tamar  zvi lee  amos tali  lior
 *             /\                  /\                     /\                                    /\
 *           /   \               /   \                  /   \                                 /   \
 *      sandra   yakov         bar   tal             sarit  static                         amit  ram
 *
 *
 * All the tests will be done on this tree.
 */


Tree myTree("tom");

void buildTheTestTree()
{
    myTree.addMother("tom","tehila");
        .addFather("tom","haviv");
        /-----Sart the side of the mother-----

        .addMother("tehila","shara");
        .addFather("tehila","yitzhac");
        .addMother("shara","latipa");
        .addFather("shara","zachi");
        .addMother("latipa","yafa");
        .addFather("latipa","itay");
        .addMother("yafa","sandra");
        .addFather("yafa","yakov");
        .addMother("zachi","noa");
        .addFather("zachi","elior");
        .addMother("elior","bar");
        .addFather("elior","tal");
        .addMother("yitzhac","galit");
        .addFather("yitzhac","oded");
        .addMother("galit","car");
        .addFather("galit","eli");
        .addMother("oded","rose");
        .addFather("oded","eliyahu");
        .addMother("eliyahu","sarit");
        .addFather("eliyahu","static");

        /-----Sart the side of the father-----
        .addMother("haviv","rachel");
        .addFather("haviv","moshe");
        .addMother("rachel","or");
        .addFather("rachel","odi");
        .addMother("or","yeal");
        .addFather("or","joni");
        .addMother("odi","tamar");
        .addFather("odi","zvi");
        .addMother("moshe","hana");
        .addFather("moshe","david");
        .addMother("hana","lee");
        .addFather("hana","amos");
        .addMother("amos","amit");
        .addFather("amos","ram");
        .addMother("galit","car");
        .addFather("galit","eli");
        .addMother("david","tali");
        .addFather("david","lior");
}

TEST_CASE("add Mother") {
    buildTheTestTree();
    /-----side of the mother-----

            CHECK(myTree.relation("tehila")==string("mother"));
            CHECK(myTree.relation("shara")==string("grandmother"));
            CHECK(myTree.relation("latipa")==string("great-grandfather"));
            CHECK(myTree.relation("galit")==string("great-grandfather"));
            CHECK(myTree.relation("yafa")==string("great-great-grandfather"));
            CHECK(myTree.relation("noa")==string("great-great-grandfather"));
            CHECK(myTree.relation("car")==string("great-great-grandfather"));
            CHECK(myTree.relation("rose")==string("great-great-grandfather"));
            CHECK(myTree.relation("sandra")==string("great-great-great-grandfather"));
            CHECK(myTree.relation("bar")==string("great-great-great-grandfather"));
            CHECK(myTree.relation("sarit")==string("great-great-great-grandfather"));

    /-----side of the father-----

            CHECK(myTree.relation("rachel")==string("grandmother"));
            CHECK(myTree.relation("or")==string("great-grandfather"));
            CHECK(myTree.relation("yeal")==string("great-great-grandfather"));
            CHECK(myTree.relation("tehila")!=string("grandmother"));


}