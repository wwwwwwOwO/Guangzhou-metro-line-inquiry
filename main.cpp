#include"SubwaySystem.h"
void menu(){
	cout << "Welcome to Guangzhou Subway System." << endl;
	cout << "       1.Line Inquiry" << endl;
	cout << "       2.Site Inquiry" << endl;
	cout << "       3.Route Inquiry" << endl;
	cout << "Your choice:" << endl;
}
int main(){
	string Dataname = "data.txt";
	SubwaySystem sol(Dataname);
	int choice;
	menu();
	cin >> choice;
	switch (choice)
	{
		case 1:
			sol.Line_Inquiry();
			break;
		case 2:
			sol.Site_Inquiry();
			break;
		case 3:
			sol.Route_Inquiry();
			break;
		default:
			cout << "Error!" << endl;
			break;
	}
	system("pause");
}
//Higher Education Mega Center North
//Dongshankou