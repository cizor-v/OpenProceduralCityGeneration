#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include "turtle.hpp"
using namespace std;

class L_system
{
    public:
        L_system(string popDensityMap);
        virtual ~L_system();

        void iterate();
        void render();

        string getString();

    private:
        // input data maps
        string popDensity_map_path;
        string height_map_path;
        string streetPattern_map_path;
        string land_map_path;
        string zoning_map_path;
        string buildHeight_map_path;

        // result string
        string L_string;

        // functions to initialize / update road parameters
        vector<vector<string>> globalGoals(string ruleAttr, string roadAttr);
        string localConstraints(string roadAttr);

        // utility
        vector<string> splitString(string str, string separator);
};

#endif // L_SYSTEM_H
