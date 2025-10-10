#include <iostream>
#include "clsLoginScreen.h"

using namespace std;

//  Enter Username? = Admin
//  Enter Password? = Admin

int main()
{

	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}

	system("pause>0");
	return 0;
}