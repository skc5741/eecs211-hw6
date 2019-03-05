#include "model.h"
#include <catch.h>

using namespace ge211;

struct Test_access {
    Model &m_;
    Board &board() {return m_.board_;}
    Position_set find_flips(Position start, Dimensions dir) {return m_.find_flips_(start, dir);}
    Position_set evaluate_position(Position pos) {return m_.evaluate_position_(pos);}
    Move_map next_moves() {return m_.next_moves_;}
    void compute_next_moves() {m_.compute_next_moves_();}
    bool advance_turn() {return m_.advance_turn_();}
    void set_game_over() {m_.set_game_over_();}
    void play_move(Position pos) {m_.play_move(pos);}
    void really_play_move(Move m) {m_.really_play_move_(m);}
    Move const* find_move(Position pos) {m_.find_move(pos);}
};


// These pass with the starter code and should continue
// to pass.
TEST_CASE("Passes with starter code")
{
    Model m(8, 8);
    CHECK( m.board() == Rectangle{0, 0, 8, 8} );
    CHECK_FALSE( m.is_game_over() );
    CHECK( m.turn() == Player::dark );
    CHECK( m.winner() == Player::neither );
    CHECK( m[{0, 0}] == Player::neither );
    CHECK( m.find_move({0, 0}) == nullptr );
    CHECK_THROWS_AS( m.play_move({0, 0}), Client_logic_error );
}

// This fails with the starter code, but should pass.
TEST_CASE("Fails with starter code")
{
    Model m(6);
    CHECK( m.find_move({2, 2}) );
}

// This fails with the starter code, but should pass.
TEST_CASE("Throws with starter code")
{
    Model m(4);
    m.play_move({1, 1});
}

TEST_CASE("Test constructor") {
    Model m1(8);
    Test_access t1{m1};

    CHECK(t1.board().dimensions().width == 8);
    CHECK(t1.board().dimensions().height == 8);

    CHECK(t1.next_moves()[{3,3}][{3,3}] == true);
    CHECK(t1.next_moves()[{3,4}][{3,4}] == true);
    CHECK(t1.next_moves()[{4,3}][{4,3}] == true);
    CHECK(t1.next_moves()[{4,4}][{4,4}] == true);

    CHECK(t1.next_moves()[{2,2}][{2,2}] == false);
    CHECK(t1.next_moves()[{2,5}][{2,5}] == false);
    CHECK(t1.next_moves()[{5,2}][{5,2}] == false);
    CHECK(t1.next_moves()[{5,5}][{5,5}] == false);

    CHECK(m1.turn() == Player::dark);

    Model m2(5,4);
    Test_access t2{m2};

    CHECK(t2.board().dimensions().width == 5);
    CHECK(t2.board().dimensions().height == 4);
    CHECK(t2.next_moves()[{1,1}][{1,1}] == true);
    CHECK(t2.next_moves()[{1,2}][{1,2}] == true);
    CHECK(t2.next_moves()[{2,1}][{2,1}] == true);
    CHECK(t2.next_moves()[{2,2}][{2,2}] == true);

    CHECK(t2.next_moves()[{0,0}][{0,0}] == false);
    CHECK(t2.next_moves()[{0,3}][{0,3}] == false);
    CHECK(t2.next_moves()[{3,0}][{3,0}] == false);
    CHECK(t2.next_moves()[{3,3}][{3,3}] == false);

    CHECK(m1.turn() == Player::dark);
}

TEST_CASE("Test starting four placement: also testing compute_next_moves, play_move") {
    Model m1(8);
    Test_access t1{m1};

    CHECK(t1.next_moves()[{3,3}][{3,3}] == true);
    CHECK(t1.next_moves()[{3,4}][{3,4}] == true);
    CHECK(t1.next_moves()[{4,3}][{4,3}] == true);
    CHECK(t1.next_moves()[{4,4}][{4,4}] == true);

    t1.compute_next_moves();
    CHECK(t1.next_moves().size() == 4);

    t1.play_move({3,3});
    CHECK(t1.next_moves()[{3,3}][{3,3}] == false);
    CHECK(t1.next_moves().size() == 3);

    t1.play_move({4,3});
    CHECK(t1.next_moves()[{4,3}][{4,3}] == false);
    CHECK(t1.next_moves().size() == 2);

    t1.play_move({4,4});
    CHECK(t1.next_moves()[{4,4}][{4,4}] == false);
    CHECK(t1.next_moves().size() == 1);

    t1.play_move({3,4});
    CHECK(t1.next_moves()[{3,4}][{3,4}] == false);
    CHECK(t1.next_moves().size() == 4);

    CHECK(m1.turn() == Player::dark);

    CHECK(t1.next_moves()[{4,2}][{4,3}] == true);
    CHECK(t1.next_moves()[{5,3}][{4,3}] == true);
    CHECK(t1.next_moves()[{2,4}][{3,4}] == true);
    CHECK(t1.next_moves()[{3,5}][{3,4}] == true);
}

