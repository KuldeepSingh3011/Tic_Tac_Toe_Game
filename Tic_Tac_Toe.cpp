#include<iostream>
#include<vector>
using namespace std;

// 'x' represent the player(Human) and 'o' represent the opponent(Computer)
char player ='x';
char opponent = 'o';

// Structure to store the move on the board
struct Move{
    int row;
    int col;
};

// This function will returns true if their are moves remaining on the board
bool isMovesLeft(vector<vector<char> > &board){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == '_')
                return true;
        }
    }
    return false;
}

// This function will print the current state of board.
void printBoard(vector<vector<char> > &board){
    cout<<"Current board state is as follows:-\n";
    for(int i=0;i<board.size();i++){
       cout<<board[i][0]<<" | "<<board[i][1]<<" | "<<board[i][2]<<" | \n";
    }
}

// This function will evaluate the current state of board and returns a +ve value if Maximizer(Human) is winning
// returns a -ve value if Minimizer(computer) is winning and it will returns 0 if game is going for a draw.
int evaluateCurState(vector<vector<char> > &board,int depth){
    for(int i=0;i<board.size();i++){
        if((board[i][0] == board[i][1])&&(board[i][1] == board[i][2])){
            if(board[i][0] == player)
            return (100-depth);
            else if(board[i][0] == opponent)
            return (-100+depth);
        }
        if((board[0][i] == board[1][i])&&(board[1][i] == board[2][i])){
            if(board[0][i] == player)
            return (100-depth);
            else if(board[0][i] == opponent)
            return (-100+depth);
        }
    }
    if((board[0][0] == board[1][1])&&(board[1][1] == board[2][2])){
        if(board[0][0] == player)
        return (100-depth);
        else if(board[0][0] == opponent)
        return (-100+depth);
    }
    if((board[0][2] == board[1][1])&&(board[1][1] == board[2][0])){
        if(board[0][2] == player)
        return (100-depth);
        else if(board[0][2] == opponent)
        return (-100+depth);
    }
    return 0;
}

bool isValidMove(Move &m,vector<vector<char> > &board){
    if((m.row>2)||(m.row<0)||(m.col>2)||(m.col<0))
    return false;
    if(board[m.row][m.col] != '_')
    return false;
    return true;
}
//This function will consider all the choices available and returns the most optimal  value of the board. 
int miniMax(vector<vector<char> > &board,int depth,bool isMax){
    int Val = evaluateCurState(board,depth);
    if((Val>0)||(Val<0))
    return Val;
    if(isMovesLeft(board)==false)
    return 0;
    if (isMax)
    {
        int bestVal = -1000;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = player;

                    // Call minimax recursively and choose
                    // the maximum value
                    bestVal = max( bestVal,miniMax(board, depth+1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return bestVal;
    }

    // If this minimizer's move
    else
    {
        int bestVal = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = opponent;

                    // Call minimax recursively and choose
                    // the minimum value
                    bestVal = min(bestVal,miniMax(board,depth+1,!isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return bestVal;
    }
}

//This function will find the best possible move available for Computer program to win against human.
Move  findBestMove(vector<vector<char> > &board){
    Move m;
    m.row = -1;
    m.col = -1;
    int bestVal = 1000;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == '_'){
                board[i][j] = opponent;
                int Val = miniMax(board,0,true);
                board[i][j] = '_';
                if(Val<bestVal)
                {
                    bestVal = Val;
                    m.row = i;
                    m.col = j;
                }
            }
        }
    }
    return m;
}

int main(){
    vector<vector<char> > board(3,vector<char>(3));
    int winner = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        board[i][j] = '_';
    }
    cout<<"Welcome to Tic-Tac-Toe game:\n";
    cout<<"You are playing against computer so play wisely:\n";
    cout<<"Assume that board has rows and column starting from 1 and ending at 3.\n";
    cout<<"Human moves: 'x' \t Computer moves:'o'\n";
    while(isMovesLeft(board)){
        printBoard(board);
        Move m1;
        cout<<"Enter the row and column where you want to move\n";
        cin>>m1.row>>m1.col;
        m1.row--; m1.col--;
        while(isValidMove(m1,board)==false)
        {
            cout<<"Invalid row or column.\n";
            cout<<"Please,enter row and column again:";
            cin>>m1.row>>m1.col;
            m1.row--;
            m1.col--;
        }
        board[m1.row][m1.col] = 'x';
        printBoard(board);
        if(evaluateCurState(board,0)>0){
            winner = 1;
            break;
        }
        if(isMovesLeft(board)){
            Move m2 = findBestMove(board);
            board[m2.row][m2.col] = 'o';
            printBoard(board);
            if(evaluateCurState(board,0)<0){
                winner = 2;
                break;
            }
        }

    }
    if(winner == 0){
        cout<<"Game Draw:\n";
    }
    else if(winner == 1){
        cout<<"Human Wins over Computer.\n";
    }
    else{
        cout<<"Computer Wins over human brain.\n";
    }
}
