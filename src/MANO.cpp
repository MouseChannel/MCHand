#include "MANO.hpp"

#include <sstream>
#include <string>
#include "left_faces.h"
#include "right_faces.h"

namespace mchand
{
    std::vector<std::pair<int, int>> MANO::skeleton
    {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {0, 5},
        {5, 6},
        {6, 7},
        {7, 8},
        {0, 9},
        {9, 10},
        {10, 11},
        {11, 12},
        {0, 13},
        {13, 14},
        {14, 15},
        {15, 16},
        {0, 17}, {17, 18}, {18, 19}, {19, 20}
    };

    std::vector<std::vector<int>> MANO::rhand_faces;
    std::vector<std::vector<int>> MANO::lhand_faces;

    std::vector<std::vector<int>> split(const std::string& s, char delimiter)
    {
        std::vector<std::vector<int>> tokens;
        std::istringstream tokenStream(s);
        std::string token;

        while (std::getline(tokenStream, token, delimiter))
        {
            std::vector<int> temp;
            std::istringstream singletokenStream(token);
            std::string single_token;
            while (std::getline(singletokenStream, single_token, ' '))
            {
                temp.push_back(std::stoi(single_token));
            }
            tokens.push_back(temp);
        }

        return tokens;
    }

    void MANO::Init()
    {
        rhand_faces = split((const char*)right_faces_txt, '\n');
        lhand_faces = split((const char*)left_faces_txt, '\n');
       
        // rhand_faces
    }
}
