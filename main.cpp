#include "rubiks_cube.h"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    Cube cube;
    cube.display();
    std::string rotate_command;
    while (std::getline(std::cin, rotate_command))
    {
        if (rotate_command == std::string("END GAME"))
        {
            return 0;
        }
        char color_char;
        char right_or_left;
        sscanf(rotate_command.c_str(), "%c %c", &color_char, &right_or_left);
        Color turn_face;
        switch (color_char)
        {
            case 'Y':
                turn_face = Color::YELLOW;
                break;
            case 'B':
                turn_face = Color::BLUE;
                break;
            case 'O':
                turn_face = Color::ORANGE;
                break;
            case 'G':
                turn_face = Color::GREEN;
                break;
            case 'R':
                turn_face = Color::RED;
                break;
            case 'W':
                turn_face = Color::WHITE;
                break;
            default:
                break;
        }
        if (right_or_left == 'R')
        {
            cube.rotate(turn_face, true);
        }
        else if (right_or_left == 'L')
        {
            cube.rotate(turn_face, false);
        }
        cube.display();
    }
    return 0;
}