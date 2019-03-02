#pragma once

#include "model.h"
#include "view.h"

// The main game class for Reversi.
class Controller : public ge211::Abstract_game
{
public:
    // Constructs a game with `size` as both its width and height.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if `size` is less than 2
    //    or greater than 8.
    explicit Controller(int size = 8);

    // Constructs a game with the given width and height.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if either dimension is less
    //    than 2 or greater than 8.
    Controller(int width, int height);

// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //

    // TODO: Add any input handlers you need, e.g.:
    //  - on_mouse_up for mouse clicks,
    //  - on_mouse_move for mouse tracking, or
    //  - on_frame for animation (?).

    void on_mouse_up(ge211::Mouse_button button, ge211::Position position)
    {
        // check if valid, perform swap
    }

    void on_mouse_move(ge211::Mouse_button button, ge211::Position position)
    {
        mouse_posn = position;
        if(button == ge211::Mouse_button::left) {
            model_.play_move(position);
        }
    }

    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model            model_;
    View             view_;

    // TODO: Add any UI state you need, e.g.:
    //  - the position of the mouse, or
    //  - the position of a keyboard-controller cursor.

    ge211::Position  mouse_posn;
};
