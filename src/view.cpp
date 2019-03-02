#include "view.h"

using namespace ge211;

// You can change this or even determine it some other way:
static int const grid_size = 36;

View::View(Model const& model)
        : model_(model)
        // You may want to add sprite initialization here
{ }

void View::draw(Sprite_set& set, ge211::Position pos)
{
    // TODO, PROBABLY
    for(size_t x = 0; x < model_.board().width; x++) {
        for(size_t y = 0; y < model_.board().height; y++) {
            ge211::Rectangle rec;
            rec.width = space_dim;
            rec.height = space_dim;
            rec.x = x * (space_dim + spacing) + spacing;
            rec.y = y * (space_dim + spacing) + spacing;

            set.add_sprite(space_sprite_, {rec.x, rec.y});
        }
    }

    //for(size_t index; index < ) {

    //}
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}


