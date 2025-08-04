#include <iostream>

using namespace std;

enum enQLevel { Easy = 1, Mid = 2, Hard = 3, Mixed = 4 };
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };

struct stData
{
	int qNumber;
	int qLevel;
	int opType;
	int num1;
	int num2;
	int rightAnswers;
	int wrongAnswers;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

void ResetGame(stData& GameData)
{
	GameData.rightAnswers = 0;
	GameData.wrongAnswers = 0;
	system("color 0F");
	system("cls");
}

void GetInfo(stData& GameData)
{
	cout << "How Many Questions Do You Want To Answer ? ";
	cin >> GameData.qNumber;
	cout << "Enter Questions Level: [1] Easy, [2] Mid, [3] Hard, [4] Mix ? ";
	cin >> GameData.qLevel;
	cout << "Enter Operation Type: [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
	cin >> GameData.opType;
}

string GetLevelSymbol(int level)
{
	string symbols[] = { "Easy", "Mid", "Hard", "Mix" };
	return symbols[level - 1];
}

string GetOpSymbol(int opType)
{
	string symbols[] = { "+", "-", "*", "/", "Mix" };
	return symbols[opType - 1];
}

void GetNums(int qLevel, int& num1, int& num2)
{
	switch (qLevel)
	{
	case enQLevel::Easy:
		num1 = RandomNumber(1, 10);
		num2 = RandomNumber(1, 10);
		break;
	case enQLevel::Mid:
		num1 = RandomNumber(10, 50);
		num2 = RandomNumber(10, 50);
		break;
	case enQLevel::Hard:
		num1 = RandomNumber(50, 100);
		num2 = RandomNumber(50, 100);
		break;
	case enQLevel::Mixed:
		GetNums(RandomNumber(enQLevel::Easy, enQLevel::Hard), num1, num2);
		break;
	}
}

int GetRightAnswer(int opType, int num1, int num2)
{
	switch (opType)
	{
	case enOpType::Add:
		return num1 + num2;
		break;
	case enOpType::Sub:
		return num1 - num2;
		break;
	case enOpType::Mul:
		return num1 * num2;
		break;
	case enOpType::Div:
		return num1 / num2;
		break;
	}
}

void CheckUserAnswer(stData& GameData, int rightAnswer, int userAnswer)
{
	if (userAnswer == rightAnswer)
	{
		system("color 2F");
		GameData.rightAnswers++;
		cout << "Right Answer :-)\n\n";
	}
	else {
		system("color 4F");
		GameData.wrongAnswers++;
		cout << "\aWrong Answer :-(\n";
		cout << "The Right Answer Is: " << rightAnswer << "\n\n";
	}
}

void MakeQuestion(stData& GameData)
{
	GetNums(GameData.qLevel, GameData.num1, GameData.num2);

	int qOpType = GameData.opType;
	if (GameData.opType == enOpType::Mix)
		qOpType = RandomNumber(enOpType::Add, enOpType::Div);

	cout << GameData.num1 << endl;
	cout << GameData.num2 << ' ' << GetOpSymbol(qOpType);
	cout << "\n__________\n";

	int userAnswer;
	cin >> userAnswer;
	int rightAnswer = GetRightAnswer(qOpType, GameData.num1, GameData.num2);
	CheckUserAnswer(GameData, rightAnswer, userAnswer);
}

string GetFinalResult(int rightAnswers, int wrongAnswers)
{
	if (rightAnswers > wrongAnswers)
	{
		system("color 2F");
		return "PASS :-)";
	}
	else if (rightAnswers < wrongAnswers)
	{
		system("color 4F");
		return "FAIL :-(\a";
	}
	else
	{
		system("color 6F");
		return "TIE :-|";
	}
}

void PrintResults(stData GameData)
{
	cout << "\n______________________________\n\n";
	cout << " Final Result Is " << GetFinalResult(GameData.rightAnswers, GameData.wrongAnswers);
	cout << "\n______________________________\n\n";
	cout << "Number Of Questions : " << GameData.qNumber << endl;
	cout << "Questions Level     : " << GetLevelSymbol(GameData.qLevel) << endl;
	cout << "OpType              : " << GetOpSymbol(GameData.opType) << endl;
	cout << "Right Answers       : " << GameData.rightAnswers << endl;
	cout << "Wrong Answers       : " << GameData.wrongAnswers << endl;
	cout << "______________________________\n\n";
}

void StartGame(stData& GameData)
{
	ResetGame(GameData);
	GetInfo(GameData);

	for (int i = 1; i <= GameData.qNumber; i++)
	{
		cout << "\nQuestion [" << i << '/' << GameData.qNumber << "]\n\n";
		MakeQuestion(GameData);
	}

	PrintResults(GameData);
}

bool PlayAgain()
{
	char again;
	cout << "Do You Want To Play Again? Y/N? ";
	cin >> again;

	if (again == 'Y' || again == 'y') return true;
	else return false;
}

int main()
{
	srand((unsigned)time(NULL));
	stData GameData;

	do StartGame(GameData);
	while (PlayAgain());
}
