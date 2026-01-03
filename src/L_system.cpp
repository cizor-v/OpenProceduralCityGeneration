#include "L_system.h"

L_system::L_system(string popDensityMap)
{
    //constructor
    this.popDensity_map_path = popDensityMap;
    this.L_string = ""; // Axiom with initial road parameters
}

L_system::~L_system()
{
    //dtor
}

vector<string> L_system::splitString(string str, string delimiter)
{
    vector<string> modules;
    string module;
    stringstream ss = stringstream(str);

    while (getline(ss, module, delimiter))
    {
        modules.push_back(module);
    }

    return modules;
}

vector<vector<string>> L_system::globalGoals(string ruleAttr, string roadAttr) // create parameters for pDel[0-2], pRuleAttr[0-2], pRoadAttr[0-2]
{
    // retrieve attribute values
    vector<string> vec_roadAttr = splitString(roadAttr, ' ');
    vector<string> vec_ruleAttr = splitString(ruleAttr, ' ');
    float angle, length, posx, posy, dirx, diry;
    // road attributes
    angle = std::stof(vec_roadAttr.at(0));
    length = std::stof(vec_roadAttr.at(1));
    bool isHighway = vec_roadAttr.at(2) == "TRUE";
    //rule attributes
    posx = std::stof(vec_ruleAttr.at(0));
    posy = std::stof(vec_ruleAttr.at(1));
    dirx = std::stof(vec_ruleAttr.at(2));
    diry = std::stof(vec_ruleAttr.at(3));

    if (isHighway) // highway
    {
        ;
    }
    else // street
    {
        ;
    }

}

string L_system::localConstraints(string roadAttr)
{
    // adjust parameters for state, roadAttr
}

void L_system::iterate()
{
    string temp_L_string = "";

    // remove square brackets
    string str = this.L_string;
    str.erase(remove(str.begin(), str.end(), "["), str.end());
    str.erase(remove(str.begin(), str.end(), "]"), str.end());

    // split L_string into its constituent modules
    vector<string> modules = splitString(str, ";");

    for (int i = 0; i < modules.size(); i++)
    {
        string module = modules.at(i);
        // apply production rules
        switch(module[0])
        {
        // productions p1, p2, p3
        case "R":
            vector<string> params = splitString(splitString(module, ":").at(1), ",");

            // production p1
            if (std::stoi(params.at(0)) < 0)
            {
                break; // do not add a module to the result string (delete current module)
            }

            if (i+1 < modules.size())
            {
                string nextModule = modules.at(i+1);
                if (nextModule[0] == "I")
                {
                    //production p2
                    string state = splitString(splitString(nextModule, ":").at(1), ",").at[1]
                    if (state == "SUCCEED")
                    {
                        // global goals

                        // newParams:
                        // 0 : pDel[0-2]
                        // 1 : pRuleAttr[0-2]
                        // 2 : pRoadAttr[0-2]
                        vector<vector<str>> newParams = this.globalGoals(params.at(1), I_roadAttr);
                        string I_roadAttr = splitString(splitString(nextModule, ":").at(1), ",").at(0);
                        temp_L_string += "+(" + splitString(I_roadAttr, " ").at(0)+ ");"; // turn right by roadAttr.angle
                        temp_L_string += "F(" + splitString(I_roadAttr, " ").at(1) + ");"; // go forward by roadAttr.length
                        temp_L_string += "B(" + newParams.at(0).at(1) + "," + newParams.at(1).at(1) + "," + newParams.at(2).at(1) + ");";
                        temp_L_string += "B(" + newParams.at(0).at(2) + "," + newParams.at(1).at(2) + "," + newParams.at(2).at(2) + ");";
                        temp_L_string += "R(" + newParams.at(0).at(0) + "," + newParams.at(1).at(0) + ");";
                        temp_L_string += "I(" + newParams.at(2).at(0) + ",UNASSIGNED);";
                        break;
                    }

                    //production p3
                    if (state == FAILED)
                    {
                        break; // do not add a module to the result string (delete current module)
                    }
                }
            }
            break;

        // productions p4, p5, p6
        case "B":
            vector<string> params = splitString(splitString(module, ":").at(1), ",");

            // production p4
            if (std::stoi(params.at(0)) > 0)
            {
                // add B module with same params except del is decremented by 1
                temp_L_string += "B:" + std::stoi(params.at[0])-1 + "," + params.at(1) + "," + params.at(2) + ";";
                break;
            }

            // production p5
            if (std::stoi(params.at(0)) == 0)
            {
                // add branch with R and I modules
                temp_L_string += "[" +
                                                    "R:" + params.at(0) + "," + params.at(1) + ";" +
                                                    "I:" + params.at(2) + "," + "UNASSIGNED" + ";" +
                                            "]";
                break;
            }

            //production p6
            if (std::stoi(params.at(0)) < 0)
            {
                break; // do not add a module to the result string (delete current module)
            }

            break;

        // productions p7, p8, p9
        case "I":
            vector<string> params = splitString(splitString(module, ":").at(1), ",");

            // production p7
            if (i != 0)
            {
                string delPrev = splitString(splitString(modules.at(i-1), ":").at(1), ",").at[0];
                if (std::stoi(delPrev) < 0)
                {
                    break; // do not add a module to the result string (delete current module)
                }
            }

            if  (params.at(1) == "UNASSIGNED") // production p8
            {
                // local constraints
                string updatedParams = this.localConstraints(params.at(0));
                temp_L_string += "I:" + updatedParams + ";";
                break;
            }
            else // production p9
            {
                break; // do not add a module to the result string (delete current module)
            }

            break;

        default:
            // add same module = do nothing
            temp_L_string += module;
            break;
        }
    }

    this.L_string = temp_L_string;
}
