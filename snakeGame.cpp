#include<iostream>
using namespace std;
char ** createField(int length, int width);
void playGame(char **twoDArr, int length, int width);
int main()
{
    int rows, cols;
    cout<<"Enter the number of rows: "<<endl;
    cin>>rows;
    cout<<"Enter the number of columns: "<<endl;
    cin>>cols;
    char ** twoDArr = createField(cols, rows); // storing the created list into a double pointer
    playGame(twoDArr, cols, rows);
    for (int i = 0; i<rows; i++) // printing the list after play game function is called
    {
        for (int j = 0; j<cols; j++)
        {
            cout<<twoDArr[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i = 0; i<rows; i++) // deallocating memory of the 2d char array
    {
        delete [] twoDArr[i];
    }
    delete [] twoDArr;
    return 0;
}
char ** createField(int length, int width) // width = rows, length = cols
{
    int obstacles, x, y;
    char comma;
    char ** twoDArr = new char*[width]; // dynamically allocating the rows
    for (int i = 0; i < width; i++)
    {
        twoDArr[i] = new char[length]; // dynamically allocating the columns
    }
    for (int i = 0; i<width; i++) // i = rows, j = cols, these for loops are creating the walls and periods
    {
        for (int j = 0; j < length; j++)
        {
            if (i == 0 || i == width-1)
            {
                twoDArr[i][j] = 'W';
            }
            else
            {
                if (j == 0)
                {
                    twoDArr[i][j] = 'W';
                }
                else if (j >= 1 && j <= (length-2))
                {
                    twoDArr[i][j] = '.';
                }
                else
                {
                    twoDArr[i][j] = 'W';
                }
            }
        }
    }
    cout<<"Enter the number of obstacles: "<<endl;
    cin>>obstacles;
    if (obstacles != 0) // gathering locations of obstacles
    {
        cout<<"Enter the locations of the obstacles: "<<endl;
        for (int i = 0; i < obstacles; i++)
        {
            cin>>x>>comma>>y; // comma is a junk char
            twoDArr[x][y] = 'O';
        }
    }
    return twoDArr;
}
void playGame(char **twoDArr, int length, int width)
{
    int x, y, t, directionNum, X = 0, Y = 0;
    char comma, directionChar;
    bool obstacle = false, gameEnd = false;
    cout<<"Enter the location of the gate: "<<endl;
    cin>>x>>comma>>y;
    twoDArr[x][y] = 'G'; // placing the gate
    cout<<"Enter the number of turns: "<<endl;
    cin>>t;
    while (gameEnd == false)
    {
        if (t != 0) // put this here just in case turns = 0
        {
            cout<<"Enter the turns: "<<endl;
            for (int a = 0; a < t; a++)
            {
                cin>>directionChar>>directionNum;
                if (directionChar == 'D') // each of these if statements checking the directionChar are the same, so comments on this apply to all of these
                {
                    for (int i = 0; i<width; i++)
                    {
                        for (int j = 0; j<length; j++)
                        {
                            if (j == y && i<x+directionNum+1 && i > x) // navigates the for loops and figures out the possible spots of going down
                            {
                                if (twoDArr[i][j] == 'O' || twoDArr[i][j] == 'W') // skipping the turn if the position of the S we are trying to place is already an O
                                {
                                    obstacle = true;
                                }
                                else if (twoDArr[i][j] == 'S') // ends the game when the position of the S we are trying to place is already an S
                                {
                                    gameEnd = true;
                                }
                                else if (obstacle == false && gameEnd == false) // only places the S character if there are no obstacles and the game hasn't ended, gameEnd keeps it from continuing to place S's after it has hit itself
                                {
                                    twoDArr[i][j] = 'S';
                                    X = i; // captures the last position of x so that we can do the next turn according to where the S ends up
                                    Y = j; // captures the last position of y so that we can do the next turn according to where the S ends up
                                }
                            }
                        }
                    }
                    obstacle = false; // resetting obstacle to false so we can assume the next turn doesn't hit obstacles yet
                    x = X; // this does essentially the same thing as above when X = i and Y = j but i couldn't update it up there because it would continue to update and give me inaccurate results
                    y = Y;
                }
                if (directionChar == 'U')
                {
                    for (int i = width-1; i > 0; i--)
                    {
                        for (int j = length-1; j>0; j--)
                        {
                            if (j == y && i < x && i > x-directionNum-1)
                            {
                                if (twoDArr[i][j] == 'O' || twoDArr[i][j] == 'W')
                                {
                                    obstacle = true;
                                }
                                else if (twoDArr[i][j] == 'S')
                                {
                                    gameEnd = true;
                                }
                                else if (obstacle == false && gameEnd == false)
                                {
                                    twoDArr[i][j] = 'S';
                                    X = i;
                                    Y = j;
                                }
                            }
                        }
                    }
                    obstacle = false;
                    x = X;
                    y = Y;
                }
                if (directionChar == 'R')
                {
                    for (int i = 0; i<width; i++)
                    {
                        for (int j = 0; j<length; j++)
                        {
                            if (i == x && j > y && j<directionNum+y+1)
                            {
                                if (twoDArr[i][j] == 'O' || twoDArr[i][j] == 'W')
                                {
                                    obstacle = true;
                                }
                                else if (twoDArr[i][j] == 'S')
                                {
                                    gameEnd = true;
                                }
                                else if (obstacle == false && gameEnd == false)
                                {
                                    twoDArr[i][j] = 'S';
                                    X = i;
                                    Y = j;
                                }
                            }
                        }
                    }
                    obstacle = false;
                    x = X;
                    y = Y;
                }
                if (directionChar == 'L')
                {
                    for (int i = width-1; i > 0; i--)
                    {
                        for (int j = length-1; j>0; j--)
                        {
                            if (i == x && j < y && j>y-directionNum-1)
                            {
                                if (twoDArr[i][j] == 'O' || twoDArr[i][j] == 'W')
                                {
                                    obstacle = true;
                                }
                                else if (twoDArr[i][j] == 'S')
                                {
                                    gameEnd = true;
                                }
                                else if (obstacle == false && gameEnd == false)
                                {
                                    twoDArr[i][j] = 'S';
                                    X = i;
                                    Y = j;
                                }
                            }
                        }
                    }
                    obstacle = false;
                    x = X;
                    y = Y;
                }
            }
        }
        gameEnd = true; // makes gameEnd true and ends the loop, here turns will be done.
    }
}