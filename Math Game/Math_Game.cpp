#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int CorrectAnswers = 0;
int IncorrectAnswers = 0;

int AskHowManyQuestions()
{
    int numberOfQuestions;
    cout << "How many questions do you want to answer? ";
    cin >> numberOfQuestions;
    return numberOfQuestions;
}

enum class enLevelOfQuestion
{
    Easy = 1,
    Medium = 2,
    Hard = 3,
    Mixed = 4
};

enLevelOfQuestion ChooseQuestionLevel()
{
    int level;
    cout << "Enter Question Level: [1]: Easy, [2]: Medium, [3]: Hard, [4]: Mixed\n";
    cin >> level;
    while (level < 1 || level > 4)
    {
        cout << "Invalid level. Please enter 1, 2, 3, or 4:\n";
        cin >> level;
    }
    return enLevelOfQuestion(level);
}

enum class enOperationType
{
    Addition = 1,
    Subtraction = 2,
    Multiplication = 3,
    Division = 4,
    Mixed = 5
};

enOperationType ChooseOperationType()
{
    int operationType;
    cout << "Choose Operation Type: [1]: Addition, [2]: Subtraction, [3]: Multiplication, [4]: Division, [5]: Mixed\n";
    cin >> operationType;
    while (operationType < 1 || operationType > 5)
    {
        cout << "Invalid operation type. Please enter 1, 2, 3, 4, or 5:\n";
        cin >> operationType;
    }
    return enOperationType(operationType);
}

enLevelOfQuestion chosenLevel;
enOperationType chosenOperation;

int RandomNumber(int From, int To)
{
    int RandNumber = rand() % (To - From + 1) + From;
    return RandNumber;
}

void PrintQuestion(float number1, float number2, enOperationType operation)
{
    float answer;
    switch (operation)
    {
    case enOperationType::Addition:
        cout << number1 << "\n+\n";
        cout << number2 << "\n______________\n";

        while (!(cin >> answer))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number:\n";
        }
        if (answer == number1 + number2)
        {
            cout << "Correct!\n";
            CorrectAnswers++;
        }
        else
        {
            cout << "Incorrect. The correct answer is " << number1 + number2 << ".\n";
            IncorrectAnswers++;
        }
        break;
    case enOperationType::Subtraction:
        cout << number1 << "\n-\n";
        cout << number2 << "\n______________\n";

        while (!(cin >> answer))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number:\n";
        }
        if (answer == number1 - number2)
        {
            cout << "Correct!\n";
            CorrectAnswers++;
        }
        else
        {
            cout << "Incorrect. The correct answer is " << number1 - number2 << ".\n";
            IncorrectAnswers++;
        }
        break;
    case enOperationType::Multiplication:
        cout << number1 << "\n*\n";
        cout << number2 << "\n______________\n";

        while (!(cin >> answer))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number:\n";
        }
        if (answer == number1 * number2)
        {
            cout << "Correct!\n";
            CorrectAnswers++;
        }
        else
        {
            cout << "Incorrect. The correct answer is " << number1 * number2 << ".\n";
            IncorrectAnswers++;
        }
        break;
    case enOperationType::Division:
        if (number2 == 0)
        {
            cout << "Division by zero error. Changing denominator to 1.\n";
            number2 = 1;
        }
        cout << number1 << "\n/\n";
        cout << number2 << "\n______________\n";

        while (!(cin >> answer))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number:\n";
        }
        if (answer == number1 / number2)
        {
            cout << "Correct!\n";
            CorrectAnswers++;
        }
        else
        {
            cout << "Incorrect. The correct answer is " << number1 / number2 << ".\n";
            IncorrectAnswers++;
        }
        break;
    default:
        break;
    }
}

string LevelToString(enLevelOfQuestion level)
{
    switch (level)
    {
    case enLevelOfQuestion::Easy:
        return "Easy";
    case enLevelOfQuestion::Medium:
        return "Medium";
    case enLevelOfQuestion::Hard:
        return "Hard";
    case enLevelOfQuestion::Mixed:
        return "Mixed";
    default:
        return "Unknown";
    }
}

string OperationToString(enOperationType op)
{
    switch (op)
    {
    case enOperationType::Addition:
        return "Addition";
    case enOperationType::Subtraction:
        return "Subtraction";
    case enOperationType::Multiplication:
        return "Multiplication";
    case enOperationType::Division:
        return "Division";
    case enOperationType::Mixed:
        return "Mixed";
    default:
        return "Unknown";
    }
}

void GenerateQuestion(enLevelOfQuestion level, enOperationType operation)
{
    float number1, number2;

    if (level == enLevelOfQuestion::Mixed)
    {
        level = static_cast<enLevelOfQuestion>(RandomNumber(1, 3));
    }

    switch (level)
    {
    case enLevelOfQuestion::Easy:
        number1 = RandomNumber(1, 10);
        number2 = RandomNumber(1, 10);
        break;
    case enLevelOfQuestion::Medium:
        number1 = RandomNumber(10, 100);
        number2 = RandomNumber(10, 100);
        break;
    case enLevelOfQuestion::Hard:
        number1 = RandomNumber(100, 1000);
        number2 = RandomNumber(100, 1000);
        break;
    default:
        return;
    }

    if (operation == enOperationType::Mixed)
    {
        operation = enOperationType(RandomNumber(1, 4));
    }

    PrintQuestion(number1, number2, operation);
}

string PlayerState()
{
    if (CorrectAnswers > IncorrectAnswers)
    {
        return "Win";
    }
    else if (IncorrectAnswers > CorrectAnswers)
    {
        return "Lose";
    }
    else
    {
        return "Draw";
    }
}

void StartGame();

void CheckPlayingAgain()
{
    string response;
    cout << "Do you want to play again? (Y/N): ";
    cin >> response;

    if (response == "Y" || response == "y")
    {
        CorrectAnswers = 0;
        IncorrectAnswers = 0;
        StartGame();
    }
    else
    {
        cout << "Thank you for playing! Goodbye!" << endl;
    }
}

void PrintResults()
{
    cout << "\n_____________________________________\n";
    cout << endl;
    cout << "\nFinal Results  is " << PlayerState() << endl;
    cout << "_____________________________________\n";
    cout << endl;

    cout << "Total Questions: " << CorrectAnswers + IncorrectAnswers << endl;
    cout << "Questions Level: " << LevelToString(chosenLevel) << endl;
    cout << "Operation Type: " << OperationToString(chosenOperation) << endl;
    cout << "Correct Answers: " << CorrectAnswers << endl;
    cout << "Incorrect Answers: " << IncorrectAnswers << endl;

    CheckPlayingAgain();
}

void StartGame()
{
    int numberOfQuestions = AskHowManyQuestions();
    chosenLevel = ChooseQuestionLevel();
    chosenOperation = ChooseOperationType();

    for (int i = 1; i <= numberOfQuestions; ++i)
    {
        cout << "\nQuestion [" << i << " / " << numberOfQuestions << "]\n";
        GenerateQuestion(chosenLevel, chosenOperation);
    }

    PrintResults();
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}