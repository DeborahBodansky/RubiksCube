#include "rubiks_cube.h"
#include <vector>
#include <iostream>

Face::Face(Color c, Face** t, Face** r, Face** b, Face** l)
    : center_color(c)
    , top_face(t)
    , right_face(r)
    , bottom_face(b)
    , left_face(l)
    , top_left(new CornerCell(c, 1))
    , top(new SideCell(c, 2))
    , top_right(new CornerCell(c, 3))
    , left(new SideCell(c, 4))
    , center(new CentralCell(c, 5))
    , right(new SideCell(c, 6))
    , bottom_left(new CornerCell(c, 7))
    , bottom(new SideCell(c, 8))
    , bottom_right(new CornerCell(c, 9))
{
    vector<Cell*> top_row;
    top_row.push_back(top_left);
    top_row.push_back(top);
    top_row.push_back(top_right);

    vector<Cell*> middle_row;
    middle_row.push_back(left);
    middle_row.push_back(center);
    middle_row.push_back(right);

    vector<Cell*> bottom_row;
    bottom_row.push_back(bottom_left);
    bottom_row.push_back(bottom);
    bottom_row.push_back(bottom_right);

    cells.push_back(top_row);
    cells.push_back(middle_row);
    cells.push_back(bottom_row);
}

Face::~Face()
{
  delete top_left;
  delete top;
  delete top_right;
  delete left;
  delete center;
  delete right;
  delete bottom_left;
  delete bottom;
  delete bottom_right;
}

void Face::populate_adjacent(vector<int> top_adj
                            , vector<int> right_adj
                            , vector<int> bottom_adj
                            , vector<int> left_adj)
{
    top_left->left_cell = (*top_face)->cells[top_adj[0] / 3][top_adj[0] % 3];
    top->adj_cell = (*top_face)->cells[top_adj[1] / 3][top_adj[1] % 3];
    top_right->right_cell = (*top_face)->cells[top_adj[2] / 3][top_adj[2] % 3];

    top_right->left_cell = (*right_face)->cells[right_adj[0] / 3][right_adj[0] % 3];
    right->adj_cell = (*right_face)->cells[right_adj[1] / 3][right_adj[1] % 3];
    bottom_right->right_cell = (*right_face)->cells[right_adj[2] / 3][right_adj[2] % 3];

    bottom_right->left_cell = (*bottom_face)->cells[bottom_adj[0] / 3][bottom_adj[0] % 3];
    bottom->adj_cell = (*bottom_face)->cells[bottom_adj[1] / 3][bottom_adj[1] % 3];
    bottom_left->right_cell = (*bottom_face)->cells[bottom_adj[2] / 3][bottom_adj[2] % 3];

    bottom_left->left_cell = (*left_face)->cells[left_adj[0] / 3][left_adj[0] % 3];
    left->adj_cell = (*left_face)->cells[left_adj[1] / 3][left_adj[1] % 3];
    top_left->right_cell = (*left_face)->cells[left_adj[2] / 3][left_adj[2] % 3];
}

void Face::rotate_right()
{
    CornerCell corner_temp = *top_left;
    *top_left = *bottom_left;
    *bottom_left = *bottom_right;
    *bottom_right = *top_right;
    *top_right = corner_temp;

    SideCell side_temp = *top;
    *top = *left;
    *left = *bottom;
    *bottom = *right;
    *right = side_temp;

    Cell adj_temp = *top_left->left_cell;
    *top_left->left_cell = *bottom_left->left_cell;
    *bottom_left->left_cell = *bottom_right->left_cell;
    *bottom_right->left_cell = *top_right->left_cell;
    *top_right->left_cell = adj_temp;

    adj_temp = *top->adj_cell;
    *top->adj_cell = *left->adj_cell;
    *left->adj_cell = *bottom->adj_cell;
    *bottom->adj_cell = *right->adj_cell;
    *right->adj_cell = adj_temp;

    adj_temp = *top_left->right_cell;
    *top_left->right_cell = *bottom_left->right_cell;
    *bottom_left->right_cell = *bottom_right->right_cell;
    *bottom_right->right_cell = *top_right->right_cell;
    *top_right->right_cell = adj_temp;
}

void Face::rotate_left()
{
    CornerCell corner_temp = *top_left;
    *top_left = *top_right;
    *top_right = *bottom_right;
    *bottom_right = *bottom_left;
    *bottom_left = corner_temp;

    SideCell side_temp = *top;
    *top = *right;
    *right = *bottom;
    *bottom = *left;
    *left = side_temp;

    Cell adj_temp = *top_left->left_cell;
    *top_left->left_cell = *top_right->left_cell;
    *top_right->left_cell = *bottom_right->left_cell;
    *bottom_right->left_cell = *bottom_left->left_cell;
    *bottom_left->left_cell = adj_temp;

    adj_temp = *top->adj_cell;
    *top->adj_cell = *right->adj_cell;
    *right->adj_cell = *bottom->adj_cell;
    *bottom->adj_cell = *left->adj_cell;
    *left->adj_cell = adj_temp;

    adj_temp = *top_left->right_cell;
    *top_left->right_cell = *top_right->right_cell;
    *top_right->right_cell = *bottom_right->right_cell;
    *bottom_right->right_cell = *bottom_left->right_cell;
    *bottom_left->right_cell = adj_temp;
}

