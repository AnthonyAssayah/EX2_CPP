#include "doctest.h"
#include "Direction.hpp"
#include "Notebook.hpp"
#include <string>

using namespace ariel;
using namespace std;

ariel::Notebook notebook;

TEST_CASE("Test read before write")
{
    CHECK(notebook.read(0, 0, 0, Direction::Vertical, 1) == string("_"));
    CHECK(notebook.read(5, 23, 41, Direction::Vertical, 2) == string("__"));
    CHECK(notebook.read(4, 4, 4, Direction::Vertical, 3) == string("___"));
    CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 2) == string("__"));
    CHECK(notebook.read(33, 77, 111, Direction::Horizontal, 1) == string("_"));
    CHECK(notebook.read(88, 63, 422, Direction::Horizontal, 4) == string("____"));
}

TEST_CASE("Test write on notebook")
{
    CHECK_NOTHROW(notebook.write(1, 0, 0, Direction::Horizontal, "Anthony"));
    CHECK_NOTHROW(notebook.write(1, 0, 0, Direction::Vertical, "Ariel"));
    CHECK_NOTHROW(notebook.write(1, 5, 10, Direction::Vertical, "University"));
    CHECK_NOTHROW(notebook.write(1, 10, 15, Direction::Horizontal, "HelloWorld"));

}


TEST_CASE("Test read after write")
{
    CHECK(notebook.read(1, 0, 0, Direction::Horizontal, 1) == string("A"));
    CHECK(notebook.read(1, 0, 0, Direction::Horizontal, 4) == string("Anth"));
    CHECK(notebook.read(1, 0, 0, Direction::Vertical, 3) == string("Ari"));
    CHECK(notebook.read(1, 5, 9, Direction::Vertical, 3) == string("_Un"));
}

TEST_CASE("Test try to write after erase ") {
   
    notebook.erase(1, 0, 0, Direction::Horizontal, 7);                                     // erase "Anthony" at page:1 row: 0 col: 0
    CHECK_THROWS(notebook.write(1, 0, 0, Direction::Horizontal, "CPP"));                  // try to write at the same place
}


TEST_CASE("Test read words where lenght is 0") {

    CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 0) == "");
    CHECK(notebook.read(0, 0, 0, Direction::Vertical, 0) == "");
    CHECK(notebook.read(30, 60, 90, Direction::Horizontal, 0) == "");
    CHECK(notebook.read(45, 115, 325, Direction::Vertical, 0) == "");
    CHECK(notebook.read(11, 111, 1, Direction::Horizontal, 0) == "");
    CHECK(notebook.read(7, 77, 777, Direction::Vertical, 0) == "");
}

TEST_CASE("Test special characters") {

    CHECK_NOTHROW(notebook.write(15, 0, 0, Direction::Horizontal, "?"));
    CHECK_NOTHROW(notebook.write(15, 0, 2, Direction::Horizontal, "+"));
    CHECK_NOTHROW(notebook.write(15, 1, 2, Direction::Horizontal, "*"));
    
    CHECK(notebook.read(15, 0, 0, Direction::Horizontal, 1) == "?");
    CHECK(notebook.read(15, 0, 2, Direction::Horizontal, 1) == "+");
    CHECK(notebook.read(15, 1, 2, Direction::Horizontal, 1) == "*");
   
}


TEST_CASE("Test erase before and after") {

    Notebook notebook1;
    notebook1.write(2, 2, 2, Direction::Horizontal, "myNotebook");

       CHECK(notebook.read(2, 2, 2, Direction::Horizontal, 2) == "my");
       notebook.erase(2, 2, 3, Direction::Horizontal, 1);
       CHECK(notebook.read(2, 2, 2, Direction::Horizontal, 3) == "m-N");
       notebook.erase(2, 2, 5, Direction::Horizontal, 2);
       CHECK(notebook.read(2, 2, 2, Direction::Horizontal, 7) == "m-Not--");

}


TEST_CASE("Test on negative arguments") {
    CHECK_THROWS(notebook.read(-3, 0, 3, Direction::Horizontal, 0));         // negative page number
    CHECK_THROWS(notebook.read( 5, -15, 30, Direction::Vertical, 4));        // negative row number
    CHECK_THROWS(notebook.read(6, 20, -9, Direction::Horizontal, 10));       // negative col number
    CHECK_THROWS(notebook.read(-11, -23, 52, Direction::Horizontal, 0));     // two negative arguments
    CHECK_THROWS(notebook.read(-7, -77, -100, Direction::Horizontal, -44));  // four negative arguments

}  
