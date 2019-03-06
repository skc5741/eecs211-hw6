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
    if (is_game_over())
        throw Client_logic_error("Model::play_move: game over");

    Move const* movep = find_move(pos);
    if (!movep)
        throw Client_logic_error("Model::play_move: no such move");

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
    Position temp = current;
    Position_set flips;
    temp = temp + dir;
    for(;;) {
        if(!board_.good_position(temp) || board_[temp] == Player::neither) {
            return {};
        }
        else if(board_[temp] == other_player(turn_)) {
            flips[temp] = true;
            temp = temp + dir;
        }
        else if(board_[temp] == turn_) {
            return flips;
        }
        else
            throw Client_logic_error("Infinite loop, dumbass");
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

    int mid_x = board_.dimensions().width/2-1;
    int mid_y = board_.dimensions().height/2-1;

    if (board_[{mid_x, mid_y}] == Player::neither ||
        board_[{mid_x+1, mid_y}] == Player::neither ||
        board_[{mid_x, mid_y+1}] == Player::neither ||
        board_[{mid_x+1, mid_y+1}] == Player::neither) {

        avail_positions = Rectangle::from_top_left
                ({board_.dimensions().width/2-1,
                  board_.dimensions().height/2-1},
                 {2, 2});;

        for(Position pos : avail_positions) {
            Position_set pset;
            pset[pos] = true;
            if(board_[pos] == Player::neither) {
                next_moves_[pos] = pset;
            }
        }
    }
    else {
        avail_positions = board_.all_positions();
        for(Position pos : avail_positions) {
            if(board_[pos] == Player::neither) {
                Position_set pset = evaluate_position_(pos);
                if (!pset.empty()) {
                    next_moves_[pos] = pset;
                }
            }
        }
    }
}

bool Model::advance_turn_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    turn_ = other_player(turn_);
    compute_next_moves_();
    return !next_moves_.empty();
}

void Model::set_game_over_()
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    turn_ = Player::neither;
    if(board_.count_player(Player::dark)
        > board_.count_player(Player::light))
        winner_ = Player::dark;
    else if(board_.count_player(Player::dark)
            < board_.count_player(Player::light))
        winner_ = Player::light;
    else
        winner_ = Player::neither;
}

void Model::really_play_move_(Move move)
{
    // TODO OR NOT TODO: OPTIONAL HELPER
    board_[move.first] = turn_;
    board_[move.second] = turn_;
    if(!advance_turn_())
        set_game_over_();
}