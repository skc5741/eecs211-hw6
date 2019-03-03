#pragma once

#include "model.h"
#include "board.h"
#include "player.h"

#include <string>

ge211::Color const space_color    {0, 245, 0};
ge211::Color const white_color  {245, 245, 245};
ge211::Color const black_color   {10, 10, 10};
ge211::Color const star_color    {245, 0, 0};

class View
{
public:
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, ge211::Position pos);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_;

    int space_dim = 32;
    int piece_rad = 12;
    int spacing = 3;

    // TODO: Add any private members you need, such as sprites
    ge211::Rectangle_sprite    const    // Dimensions, color
            space_sprite_    {{ space_dim, space_dim }, space_color};
    ge211::Circle_sprite    const       // Radius, color
            light_sprite_    { piece_rad,  white_color};
    ge211::Circle_sprite    const       // Radius, color
            dark_sprite_    { piece_rad,  black_color};
};

