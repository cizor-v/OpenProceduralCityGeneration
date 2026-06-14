#include "L_system.h"

L_system::L_system(std::string popDensityMap)
{
    //constructor
    this->popDensity_map_path = popDensityMap;
    // this->L_string = ""; // Axiom with initial road parameters
}

L_system::~L_system()
{
    //dtor
}

// delete road module
void L_system::prod1(std::vector<module> * output)
{
    ; // deletion
}

// initialize parameters
void L_system::prod2(std::vector<module> * output, roadAttributes roadAttr, ruleAttributes ruleAttr)
{
    module turn, forward, branch1, branch2, road, query;

    turn.eType = moduleType::turn;
    forward.eType = moduleType::forward;
    turn.sRoadAttrib = forward.sRoadAttrib = roadAttr;

    output->push_back(turn);
    output->push_back(forward);

    std::vector<module> globals = this->globalGoals(roadAttr, ruleAttr);

    branch1.eType = branch2.eType = moduleType::branch;

    branch1.iDel = globals.at(1).iDel;
    branch1.sRoadAttrib = globals.at(1).sRoadAttrib;
    branch1.sRuleAttrib = globals.at(1).sRuleAttrib;

    branch2.iDel = globals.at(2).iDel;
    branch2.sRoadAttrib = globals.at(2).sRoadAttrib;
    branch2.sRuleAttrib = globals.at(2).sRuleAttrib;

    road.eType = moduleType::road;
    road.iDel = globals.at(0).iDel;
    road.sRuleAttrib = globals.at(0).sRuleAttrib;

    query.eType = moduleType::query;
    query.eState = state::UNASSIGNED;
    query.sRoadAttrib = globals.at(0).sRoadAttrib;

    output->push_back(branch1);
    output->push_back(branch2);
    output->push_back(road);
    output->push_back(query);
}

// delete road module
void L_system::prod3(std::vector<module> * output)
{
    ; // deletion
}

// decrement branch module's del
void L_system::prod4(std::vector<module> * output, module input)
{
    input.iDel -= 1;
    output->push_back(input);
}

// branching
void L_system::prod5(std::vector<module> * output, module input)
{
    module road, query;

    road.eType = moduleType::road;
    road.iDel = input.iDel;
    road.sRuleAttrib = input.sRuleAttrib;

    query.eType = moduleType::query;
    query.eState = state::UNASSIGNED;
    query.sRoadAttrib = input.sRoadAttrib;

    road.fPosX = query.fPosX = input.fPosX;
    road.fPosY = query.fPosY = input.fPosY;

    output->push_back(road);
    output->push_back(query);
}

// delete branch module
void L_system::prod6(std::vector<module> * output)
{
    ; // deletion
}

// delete query module
void L_system::prod7(std::vector<module> * output)
{
    ; // deletion
}

// adjust parameters
void L_system::prod8(std::vector<module> * output, module input)
{
    std::pair<state, roadAttributes> locals = localConstraints(input.sRoadAttrib);

    input.eState = locals.first;
    input.sRoadAttrib = locals.second;

    output->push_back(input);
}

// delete query module
void L_system::prod9(std::vector<module> * output)
{
    ; // deletion
}

std::vector<module> globalGoals(roadAttributes roadAttr, ruleAttributes ruleAttr)
{
    ;
}

std::pair<state, roadAttributes> localConstraints(roadAttributes roadAttr)
{
    ;
}


// std::vector<std::string> L_system::splitString(std::string str, char delimiter)
// {
//     std::vector<std::string> modules;
//     std::string module;
//     std::stringstream ss = std::stringstream(str);

//     for (std::string module; std::getline(ss, module, delimiter);)
//     {
//         modules.push_back(module);
//     }

//     return modules;
// }

// std::vector<std::vector<std::string>> L_system::globalGoals(std::string ruleAttr, std::string roadAttr) // create parameters for pDel[0-2], pRuleAttr[0-2], pRoadAttr[0-2]
// {
//     // retrieve attribute values
//     std::vector<std::string> vec_roadAttr = splitString(roadAttr, ' ');
//     std::vector<std::string> vec_ruleAttr = splitString(ruleAttr, ' ');
//     float angle, length, posx, posy, dirx, diry;
//     // road attributes
//     angle = std::stof(vec_roadAttr.at(0));
//     length = std::stof(vec_roadAttr.at(1));
//     bool isHighway = vec_roadAttr.at(2) == "TRUE";
//     //rule attributes
//     posx = std::stof(vec_ruleAttr.at(0));
//     posy = std::stof(vec_ruleAttr.at(1));
//     dirx = std::stof(vec_ruleAttr.at(2));
//     diry = std::stof(vec_ruleAttr.at(3));

