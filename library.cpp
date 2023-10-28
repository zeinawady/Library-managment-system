#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<cstdlib>           //we use it ( built in function exit)
#include <conio.h>
#include<algorithm>
using namespace std;

void welcome();
void intro();                               // switch cases contain function of logging
void ModifyBookInfo();
void Modify_order();
void borrowbook();
void returnbook();
void display_available_books_only();
void display_booklist();
void book_info();
void addbook();
void deletebook();
void sign_up();
void login_student();
void login_admin();
void forgot();
void change_password();
int loading1();                         // load data from file to array( students)
void loading2();                         // load data  from array to file( students)
int loading3();                         //load data from file to array (books)
void loading4();                       // load data  from array to file(books)
void hide_password();
string hide_password_check();
void logging();
void main_student();                    //switch cases----> list
void main_admin();                   //switch cases for admin features
void myprofile();
void info_stud();
void bookservices();
//-------------------------------------Bouns------//
void displaystudentinfo();
int displaystudentinfo_for_admin();
int displayfeedback(int code);
int date();
void search_author();
void search_category();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

#define book_limit 50
#define students_number 100
int answer;
int counter = 0;
int counter_logging = 0;        // determine numbers of lines in file 
int index;



struct library
{
	int code;
	int edition;
	string book_name, author_name, category;
	int available = 0;      // not available to borrow 
	string feedback = " No feedback right now ";
}books[book_limit];

//struct for students information
struct student_info
{
	int ID;
	string student_name, username, password;
	string borrowed_books = " No borrowed books";      //name of borrowed book
	bool full = 0; //=0 //borrow and return function student borrowed books check

}student[students_number];

