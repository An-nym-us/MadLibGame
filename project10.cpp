/***********************************************************************
* Program:
*    Project 10, MadLib continued
*    Brother Foushee, CS124
* Author:
*    Jonathan Gunderson
* Summary:
*    This will read the madLib text file taken from the user, ensure that
* it is valid, then ask questions, and display them to the user.
*
*    Estimated:  5.0 hrs
*    Actual:     8.0 hrs
*      The most difficult part of this program, was getting the test 
* bed to like my formatting. I had a lot of problems with it saying I
* added spaces when I didn't. At some point I fixed it but have no idea
* what I did that fixed it. It works and thats all that matters.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>
#include <iomanip>
using namespace std;





/***********************************************************************
* This will display the full story to the user 
* with the proper grammer and text format. 
***********************************************************************/
void displayFullStory(char story[][32], int numWords)
{
   cout << "\n";

   for (int i = 0; i < numWords; i++)
   {
      if (story[i][0] == ':')
      {
         if (story[i][1] == '!')
         {
            cout << endl;
         }
         else if (story[i][1] == '<')
         {
            cout << '"';
         }
         else if (story[i][1] == '>')
         {
            if (story[i + 1][1] == '!')
            {
               cout << '"';
            }
            else
            {
               cout << "\" ";
            }
         }
         else if (story[i][1] == '.')
         {
            if (!isalpha(story[i + 1][0]))
            {
               cout << '.';
            }
            else
            {
               cout << ". ";
            }
         }
         else if (story[i][1] == ',')
         {
            if (!isalpha(story[i + 1][0]))
            {
               cout << ',';
            }
            else if (story[i + 1][0] == '\n')
            {
               cout << ',';
            }
            else
            {
               cout << ", ";
            }
         }
      }
      else if (!isalpha(story[i][0]) && isalpha(story[i][1]))
      {
         cout << ' ' << story[i] << ' ';
      }
      else if (isalpha(story[i][0]))
      {
         if (!isalpha(story[i + 1][0]))
         {
            if (story[i + 1][1] == '<')
               cout << story[i] << ' ';
            else
               cout << story[i];
         }
         else
         {
            cout << story[i] << ' ';
         }
      }
      else
      {
         if (!isalpha(story[i + 1][0]))
         {
            cout << story[i];
         }
         else
         {
            cout << story[i] << ' ';
         }
      }
   }
   cout << "\n";
}


/***********************************************************************
 * This will read, format, and display the question from the madLib
 * file, then present them to the user.
***********************************************************************/
void askQuestions(char story[],int size, int &tracker)
{
   if (isalpha(story[1]))
   {
      tracker++;
      cout << "\t" << (char)toupper(story[1]);

      for (int j = 2; story[j]; j++)
      {
         if (story[j] == '_')
         {
            cout << " ";
         }
         else
         {
            cout << (char)tolower(story[j]);
         }
      }

      cout << ": ";


      if (tracker <= 1)                  
      {
         cin.ignore();                 
         cin.getline(story,32);        
      }
      else
      {
         cin.getline(story,32);
      }

   }

}



/***********************************************************************
 * This will read the file taken by the user, it will do general
 * error check and max word count checks.
***********************************************************************/
int readFileText(char story[][32], char fileName[], int &tracker)
{
   ifstream fin;
   fin.open(fileName);


   if (fin.fail())
      cout << "Error reading file: " << fileName;

   int size = 0;
   
   while (fin >> story[size])
   {
      size++;
   }
   fin.close();

   for (int i = 0; i < size; i++)
   {
      if (story[i][0] == ':')
      {
         askQuestions(story[i], size, tracker);
      }
   }
   
   return size;
}



/***********************************************************************
* This will ask the user if they would
* like to play the game again .
***********************************************************************/
bool playGameAgain(int &tracker)
{
   bool again;
   char answer;
   tracker = 0;
   cout << "Do you want to play again (y/n)? ";
   cin >> answer;

   if (answer == 'y')
      again = true;
   else if (answer == 'n')
      again = false;
   else
   {
      cout << "Invalid entry. Do you want to play again (y/n)? ";
      cin >> answer;
   }
   return again;
}

/***********************************************************************
 * This will set variables that will be used throughout the program
 * It will call other functions as needed.
***********************************************************************/
int main()
{
   char fileName[256];
   char story[1024][32];
   int size = 0;
   bool playAgain = true;
   int tracker = 0;                      

   do
   {
      cout << "Please enter the filename of the Mad Lib: ";
      cin >> fileName;
      size = readFileText(story, fileName, tracker);
      displayFullStory(story, size);
      playAgain = playGameAgain(tracker);
   }
   while (playAgain == true);  
      cout << "Thank you for playing.\n";
   
   return 0;
}