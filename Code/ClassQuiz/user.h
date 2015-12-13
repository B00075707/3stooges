#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

class User;
class StudentUser;
class StudentProfile;
class AdminUser;
int loginCheck(string,string);
string encryptPassword(string);

#include <fstream>
#include <string.h>
#include <iomanip>
#include <iostream>

using namespace std;

//! StudentProfile class
/********************************************//**
Class for a StudentProfile, which is a log of all quiz results for a particular student.
***********************************************/
class StudentProfile
{
    public:

        //! StudentProfile constructor for initialisation.
        /*!
          \param ID a string containing the StudentUser's ID.
        */
        StudentProfile(string ID)
        {
            studentID = ID;
            profileFileName = "data\\profiles\\" + ID + ".txt";
        }

        //! A member function to add a QuizResult from a quiz attempt.
        /*!
            \param dateOfQuiz the date the quiz was taken.
            \param correctAnswers the number of questions answered correctly.
        */
        void addResult(string dateOfQuiz, int correctAnswers)
        {
            //results.push_back(result);

            ofstream output(profileFileName.c_str(), std::ofstream::app);

            output << setw(15) << left << "Date of quiz: " << dateOfQuiz << endl;
            output << setw(15) << left << "Result: " << correctAnswers << "/10\n";

            output.close();
        }

        //! A member function to print a profile to the screen.
        /*!
            Just calls printToFile, but passes it the console output instead of a file.
        */
        void printToScreen()
        {
            printToFile(cout);
        }

        //! A member function to print a profile to a specified file.
        /*!
            \param &output a pointer to the output file stream to print to.
        */
        void printToFile(ostream &output)
        {
            ifstream input(profileFileName.c_str());

            cout << "Student ID: " << studentID << endl;

            if(input.is_open())
            {
                output << input.rdbuf();
                input.close();
            }
        }

    protected:

        //! ID of StudentUser which owns the profile.
        string studentID;
        //! Name of file which stores the profile.
        string profileFileName;
};

//! Base User class
/********************************************//**
Abstract base class User, to be used to implement different types of users.
***********************************************/
class User
{
    public:

		//! A constructor for creating a new User with the provided userID.
		/*!
				\param ID a string containing the User's ID.
		*/
		User(string ID)
		{
			userID = ID;
		}

	protected:
		//! User ID variable.
		string userID;
		//! User permission level (higher = more permissions).
		char permissionLevel;
};

//! StudentUser class
/********************************************//**
Class for a StudentUser, which is created by a User logging in with student credentials.
***********************************************/
class StudentUser: public User
{
    public:

        //! StudentUser constructor for students after logging in.
		/*!
	      \param ID a string containing the StudentUser's ID.
		*/
		StudentUser(string ID):
            User::User(ID)
		{
			permissionLevel=1;
			StudentProfile profile(ID);
		}

		//! A member function to attempt a quiz.
		/*!

		*/
        void takeQuiz()
        {

        }


    protected:
        //! Student's profile containing previous quiz results.
		StudentProfile profile();
};

//! AdminUser class
/********************************************//**
Class for a AdminUser, which is created by a User logging in with admin credentials.
***********************************************/
class AdminUser: public User
{
    public:

        //! AdminUser constructor for admins after logging in.
		/*!
            \param ID a string containing the AdminUser's ID.
		*/
		AdminUser(string ID):
            User(ID)
		{
            permissionLevel = 2;
		}

		//! A member function to view the profile of a student.
		/*!
            \param studentID a string containing the ID of the student whose profile is desired.
		*/
		void viewProfile(string studentID)
		{
			string profileFileName = "data\\profiles\\" + studentID + ".txt";
			ifstream input(profileFileName.c_str());
			cout << "Student ID: " << studentID << endl;

            if(input.is_open())
            {
                cout << input.rdbuf();
                input.close();
            }
			else
			{
				cout << "ERROR: There is no profile for that student.\n";
			}
		}
};

//! A function to login as a User.
/*!
		\param userID a string of the desired ID.
		\param userPass a string containing the User's corresponding password.
*/
int loginCheck(string userID, string userPass)
{
    ifstream input("data\\users.txt");

    if(input.is_open())
    {
        //cout << input.rdbuf();
        string fileID, filePassword;
        int permissionLevel, status;
        do
        {
            input >> fileID >> filePassword >> permissionLevel;
        }while((userID != fileID)&&(!input.eof()));
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
                status = ERROR;
                break;
            }

        }
        else status = ERROR;
        //cout << fileID << " " << filePassword << endl;
        input.close();
        return status;
    }
    else return ERROR;
}

string encryptPassword(string inputPassword)
{
    string encryptedPassword;
    int passlength = inputPassword.length() + (inputPassword.length())/3;
    for(int i=0; i<passlength; i++)
    {
        if(i%3==0)
        {
            encryptedPassword += 128-(i*3)+'0';
        }
        else
        {
            encryptedPassword += inputPassword[i]+20-i+'0';
        }
    }

    return encryptedPassword;
}


#endif // USER_H_INCLUDED