TEST_CASE("Test find_flips") {
    Model m1(8);
    Test_access t1{m1};
    t1.compute_next_moves();
    t1.play_move({3,3});
    t1.play_move({4,3});
    t1.play_move({4,4});
    t1.play_move({3,4});

    CHECK(!t1.find_flips({4,2}, {0,1}).empty());
    CHECK(t1.find_flips({4,2}, {-1,-1}).empty());
    CHECK(t1.find_flips({4,2}, {0,-1}).empty());
    CHECK(t1.find_flips({4,2}, {1,-1}).empty());
    CHECK(t1.find_flips({4,2}, {1,0}).empty());
    CHECK(t1.find_flips({4,2}, {1,1}).empty());
    CHECK(t1.find_flips({4,2}, {-1,0}).empty());
    CHECK(t1.find_flips({4,2}, {-1,1}).empty());

    CHECK(t1.find_flips({2,4}, {0,1}).empty());
    CHECK(t1.find_flips({2,4}, {-1,-1}).empty());
    CHECK(t1.find_flips({2,4}, {0,-1}).empty());
    CHECK(t1.find_flips({2,4}, {1,-1}).empty());
    CHECK(!t1.find_flips({2,4}, {1,0}).empty());
    CHECK(t1.find_flips({2,4}, {1,1}).empty());
    CHECK(t1.find_flips({2,4}, {-1,0}).empty());
    CHECK(t1.find_flips({2,4}, {-1,1}).empty());
}

TEST_CASE("Test evaluate_position") {
    Model m1(8);
    Test_access t1{m1};
    t1.compute_next_moves();
    t1.play_move({3,3});
    t1.play_move({4,3});
    t1.play_move({4,4});
    t1.play_move({3,4});

    CHECK(!t1.evaluate_position({4,2}).empty());
    CHECK(!t1.evaluate_position({5,3}).empty());
    CHECK(!t1.evaluate_position({2,4}).empty());
    CHECK(!t1.evaluate_position({3,5}).empty());

    CHECK(t1.evaluate_position({3,2}).empty());
    CHECK(t1.evaluate_position({2,2}).empty());
    CHECK(t1.evaluate_position({5,5}).empty());
    CHECK(t1.evaluate_position({0,0}).empty());
}

TEST_CASE("Test advance_turn()") {
    Model m1(8);
    Test_access t1{m1};
    t1.play_move({3,3});
    t1.play_move({4,3});
    t1.play_move({4,4});
    t1.play_move({3,4});
    t1.board()[{3,4}] = Player::dark;
    CHECK(t1.advance_turn());
    t1.board()[{4,3}] = Player::dark;
    CHECK(!t1.advance_turn());
}

TEST_CASE("Test set_game_over") {
    Model m1(8);
    Test_access t1{m1};

    CHECK(!m1.is_game_over());
    CHECK(m1.winner() == Player::neither);
    t1.set_game_over();
    CHECK(m1.is_game_over());
    CHECK(m1.winner() == Player::neither);

    Model m2(8);
    Test_access t2{m2};

    t2.play_move({3,3});
    t2.play_move({4,3});
    t2.play_move({4,4});
    t2.play_move({3,4});
    t2.play_move({3,5});

    CHECK(!m2.is_game_over());
    CHECK(m2.winner() == Player::neither);
    t2.set_game_over();
    CHECK(m2.is_game_over());
    CHECK(m2.winner() == Player::dark);
}

TEST_CASE("Test really_play_move") {
    Model m1(8);
    Test_access t1{m1};

    t1.play_move({3,3});
    t1.play_move({4,3});
    t1.play_move({4,4});
    t1.play_move({3,4});

    Move const* move = t1.find_move({3,3});
    t1.really_play_move(*move);
    CHECK(t1.board()[{3,3}] == Player::dark);
    CHECK(m1.turn() == Player::light);

    move = t1.find_move({4,3});
    t1.really_play_move(*move);
    CHECK(t1.board()[{4,3}] == Player::light);
    CHECK(m1.turn() == Player::dark);

    move = t1.find_move({4,4});
    t1.really_play_move(*move);
    CHECK(t1.board()[{4,4}] == Player::dark);
    CHECK(m1.turn() == Player::light);

    move = t1.find_move({3,4});
    t1.really_play_move(*move);
    CHECK(t1.board()[{3,4}] == Player::light);
    CHECK(m1.turn() == Player::dark);
}
