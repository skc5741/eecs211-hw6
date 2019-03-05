#include "controller.h"

using namespace ge211;

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
        , mouse_posn(-100,-100)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites, mouse_posn);
}

void Controller::on_mouse_down(ge211::Mouse_button, ge211::Position position)
{
    // check if valid, perform swap
    ge211::Position grid_pos = view_.pos_to_grid(position);
    if(model_[grid_pos] == Player::neither && model_.find_move(grid_pos)
        != nullptr && !model_.is_game_over())
        model_.play_move(grid_pos);
}

void Controller::on_mouse_move(ge211::Position position)
{
    mouse_posn = position;
}


Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}