#include <iostream>
#include <string>
#include <math.h>
#include <windows.h>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stGameInfo {
    short GameRounds;
    short Player1Win;
    short ComputerWin;
    short Draw;
    enWinner WinnerGame;
    string WinnerName;
};

struct stRoundInfo {
    enGameChoice Player1;
    enGameChoice Computer;
    enWinner WinnerRound;
};

enGameChoice Player1Choice()
{
    short Choice = 1;

    do
    {
        cout << "Your Choice: Stone[1], Paper[2], Sessoirce[3]? ";
        cin >> Choice;
    } while (Choice < 1 || Choice>3);

    return (enGameChoice)Choice;
}


int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enGameChoice ComputerChoice()
{
    return enGameChoice(RandomNumber(1, 3));
}

short HowManyRounds()
{
    short a = 1;
    do
    {
        cout << "How Many Rounds do you want? (1 to 10) ";
        cin >> a;
    } while (a < 1 || a> 10);
    return a;
}

enWinner CompireItems(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1 == RoundInfo.Computer)
        return enWinner::Draw;

    if (RoundInfo.Computer == Stone && RoundInfo.Player1 == Scissors)
        return enWinner::Computer;

    if (RoundInfo.Computer == enGameChoice::Paper && RoundInfo.Player1 == enGameChoice::Stone)
        return Computer;

    if (RoundInfo.Computer == enGameChoice::Scissors && RoundInfo.Player1 == enGameChoice::Paper)
        return Computer;

    return Player1;
}

string PrintChoice(enGameChoice Choice)
{
    string arrGameChocie[3] = { "Stone" , "Paper" , "Scissors" };
    return arrGameChocie[Choice - 1];
}

string PrintWinner(enWinner Winner)
{
    string arrGameChocie[3] = { "Player1" , "Computer" , "Draw" };
    return arrGameChocie[Winner - 1];
}

void ShowResultRound(stRoundInfo RoundInfo)
{
    cout << "\n_________________________________________\n";
    cout << "\nPlayer1 choice         :" << PrintChoice(RoundInfo.Player1);
    cout << "\nComputer choice choice :" << PrintChoice(RoundInfo.Computer);
    cout << "\nThe winner             :" << PrintWinner(RoundInfo.WinnerRound);
    cout << "\n_________________________________________\n\n";
}

enWinner CompireManyWins(stGameInfo GameInfo)
{
    if (GameInfo.ComputerWin == GameInfo.Player1Win)
        return Draw;
    else if (GameInfo.ComputerWin > GameInfo.Player1Win)
        return Computer;
    else
        return Player1;
}

stGameInfo PlayGame()
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    short GameRound = 0;
    GameRound = HowManyRounds();
    for (int i = 1; i <= GameRound; i++)
    {
        cout << "\n\nRound [" << i << "] begin\n";
        RoundInfo.Player1 = Player1Choice();
        RoundInfo.Computer = ComputerChoice();
        RoundInfo.WinnerRound = CompireItems(RoundInfo);
        ShowResultRound(RoundInfo);

        if (RoundInfo.WinnerRound == Player1)
        {
            system("color 2F");
            Player1WinTimes++;
        }

        else if (RoundInfo.WinnerRound == Computer)
        {
            system("color 4F");
            ComputerWinTimes++;
        }

        else
        {
            system("color 6F");
            DrawTimes++;
        }

    }

    stGameInfo GameInfo;

    GameInfo.GameRounds = GameRound;
    GameInfo.Player1Win = Player1WinTimes;
    GameInfo.ComputerWin = ComputerWinTimes;
    GameInfo.Draw = DrawTimes;
    GameInfo.WinnerGame = CompireManyWins(GameInfo);
    GameInfo.WinnerName = PrintWinner(GameInfo.WinnerGame);

    return GameInfo;
}

string Tabs(short Num)
{
    string t = "";
    for (short i = 1; i <= Num; i++)
    {
        t = t + "\t";
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinallGameResults(stGameInfo GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << "\t\t" << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1Win << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWin << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.Draw << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}


void StartGame()
{
    char agin = 'y';

    do
    {
        ResetScreen();
        stGameInfo GameResults = PlayGame();;
        ShowGameOverScreen();
        ShowFinallGameResults(GameResults);


        cout << "Do you want to play agin? (Y/N)? ";
        cin >> agin;
    } while (agin == 'Y' || agin == 'y');

}



int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    //cout << Tabs(9) << "hsdfs  i";
    //system("color 6F");
    cout << endl;
    return 0;
}