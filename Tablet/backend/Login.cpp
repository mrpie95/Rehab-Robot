#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, wchar_t* argv[])
{
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<html>\n<head>\n<title>Log In Page</title>\n</head>\n";
	cout << "<body>\n";

	cout << "<h2>Log In</h2>\n";
	cout << "<form action='landingpage.html'>\n";
	cout << "Username:<br>\n<input type = 'text' name = 'username' value = ''>\n<br>\n";
	cout << "Password : <br>\n<input type = 'text' name = 'password' value = ''>\n<br>\n<br>\n";
	cout << "<a href='Register.cgi'>Register<br></a><a href=ForgotPassword.cgi>Forgot Password</a><br><br>\n";
	cout << "<input type ='submit' value = 'Log in'>\n</form>\n";

	cout << "</body>\n";
	cout << "</html>\n";
	return 0;
}