int main()
{
	system("color 7d");
	welcome();
	intro();
	return 0;
}
void welcome()
{
	cout << endl << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                               welcome To Our Library                                                                 " << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

	cout << endl;
}
//----------------------------------------------logging functions-------------------------------------------//
int loading1()
{
	// load data from file to array

	ifstream file;             // input from file =read from file
	file.open("data1.txt");
	int sz = 0;
	file >> sz;
	for (int i = 0; i < sz; i++)
	{
		file >> student[i].username >> student[i].password >> student[i].student_name >> student[i].borrowed_books >> student[i].ID;
	}
	file.close();
	return sz;
}
void loading2()
{
	// from array to file
	ofstream file("data1.txt");//input to file=write in file
	file << counter_logging << endl;
	for (int i = 0; i < counter_logging; i++)
	{

		file << student[i].username << ' ' << student[i].password << ' ' << student[i].student_name << ' ' << student[i].borrowed_books << ' ' /*<< student[i].wish_list_arr[counter2]<<<<student[i].full<<' ' */ << student[i].ID << endl;

	}
	file.close();
}
int  loading3()
{
	// load data from file to array
	int size = 0;
	ifstream nfile;             // input from file 
	nfile.open("data2.txt");
	nfile >> size;
	for (int i = 0; i < size; i++)
	{
		nfile >> books[i].code >> books[i].edition >> books[i].book_name >> books[i].author_name >> books[i].category >> books[i].available;        // determine numbers of lines in file 
	}
	nfile.close();
	return size;
}
void loading4()
{
	// from array to file
	ofstream nfile("data2.txt");
	nfile << counter << endl;
	for (int i = 0; i < counter; i++)
	{

		nfile << books[i].code << ' ' << books[i].edition << ' ' << books[i].book_name << ' ' << books[i].author_name << ' ' << books[i].category << ' ' << books[i].available << endl;
	}
	nfile.close();
}
void hide_password()          //we use this function to hide passsword only in sign up to take password from uer in first time
{
	int count = 0;          //counter to check if user enter 8 characters
	char ch;                // must be char because getch() store only one value with each press on buttons
	while ((ch = _getch()) != '\r')           //user donot press enter
	{
		count++;
		student[counter_logging].password += ch;      // in string: a+b=ab
		cout << "*";
	}

}
string hide_password_check()     //it is okay to take a parameter or not as you like
{
	string pass;
	char ch;                                  // must be char because getch() store only one value with each press on buttons
	while ((ch = _getch()) != '\r')           //user donot press enter
	{

		pass += ch;      // in string: a+b=ab
		cout << "*";
	}
	return pass;
}
void sign_up()
{

	string username1, p;
	bool found = 0;
	cout << endl;
	cout << "\t>>Enter The Username: ";
	cin >> username1;
	//cout << ">>" << endl;
	for (int i = 0; i < students_number; i++)
	{
		if (student[i].username == username1)
		{
			found = 1;
			break;
		}
	}
	if (found == 1)
	{
		cout << endl;
		cout << "\t\t  ------------------------------" << endl;
		cout << "\t\t |       Username Exists        |" << endl;
		cout << "\t\t  ------------------------------" << endl;
		cout << "\t\t\t<<<< Please Try again >>>>" << endl << endl;
		sign_up();
	}

	else
	{
		student[counter_logging].username = username1;
		cout << "\t>>Enter Your Name: ";
		cin.ignore();
		getline(cin, student[counter_logging].student_name);// cout << ">>" << endl;
		cout << "\t>>Enter Your ID: "; cin >> student[counter_logging].ID; //cout << ">>" << endl;

		cout << "\t>>Enter The Password: ";
		hide_password(); cout << endl;
		while (true)        //user enter password correctly in check
		{
			cout << "\t>>Confirm password: ";
			p = hide_password_check(); cout << endl;
			if (p == student[counter_logging].password)
			{
				counter_logging++;
				cout << endl;
				cout << "\t\t\t\t-----------Registerition is successful!!-----------\t\t\t\t\t\t" << endl << endl;
				break;
			}
			else
			{
				cout << "Password is Wrong!!Try again\n";
				continue;
			}
		}
	}
}
void login_student()
{
	bool found = 0, found1 = 0, found2 = 0;

	string user, p;
	cout << "Please, Enter Your Username : ";
	cin >> user;
	cout << "Please, Enter Your Password : ";
	p = hide_password_check();

	for (int i = 0; i < students_number; i++)
	{
		//--------------------------------check what is wrong/true(username or password)----------------------------------------------------------------//


		if ((student[i].username == user) && (student[i].password == p))
		{
			found = 1;
			index = i; // global variable ,we use it to know index of student in array to  edit his information recently
			cout << "\t\t\t\t\t-------You have logged in successfully!-------\t\t\t\t\t\t" << endl << endl;
			main_student();
			break;
		}
		else if ((student[i].username == user) && (student[i].password != p))
		{
			found1 = 1;
			cout << endl;
			cout << "\t\t\t\t\t-------Login is not successful!! Your password is wrong-------\t\t\t\t\t\t " << endl << endl;
			cout << endl << "Please, try again" << endl << endl;
			login_student();
		}

	}
	// if ((student[i].username != user) 
	if (found == 0 && found1 == 0)
	{
		cout << "\t\t\t\t-------Please,Sign up your username isnot found in our library-------\t\t\t\t\t\t " << endl << endl;
		system("pause");
		system("CLS");
		logging();
	}



}
void login_admin()
{
	string identifying_pass = "456123", pass; // password admin

	cout << "\t\t < Enter admin's password :";
	cin >> pass; cout << ">" << endl;

	if (pass == identifying_pass)
	{
		cout << "\t\t  ------------------------------------------------------" << endl;
		cout << "\t\t |         Hello, you have logged in successfully        | " << endl;
		cout << "\t\t  -------------------------------------------------------" << endl;
		system("pause");
		system("CLS");
		main_admin();
	}
	else
	{
		cout << "\t\t  --------------------------------------------" << endl;
		cout << "\t\t |        Your Paasword is Wrong!!             |" << endl;
		cout << "\t\t  --------------------------------------------" << endl;
		cout << "\t\t\t<<< Please!! Try again>>>" << endl << endl;
		system("pause");
		system("CLS");
		login_admin();
	}
}
void forgot()
{
	//loading1();
	int count = 0, index;
	string f_username, f_pass;
	cout << "\t\t---->> Please Enter your username: "; cin >> f_username;

	for (int i = 0; i < students_number; i++)
	{
		if (f_username == student[i].username)
		{
			count = 1;
			index = i;
			break;
		}
	}
	if (count == 1)
	{
		cout << "\t\t  ---------------------------------" << endl;
		cout << "\t\t |     Your password is found       |" << endl;
		cout << "\t\t  ---------------------------------" << endl;
		cout << "<< Your password is:" << student[index].password << ">>" << endl << endl;

	}
	else
	{
		cout << "\t\t   ---------------------------------------------------------------------------------" << endl;
		cout << "\t\t\ |      !! Sorry your password is not found You have entered invalid username       |" << endl;
		cout << "\t\t   ---------------------------------------------------------------------------------" << endl;
		intro();
	}
}
void change_password()
{
	// student already make login and use system

	string user, new_pass;
	bool found = 0;


	cout << "\t\t<< Enter Your New Password:";
	cin >> new_pass; cout << ">>" << endl;

	student[index].password = new_pass;
	cout << "\t\t\t  --------------------------------------------------------- " << endl;// replace old password with new
	cout << "\t\t\t |       Your password has been edited sucessfully         |" << endl;
	cout << "\t\t\t  --------------------------------------------------------- " << endl;
	myprofile();

}
void logging()
{

	int c;
	while (true)
	{
		cout << "\t\t * 1.login As Admin.\t\t * 2.Login As Student.\t\t * 3.Sign up.\t\t * 4.Forget password.\t\t * 5.Exit." << endl;
		cout << "\n\t\t > Please Enter your choice: ";
		cin >> c; cout << endl;

		system("CLS");

		switch (c)
		{
		case 1:
			login_admin();
			break;

		case 2:
			login_student();
			break;

		case 3:
			sign_up();
			logging();
			break;

		case 4:
			forgot();
			logging();
			break;

		case 5:
			cout << endl << endl;
			cout << "\t\t\t  ------------------------------------------" << endl;
			cout << " \t\t\t|     Thank you for Using Our Library      |\t\t\t \n\n";
			cout << "\t\t\t  ------------------------------------------" << endl;
			loading2();
			loading4();
			exit(1);
			break;

		default:
			cout << "\t\t\t----> Please select from previous options <---- \t\t\t" << endl;
			break;
		}
	}

}
void intro()
{
	counter_logging = loading1();
	counter = loading3();
	logging();

}
//-----------------------------------------------student functions-----------------------------//
void info_stud()
{
	int choice, answer;
	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                                Your information                                                                                " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;

	cout << "\t\t * Name: " << student[index].student_name << endl;
	cout << "\t\t * ID: " << student[index].ID << endl;
	cout << "\t\t * Username: " << student[index].username << endl;
	cout << "\t\t * Password: " << student[index].password << endl;
	cout << "\t\t * Borrowed books: " << student[index].borrowed_books << endl;
	cout << "\t\t > Do You Want To Edit it?\n";
	cout << "\t\t\t * 1.YES\n";
	cout << "\t\t\t * 2.NO\n\n";
	cout << "\t\t > Enter your choice : ";
	cin >> choice; cout << endl;
	switch (choice)
	{
	case 1:        //from here student start edit his information
	{
		cout << "\t\t * What do You want to edit ? \n";
		cout << "\t\t\t * 1. Name \n \t\t\t * 2.ID\n \t\t\t * 3.Username\n\n \t\t\t > Enter a Choice: ";
		cin >> answer; cout << endl;
		switch (answer)
		{
		case 1:
			cout << "\t\t > Enter Your new name:"; cin >> student[index].student_name;
			system("pause");
			cout << "\t\t------> Your name has been edited successfully!! <------" << endl;
			system("CLS");
			myprofile();
			break;
		case 2:
			cout << "\t\t > Enter Your New ID:"; cin >> student[index].ID;
			system("pause");
			cout << "\t\t------> Your ID has been edited successfully!! <------" << endl;
			system("CLS");
			myprofile();
			break;
		case 3:
			cout << "\t\t > Enter Your New Username:"; cin >> student[index].username;
			system("pause");
			cout << "\t\t------> Your username has been edited successfully!! <------" << endl;
			system("CLS");
			myprofile();
			break;
		default:
			cout << "\t\t\t > Enter valid Choice:";
			info_stud();
			break;
		}

		break;
	}

	case 2:
	{
		system("CLS");
		myprofile();
		break;
	}


	default:
	{
		cout << "----> Enter a valid choice ,Please. <-----";
		break;
	}
	}
}
void myprofile()
{
	int choice;
	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                                      My profile                                                                                " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;
	cout << "\t\t * 1.Edit my information " << endl << "\t\t * 2.Change my password " << endl << "\t\t * 3.Back " << endl << "\t\t\t > Enter choice: ";
	cin >> choice;
	//system("pause");
	system("CLS");
	switch (choice)
	{
	case 1:
	{
		info_stud();
		break;
	}
	case 2:
	{
		change_password();
		break;
	}
	case 3:
	{

		main_student();
		break;
	}
	default:
	{
		myprofile();
		break;

	}
	}
}
void bookservices()
{
	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                                 Book services                                                                                  " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;
	int answer;
	int answer2;
	cout << "\t\t * 1.Display books" << endl;
	cout << "\t\t * 2.View information about specific book" << endl;
	cout << "\t\t * 3.Borrow " << endl;
	cout << "\t\t * 4.Return" << endl;
	cout << "\t\t * 5.Modify your order." << endl;
	cout << "\t\t * 6.Search about Book.  " << endl;
	cout << "\t\t * 7.Back" << endl << endl;
	cout << "\t\t\t > Enter  your choice: ";
	cin >> answer;
	system("pause");
	system("CLS");
	switch (answer)
	{
	case 1:
	{
		while (true)
		{

			cout << "\t\t * 1.Display all books." << endl;
			cout << "\t\t * 2.Display availaible books." << endl << endl;
			cout << "\t\t > Enter your choice:";

			cin >> answer2;
			system("pause");
			system("CLS");
			if (answer2 == 1)
			{
				display_booklist();
				bookservices();
				break;
			}
			else if (answer2 == 2)
			{
				display_available_books_only();
				bookservices();
				break;
			}
			else {
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "\t\t\t|                 Invalid choice!           |" << endl;
				cout << "\t\t\t---------------------------------------------" << endl << endl;
				cout << "\t\t Please, try again: \n";
				continue;
			}
		}
		break;
	}
	case 2:
	{
		book_info();
		break;
	}
	case 3:
	{
		borrowbook();
		break;
	}
	case 4:
	{
		returnbook();
		break;
	}
	case 5:
	{
		Modify_order();
		break;
	}
	case 6:
	{
		int choice;


		while (true)
		{

			cout << "\t\t * Do you want to search by:\n";
			cout << "\t\t\t * 1.Author name";
			cout << "\t\t\t * 2.Category\n\n";
			cout << "\t\t > Enter choice:";
			cin >> choice;
			system("pause");
			system("CLS");
			if (choice == 1)
			{
				search_author();
				bookservices();
				break;
			}
			else if (choice == 2)
			{
				search_category();
				bookservices();
				break;
			}
			else {
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "\t\t\t|                 Invalid choice!           |" << endl;
				cout << "\t\t\t---------------------------------------------" << endl << endl;
				cout << "\t\t Please, try again: \n";
				continue;
			}
		}
		break;
	}
	case 7:
	{
		main_student();
		break;
	}
	default:
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|                 Invalid choice!           |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl << endl;
		cout << "\t\t Please, try again: \n";
		bookservices();
		break;
	}
}
void display_booklist()
{
	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                                    list of books:                                                                              " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t" << "Book name" << "\t\t\t" << "Book code" << "\t\t\t" << "Book edition" << "\t\t\t" << "Book category" << "\t\t\t" << "Author name" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


	;	for (int i = 0; i < counter; i++)
	{
		cout << "\t\t|" << books[i].book_name << "\t\t\t|" << books[i].code << "\t\t\t|" << books[i].edition << "\t\t\t|" << books[i].category << "\t\t\t|" << books[i].author_name << endl;
	}
	system("pause");
	system("CLS");
}
void display_available_books_only()
{
	bool found = 0;

	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                          list of available books:                                                                              " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t" << "Book name" << "\t\t\t" << "Book code" << "\t\t\t" << "Book edition" << "\t\t\t" << "Book category" << "\t\t\t" << "Author name" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < counter; i++)
	{
		if (books[i].available == 1)
		{
			cout << "\t\t|" << books[i].book_name << "\t\t\t|" << books[i].code << "\t\t\t|" << books[i].edition << "\t\t\t|" << books[i].category << "\t\t\t|" << books[i].author_name << endl;
			found = 1;
		}
	}
	system("pause");
	system("CLS");

	if (found == 0)//system does not contain any available books==all books in system have been borrowed
	{
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\tNo Avaliable books right now\n\n";
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		system("pause");
		system("CLS");
	}
}
void book_info()
{
	string title;
	int found = 0;

	cout << "\t\t Please, enter the name of the book: ";
	cin.ignore();
	getline(cin, title);
	for (int i = 0; i < counter; i++) {
		if (books[i].book_name == title) {
			found = 1;
			cout << "****************************************************************************************************************************************************************" << endl;
			cout << "                                                             Book Information:                                                                                  " << endl;
			cout << "****************************************************************************************************************************************************************" << endl << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t\t" << "Book name" << "\t\t\t" << "Book code" << "\t\t\t" << "Book edition" << "\t\t\t" << "Book category" << "\t\t\t" << "Author name" << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t\t|" << books[i].book_name << "\t\t\t\t|" << books[i].code << "\t\t\t|" << books[i].edition << "\t\t\t|" << books[i].category << "\t\t\t|" << books[i].author_name << endl;
			system("pause");
			system("CLS");
			bookservices();

		}
	}
	if (found == 0)
	{
		cout << "\t\t\t -------------------------------------" << endl;
		cout << "\t\t\t |" << "  Book does not exist in our library   |" << endl;
		cout << "\t\t\t -------------------------------------" << endl;
		bookservices();
	}

}
void borrowbook()
{
	int code;
	int answer; int ans;
	bool found1 = 0;
	bool found2 = 0;
	bool found3 = 0;

	cout << "\t\t > Enter the code of the book you want to borrow: ";
	cin >> code;
	for (int i = 0; i < counter; i++)
	{
		//---------------------book is found----------------//
		if (code == books[i].code && books[i].available == 1)
		{
			if (student[index].full == 0)            //student has not borrowed any book
			{
				found1 = 1;
				books[i].available = 0;               //now book not available
				student[index].borrowed_books = books[i].book_name;
				student[index].full = 1;        //now he can not borrow another book
				break;
			}
			else if (student[index].full == 1)    //student already borrow book 
			{
				cout << "\t\t\t * You have a book already in your borrowed book list, you should return it first! *" << endl;
				cout << "\t\t\t * Do you want to return it? " << endl;
				cout << "\t\t\t * 1.Yes" << endl << "\t\t\t * 2.No";
				cout << "\t\t\t > Enter your choice:";
				cin >> answer;
				if (answer == 1)
					returnbook();
				else if (answer == 2)
					bookservices();
			}


		}

		//--------------the book is not avalaible-------------------//
		else if (code == books[i].code && books[i].available == 0)
		{
			found2 = 1;
		}
		//---------------------------invaild code---------------------//
		else if (code != books[i].code)
		{
			found3 = 1;
		}
	}
	if (found1 == 1)
	{
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|  Your book has been borrowed sucessfully! |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl;
		date();
		while (true)
		{
			cout << "\t\t Do you want to see the feedback about this book?" << endl << endl;
			cout << "\t\t\t * 1.YES";
			cout << "\t\t\t * 2.NO";
			cout << "\t\t\t > Enter Choice : ";
			int ans;
			cin >> ans;
			system("pause");
			system("CLS");
			if (ans == 1)
			{
				displayfeedback(code);
				bookservices();
				break;
			}
			else if (ans == 2)
			{
				bookservices();
				break;
			}
			else
			{
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "\t\t\t|                 Invalid choice!           |" << endl;
				cout << "\t\t\t---------------------------------------------" << endl << endl;
				cout << "\t\t * Please, try again\n";
				//continue;

			}
		}
	}
	else if (found2 == 1)
	{
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|      Book is not available right now!     |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl << endl;

		cout << "\t\t * 1.Try again";
		cout << "\t\t * 2.Back.";
		cout << "\t\t > Enter Choice : ";
		while (cin >> ans)
		{

			switch (ans)
			{
			case 1:
				borrowbook();
				break;

			case 2:
				bookservices();
				break;

			default:
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "\t\t\t|                 Invalid choice!           |" << endl;
				cout << "\t\t\t---------------------------------------------" << endl << endl;
				cout << "\t\t * Please, try again\n";
				continue;

			}
		}

	}
	else if (found3 == 1) {
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|                 Invalid Code!           |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl << endl;
		cout << "\t\t * Do you want to try again?";

		cout << "\t\t * 1.Yes.\n\t\t * 2.No. \n\n \t\t  > Enter Choice: ";
		cin >> answer; cout << endl;
		system("pause");
		system("CLS");
		if (answer == 1)
			borrowbook();
		else
			bookservices();
	}

}
void returnbook()
{
	int code;
	bool found1 = 0, found2 = 0;
	//int answer = 1;
	int ans;
	cout << "\t\t > Enter the code of the book you want to return: ";
	cin >> code;
	int i;
	for (i = 0; i < counter; i++)
	{
		if (code == books[i].code && books[i].book_name == student[index].borrowed_books)//user enter correct code and this is the code of his borrowed book
		{
			found1 = 1;
			books[i].available = 1;
			student[index].borrowed_books = "You do not have borrowed books";                   //put null value in student info (erase==clear)
			student[index].full = 0;                                              //user now can borrow book

			//----------- return boorowed book !!-----------------//
			break;
		}
		else if (code == books[i].code && books[i].book_name != student[index].borrowed_books)//user enter correct code and this is not the code of his borrowed book
		{
			found2 = 1;
			break;

		}
	}
	if (found1 == 1)
	{
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|  Your book has been returned sucessfully! |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl << endl;
		cout << "\t\t * 1.Bookservice." << endl;
		cout << "\t\t * 2.Feedback." << endl << "\t\t\t > Enter Choice:";
		cin >> ans; cout << endl;
		switch (ans)
		{
		case 1:
			system("CLS");
			bookservices();
			break;
		case 2:
			cout << "\t\t > Enter your feedback:";
			cin.ignore();
			getline(cin, books[i].feedback);
			cout << "\t\t\t---------------------------------------------" << endl;
			cout << "\t\t\t|          Your feedback is saved!          |" << endl;
			cout << "\t\t\t---------------------------------------------" << endl << endl;
			system("pause");
			system("CLS");
			bookservices();
			break;
		default:
			cout << "\t\t\t---------------------------------------------" << endl;
			cout << "\t\t\t|                 Invalid choice!           |" << endl;
			cout << "\t\t\t---------------------------------------------" << endl << endl;
			cout << "\t\t * Please, try again\n";
			break;
		}

	}
	else if (found2 == 1)
	{
		cout << "\t\t\t ----> You have not borrowed this book!! <---- \n\n";
		while (true)
		{
			cout << "\t\t * 1.Try again";
			cout << "\t\t * 2.Back." << endl;
			cout << "\t\t > Enter a Choice : ";
			cin >> ans;

			switch (ans)
			{
			case 1:
				returnbook();
				break;

			case 2:
				bookservices();
				break;

			default:
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "\t\t\t|                 Invalid choice!           |" << endl;
				cout << "\t\t\t---------------------------------------------" << endl << endl;
				cout << "\t\t * Please, try again\n";
			}
		}
	}
	else
	{
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|                 Invalid Code!           |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl << endl;

		while (true)
		{
			cout << "\t\t * 1.Try again";
			cout << "\t\t * 2.Back." << endl;
			cout << "\t\t > Enter a Choice : ";
			cin >> ans;

			switch (ans)
			{
			case 1:
				returnbook();
				break;

			case 2:
				bookservices();
				break;

			default:
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "\t\t\t|                 Invalid choice!           |" << endl;
				cout << "\t\t\t---------------------------------------------" << endl << endl;
				cout << "\t\t * Please, try again\n";
				continue;

			}
		}
	}


}
void Modify_order()
{
	int ans;
	bool exist = 0;
	bool found1 = 0;
	bool found2 = 0;
	bool found3 = 0;
	int code;
	cout << "Enter the code of the book that you have already borrowed: ";
	cin >> code;
	for (int i = 0; i < counter; i++)
	{
		if (books[i].code == code && books[i].book_name == student[index].borrowed_books)
		{
			books[i].available = 1;
			exist = 1;
		}
	}
	if (exist == 0) {
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|                 Invalid code!             |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t Do you want to try again ?\n\t\t* 1.YES.\n\t\t * 2.NO.\n \n\t\t > Enter Choice: ";
		cin >> answer;
		system("pause");
		system("CLS");
		cout << endl;
		if (answer == 1)
			Modify_order();
		else
			bookservices();
	}

	cout << "Enter the code of the book you want to replace: ";
	cin >> code;
	for (int i = 0; i < counter; i++)
	{

		//---------------------book is found----------------//
		if (code == books[i].code && books[i].available == 1)
		{
			student[index].borrowed_books = books[i].book_name;
			books[i].available = 0;
			found1 = 1;
		}
		else if (code == books[i].code && books[i].available == 0)
		{
			found2 = 1;
		}
		//---------------------------invaild code---------------------//
		else if (code != books[i].code)
		{
			found3 = 1;
		}

	}
	if (found1 == 1)
	{

		cout << "\t\t\t----------------------------------------------" << endl;
		cout << "\t\t\t| Your order has been modified successfully!!|\t\t\t\n";
		cout << "\t\t\t----------------------------------------------" << endl;
		bookservices();
	}
	else if (found2 == 1)
	{
		cout << "\t\t\t----------------------------------------------" << endl;
		cout << "\t\t\t|    Book is not available right now          |\t\t\t\n";
		cout << "\t\t\t----------------------------------------------" << endl;
		cout << "1.Try again \n2.Back. \n \n Enter Choice:";
		while (cin >> ans)
		{

			switch (ans)
			{
			case 1:
				Modify_order();
				break;

			case 2:
				bookservices();
				break;

			default:
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "\t\t\t|                 Invalid choice!           |" << endl;
				cout << "\t\t\t---------------------------------------------" << endl;
				cout << "Please, enter valid choice \n";
				cout << "1.Try again \n2.Back. \n \n Enter Choice:";
				continue;
			}
		}

	}
	else if (found3 == 1) {
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t| This book is not included in our system    |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t Do you want to try again ?\n\t\t* 1.YES.\n\t\t * 2.NO.\n \n\t\t > Enter Choice: ";
		cin >> answer;
		system("pause");
		system("CLS");
		cout << endl;
		if (answer == 1)
			Modify_order();
		else
			bookservices();
	}
}
void main_student()
{
	int answer;

	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                                    Main menu                                                                                   " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;

	cout << "\t\t\t * 1.Book Service " << endl;
	cout << "\t\t\t * 2.My Profile " << endl;
	cout << "\t\t\t * 3.Log out" << endl << endl;
	cout << "\t\t\t > Enter choice: ";
	cin >> answer;
	system("CLS");
	switch (answer)
	{
	case 1:
	{
		bookservices();

		break;
	}
	case 2:
	{
		myprofile();
		break;
	}
	case 3:
	{
		logging();
		break;
	}
	default:

		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|                 Invalid choice!           |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl << endl;

		main_student();
		break;

	}
}
//----------------------------------------------admin function------------------------------------------------//
void ModifyBookInfo()
{
	int admincode; bool found = 0; int admin_choice; // admin's choice about what he wants to modify 
	cout << "\t\t > Please Enter the code of the book you want to modify it's information: ";
	cin >> admincode;
	for (int i = 0; i < book_limit; i++)
	{
		if (books[i].code == admincode)
		{
			found = 1;

			cout << "\t\t * 1.Modify book's code" << endl;
			cout << "\t\t * 2.Modify book's eddition" << endl;
			cout << "\t\t * 3.Modify book's name" << endl;
			cout << "\t\t * 4.Modify author name of the book" << endl;
			cout << "\t\t * 5.Modify book's category" << endl;
			cout << "\t\t * 6.Check if the book is available or not" << endl;
			cout << "\t\t * 7.Modify all book's information" << endl;
			cout << "\t\t > Enter choice:";
			cin >> admin_choice;
			cout << ">>" << endl;
			system("Pause");
			system("CLS");
			switch (admin_choice)
			{

			case 1:  cout << "\t\t > Modify code of the book:";
				cin >> books[i].code;
				cout << "\t\t\t------------------------------------------------" << endl;
				cout << "\t\t\t|   You have successfully changed book's code   |\t\t\t\n";
				cout << "\t\t\t------------------------------------------------" << endl;
				cout << "\t\t\t\t\t * It's new one is: " << books[i].code << endl;
				break;

			case 2:  cout << ">>Modify editon of the book: ";
				cin >> books[i].edition;
				cout << "\t\t\t-------------------------------------------------" << endl;
				cout << "\t\t\t|  You have successfully changed book's edition  |\t\t\t\n";
				cout << "\t\t\t-------------------------------------------------" << endl;
				cout << "\t\t\t\t * It's new one is: " << books[i].edition << endl;
				break;

			case 3:
				cout << ">>Modify name of the book: ";
				cin.ignore();
				getline(cin, books[i].book_name);
				cout << "\t\t\t----------------------------------------------" << endl;
				cout << "\t\t\t|  You have successfully changed book's name  |\t\t\t\n";
				cout << "\t\t\t----------------------------------------------" << endl;
				cout << "\t\t\t\t * It's new one is:" << books[i].book_name << endl;
				break;

			case 4:
				cout << ">>Modify author name of the book: ";
				cin.ignore();
				getline(cin, books[i].author_name);
				cout << "\t\t\t --------------------------------------------------" << endl;
				cout << "\t\t\t| You have successfully changed book's author name  |\t\t\t\n";
				cout << "\t\t\t --------------------------------------------------" << endl;
				cout << "\t\t\t * It's new one is:" << books[i].author_name << endl;
				break;

			case 5:   cout << ">>Modify category of the book: ";
				cin.ignore();
				getline(cin, books[i].category);
				cout << "\t\t\t ----------------------------------------------" << endl;
				cout << "\t\t\t| You have successfully changed book's category |\t\t\t\n";
				cout << "\t\t\t ----------------------------------------------" << endl;
				cout << "\t\t\t * It's new one is:" << books[i].category << endl;
				break;

			case 6:
				cout << "\t\t\t\t\t\t  -----------------------------------------" << endl;
				cout << "\t\t\t\t\t\t |    Check if the book is available or not    |" << endl;
				cout << "\t\t\t\t\t\t ------------------------------------------" << endl;
				cout << "\t\t\t > Enter 1 if it's available or 0 if it's not available: ";
				cin >> books[i].available;
				break;
			case 7:
				cout << "\t\t>> Modify code of the book:";
				cin >> books[i].code;
				cout << "\t\t>> Modify editon of the book:";
				cin >> books[i].edition;
				cout << "\t\t>> Modify name of the book:";
				cin.ignore();
				getline(cin, books[i].book_name);

				cout << "\t\t>> Modify author name of the book:";
				getline(cin, books[i].author_name);

				cout << "\t\t>> Modify category of the book:";
				getline(cin, books[i].category);

				cout << "\t\t---->Check if the book is available or not<----" << endl;
				cout << "\t\t > Enter 1 if it's available or 0 if it's not available: ";
				cin >> books[i].available;
				cout << "\t\t\t ----------------------------------------------------" << endl;
				cout << "\t\t\t|You have successfully changed all books's information|\t\t\t\n" << endl;
				cout << "\t\t\t ----------------------------------------------------" << endl << endl;
				cout << "\t\t * Book's new name:" << books[i].book_name << endl;
				cout << "\t\t * Book's new code:" << books[i].code << endl;
				cout << "\t\t * Book's new edition: " << books[i].edition << endl;
				cout << "\t\t * Book's new category: " << books[i].category << endl;
				cout << "\t\t * Book's new author name: " << books[i].author_name << endl;
				break;

			default:
				cout << "\t\t\t ------------------------------------------" << endl;
				cout << "\t\t\t|            Invalid choice!!             | \n";
				cout << "\t\t\t ------------------------------------------" << endl;
				cout << "----> Please, choose again <-----" << endl;
				ModifyBookInfo();
				break;
			}
			break;
		}
	}
	if (found == 0)

	{
		cout << "\t\t\t ------------------------------------------" << endl;
		cout << "\t\t\t|            Invalid code!!              | \n";
		cout << "\t\t\t ------------------------------------------" << endl;
		cout << "\t\t\t Do you want to try again ?\n\t\t* 1.YES.\n\t\t * 2.NO.\n \n\t\t > Enter Choice: ";
		cin >> answer; cout << endl;
		if (answer == 1)
			ModifyBookInfo();
		else
			main_admin();

	}
}
void addbook()
{
	bool found = 0; int code;
	cout << "\t\t > Add code of the book:";
	cin >> code;
	for (int i = 0; i < counter; i++)
	{
		if (books[i].code == code)
		{
			found = 1;
			break;
		}
	}
	if (found == 1)
	{
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|             Code already exists!          |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t * Please, try again\n";
		addbook();

	}
	else
	{
		books[counter].code = code;
		cout << "\t\t * Add edition of the book (Please, enter numbers) : ";
		cin >> books[counter].edition;
		cout << "\t\t * Add the name of the book: ";
		cin.ignore();
		getline(cin, books[counter].book_name);
		cout << "\t\t * Add author's name of the book: ";
		getline(cin, books[counter].author_name);
		cout << "\t\t * Add category of the book: ";
		getline(cin, books[counter].category);

		books[counter].available = 1;
		counter++;                        //now counter increased
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|         Book is added succefully!!         |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << endl;
		system("pause");
		system("CLS");
	}
}
void deletebook()
{

	int book_code, found = 0, answer;

	cout << "\t\t > Enter the code of the book you want to delete:"; cin >> book_code; cout << endl;

	for (int i = 0; i < counter; i++)
	{
		if (books[i].code == book_code)
		{
			//for loop to delete the book
			for (int j = i; j < counter; j++)
			{

				books[j] = books[j + 1];
				found = 1;
				i--;
			}
			counter--;
			break;

		}

	}
	//to check if the book was deleted croctly
	if (found == 0)
	{
		cout << "\t\t\t ------------------------------------------" << endl;
		cout << "\t\t\t|            Invalid code!!             | \n";
		cout << "\t\t\t ------------------------------------------" << endl;

		cout << "\t\t * Do you want to try again?";

		cout << "\t\t * 1.Yes.\n\t\t * 2.No. \n\n \t\t  > Enter Choice: ";
		cin >> answer; cout << endl;
		system("pause");
		system("CLS");
		if (answer == 1)
			deletebook();
		else
			main_admin();

	}
	else
	{
		cout << "\t\t ---------------------------------" << endl;
		cout << "\t\t|          Book is deleted!!      |\t\t" << endl;
		cout << "\t\t ---------------------------------" << endl;
		cout << "\t\t * Do you want to delete another book?\n";
		cout << "\t\t * 1.YES.\n\t\t * 2.NO.\n \n\t\t > Enter Choice: ";
		cin >> answer; cout << endl;
		system("pause");
		system("CLS");
		if (answer == 1)
			deletebook();
		else
			main_admin();
	}
}
void main_admin()
{
	int answer;
	cout << endl;
	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                                    Main menu                                                                                   " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;
	cout << "* 1.Add book." << endl;
	cout << "* 2.Modify book information. " << endl;
	cout << "* 3.Delete book. " << endl;
	cout << "* 4.Display student information." << endl;
	cout << "* 5.Edit student information. " << endl;
	cout << "* 6.Log out. " << endl; //hyrg3ne ll log in & sign up 
	cout << "* 7.Exit from system. " << endl << endl;

	cout << " \t\t\t<<Enter your choice: ";
	cin >> answer; cout << ">>" << endl;
	system("CLS");
	switch (answer)
	{
	case 1:
	{
		addbook();
		main_admin();
		break;
	}
	case 2:
	{
		ModifyBookInfo();
		main_admin();
		break;
	}
	case 3:
	{
		deletebook();
		main_admin();
		break;
	}
	case 4:
	{
		displaystudentinfo();
		main_admin();
		break;
	}
	case 5:
	{
		displaystudentinfo_for_admin();
		main_admin();
		break;
	}
	case 6:
	{
		logging();
		break;
	}
	case 7:
	{
		cout << endl << endl;
		cout << "\t\t\t  ------------------------------------------" << endl;
		cout << " \t\t\t|     Thank you for Using Our Library      |\t\t\t \n\n";
		cout << "\t\t\t  ------------------------------------------" << endl;
		loading4();
		exit(1);

		break;
	}
	default:
		cout << "\t\t\t ------------------------------------------" << endl;
		cout << "\t\t\t|            Invalide choice!!             | \n";
		cout << "\t\t\t ------------------------------------------" << endl;
		cout << "---->Choose another choice: ";
		main_admin();
		break;
	}
}
//-------------------------------------------------features-------------------------------------------------//
void displaystudentinfo()
{
	int id;

	bool found = 0;
	cout << "\t\t\t > Please, Enter ID of student:";
	cin >> id;

	if (counter_logging == 0)//no students in system
	{
		cout << " \t\t\t -------> There is no student in our system to display his information. <-------";
		main_admin();
	}
	else
	{
		for (int i = 0; i < counter_logging; i++)
		{
			if (student[i].ID == id)
			{
				found = 1;
				cout << "\t\t * Name: " << student[i].student_name << endl;
				cout << "\t\t * ID: " << student[i].ID << endl;
				cout << "\t\t * Username: " << student[i].username << endl;
				cout << "\t\t * Password: " << student[i].password << endl;
				cout << "\t\t * Borrowed Book: " << student[i].borrowed_books << endl;
				system("pause");
				system("CLS");
				main_admin();
				break;
			}
		}
	}
	if (found == 0)
	{
		cout << "\t\t\t---------------------------------------------" << endl;
		cout << "\t\t\t|                 Invalid ID!           |" << endl;
		cout << "\t\t\t---------------------------------------------" << endl << endl;
		cout << "\t\t * Please, try again\n";
		displaystudentinfo();
	}

}
int displaystudentinfo_for_admin() //Edit student info
{
	int choice, answer, id, student_index;
	bool found = 0;


	cout << "Enter the ID of the specific student: ";
	cin >> id;//2022170
	for (int i = 0; i < students_number; i++)
	{
		if (id == student[i].ID)
		{
			found = 1;
			student_index = i;
			break;
		}
	}
	if (found == 0)
	{
		cout << "\t\t\t\t\t\t\t\t\t\t-------Invalid ID!!-------" << endl;
		cout << "\t\t * Do you want to try Again?\n";
		cout << "\t\t * 1.YES.\n\t\t * 2.NO.\n \n\t\t > Enter Choice: ";
		cin >> answer;
		cout << endl;
		system("pause");
		system("CLS");
		if (answer == 1)
			displaystudentinfo_for_admin();
		else
			main_admin();
	}
	else
	{
		cout << "1. Edit information For Specific student " << endl << "2.Delete Specific Student." << endl << "3.Back" << endl << "Enter choice:";
		cin >> choice;
		system("pause");
		system("CLS");
		switch (choice)
		{
		case 1:
		{
			cout << "What Do You Want to Edit:" << endl;
			cout << "1.Name\n2.ID\n3.Username\n Enter Choice:";

			cin >> answer; cout << endl;
			//------------------------------Edit information----------------------------------//
			switch (answer)
			{
			case 1:
				cout << "Enter new name:";
				cin.ignore();
				getline(cin, student[student_index].student_name);
				cout << " \t\t\t\t\tYour name is edited successfully!!";
				system("pause");
				system("CLS");
				main_admin();
				break;

			case 2:
				cout << "Enter New ID:"; cin >> student[student_index].ID;
				cout << " Your ID is edited successfully!!";
				system("pause");
				system("CLS");
				main_admin();


				break;
			case 3:
				cout << "Enter New Username:";
				cin.ignore();
				getline(cin, student[student_index].username);
				cout << "\t\t\t\t\t\t\t\t\t\tYour Username is edited successfully!!";
				system("CLS");
				displaystudentinfo_for_admin();


				break;
			default:
				cout << "\t\t\t\t\t\t\t\t\t\t-------Invalid choice!!-------" << endl;
				cout << "Please, try Again";
				displaystudentinfo_for_admin();
				break;
			}
			break;

		}
		case 2:
		{
			student[student_index].ID = 0;  //show
			student[student_index].student_name.erase();
			student[student_index].username.erase();
			student[student_index].password.erase();
			student[student_index].borrowed_books.erase();
			cout << "\t\t\t\t\t All information about this student is deleted successfully!!";
			break;
		}
		case 3:
		{
			main_admin();
			break;
		}
		default:
		{
			cout << "\t\t\t\t\t\t\t\t\t\t-------Invalid choice!!-------" << endl;
			cout << "Please, try Again";
			break;
		}
		}
	}

	return 0;
}
int displayfeedback(int code)
{
	cout << "****************************************************************************************************************************************************************" << endl;
	cout << "                                                                     Feedback                                                                                   " << endl;
	cout << "****************************************************************************************************************************************************************" << endl << endl;
	for (int i = 0; i < book_limit; i++)
	{
		if (code == books[i].code)
		{
			cout << "\t\t\t * The feedback of this book is: " << books[i].feedback << endl;
		}
	}
	system("pause");
	system("CLS");
	return 0;
}
int date()
{
	int day, month, year;
	cout << "\t\t * Enter the date of the day of borrowing (DD MM 2023): " << endl;
	cout << "\t\t\t * Day:";
	cin >> day;
	cout << endl;
	cout << "\t\t\t * Month:";
	cin >> month;
	cout << endl;
	cout << "\t\t\t * Year:";
	cin >> year;
	cout << "\n\n";
	while (year != 2023) {
		system("pause");
		system("CLS");
		cout << "\t\t\t ----> Enter date in year 2023 <---- " << endl;
		cout << "\t\t * Enter the date again:";
		cout << "\t\t\t * Day:";
		cin >> day;
		cout << endl;
		cout << "\t\t\t * Month:";
		cin >> month;
		cout << endl;
		cout << "\t\t\t * Year:";
		cin >> year;
		cout << "\n\n";
	}
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:

		if (day >= 26 && day < 31) {
			for (int i = 0; i < 5; i++) {
				day = day + 1;
				if (day == 31)
				{
					day = 1;
					month += 1;
				}
			}
			cout << "\t ----> You should return the book before:" << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}

		else if (day == 31)
		{
			day = 6;
			month += 1;
			cout << "\t ----> You should return the book before:" << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}

		else if (day < 26)
		{
			day += 5;
			cout << "\t ----> you should return the book before:" << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}
	case 4:
	case 6:
	case 9:
	case 11:
		if (day >= 25 && day < 30) {
			for (int i = 0; i < 5; i++) {
				day = day + 1;
				if (day == 30)
				{
					day = 1;
					month += 1;
				}
			}
			cout << "\t ----> You should return the book before:" << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}

		else if (day == 30)
		{
			day = 6;
			month += 1;
			cout << "\t ----> You should return the book before:" << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}

		else if (day < 25)
		{
			day += 5;
			cout << "\t ----> You should return the book before:" << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}
	case 2:
		if (day >= 23 && day < 28) {
			for (int i = 0; i < 5; i++) {
				day = day + 1;
				if (day == 28)
				{
					day = 1;
					month += 1;
				}
			}
			cout << "\t ----> You should return the book before: " << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}
		else if (day == 28)
		{
			day = 6;
			month += 1;
			cout << "\t ----> You should return the book before: " << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}

		else if (day < 23)
		{
			day += 5;
			cout << "\t ----> You should return the book before: " << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}

	case 12:
		if (day >= 25 && day < 30) {
			for (int i = 0; i < 5; i++) {
				day = day + 1;
				if (day == 30)
				{
					day = 1;
					month = 1;
					year += 1;
				}
			}
			cout << "\t ----> You should return the book before: " << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}
		else if (day == 30)
		{
			day = 6;
			month = 1;
			year += 1;
			cout << "\t ----> You should return the book before: " << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}
		else if (day < 25)
		{
			day += 5;
			cout << "\t ----> You should return the book before: " << day << "-" << month << "-" << year << " <----" << endl << endl;
			break;
		}

	default:
		break;
	}
	return 0;

}
void search_author()
{
	int ans;
	bool available = 0;
	string author;
	cout << "\t\t\t > Enter the name of the author to display his books: ";
	int index = 0;
	cin.ignore();
	getline(cin, author);

	for (int i = 0; i < counter; i++)
	{
		if (author == books[i].author_name)
		{
			index++;
			available = 1;
			cout << "\t\t | Book's no." << index << " name is: " << books[i].book_name << endl << endl;
			continue;
		}
	}
	if (available == 0)
	{
		cout << "\t\t ----> No available books right now for this author <----\n";
		cout << "\t\t\t  * Do you want to enter another?";
		cout << "\t\t * 1.Yes\n";
		cout << "\t\t * 2.No \n\t > Enter choice: ";
		cin >> ans;
		if (ans == 1)
		{
			search_author();
		}
		else
		{
			bookservices();
		}
	}
	system("pause");
	system("CLS");
}
void search_category()
{
	int ans;
	bool available = 0;
	string category;
	int index = 1;
	cout << "\t\t > Enter the category: ";
	cin.ignore();
	getline(cin, category); cout << endl;

	for (int i = 0; i < counter; i++)
	{
		if (books[i].category == category)
		{
			cout << "\n |Book's no. " << index << " name is: " << books[i].book_name << "|" << endl;
			index++;
			available = 1;
			continue;
		}
	}
	if (available == 0)
	{
		cout << "\t\t  -------------------------------------------------------" << endl;
		cout << "\t\t |       No available books right now in this category    |" << endl;
		cout << "\t\t  --------------------------------------------------------" << endl;
		cout << "\t\t * Do you want to try again?";
		cout << "\t\t\t * 1.Yes\n\t\t\t * 2.No\n \t > Enter choice: ";
		cin >> ans; cout << endl;
		if (ans == 1)
		{
			search_category();
		}
		else
		{
			bookservices();
		}
	}
}
