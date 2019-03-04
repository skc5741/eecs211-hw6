#include "model.h"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    // TODO: initialize `next_moves_` to `turn_`'s available moves
    compute_next_moves_();
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
    std::cout << pos.x << ", " << pos.y << " passed into play_move" << std::endl;
    if (is_game_over())
        throw Client_logic_error("Model::play_move: game over");

    Move const* movep = find_move(pos);
    if (!movep) {}
        //throw Client_logic_error("Model::play_move: no such move");

    // TODO: actually execute the move, advance the turn, refill
    // `next_moves_`, etc.
    else
        really_play_move_(*movep);
}

//
// BELOW ARE *OPTIONAL* HELPER FUNCTIONS
//

Position_set Model::find_flips_(Position current, Dimensions dir) const
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    Position_set flips;
    size_t index = 1;
    current = current + (index*dir);
    for(;;) {
        if(!board_.good_position(current) || board_[current] == Player::neither)
            return {};
        else if(board_[current] == other_player(turn_)) {
            flips[current] = true;
            index++;
            current = current + (index * dir);
        }
        else if(board_[current] == turn_)
            return flips;
    }
}

Position_set Model::evaluate_position_(Position pos) const
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    Position_set flips;
    for(Dimensions dir : Board::all_directions()) {
        flips |= find_flips_(pos, dir);
    }
    return flips;
}

void Model::compute_next_moves_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    next_moves_.clear();
    Rectangle avail_positions;
    if (turn_count < 4) {
        avail_positions = Rectangle::from_top_left({3, 3}, {2, 2});
        for(Position pos : avail_positions) {
            Position_set pset;
            if(board_[pos] == Player::neither) {
                next_moves_[pos] = pset;
            }
        }
    }
    else {
        stdcout << ""
        avail_positions = board_.all_positions();
        for(Position pos : avail_positions) {
            Position_set pset = evaluate_position_(pos);
            if(!pset.empty()) {
                next_moves_[pos] = pset;
            }
        }
    }


}

bool Model::advance_turn_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    turn_ = other_player(turn_);
    turn_count++;
    compute_next_moves_();
    return !next_moves_.empty();
}

void Model::set_game_over_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    turn_ = Player::neither;
    int num_spaces = board_.all_positions().width * board_.all_positions().height;
    if(board_.count_player(Player::dark) > ((double)num_spaces)/2) {
        winner_ = Player::dark;
    }
    else if(board_.count_player(Player::light) > ((double)num_spaces)/2) {
        winner_ = Player::light;
    }
    else {
        winner_ = Player::neither;
    }
}

void Model::really_play_move_(Move move)
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    board_[move.first] = turn_;
    board_[move.second] = turn_;
    advance_turn_();
}


