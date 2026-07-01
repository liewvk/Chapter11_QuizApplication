#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cctype>

struct Question
{
    std::string questionText;
    std::string optionA;
    std::string optionB;
    std::string optionC;
    std::string optionD;
    char correctAnswer;
};

struct QuizResult
{
    int totalQuestions;
    int correctAnswers;
    int wrongAnswers;
    double scorePercentage;
};

void displayMenu()
{
    std::cout << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "          Quiz Application" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "1. Start Quiz" << std::endl;
    std::cout << "2. View Last Result" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Please choose an option: ";
}

std::vector<Question> createQuestions()
{
    std::vector<Question> questions;

    questions.push_back({
        "What does CPU stand for?",
        "Central Processing Unit",
        "Computer Programming Utility",
        "Central Program User",
        "Control Processing Unit",
        'A'
        });

    questions.push_back({
        "Which language is mainly used in this book?",
        "Python",
        "Java",
        "C++",
        "PHP",
        'C'
        });

    questions.push_back({
        "Which symbol is used to end most C++ statements?",
        ".",
        ";",
        ":",
        ",",
        'B'
        });

    questions.push_back({
        "Which C++ library is used for input and output?",
        "iostream",
        "fstream",
        "vector",
        "iomanip",
        'A'
        });

    questions.push_back({
        "Which data type stores true or false values?",
        "int",
        "double",
        "bool",
        "char",
        'C'
        });

    return questions;
}

void displayQuestion(const Question& question, int questionNumber)
{
    std::cout << std::endl;
    std::cout << "Question " << questionNumber << ":" << std::endl;
    std::cout << question.questionText << std::endl;
    std::cout << "A. " << question.optionA << std::endl;
    std::cout << "B. " << question.optionB << std::endl;
    std::cout << "C. " << question.optionC << std::endl;
    std::cout << "D. " << question.optionD << std::endl;
}

char getUserAnswer()
{
    char answer;

    std::cout << "Your answer: ";
    std::cin >> answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    answer = static_cast<char>(std::toupper(static_cast<unsigned char>(answer)));

    return answer;
}

bool isValidAnswer(char answer)
{
    return answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D';
}

char getValidUserAnswer()
{
    char answer;

    while (true)
    {
        answer = getUserAnswer();

        if (isValidAnswer(answer))
        {
            return answer;
        }

        std::cout << "Invalid answer. Please enter A, B, C, or D." << std::endl;
    }
}

QuizResult startQuiz(const std::vector<Question>& questions)
{
    QuizResult result;
    result.totalQuestions = static_cast<int>(questions.size());
    result.correctAnswers = 0;
    result.wrongAnswers = 0;
    result.scorePercentage = 0.0;

    for (int i = 0; i < static_cast<int>(questions.size()); ++i)
    {
        displayQuestion(questions[i], i + 1);

        char userAnswer = getValidUserAnswer();

        if (userAnswer == questions[i].correctAnswer)
        {
            std::cout << "Correct!" << std::endl;
            result.correctAnswers++;
        }
        else
        {
            std::cout << "Wrong. The correct answer is "
                << questions[i].correctAnswer << "." << std::endl;
            result.wrongAnswers++;
        }
    }

    result.scorePercentage =
        (static_cast<double>(result.correctAnswers) / result.totalQuestions) * 100.0;

    return result;
}

void displayResult(const QuizResult& result)
{
    std::cout << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "             Quiz Result" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Total Questions : " << result.totalQuestions << std::endl;
    std::cout << "Correct Answers : " << result.correctAnswers << std::endl;
    std::cout << "Wrong Answers   : " << result.wrongAnswers << std::endl;
    std::cout << "Score           : "
        << std::fixed << std::setprecision(2)
        << result.scorePercentage << "%" << std::endl;
}

void displayFeedback(const QuizResult& result)
{
    if (result.scorePercentage >= 80)
    {
        std::cout << "Excellent work!" << std::endl;
    }
    else if (result.scorePercentage >= 60)
    {
        std::cout << "Good effort. Keep practicing." << std::endl;
    }
    else if (result.scorePercentage >= 40)
    {
        std::cout << "You need more revision." << std::endl;
    }
    else
    {
        std::cout << "Please review the topic and try again." << std::endl;
    }
}

void saveResultToFile(const QuizResult& result, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Error: Could not save quiz result." << std::endl;
        return;
    }

    file << "Total Questions: " << result.totalQuestions << std::endl;
    file << "Correct Answers: " << result.correctAnswers << std::endl;
    file << "Wrong Answers: " << result.wrongAnswers << std::endl;
    file << "Score: " << std::fixed << std::setprecision(2)
        << result.scorePercentage << "%" << std::endl;

    file.close();

    std::cout << "Quiz result saved successfully." << std::endl;
}

void viewLastResult(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        std::cout << "No quiz result found." << std::endl;
        return;
    }

    std::string line;

    std::cout << std::endl;
    std::cout << "========== Last Quiz Result ==========" << std::endl;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    file.close();
}

int main()
{
    std::vector<Question> questions = createQuestions();
    const std::string resultFile = "quiz_result.txt";
    int choice;

    while (true)
    {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            QuizResult result = startQuiz(questions);
            displayResult(result);
            displayFeedback(result);
            saveResultToFile(result, resultFile);
            break;
        }

        case 2:
            viewLastResult(resultFile);
            break;

        case 3:
            std::cout << "Thank you for using the Quiz Application." << std::endl;
            return 0;

        default:
            std::cout << "Invalid option. Please choose again." << std::endl;
        }
    }
}
