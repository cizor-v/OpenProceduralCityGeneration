#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include "../turtle.hpp"
#include <vector>
#include <string>
#include <sstream>

class L_system
{
    public:
        L_system(std::string popDensityMap);
        virtual ~L_system();

        void iterate();
        void render();

        std::string getString();

    private:
        // input data maps
        std::string popDensity_map_path;
        char* popDensityMap;
        std::string height_map_path;
        std::string streetPattern_map_path;
        std::string land_map_path;
        std::string zoning_map_path;
        std::string buildHeight_map_path;

        int mapWidth;
        int mapHeight;

        // result string
        std::string L_string;

        // functions to initialize / update road parameters
        std::vector<std::vector<std::string>> globalGoals(std::string ruleAttr, std::string roadAttr);
        std::string localConstraints(std::string roadAttr);

        // utility
        std::vector<std::string> splitString(std::string str, char separator);
};

#endif // L_SYSTEM_H
