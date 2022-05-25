#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

int main() {
    OrgChart football_team;

    football_team.add_root("NFL")
    .add_sub("NFL", "DEFENSE")
    .add_sub("NFL", "OFFENSE")
    .add_sub("OFFENSE", "QB")
    .add_sub("QB", "WR")
    .add_sub("QB", "RB")
    .add_sub("OFFENSE", "C")
    .add_sub("C", "G")
    .add_sub("C", "T")
    .add_sub("DEFENSE", "LB")
    .add_sub("DEFENSE", "DL")
    .add_sub("DEFENSE", "DB")
    .add_root("TEAM")
    .add_sub("DB", "CB")
    .add_sub("DB", "S")
    .add_sub("DL", "DE")
    .add_sub("QB", "TE")
    .add_sub("DL", "DT");

    cout << football_team << endl;
    /*
    <----------OrgChart---------->

    └──TEAM
        └──DEFENSE
            └──LB
            └──DL
                └──DE
                └──DT
            └──DB
                └──CB
                └──S
        └──OFFENSE
            └──QB
                └──WR
                └──RB
                └──TE
            └──C
                └──G
                └──T

    <----------OrgChart---------->
    */

    for(auto player : football_team) {
        cout << player << " ";
    } // should print: TEAM DEFENSE OFFENSE LB DL DB QB C DE DT CB S WR RB TE G T
    cout << endl;

    football_team.add_root("MIAMI-DOLPHINS");

    for (auto it = football_team.begin_level_order(); it != football_team.end_level_order(); ++it) {
        cout << (*it) << " " ;
    } // should print: MIAMI-DOLPHINS DEFENSE OFFENSE LB DL DB QB C DE DT CB S WR RB TE G T
    cout << endl;

    football_team.add_sub("MIAMI-DOLPHINS", "SPECIAL-TEAMS")
    .add_sub("SPECIAL-TEAMS", "FG-UNIT")
    .add_sub("FG-UNIT", "K")
    .add_sub("FG-UNIT", "HOLDER")
    .add_sub("SPECIAL-TEAMS", "P-UNIT")
    .add_sub("P-UNIT", "P")
    .add_sub("P-UNIT", "LS");

    cout << football_team << endl;
    /*
    <----------OrgChart---------->

    └──MIAMI-DOLPHINS
        └──DEFENSE
            └──LB
            └──DL
                └──DE
                └──DT
            └──DB
                └──CB
                └──S
        └──OFFENSE
            └──QB
                └──WR
                └──RB
                └──TE
            └──C
                └──G
                └──T
        └──SPECIAL-TEAMS
            └──FG-UNIT
                └──K
                └──HOLDER
            └──P-UNIT
                └──P
                └──LS

    <----------OrgChart---------->
    */

    for (auto it = football_team.begin_reverse_order(); it != football_team.reverse_order(); ++it) {
        cout << (*it) << " " ;
    } // should print: DE DT CB S WR RB TE G T K HOLDER P LS LB DL DB QB C FG-UNIT P-UNIT DEFENSE OFFENSE SPECIAL-TEAMS MIAMI-DOLPHINS
    cout << endl;

    football_team.add_sub("WR", "SLOT")
    .add_sub("WR", "DEEP");

    for (auto it = football_team.begin_preorder(); it != football_team.end_preorder(); ++it) {
        cout << (*it) << " " ;
    } // should print: MIAMI-DOLPHINS DEFENSE LB DL DE DT DB CB S OFFENSE QB WR SLOT DEEP RB TE C G T SPECIAL-TEAMS FG-UNIT K HOLDER P-UNIT P LS
    cout << endl;

    for (auto it = football_team.begin_level_order(); it != football_team.end_level_order(); ++it) {
        cout << it->size() << " " ;
    } // prints: 14 7 7 13 2 2 2 2 1 7 6 2 2 2 1 2 2 2 1 1 1 6 1 2 4 4
    cout << endl;

    cout << football_team << endl;
    /*
    <----------OrgChart---------->

    └──MIAMI-DOLPHINS
        └──DEFENSE
            └──LB
            └──DL
                └──DE
                └──DT
            └──DB
                └──CB
                └──S
        └──OFFENSE
            └──QB
                └──WR
                    └──SLOT
                    └──DEEP
                └──RB
                └──TE
            └──C
                └──G
                └──T
        └──SPECIAL-TEAMS
            └──FG-UNIT
                └──K
                └──HOLDER
            └──P-UNIT
                └──P
                └──LS

    <----------OrgChart---------->
    */
}