string Face::str_representation_of_row(size_t row_idx)
{
  string row_str = "";
  vector<Cell*> row = cells[row_idx];
  for (size_t i = 0; i < row.size(); i++)
  {
    row_str += color_to_char(row[i]->color) + to_string(row[i]->number) + string(" ");
    if (i < 2)
    {
      row_str += string(" ");
    }
  }
  return row_str;
}

char Face::color_to_char(Color color)
{
  char to_return = ' ';
  switch (color)
  {
    case Color::YELLOW:
      to_return = 'Y';
      break;
    case Color::BLUE:
      to_return = 'B';
      break;
    case Color::ORANGE:
      to_return = 'O';
      break;
    case Color::GREEN:
      to_return = 'G';
      break;
    case Color::RED:
      to_return = 'R';
      break;
    case Color::WHITE:
      to_return = 'W';
      break;
    default:
      break;
  }
  return to_return;
}

Cube::Cube()
    : yellow(new Face(Color::YELLOW, &red, &green, &orange, &blue))
    , blue(new Face(Color::BLUE, &yellow, &orange, &white, &red))
    , orange(new Face(Color::ORANGE, &yellow, &green, &white, &blue))
    , green(new Face(Color::GREEN, &yellow, &red, &white, &orange))
    , red(new Face(Color::RED, &yellow, &blue, &white, &green))
    , white(new Face(Color::WHITE, &orange, &green, &red, &blue))
{
    vector<int> top_indices;
    top_indices.push_back(2);
    top_indices.push_back(1);
    top_indices.push_back(0);

    vector<int> right_indices;
    right_indices.push_back(8);
    right_indices.push_back(5);
    right_indices.push_back(2);

    vector<int> bottom_indices;
    bottom_indices.push_back(6);
    bottom_indices.push_back(7);
    bottom_indices.push_back(8);

    vector<int> left_indices;
    left_indices.push_back(0);
    left_indices.push_back(3);
    left_indices.push_back(6);
    
    yellow->populate_adjacent(top_indices, top_indices, top_indices, top_indices);
    blue->populate_adjacent(left_indices, left_indices, left_indices, right_indices);
    orange->populate_adjacent(bottom_indices, left_indices, top_indices, right_indices);
    green->populate_adjacent(right_indices, left_indices, right_indices, right_indices);
    red->populate_adjacent(top_indices, left_indices, bottom_indices, right_indices);
    white->populate_adjacent(bottom_indices, bottom_indices, bottom_indices, bottom_indices);
}

Cube::~Cube()
{
  delete yellow;
  delete blue;
  delete orange;
  delete green;
  delete red;
  delete white;
}

void Cube::rotate(Color color, bool rotate_right)
{
    Face* to_rotate;
    switch (color)
    {
        case Color::YELLOW:
            to_rotate = yellow;
            break;
        case Color::BLUE:
            to_rotate = blue;
            break;
        case Color::ORANGE:
            to_rotate = orange;
            break;
        case Color::GREEN:
            to_rotate = green;
            break;
        case Color::RED:
            to_rotate = red;
            break;
        case Color::WHITE:
            to_rotate = red;
            break;
        default:
            break;
    }
    if (rotate_right)
    {
        to_rotate->rotate_right();
    }
    else
    {
        to_rotate->rotate_left();
    }
}

void Cube::display()
{
    cout << "             +------------+" << endl;

    for (size_t i = 0; i < 3; i++)
    {
      cout << "             | " << yellow->str_representation_of_row(i) << "|" << endl;
      if (i < 2)
      {
        cout << "             |            |" << endl;
      }
    }

    cout << "+------------+------------+------------+------------+" << endl;
    for (size_t i = 0; i < 3; i++)
    {
      cout << "| " << blue->str_representation_of_row(i) << "| " << orange->str_representation_of_row(i) << "| ";
      cout << green->str_representation_of_row(i) << "| " << red->str_representation_of_row(i) << "|" << endl;
      if (i < 2)
      {
        cout << "|            |            |            |            |" << endl;
      }
    }
    cout << "+------------+------------+------------+------------+" << endl;

    for (size_t i = 0; i < 3; i++)
    {
      cout << "             | " << white->str_representation_of_row(i) << "|" << endl;
      if (i < 2)
      {
        cout << "             |            |" << endl;
      }
    }

    cout << "             +------------+" << endl;
}