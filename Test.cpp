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


static Tree myTree("tom");

void buildTheTestTree(Tree myTree)
{
    myTree.addMother("tom","tehila");
    myTree.addFather("tom","haviv");
        //-----Sart the side of the mother-----

    myTree.addMother("tehila","shara");
    myTree.addFather("tehila","yitzhac");
    myTree.addMother("shara","latipa");
    myTree.addFather("shara","zachi");
    myTree.addMother("latipa","yafa");
    myTree.addFather("latipa","itay");
    myTree.addMother("yafa","sandra");
    myTree.addFather("yafa","yakov");
    myTree.addMother("zachi","noa");
    myTree.addFather("zachi","elior");
    myTree.addMother("elior","bar");
    myTree.addFather("elior","tal");
    myTree.addMother("yitzhac","galit");
    myTree.addFather("yitzhac","oded");
    myTree.addMother("galit","car");
    myTree.addFather("galit","eli");
    myTree.addMother("oded","rose");
    myTree.addFather("oded","eliyahu");
    myTree.addMother("eliyahu","sarit");
    myTree.addFather("eliyahu","static");

        //-----Sart the side of the father-----
    myTree.addMother("haviv","rachel");
    myTree.addFather("haviv","moshe");
    myTree.addMother("rachel","or");
    myTree.addFather("rachel","odi");
    myTree.addMother("or","yeal");
    myTree.addFather("or","joni");
    myTree.addMother("odi","tamar");
    myTree.addFather("odi","zvi");
    myTree.addMother("moshe","hana");
    myTree.addFather("moshe","david");
    myTree.addMother("hana","lee");
    myTree.addFather("hana","amos");
    myTree.addMother("amos","amit");
    myTree.addFather("amos","ram");
    myTree.addMother("galit","car");
    myTree.addFather("galit","eli");
    myTree.addMother("david","tali");
    myTree.addFather("david","lior");
}

TEST_CASE("Test the function addMother and function relation") {
    buildTheTestTree(myTree);

            CHECK(myTree.relation("tom")==string("me"));

    //-----side of the mother-----

            CHECK(myTree.relation("tehila")==string("mother"));
            CHECK(myTree.relation("shara")==string("grandmother"));
            CHECK(myTree.relation("latipa")==string("great-grandmother"));
            CHECK(myTree.relation("galit")==string("great-grandmother"));
            CHECK(myTree.relation("yafa")==string("great-great-grandmother"));
            CHECK(myTree.relation("noa")==string("great-great-grandmother"));
            CHECK(myTree.relation("car")==string("great-great-grandmother"));
            CHECK(myTree.relation("rose")==string("great-great-grandmother"));
            CHECK(myTree.relation("sandra")==string("great-great-great-grandmother"));
            CHECK(myTree.relation("bar")==string("great-great-great-grandmother"));
            CHECK(myTree.relation("sarit")==string("great-great-great-grandmother"));

            CHECK(myTree.relation("tehila")!=string("grandmother"));
            CHECK(myTree.relation("shara")!=string("mother"));
            CHECK(myTree.relation("latipa")!=string("great-great-grandmother"));
            CHECK(myTree.relation("galit")!=string("great-grandmother"));
            CHECK(myTree.relation("yafa")!=string("great-grandmother"));
            CHECK(myTree.relation("noa")!=string("great-grandmother"));
            CHECK(myTree.relation("car")!=string("great-grandmother"));
            CHECK(myTree.relation("rose")!=string("great-grandmother"));
            CHECK(myTree.relation("sandra")!=string("great-great-great-great-great-grandmother"));
            CHECK(myTree.relation("bar")!=string("great-great-great-great-great-grandmother"));
            CHECK(myTree.relation("sarit")!=string("great-grandmother"));

    //-----side of the father-----

            CHECK(myTree.relation("rachel")==string("grandmother"));
            CHECK(myTree.relation("or")==string("great-grandmother"));
            CHECK(myTree.relation("hana")==string("great-grandmother"));
            CHECK(myTree.relation("yeal")==string("great-great-grandmother"));
            CHECK(myTree.relation("tamar")==string("great-great-grandmother"));
            CHECK(myTree.relation("lee")==string("great-great-grandmother"));
            CHECK(myTree.relation("tali")==string("great-great-grandmother"));
            CHECK(myTree.relation("amit")==string("great-great-great-grandmother"));

            CHECK(myTree.relation("rachel")!=string("great-great-grandmother"));
            CHECK(myTree.relation("or")!=string("grandmother"));
            CHECK(myTree.relation("hana")!=string("great-great-great-grandmother"));
            CHECK(myTree.relation("yeal")!=string("great-grandmother"));
            CHECK(myTree.relation("tamar")!=string("great-great-great-great-grandmother"));
            CHECK(myTree.relation("lee")!=string("mother"));
            CHECK(myTree.relation("tali")!=string("great-grandmother"));
            CHECK(myTree.relation("amit")!=string("great-great-great-great-grandmother"));

    //-----NOT in the family-----

            CHECK(myTree.relation("x")==string("unrelated"));
            CHECK(myTree.relation("orian")==string("unrelated"));
            CHECK(myTree.relation("yirat")==string("unrelated"));
            CHECK(myTree.relation("gargamel")==string("unrelated"));
            CHECK(myTree.relation("dardas")==string("unrelated"));
            CHECK(myTree.relation("shani")==string("unrelated"));
            CHECK(myTree.relation("orel")==string("unrelated"));
            CHECK(myTree.relation("haivva")==string("unrelated"));
            CHECK(myTree.relation("sandtra")==string("unrelated"));
            CHECK(myTree.relation("baur")==string("unrelated"));
            CHECK(myTree.relation("sarrit")==string("unrelated"));
            CHECK(myTree.relation("til")==string("unrelated"));
            CHECK(myTree.relation("mama")==string("unrelated"));
            CHECK(myTree.relation("papa")==string("unrelated"));
}

