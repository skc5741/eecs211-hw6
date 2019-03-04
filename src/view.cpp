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

    // Initialize better background
    set.add_sprite(background_sprite, {0,0}, 0);

    for(int x = 0; x < model_.board().width; x++) {
        for(int y = 0; y < model_.board().height; y++) {

            // Initialize board spaces
            ge211::Rectangle rec;
            rec.x = x * (space_dim + spacing) + spacing;
            rec.y = y * (space_dim + spacing) + spacing;

            set.add_sprite(space_sprite_, {rec.x, rec.y}, 1);

            // Initialize board pieces
            if(model_[{x, y}] != Player::neither) {
                ge211::Rectangle rec;
                rec.x = x * (space_dim + spacing) + spacing + (space_dim/2 - piece_rad);
                rec.y = y * (space_dim + spacing) + spacing + (space_dim/2 - piece_rad);

                if (model_[{x, y}] == Player::light)
                    set.add_sprite(light_sprite_, {rec.x, rec.y}, 2);
                else if (model_[{x, y}] == Player::dark)
                    set.add_sprite(dark_sprite_, {rec.x, rec.y}, 2);
            }

            // Initialze move markers
            if (model_.find_move({x,y})) {
                ge211::Rectangle rec;
                rec.x = x * (space_dim + spacing) + spacing + (space_dim/2 - marker_rad);
                rec.y = y * (space_dim + spacing) + spacing + (space_dim/2 - marker_rad);

                set.add_sprite(marker_sprite_, {rec.x, rec.y}, 3);
            }
        }
    }

    // Initialize mouse piece
    mouse_pos = mouse_pos.left_by(piece_rad);
    mouse_pos = mouse_pos.up_by(piece_rad);
    if (model_.turn() == Player::light)
        set.add_sprite(light_sprite_, mouse_pos, 4);
    else if (model_.turn() == Player::dark)
        set.add_sprite(light_sprite_, mouse_pos, 4);
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    //return grid_size * model_.board().dimensions();

    return { model_.board().dimensions().width * (space_dim + spacing) + spacing,
             model_.board().dimensions().height * (space_dim + spacing) + spacing };
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}

ge211::Position View::pos_to_grid(ge211::Position pos) const {
    return { (pos.x - spacing) / (space_dim + spacing),
             (pos.y - spacing) / (space_dim + spacing)};
}

