#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

class User;
class StudentUser;
class AdminUser;
class QuizResult;
class QuizAttempt;
class QuestionBank;
class Question;


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
		StudentProfile(string ID)
		{
			userID = ID;
		}

		//! A pure virtual member function to view the profile of a User.
		/*!

		*/
		virtual StudentProfile viewProfile() = 0;

	protected:
		//! User ID variable.
		string userID=0;
		//! User permission level (higher = more permissions).
		char permissionLevel=0;
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
		StudentUser(string ID)
		{
			User(ID);
			permissionLevel=1;
			profile = new StudentProfile(ID);
		}


  protected:
    //! Student's profile containing previous quiz results.
		StudentProfile profile=0;
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
		AdminUser(string ID)
		{
			User(ID);
			permissionLevel=2;
		}

		//! A member function to view the profile of a student.
		/*!
				\param ID a string containing the ID of the student whose profile is desired.
		*/
		void viewProfile(string studentID)
		{
			// TODO: print out profile
		}

  protected:
    //! Student's profile containing previous quiz results.
		StudentProfile profile=0;
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
		StudentProfile(string ID)
		{
			studentID = ID;
			profileFileName = "data\\profiles\\" + ID + ".txt";
		}

    //! A member function to add a QuizResult from a quiz attempt.
		/*!
		    \param *result a pointer to the QuizResult to add.
		*/
    void addResult(QuizResult *result)
    {
			//results.push_back(result);

			ofstream input(profileFileName.c_str(), std::ofstream::app);

			if(input.is_open())
    	{
				string in_buff;
        while(getline(input, in_buff))
        {
          output << in_buff << endl;
        }

        input.close();
        cout << name << " added to output successfully.\n\n\n";
    	}

	    else
	    {
        throw bad_file();
	    }
    }

    //! A member function to print a profile to the screen.
		/*!

		*/
    void printToScreen()
    {
			for(int i=0; i<results.size(); i++)
			{
				//TODO: print results[i]
			}
    }

		//! A member function to print a profile to a file with the student's username as filename.
		/*!

		*/
    void printToFile()
    {
		  string outputFilename = "data\\profiles\\" + ID + ".txt";
		  ofstream output(outputFilename.c_str());

			for(int i=0; i<results.size(); i++)
			{
				//TODO: print results[i]
			}
		  output.close();
		}

		//! A member function to print a profile to a specified file.
		/*!
		    \param &output a pointer to the output file stream to print to.
		*/
    void printToFile(ofstream &output)
    {
			output << "Student: " << ID << endl;
			for(int i=0; i<results.size(); i++)
			{
				//TODO: output << results[i]
			}
    }

  protected:

		//! Previous quiz results.
    vector<QuizResult> results[];
		//! ID of StudentUser which owns the profile.
    string studentID=0;
		//! Name of file which stores the profile.
    string profileFileName=0;
};

//! QuizResult class
/********************************************//**
Class for a QuizResult
***********************************************/
class QuizResult
{
    public:

    //! A member function to add an Observation to the Observation log.
	/*!
	    \param *obs a pointer to the Observation object to add to the log.
	*/
    void addObservation(Observation *obs)
    {

    }

    //! A member function to return an Observation from a specified time.
	/*!
	    \param time, the timestamp of the desired Observation.
	*/
    Observation getObservation(string time)
    {

    }

    protected:

    vector<Observation> log[];
};

//! QuizResult class
/********************************************//**
Class for .
***********************************************/
class QuizResult
{
  public:

		//! Constructor used to generate a QuizResult.
		/*!
				\param dateOfQuiz the date the quiz was taken.
				\param questionIDs a vector containing the IDs of the 10 questions asked, in order.
				\param results a vector which stores the student's result of each of the 10 questions asked, in order.
		*/
		QuizResult(string dateOfQuiz, vector<int> questionIDs, vector<bool> results):
			dateOfQuiz(dateOfQuiz), questionIDs(questionIDs), results(results){}

	protected:
		//! The date the quiz was taken.
		string dateOfQuiz;
		//! Vector containing the IDs of the 10 questions asked, in order.
		vector<int> questionIDs[];
		//! Vector which stores the student's result of each of the 10 questions asked, in order.
		vector<bool> results[];
};


int main(void)
{
	return 0;
}

//! A function to login as a User.
/*!
		\param ID a string of the desired ID.
		\param password a string containing the User's corresponding password.
*/
bool login(string ID,string password)
{
	//TODO: scan credentials to check if legit
}

/*
Name:   file_copy_buff
Arg1:   Reference to name of input file to open.
Arg2:   Reference to already opened output stream.
Uses rdbuf(), which returns a pointer to input's stream buffer, and prints
out the contents of the input file to the output file. This method does not
need any temporary strings or chars to hold the contents before printing to
the output file.
-------------------------------------------------------------------------*/
void file_copy_buff(const string &name, ofstream &output)
{
    ifstream input(name.c_str());

    if(input.is_open())
    {
        output << input.rdbuf();
        input.close();
        cout << name << " added to output successfully.\n\n\n";
    }
    else
    {
        throw bad_file();
    }
}
