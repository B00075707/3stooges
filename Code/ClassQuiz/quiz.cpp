#include "quiz.h"

vector<Question> questionBank;

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
//from http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);

    return buf;
}

int fillQuestionBank(void)
{
    ifstream quest_input("data\\questionbank.txt");
    char questbuff[256], corbuff;

    if(quest_input.is_open())
    {
        int i=0;
        while(quest_input.getline(questbuff,256) && !quest_input.eof())
        {
            quest_input >> corbuff;
            questionBank.push_back(Question(questbuff,corbuff));

            while(quest_input.getline(questbuff,256) && questbuff[0] != '/')
            {
                questionBank[i].addAnswerChoice(questbuff);
            }
            //questionBank[i].printToScreen();
            i++;
        }
    }
    else
    {
        cout << "ERROR: NO QUESTION BANK FILE FOUND.\n";
    }
    return questionBank.size();
}


/********************************************//**
        QuizAttempt
***********************************************/
QuizAttempt::QuizAttempt(StudentUser *student_user):
        student_user(student_user)
{
    runQuiz();
}

void QuizAttempt::saveResultToProfile(void)
{
    student_user->profile->addResult(currentDateTime(), correctAnswers);
}

void QuizAttempt::runQuiz(void)
{
    try
    {
        getQuestions();
    }
    catch (too_few_questions)
    {
        cout << "ERROR. NOT ENOUGH QUESTIONS IN QUESTION BANK." << endl;
    }

    char inputAnswer;
    correctAnswers = 0;

    for(int i=0; i<quizQuestions.size(); i++)
    {
        system("CLS");
        quizQuestions[i]->askQuestion();
        cout << "Your answer: ";
        cin >> inputAnswer;
        if(quizQuestions[i]->checkAnswer(inputAnswer)) correctAnswers++;
    }

    cout << "Quiz done. You got " << correctAnswers << " right." << endl;
    saveResultToProfile();

}

void QuizAttempt::getQuestions(void)
{
    if(questionBank.size() < 10)
    {
        throw too_few_questions();
    }
    else
    {
        srand(time(0));
        random_shuffle(questionBank.begin(), questionBank.end());

        for(int i=0; i<10; i++)
        {
            quizQuestions.push_back(&questionBank[i]);
        }
    }

}


/********************************************//**
        Question
***********************************************/
void Question::addAnswerChoice(string answer)
{
    answerChoice.push_back(answer);
}

void Question::askQuestion(void)
{
    cout << questionString << endl;
    for(int i=1; i<answerChoice.size(); i++)
    {
        char index = 'A' + (i-1);
        cout << index << ": " << answerChoice[i] << endl;
    }
}

bool Question::checkAnswer(char answerInput)
{
    if(toupper(answerInput) == correctAnswer) return TRUE;
    else return FALSE;
}

void Question::printToScreen()
{
    printToFile(cout);
}

void Question::printToFile(ostream &output)
{
    output << questionString << endl << correctAnswer << endl;
    for(int i=0; i<answerChoice.size(); i++)
    {
        output << answerChoice[i] << endl;
    }
}
