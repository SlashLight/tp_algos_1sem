#include <iostream>
#include <array>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <math.h>

const int SideSize = 4;
const int FieldSize = SideSize * SideSize;
const std::array<char, FieldSize> FinalField( {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0} );



class GameState {
public:
    GameState( const std::array<char, FieldSize>& _field );

    bool CanMoveLeft() const;
    bool CanMoveUp() const;
    bool CanMoveRight() const;
    bool CanMoveDown() const;

    GameState MoveLeft() const;
    GameState MoveUp() const;
    GameState MoveRight() const;
    GameState MoveDown() const;

    bool IsFinish() const;

    char GetFieldValue( size_t pos ) const { return field[pos];}
    size_t GetFieldHeuristic( ) const { return heuristics; }
    size_t GetNumOfMinMoves( ) const { return numOfMinMoves; }
    void CalcHeuristic() { calcHeuristics(); }

    bool operator == (const GameState& state) const { return field == state.field; }
    bool operator != (const GameState& state) const { return !(*this == state); }

    size_t numOfMinMoves;
private:
    std::array<char, FieldSize> field;
    size_t zeroPos;
    size_t heuristics;

    void calcHeuristics() {
        heuristics = 0;
        for (int i = 0; i < FieldSize; i++) {
            if (i == zeroPos) continue;
            int value_1 = static_cast<int>(fabs(i - field[i] + 1)) % SideSize;
            int value_2 = static_cast<int>(fabs(i - field[i] + 1)) / SideSize;
            // result += value_1 + value_2;
            heuristics += (value_1 + value_2) * (value_1 + value_2) * 10;
        }



        /*for (int i = 0; i < FieldSize; ++i) {
            heuristics += std::abs( field[i] / SideSize - i / SideSize ) + std::abs( field[i] % SideSize - i % SideSize );
        }*/

        if ( !(field[FieldSize - 1] == FieldSize - 1 || field[FieldSize - 1] == FieldSize - SideSize) ) {
            heuristics += 2;
        }
    }
};

GameState::GameState(const std::array<char, FieldSize> &_field) :
    field(_field),
    zeroPos(-1),
    heuristics(0),
    numOfMinMoves(0)
{
    for (int i = 0; i < field.size(); ++i) {
        if ( field[i] == 0 ) {
            zeroPos = i;
            break;
        }
    }
}

bool GameState::CanMoveLeft() const {
    return zeroPos % SideSize < SideSize - 1;
}

bool GameState::CanMoveUp() const {
    return zeroPos < FieldSize - SideSize;
}

bool GameState::CanMoveRight() const {
    return zeroPos % SideSize > 0;
}

bool GameState::CanMoveDown() const {
    return zeroPos >= SideSize;
}

GameState GameState::MoveLeft() const {
    GameState newState( *this );
    std::swap( newState.field[zeroPos], newState.field[zeroPos + 1] );
    ++newState.zeroPos;
    newState.calcHeuristics();
    return newState;
}

GameState GameState::MoveUp() const {
    GameState newState( *this );
    std::swap( newState.field[zeroPos], newState.field[zeroPos + SideSize] );
    newState.zeroPos += SideSize;
    newState.calcHeuristics();
    return newState;
}

GameState GameState::MoveRight() const {
    GameState newState( *this );
    std::swap( newState.field[zeroPos], newState.field[zeroPos - 1] );
    --newState.zeroPos;
    newState.calcHeuristics();
    return newState;
}

GameState GameState::MoveDown() const {
    GameState newState( *this );
    std::swap( newState.field[zeroPos], newState.field[zeroPos - SideSize] );
    newState.zeroPos -= SideSize;
    newState.calcHeuristics();
    return newState;
}

bool GameState::IsFinish() const {
    return field == FinalField;
}

struct StateHasher {
    size_t operator()( const GameState& state ) const {
        size_t hash = 0;
        size_t p = 137;
        for (int i = 0; i < FieldSize; ++i) {
            hash += state.GetFieldValue( i ) * p;
        }
        return hash;
    }
};

struct Comparator {
    bool operator() (const GameState& state1, const GameState& state2) const {
        if (state1.GetFieldHeuristic() == state2.GetFieldHeuristic()) {
            return state1.GetNumOfMinMoves() < state2.GetNumOfMinMoves();
        }
        return state1.GetFieldHeuristic() < state2.GetFieldHeuristic();
    }
};

std::string GetSolution( GameState& state ) {
    state.CalcHeuristic();
    std::set<GameState, Comparator> bfsQueue;
    bfsQueue.insert( state );
    std::unordered_map<GameState, char, StateHasher> visited;
    visited[state] = 'S';
    while( !bfsQueue.empty() ) {
        GameState current = *bfsQueue.begin();
        bfsQueue.erase(bfsQueue.begin());
        if (current.IsFinish()) {
            break;
        }

        if( current.CanMoveLeft() ) {
            GameState newState = current.MoveLeft();
            if( visited.find( newState ) == visited.end() ) {
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert( newState );
                visited[newState] = 'L';
            } else if (newState.numOfMinMoves > current.numOfMinMoves + 1) {
                bfsQueue.erase(newState);
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert(newState);
                visited[newState] = 'L';
            }
        }

        if( current.CanMoveUp() ) {
            GameState newState = current.MoveUp();
            if( visited.find( newState ) == visited.end() ) {
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert( newState );
                visited[newState] = 'U';
            } else if (newState.numOfMinMoves > current.numOfMinMoves + 1) {
                bfsQueue.erase(newState);
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert(newState);
                visited[newState] = 'U';
            }
        }

        if( current.CanMoveRight() ) {
            GameState newState = current.MoveRight();
            if( visited.find( newState ) == visited.end() ) {
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert( newState );
                visited[newState] = 'R';
            } else if (newState.numOfMinMoves > current.numOfMinMoves + 1) {
                bfsQueue.erase(newState);
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert(newState);
                visited[newState] = 'R';
            }
        }

        if( current.CanMoveDown() ) {
            GameState newState = current.MoveDown();
            if( visited.find( newState ) == visited.end() ) {
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert( newState );
                visited[newState] = 'D';
            } else if (newState.numOfMinMoves > current.numOfMinMoves + 1) {
                bfsQueue.erase(newState);
                newState.numOfMinMoves = current.numOfMinMoves + 1;
                bfsQueue.insert(newState);
                visited[newState] = 'D';
            }
        }

    }

    std::string result;
    GameState current( FinalField );
    char move = visited[current];
    while( move != 'S' ) {
        result += move;
        switch ( move ) {
            case 'L':
                current = current.MoveRight();
                break;
            case 'U':
                current = current.MoveDown();
                break;
            case 'R':
                current = current.MoveLeft();
                break;
            case 'D':
                current = current.MoveUp();
                break;
            default:
                break;
        }
        move = visited[current];
    }
    std::reverse( result.begin(), result.end() );
    return result;

}

/* std::ostream& operator << (std::ostream& out, const GameState& state) {
    for( size_t y = 0; y < SideSize; ++y ) {
        for (size_t x = 0; x < SideSize; ++x) {
            out << static_cast<int>(state.GetFieldValue( y * SideSize + x )) << " ";
        }
        out << std::endl;
    }
    out << std::endl;
    return out;
} */

int main() {
    std::array<char, FieldSize> inputField{};
    for (int i = 0; i < FieldSize; ++i) {
        int value;
        std::cin >> value;
        inputField[i] = value;
    }
    GameState state( inputField );
    std::string result = GetSolution( state );
    std::cout << result.length() << std::endl << result;

}


