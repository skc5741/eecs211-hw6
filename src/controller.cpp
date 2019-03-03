#include "controller.h"

using namespace ge211;

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
        , mouse_posn(model_.board().width,model_.board().height)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites, mouse_posn);
}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position position)
{
    // check if valid, perform swap
    if(model_[position] == Player::neither)
    model_.play_move(position);
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