#include "user.h"
#include <windows.h>


/********************************************//**
        User
***********************************************/
User::User(string ID)
{
    userID = ID;
}

/********************************************//**
        StudentUser
***********************************************/
StudentUser::StudentUser(string ID):
    User::User(ID)
{
    permissionLevel=1;
    profile = new StudentProfile(ID);
}

/********************************************//**
        StudentProfile
***********************************************/
StudentProfile::StudentProfile(string ID)
{
    studentID = ID;
    profileFileName = "data\\profiles\\" + ID + ".txt";
}

void StudentProfile::addResult(string dateOfQuiz, int correctAnswers)
{
    //results.push_back(result);

    ofstream output(profileFileName.c_str(), ofstream::app);

    output << setw(15) << left << "Date of quiz: " << dateOfQuiz << endl;
    output << setw(15) << left << "Result: " << correctAnswers << "/10\n";
//    cout << "GOT HERE TOO";
//    output << "Date of quiz: " << dateOfQuiz << endl;
//    output << "Result: " << correctAnswers << "/10\n";

    output.close();
}

void StudentProfile::printToScreen()
{
    printToFile(cout);
}

void StudentProfile::printToFile(ostream &output)
{
    ifstream input(profileFileName.c_str());

    output << "Student ID: " << studentID << endl;

    if(input.is_open())
    {
        output << input.rdbuf();
        input.close();
    }
    else
    {
        output << "No profile for this student\n";
    }

    output << "\n\n";
}

/********************************************//**
        AdminUser
***********************************************/
AdminUser::AdminUser(string ID):
    User(ID)
{
    permissionLevel = 2;
}

void AdminUser::viewProfile(string studentID)
{
//    string profileFileName = "data\\profiles\\" + studentID + ".txt";
//    ifstream input(profileFileName.c_str());
//    cout << "Student ID: " << studentID << endl;
//
//    if(input.is_open())
//    {
//        cout << input.rdbuf();
//        input.close();
//    }
//    else
//    {
//        cout << "ERROR: There is no profile for that student.\n";
//    }

    StudentProfile *currentProfile = new StudentProfile(studentID);
    currentProfile->printToScreen();
}

void AdminUser::generateClassReport(string reportFileName)
{
    //get list of student IDs
    //open output file for report
    //copy each student profile into report file

    ifstream input("data\\users.txt");
    vector<string> studentIDsForReport;

    if(input.is_open())
    {
        string fileID, filePassword;
        int permissionLevel;
        do
        {
            input >> fileID >> filePassword >> permissionLevel;
            if(permissionLevel == 1)
            {
                studentIDsForReport.push_back(fileID);
            }
        }while(!input.eof());
    }
    input.close();

    //have list of relevant IDs in studentIDsForReport
    ofstream report_output(reportFileName.c_str(), ofstream::out);

    for(int i=0; i<studentIDsForReport.size(); i++)
    {
        StudentProfile *currentProfile = new StudentProfile(studentIDsForReport[i]);
        currentProfile->printToFile(report_output);
    }

    report_output.close();

}

void AdminUser::modifyQuestionBank()
{
    system("notepad.exe data\\questionbank.txt");
}

loginState loginCheck(string userID, string userPass)
{
    ifstream input("data\\users.txt");

    if(input.is_open())
    {
        string fileID, filePassword;
        int permissionLevel;
        loginState status;
        do
        {
            input >> fileID >> filePassword >> permissionLevel;
        }while((userID != fileID)&&(!input.eof()));

        if(!input.eof())
        {
            cout << "\nUser pass = " << encryptPassword(userPass) << endl;
            cout << "File pass = " << filePassword << endl;
        }

        if(input.eof()) status = ID_NOT_FOUND;
        else if(encryptPassword(userPass) != filePassword) status = WRONG_PASS;
        else if(encryptPassword(userPass) == filePassword)
        {
            switch(permissionLevel)
            {
            case 1:
                status = STUDENT;
                break;
            case 2:
                status = ADMIN;
                break;
            default:
                status = LOGIN_ERROR;
                break;
            }

        }
        else status = LOGIN_ERROR;
        //cout << fileID << " " << filePassword << endl;
        input.close();
        return status;
    }
    else return LOGIN_ERROR;
}

string encryptPassword(string inputPassword)
{
    string encryptedPassword = "";
    for(int i=0; i<inputPassword.length(); i++)
    {
        encryptedPassword += inputPassword[i]+20+'0';
    }

    return encryptedPassword;
}
