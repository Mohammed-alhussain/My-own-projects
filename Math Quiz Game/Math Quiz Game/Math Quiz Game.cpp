#include <iostream>
#include <string>
#include <math.h>
#include <windows.h>
using namespace std;

enum enOpretorType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, mix = 4 };


struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    int CrrectAnswe = 0;
    int PlayerAnswer = 0;
    enOpretorType OpretorType;
    enQuestionLevel QuestionLevel;
    bool AnserResult = false;

};

struct stQuizz
{
    stQuestion QuestionList[100];
    int NumQuestions = 0;
    enQuestionLevel QuestionyLevel;
    enOpretorType OpretorType;
    int RightResults = 0;
    int WrongResults = 0;
    bool isPass = false;
};

int RandomNumber(int From, int To)
{
    int Number = rand() % (To - From + 1) + From;
    return Number;
}

int HowManyQuestions()
{
    int Num = 0;

    cout << "How many Questions do you want to answer ? ";
    cin >> Num;
    return Num;
}
enOpretorType ReadOpretorType()
{
    int Num = 0;
    do
    {

        cout << "Enter Operatoin Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> Num;
    } while (Num < 1 || Num>5);
    return (enOpretorType)Num;
}
enQuestionLevel ReadQuestionLevel()
{
    int Num = 0;
    do
    {

        cout << "Enter Questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Num;
    } while (Num < 1 || Num>4);
    return (enQuestionLevel)Num;
}

int SimpleCalculate(int Number1, int  Number2, enOpretorType Opretor)
{
    switch (Opretor)
    {
    case Add:

        return Number1 + Number2;
        break;

    case Sub:

        return Number1 - Number2;
        break;

    case Mul:

        return Number1 * Number2;
        break;

    case Div:

        return Number1 / Number2;
        break;

    default:
        return -12212345;
        break;
    }
}


string PrintQuestionLevel(enQuestionLevel DfficultyLevel)
{
    string arr[4] = { "Easy" ," Med" , "Hard" , "Mix" };
    return arr[DfficultyLevel - 1];
}

string PrintOpretorType(enOpretorType OpretorType)
{
    string arr[5] = { "Add ", "Sub" , "Mul", "Div" , "Mix" };
    return arr[OpretorType - 1];
}

string ShowFinalResults(bool isPass)
{

    if (isPass)
    {
        return " PASS :-) ";
    }
    else
    {
        return " is  Fail :-(";
    }
}

void ShowResultsQuestions(stQuizz ResultAnswer)
{
    cout << "\n_______________________________\n";
    cout << "Final Results is " << ShowFinalResults(ResultAnswer.isPass);
    cout << "\n_______________________________\n\n";

    cout << "\nNumber of Questions :" << ResultAnswer.NumQuestions;
    cout << "\nQuestions Level :" << PrintQuestionLevel(ResultAnswer.QuestionyLevel);
    cout << "\nOpType :" << PrintOpretorType(ResultAnswer.OpretorType);
    cout << "\nNumber of Right Answers :" << ResultAnswer.RightResults;
    cout << "\nNumber of Wrong Answers :" << ResultAnswer.WrongResults;
    cout << "\n_______________________________\n\n";
}


stQuestion GenerateQuestions(enOpretorType OpType, enQuestionLevel QuestionLevel)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::mix)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);

    if (OpType == enOpretorType::Mix)
        OpType = (enOpretorType)RandomNumber(1, 4);


    Question.OpretorType = OpType;

    switch (QuestionLevel)
    {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CrrectAnswe = SimpleCalculate(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

        break;
    case Med:
        Question.Number1 = RandomNumber(10, 30);
        Question.Number2 = RandomNumber(10, 30);

        Question.CrrectAnswe = SimpleCalculate(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

        break;
    case Hard:
        Question.Number1 = RandomNumber(30, 100);
        Question.Number2 = RandomNumber(30, 100);

        Question.CrrectAnswe = SimpleCalculate(Question.Number1, Question.Number2, OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

        break;
    default:
        cout << "there is probmmem in 'GenerateQuestion()' funciton";
        break;
    }
}

void prepareQuestioList(stQuizz& Quizz)
{
    for (short NumberQuestion = 1; NumberQuestion <= Quizz.NumQuestions; NumberQuestion++)
        Quizz.QuestionList[NumberQuestion] = GenerateQuestions(Quizz.OpretorType, Quizz.QuestionyLevel);
}

string GetOpTypeSymbol(enOpretorType OpretorType)
{
    switch (OpretorType)
    {
    case Add:
        return "+";
        break;
    case Sub:
        return "-";

        break;
    case Mul:
        return "x";

        break;
    case Div:
        return "/";

        break;

    default:
        cout << "Wrong in 'GetOpTypeSymbol' fonction";
        break;
    }
}

void PrintQuestion(stQuestion Question)
{
    cout << endl << Question.Number1 << endl;
    cout << Question.Number2 << " " << GetOpTypeSymbol(Question.OpretorType) << endl;
    cout << "________________ \n";
}

int InputUser()
{
    int a = 0;
    cin >> a;
    return a;
}

void ChickAnswers(stQuizz& Quizz, int NumberQuestion)
{
    if (Quizz.QuestionList[NumberQuestion].PlayerAnswer == Quizz.QuestionList[NumberQuestion].CrrectAnswe)
    {
        cout << "Right Answer :-)";
        Quizz.RightResults++;
        Quizz.QuestionList[NumberQuestion].AnserResult = true;
    }
    else
    {
        cout << "Wrong Answer :-(\n";
        cout << "The right answer is " << Quizz.QuestionList[NumberQuestion].CrrectAnswe;
        Quizz.WrongResults++;
        Quizz.QuestionList[NumberQuestion].AnserResult = false;
    }
}

void showColorScreen(bool Right)
{
    if (Right)
        system("color 2F"); // Color Green

    else
        system("color 4F"); // Color Red

}

void AskAndCreestQuestioList(stQuizz& Quizz)
{
    for (int NumberQuestion = 1; NumberQuestion <= Quizz.NumQuestions; NumberQuestion++)
    {
        PrintQuestion(Quizz.QuestionList[NumberQuestion]);
        Quizz.QuestionList[NumberQuestion].PlayerAnswer = InputUser();

        ChickAnswers(Quizz, NumberQuestion);

        showColorScreen(Quizz.QuestionList[NumberQuestion].AnserResult);
    }
    Quizz.isPass = (Quizz.RightResults >= Quizz.WrongResults);
}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumQuestions = HowManyQuestions();
    Quizz.OpretorType = ReadOpretorType();
    Quizz.QuestionyLevel = ReadQuestionLevel();

    prepareQuestioList(Quizz);
    AskAndCreestQuestioList(Quizz);
    ShowResultsQuestions(Quizz);
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
        PlayMathGame();

        cout << "Do you want to play agin? (Y/N)? \n";
        cin >> agin;
    } while (agin == 'Y' || agin == 'y');
}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    system("color 2F"); // Color Green

    cout << endl;
    return 0;
}