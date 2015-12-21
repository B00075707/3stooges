#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <iomanip>
#include "user.h"
#include "quiz.h"


using namespace std;

void addUser(string ID, string password, int permissionLevel)
{
    string outfile = "data\\users.txt";
    ofstream output(outfile.c_str(),std::ofstream::app);
    output << ID << " " << encryptPassword(password) << " " << permissionLevel << endl;
    output.close();
}




int main(void)
{
//    cout << "ADDING USERS:\n";
//    string input1, input2;
//    int input3;
//    cout << "Enter username, password, and permission level, with '|' to quit.\n";
//    while((cin >> input1 >> input2 >> input3 )&& input1 != "|")
//    {
//        addUser(input1, input2, input3);
//        cout << "NEXT\n";
//    }



    string inputID, inputPassword;
    static loginState loginStatus;

    AdminUser* activeAdmin;
    StudentUser* activeStudent;

    do
    {
        system("CLS");
        cout << "\nLOGIN";
        cout << "\nusername: ";
        cin >> inputID;
        cout << "\npassword: ";
        cin.clear();
        cin >> inputPassword;

        activeAdmin = new AdminUser(inputID);
        activeStudent = new StudentUser(inputID);

        loginStatus = loginCheck(inputID, inputPassword);

        switch(loginStatus)
        {
            case ID_NOT_FOUND:
                cout << "Sorry, that ID doesn't exist.\n\n";
                break;
            case WRONG_PASS:
                cout << "Sorry, that password is incorrect.\n\n";
                break;
            case STUDENT:
                cout << "Successfully logged in as student " << inputID << ".\n\n";
                activeAdmin = NULL;
                delete activeAdmin;
                break;
            case ADMIN:
                cout << "\n\nSuccessfully logged in as admin " << inputID << ".\n\n";
                delete activeStudent;
                break;
            default:
                cout << "Unknown error occured.\n\n";
                break;
        }
        system("PAUSE");
    }while((loginStatus != ADMIN)&&(loginStatus != STUDENT));
    //User has logged in

    int menu_choice, numQuestions = 0;
    string reportName, studID;

    while(1)
    {
        system("CLS");
        switch(loginStatus)
        {
            case STUDENT:
                //Menu for Student
                cout << "(1): Take Quiz\n";
                cout << "(2): View Profile\n";
                cout << "(3): Exit\n";
                cin >> menu_choice;
                switch(menu_choice)
                {
                    case 1:
                        numQuestions = fillQuestionBank();
                        if(numQuestions == 0)
                        {
                            cout << "ERROR. NO QUESTIONS ADDED. SELF-DESTRUCT IN 5..." << endl;
                        }
                        else
                        {
                            QuizAttempt studQuizAttempt(activeStudent);
                        }
                        break;
                    case 2:
                        activeStudent->profile->printToScreen();
                        system("PAUSE");
                        break;
                    case 3:
                        return 0;
                        break;
                    default:
                        break;
                }
                break;
            case ADMIN:
                cout << "(1): Generate Class Report\n";
                cout << "(2): View Individual Student Profile\n";
                cout << "(3): Modify Question Bank\n";
                cout << "(4): Exit\n";
                cin >> menu_choice;
                switch(menu_choice)
                {
                    case 1:
                        //activeAdmin->generateClassReport("report1");
                        cout << "Name for report: ";
                        cin >> reportName;
                        reportName = "data\\reports\\" + reportName;
                        activeAdmin->generateClassReport(reportName);
                        cout << "Report Generated.\n";
                        reportName = "notepad.exe data\\reports\\" + reportName;
                        system(reportName.c_str());
                        break;
                    case 2:
                        cout << "ID of desired student: ";
                        cin >> studID;
                        activeAdmin->viewProfile(studID);
                        break;
                    case 3:
                        activeAdmin->modifyQuestionBank();
                        break;
                    case 4:
                        return 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                cout << "Unknown error occured.\n\n";
                break;
        }
        system("PAUSE");
    }


    //if(loginStatus==ADMIN)
//    if(activeAdmin)
//    {
//        //delete tempstud;
////        AdminUser currentAdminUser(inputID);
////        currentAdminUser.modifyQuestionBank();
//        activeAdmin->modifyQuestionBank();
//    }





	return 0;
}