TEST_CASE("Test the function addFather and function relation") {
    buildTheTestTree(myTree);

            CHECK(myTree.relation("tom")==string("me"));

    //-----side of the mother-----

            CHECK(myTree.relation("haviv")==string("father"));
            CHECK(myTree.relation("yitzhac")==string("grandfather"));
            CHECK(myTree.relation("zachi")==string("great-grandfather"));
            CHECK(myTree.relation("oded")==string("great-grandfather"));
            CHECK(myTree.relation("itay")==string("great-great-grandfather"));
            CHECK(myTree.relation("elior")==string("great-great-grandfather"));
            CHECK(myTree.relation("eli")==string("great-great-grandfather"));
            CHECK(myTree.relation("eliyahu")==string("great-great-grandfather"));
            CHECK(myTree.relation("yakov")==string("great-great-great-grandfather"));
            CHECK(myTree.relation("tal")==string("great-great-great-grandfather"));
            CHECK(myTree.relation("static")==string("great-great-great-grandfather"));

            CHECK(myTree.relation("haviv")!=string("grandfather"));
            CHECK(myTree.relation("yitzhac")!=string("great-grandfather"));
            CHECK(myTree.relation("zachi")!=string("grandfather"));
            CHECK(myTree.relation("oded")!=string("great-great-great-grandfather"));
            CHECK(myTree.relation("itay")!=string("great-great-great-great-great-grandfather"));
            CHECK(myTree.relation("elior")!=string("great-grandfather"));
            CHECK(myTree.relation("eli")!=string("great-great-great-grandfather"));
            CHECK(myTree.relation("eliyahu")!=string("great-great-great-great-grandfather"));
            CHECK(myTree.relation("yakov")!=string("grandfather"));
            CHECK(myTree.relation("tal")!=string("great-great-great-great-grandfather"));
            CHECK(myTree.relation("static")!=string("great-grandfather"));

    //-----side of the father-----

            CHECK(myTree.relation("moshe")==string("grandfather"));
            CHECK(myTree.relation("odi")==string("great-grandfather"));
            CHECK(myTree.relation("david")==string("great-grandfather"));
            CHECK(myTree.relation("joni")==string("great-great-grandfather"));
            CHECK(myTree.relation("zvi")==string("great-great-grandfather"));
            CHECK(myTree.relation("amos")==string("great-great-grandfather"));
            CHECK(myTree.relation("lior")==string("great-great-grandfather"));
            CHECK(myTree.relation("ram")==string("great-great-great-grandfather"));

            CHECK(myTree.relation("moshe")!=string("great-grandfather"));
            CHECK(myTree.relation("odi")!=string("grandfather"));
            CHECK(myTree.relation("david")!=string("great-great-grandfather"));
            CHECK(myTree.relation("joni")!=string("great-grandfather"));
            CHECK(myTree.relation("zvi")!=string("great-great-great-grandfather"));
            CHECK(myTree.relation("amos")!=string("great-great-great-great-grandfather"));
            CHECK(myTree.relation("lior")!=string("great-great-great-great-great-grandfather"));
            CHECK(myTree.relation("ram")!=string("father"));

    //-----NOT in the family-----

            CHECK(myTree.relation("y")==string("unrelated"));
            CHECK(myTree.relation("gil")==string("unrelated"));
            CHECK(myTree.relation("mayan")==string("unrelated"));
            CHECK(myTree.relation("inbal")==string("unrelated"));
            CHECK(myTree.relation("adin")==string("unrelated"));
            CHECK(myTree.relation("adir")==string("unrelated"));
            CHECK(myTree.relation("yair")==string("unrelated"));
            CHECK(myTree.relation("miri")==string("unrelated"));
            CHECK(myTree.relation("norit")==string("unrelated"));
            CHECK(myTree.relation("efrat")==string("unrelated"));
            CHECK(myTree.relation("tikva")==string("unrelated"));
            CHECK(myTree.relation("avital")==string("unrelated"));
            CHECK(myTree.relation("eran")==string("unrelated"));
            CHECK(myTree.relation("gilad")==string("unrelated"));
}
