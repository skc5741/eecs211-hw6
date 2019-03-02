#include "controller.h"

using namespace ge211;

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
        , mouse_posn(0,0)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites, mouse_posn);
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}