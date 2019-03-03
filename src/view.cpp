#include "view.h"

using namespace ge211;

// You can change this or even determine it some other way:
static int const grid_size = 36;

View::View(Model const& model)
        : model_(model)
        // You may want to add sprite initialization here
{ }

void View::draw(Sprite_set& set, ge211::Position mouse_pos)
{
    // TODO, PROBABLY

    // Initialize board spaces
    for(int x = 0; x < model_.board().width; x++) {
        for(int y = 0; y < model_.board().height; y++) {
            ge211::Rectangle rec;
            rec.x = x * (space_dim + spacing) + spacing;
            rec.y = y * (space_dim + spacing) + spacing;

            set.add_sprite(space_sprite_, {rec.x, rec.y}, 0);
        }
    }

    // Initialize board pieces
    for(int x = 0; x < model_.board().width; x++) {
        for(int y = 0; y < model_.board().height; y++) {
            if(model_[{x, y}] != Player::neither) {
                ge211::Rectangle rec;
                rec.x = x * (space_dim + spacing) + spacing + (space_dim - piece_rad);
                rec.y = y * (space_dim + spacing) + spacing + (space_dim - piece_rad);

                if (model_[{x, y}] == Player::light)
                    set.add_sprite(light_sprite_, {rec.x, rec.y}, 1);
                else if (model_[{x, y}] == Player::dark)
                    set.add_sprite(dark_sprite_, {rec.x, rec.y}, 1);
            }
        }
    }

    // Initialize mouse piece
    mouse_pos = mouse_pos.left_by(piece_rad);
    mouse_pos = mouse_pos.up_by(piece_rad);
    if (model_.turn() == Player::light)
        set.add_sprite(light_sprite_, mouse_pos, 2);
    else if (model_.turn() == Player::dark)
        set.add_sprite(dark_sprite_, mouse_pos, 2);
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    //return grid_size * model_.board().dimensions();

    return { model_.board().dimensions().width * (space_dim + spacing) + spacing
             , model_.board().dimensions().height * (space_dim + spacing) + spacing };
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}


