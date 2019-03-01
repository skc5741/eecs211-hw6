#include "model.h"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    // TODO: initialize `next_moves_` to `turn_`'s available moves
}

Rectangle Model::board() const
{
    return board_.all_positions();
}

Player Model::operator[](Position pos) const
{
    return board_[pos];
}

Move const* Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end())
        return nullptr;
    else
        return &*i;
}

void Model::play_move(Position pos)
{
    if (is_game_over())
        throw Client_logic_error("Model::play_move: game over");

    Move const* movep = find_move(pos);
    if (!movep)
        throw Client_logic_error("Model::play_move: no such move");

    // TODO: actually execute the move, advance the turn, refill
    // `next_moves_`, etc.
}

//
// BELOW ARE *OPTIONAL* HELPER FUNCTIONS
//

Position_set Model::find_flips_(Position current, Dimensions dir) const
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    return {};
}

Position_set Model::evaluate_position_(Position pos) const
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    return {};
}

void Model::compute_next_moves_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
}

bool Model::advance_turn_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    return false;
}

void Model::set_game_over_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
}

void Model::really_play_move_(Move move)
{
    // TODO OR NOT TODO: OPTIONAL HELPER
}


