#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED


#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <iomanip>

using namespace std;

enum loginState {LOGIN_ERROR,ID_NOT_FOUND,WRONG_PASS,STUDENT,ADMIN};

class User;
class StudentUser;
class StudentProfile;
class AdminUser;

//! A standalone function to login as a User.
/*!
		\param userID a string of the desired ID.
		\param userPass a string containing the User's corresponding password.
		\return The result of the login attempt.
		Scans through the credentials file until it either reaches the enf of file or finds a match of the username.
		If it finds a username match, it then checks the encrypted password from the file against the encrypted input password.
*/
loginState loginCheck(string userID, string userPass);

//! A standalone function to encrypt a password.
/*!
		\param inputPassword a string of the User's password.
		\return The resulting encrypted password.
		Encrypts the password by modifying each character in the string, as well as adding extra characters.
		It is consistent in its encryption, i.e. a particular input password will always result in the same encrypted password.
*/
string encryptPassword(string inputPassword);

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
		User(string ID);

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
		StudentUser(string ID);

    //protected:
        //! Student's profile containing previous quiz results.
		StudentProfile *profile;
};

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
        StudentProfile(string ID);

        //! A member function to add a QuizResult from a quiz attempt.
        /*!
            \param dateOfQuiz the date the quiz was taken.
            \param correctAnswers the number of questions answered correctly.
        */
        void addResult(string dateOfQuiz, int correctAnswers);

        //! A member function to print a profile to the screen.
        /*!
            Simply calls printToFile, but passes it the console output instead of a file.
        */
        void printToScreen(void);

        //! A member function to print a profile to a specified file.
        /*!
            \param &output a pointer to the output file stream to print to.
        */
        void printToFile(ostream &output);

    protected:

        //! ID of StudentUser which owns the profile.
        string studentID;
        //! Name of file which stores the profile.
        string profileFileName;
};



//! AdminUser class
/********************************************//**
Class for a AdminUser, which is created by a User logging in with admin credentials.
***********************************************/
class AdminUser: public User
{
    public:

        //! AdminUser constructor for initialisation.
		/*!
            \param ID a string containing the AdminUser's ID.
		*/
		AdminUser(string ID);

		//! A member function to view the profile of a student.
		/*!
            \param studentID a string containing the ID of the student whose profile is desired.
		*/
		void viewProfile(string studentID);

		//! A member function to generate class report.
		/*!
            \param reportFileName a string of what to name the report .txt file.
		*/
		void generateClassReport(string reportFileName);

		//! A member function to modify the contents of the QuestionBank file.
		/*!

		*/
		void modifyQuestionBank();
};

#endif // USER_H_INCLUDED
