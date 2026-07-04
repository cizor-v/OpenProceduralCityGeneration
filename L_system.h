#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <vector>
#include <string>

enum moduleType
{
    road = 0,
    query,
    branch,
    turn,
    forward
};

enum state
{
    UNASSIGNED = 0,
    FAILED,
    SUCCEEDED
};

struct roadAttributes
{
    float fLength;
    float fAngle;
};

struct ruleAttributes
{
    bool isHighway;
};

struct module
{
    moduleType      eType;
    state           eState;

    float           fPosX;
    float           fPosY;

    roadAttributes  sRoadAttrib;
    ruleAttributes  sRuleAttrib;

    int             iDel;

};

class L_system
{
    public:
        L_system(std::string popDensityMap, std::string landMap);
        virtual ~L_system();

        void iterate(); // one full loop over the "L-string"

        /*
            "render" the "L-string" into a street graph
        */
        void render();

        // std::string getString();

    private:
        // input data maps
        std::string popDensity_map_path;
        char* popDensityMap;
        std::string height_map_path;
        char* heightMap;
        std::string streetPattern_map_path;
        char* streetPatternMap;
        std::string land_map_path;
        char* landMap;

        // for later (building generation):
        // std::string zoning_map_path;
        // std::string buildHeight_map_path;

        int mapWidth;
        int mapHeight;

        std::vector<module> idealSuccessor;

        // production rules:
        void prod1(std::vector<module> * output); // delete road module
        void prod2(std::vector<module> * output, roadAttributes roadAttr, ruleAttributes ruleAttr); // initialize parameters
        void prod3(std::vector<module> * output); // delete road module
        void prod4(std::vector<module> * output, module input); // decrement branch module's del
        void prod5(std::vector<module> * output, module input); // branching
        void prod6(std::vector<module> * output); // delete branch module
        void prod7(std::vector<module> * output); // delete query module
        void prod8(std::vector<module> * output, module input); // adjust parameters
        void prod9(std::vector<module> * output); // delete query module

        // parameter functions:
        std::vector<module> globalGoals(roadAttributes roadAttr, ruleAttributes ruleAttr);
        std::pair<state, roadAttributes> localConstraints(roadAttributes roadAttr);




        // // result string
        // std::string L_string;

        // // functions to initialize / update road parameters
        // std::vector<std::vector<std::string>> globalGoals(std::string ruleAttr, std::string roadAttr);
        // std::string localConstraints(std::string roadAttr);

        // // utility
        // std::vector<std::string> splitString(std::string str, char separator);
};

#endif //L_SYSTEM_H
