#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

/*
 * Enum class representing the colors of a standard Rubik's cube.
 */
enum Color
{
    YELLOW = 0,
    BLUE = 1,
    ORANGE = 2,
    GREEN = 3,
    RED = 4,
    WHITE = 5
};

/*
 * Struct representing a generic cell, with color and number (initial position) properties.
 */
struct Cell
{
    // Cell constructor. Sets the unique identifying properties of this cell.
    // @param c - color of this cell
    // @param n - number (initial position) of this cell
    Cell(Color c, int n) : color(c), number(n) {}

    // Color of this cell.
    Color color;

    // Number (denoting initial position) of this cell.
    int number;
};

/*
 * Struct representing a central cell, which doesn't need any properties beyond that of a generic cell.
 */
struct CentralCell : public Cell
{
    // Central cell constructor. Sets the unique identifying properties of this cell.
    // @param c - color of this cell
    // @param n - number (initial position) of this cell
    CentralCell(Color c, int n) : Cell(c, n) {}
};

/*
 * Struct representing a side cell, which has a color, number, and one adjacent cell on an adjacent face.
 */
struct SideCell : public Cell
{
    // Side cell constructor. Sets the unique identifying properties of this cell.
    // @param c - color of this cell
    // @param n - number (initial position) of this cell
    SideCell(Color c, int n) : Cell(c, n) {}

    // The cell adjacent to this cell.
    Cell* adj_cell;
};

/*
 * Struct representing a corner cell, which has a color, number, and two adjacent cells on two adjacent faces.
 */
struct CornerCell : public Cell
{
    // Corner cell constructor. Sets the unique identifying properties of this cell.
    // @param c - color of this cell
    // @param n - number (initial position) of this cell
    CornerCell(Color c, int n) : Cell(c, n) {}

    // Cell adjacent to this cell on the left (e.g. for a bottom right cell, a cell from the bottom face).
    Cell* left_cell;

    // Cell adjacent to this cell on the right (e.g. for a bottom right cell, a cell from the right face).
    Cell* right_cell;
};

/*
 * Struct representing the face of a standard Rubik's cube.
 */
struct Face
{
    // Constructor for a face. Sets its central color, adjacent faces, and initializes independent properties of each cell.
    // @param c - central color of this face
    // @param t - face adjacent to this face on the top
    // @param r - face adjacent to this face on the right
    // @param b - face adjacent to this face on the bottom
    // @param l - face adjacent to this face on the left
    Face(Color c, Face** t, Face** r, Face** b, Face** l);

    // Destructor for a face. Deletes all cell pointers created for this face.
    ~Face();

    // Populates adjacent cells for all cells on this face.
    // @param top_adj - indices of cells on the top face to set as adjacent for the top cells of this face
    // @param right_adj - indices of cells on the right face to set as adjacent for the right cells of this face
    // @param bottom_adj - indices of cells on the bottom face to set as adjacent for the bottom cells of this face
    // @param left_adj - indices of cells on the left face to set as adjacent for the left cells of this face
    void populate_adjacent(vector<int> top_adj, vector<int> right_adj, vector<int> bottom_adj, vector<int> left_adj);

    // Rotates this face right (clockwise), and updates cells on adjacent faces accordingly.
    void rotate_right();

    // Rotates this face left (counterclockwise), and updates cells on adjacent faces accordingly.
    void rotate_left();
    
    // Returns a string representation of a row of cells on this face (top, middle, or bottom). Used to assist in displaying the cube.
    string str_representation_of_row(size_t row_idx);

    // Helper function. Converts a color to its char representation for printing purposes.
    // Note that for simplicity's sake, the char representation of a color is the first letter of that color (i.e. YELLOW <-> 'Y', etc.)
    char color_to_char(Color color);

    // The color of the center cell of this face. Uniquely identifies this face.
    Color center_color;

    // Face adjacent to this face from the top.
    Face** top_face;

    // Face adjacent to this face from the right.
    Face** right_face;

    // Face adjacent to this face from the bottom.
    Face** bottom_face;

    // Face adjacent to this face from the left.
    Face** left_face;

    // Top left cell of this face.
    CornerCell* top_left;

    // Top center cell of this face.
    SideCell* top;

    // Top right cell of this face.
    CornerCell* top_right;

    // Left center cell of this face.
    SideCell* left;

    // Center cell of this face.
    CentralCell* center;

    // Right center cell of this face.
    SideCell* right;

    // Bottom left cell of this face.
    CornerCell* bottom_left;

    // Bottom center cell of this face.
    SideCell* bottom;

    // Bottom right cell of this face.
    CornerCell* bottom_right;
    
    // Matrix of this face's cells.
    vector<vector<Cell*> > cells;
};

/*
 * Class representing a standard Rubik's cube with faces in the following configuration:
 *   Y
 * B O G R
 *   W
 */
class Cube
{
public:
    // Cube constructor. Initializes important properties of all faces in an initial (solved) configuration.
    Cube();

    // Cube destructor. Deletes all face pointers created for this game.
    ~Cube();

    // Rotates a face defined by its central color once in either the right (clockwise) or left (counterclockwise) direction.
    // @param color - color of face to rotate, determined by its central color
    // @param rotate_right - whether to rotate right (clockwise) or left (counterclockwise)
    void rotate(Color color, bool rotate_right);

    // Outputs a visual representation of the cube's current state.
    void display();

private:
    // Face with yellow as its central color.
    Face* yellow;

    // Face with blue as its central color.
    Face* blue;

    // Face with orange as its central color.
    Face* orange;

    // Face with green as its central color.
    Face* green;

    // Face with red as its central color.
    Face* red;

    // Face with white as its central color.
    Face* white;
};