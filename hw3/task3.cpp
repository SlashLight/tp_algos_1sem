#include <iostream>
#include <array>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

const int SideSize = 5;
const int FieldSize = SideSize * SideSize;
const std::array<char, FieldSize> FinalField( {1, 2, 3, 4, 5, 6, 7, 8, 0} );



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

    bool operator == (const GameState& state) const { return field == state.field; }
    bool operator != (const GameState& state) const { return !(*this == state); }
private:
    std::array<char, FieldSize> field;
    size_t zeroPos;
};

GameState::GameState(const std::array<char, FieldSize> &_field) :
    field(_field),
    zeroPos(-1)
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
    return newState;
}

GameState GameState::MoveUp() const {
    GameState newState( *this );
    std::swap( newState.field[zeroPos], newState.field[zeroPos + SideSize] );
    newState.zeroPos += SideSize;
    return newState;
}

GameState GameState::MoveRight() const {
    GameState newState( *this );
    std::swap( newState.field[zeroPos], newState.field[zeroPos - 1] );
    --newState.zeroPos;
    return newState;
}

GameState GameState::MoveDown() const {
    GameState newState( *this );
    std::swap( newState.field[zeroPos], newState.field[zeroPos - SideSize] );
    newState.zeroPos -= SideSize;
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
            p *= 137;
        }
    }
};

std::string GetSolution( const GameState& state ) {
    std::queue<GameState> bfsQueue;
    bfsQueue.push( state );
    std::unordered_map<GameState, char> visited;
    visited[state] = 'S';
    while( !bfsQueue.empty() ) {
        GameState current = bfsQueue.front();
        bfsQueue.pop();
        if (current.IsFinish()) {
            break;
        }

        if( current.CanMoveLeft() ) {
            GameState newState = current.MoveLeft();
            if( visited.find( newState ) == visited.end() ) {
                bfsQueue.push( newState );
                visited[newState] = 'L';
            }
        }

        if( current.CanMoveUp() ) {
            GameState newState = current.MoveUp();
            if( visited.find( newState ) == visited.end() ) {
                bfsQueue.push( newState );
                visited[newState] = 'U';
            }
        }

        if( current.CanMoveRight() ) {
            GameState newState = current.MoveRight();
            if( visited.find( newState ) == visited.end() ) {
                bfsQueue.push( newState );
                visited[newState] = 'R';
            }
        }

        if( current.CanMoveDown() ) {
            GameState newState = current.MoveDown();
            if( visited.find( newState ) == visited.end() ) {
                bfsQueue.push( newState );
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

std::ostream& operator << (std::ostream& out, const GameState& state) {
    for( size_t y = 0; y < SideSize, ++y ) {
        for (size_t x = 0; x < SideSize; ++x) {
            out << static_cast<int>(state.GetFieldValue( y * SideSize + x )) << " ";
        }
        out << std::endl;
    }
    out << std::endl;
}