//     if (isHighway) // highway
//     {
//         ;
//     }
//     else // street
//     {
//         ;
//     }

// }

// std::string L_system::localConstraints(std::string roadAttr)
// {
//     // adjust parameters for state, roadAttr
// }

// void L_system::iterate()
// {
//     std::string temp_L_string = "";

//     // remove square brackets
//     std::string str = this->L_string;
//     str.erase(remove(str.begin(), str.end(), "["), str.end());
//     str.erase(remove(str.begin(), str.end(), "]"), str.end());

//     // split L_string into its constituent modules
//     std::vector<std::string> modules = splitString(str, ';');

//     for (int i = 0; i < modules.size(); i++)
//     {
//         std::string module = modules.at(i);
//         // apply production rules
//         switch(module[0])
//         {
//         // productions p1, p2, p3
//         case 'R':
//             std::vector<std::string> params = splitString(splitString(module, ':').at(1), ',');

//             // production p1
//             if (std::stoi(params.at(0)) < 0)
//             {
//                 break; // do not add a module to the result string (delete current module)
//             }

//             if (i+1 < modules.size())
//             {
//                 std::string nextModule = modules.at(i+1);
//                 if (nextModule[0] == 'I')
//                 {
//                     //production p2
//                     std::string state = splitString(splitString(nextModule, ':').at(1), ';').at[1];
//                     if (state == "SUCCEED")
//                     {
//                         // global goals

//                         // newParams:
//                         // 0 : pDel[0-2]
//                         // 1 : pRuleAttr[0-2]
//                         // 2 : pRoadAttr[0-2]
//                         std::string I_roadAttr = splitString(splitString(nextModule, ":").at(1), ",").at(0);
//                         std::vector<std::vector<std::string>> newParams = this->globalGoals(params.at(1), I_roadAttr);
//                         temp_L_string += "+(" + splitString(I_roadAttr, " ").at(0)+ ");"; // turn right by roadAttr.angle
//                         temp_L_string += "F(" + splitString(I_roadAttr, " ").at(1) + ");"; // go forward by roadAttr.length
//                         temp_L_string += "B(" + newParams.at(0).at(1) + "," + newParams.at(1).at(1) + "," + newParams.at(2).at(1) + ");";
//                         temp_L_string += "B(" + newParams.at(0).at(2) + "," + newParams.at(1).at(2) + "," + newParams.at(2).at(2) + ");";
//                         temp_L_string += "R(" + newParams.at(0).at(0) + "," + newParams.at(1).at(0) + ");";
//                         temp_L_string += "I(" + newParams.at(2).at(0) + ",UNASSIGNED);";
//                         break;
//                     }

//                     //production p3
//                     if (state == "FAILED")
//                     {
//                         break; // do not add a module to the result string (delete current module)
//                     }
//                 }
//             }
//             break;

//         // productions p4, p5, p6
//         case "B":
//             std::vector<std::string> params = splitString(splitString(module, ":").at(1), ",");

//             // production p4
//             if (std::stoi(params.at(0)) > 0)
//             {
//                 // add B module with same params except del is decremented by 1
//                 temp_L_string += "B:" + std::stoi(params.at[0])-1 + "," + params.at(1) + "," + params.at(2) + ";";
//                 break;
//             }

//             // production p5
//             if (std::stoi(params.at(0)) == 0)
//             {
//                 // add branch with R and I modules
//                 temp_L_string += "[" +
//                                                     "R:" + params.at(0) + "," + params.at(1) + ";" +
//                                                     "I:" + params.at(2) + "," + "UNASSIGNED" + ";" +
//                                             "]";
//                 break;
//             }

//             //production p6
//             if (std::stoi(params.at(0)) < 0)
//             {
//                 break; // do not add a module to the result string (delete current module)
//             }

//             break;

//         // productions p7, p8, p9
//         case "I":
//             std::vector<std::string> params = splitString(splitString(module, ":").at(1), ",");

//             // production p7
//             if (i != 0)
//             {
//                 std::string delPrev = splitString(splitString(modules.at(i-1), ":").at(1), ",").at[0];
//                 if (std::stoi(delPrev) < 0)
//                 {
//                     break; // do not add a module to the result string (delete current module)
//                 }
//             }

//             if  (params.at(1) == "UNASSIGNED") // production p8
//             {
//                 // local constraints
//                 std::string updatedParams = this->localConstraints(params.at(0));
//                 temp_L_string += "I:" + updatedParams + ";";
//                 break;
//             }
//             else // production p9
//             {
//                 break; // do not add a module to the result string (delete current module)
//             }

//             break;

//         default:
//             // add same module = do nothing
//             temp_L_string += module;
//             break;
//         }
//     }

//     this->L_string = temp_L_string;
// }
