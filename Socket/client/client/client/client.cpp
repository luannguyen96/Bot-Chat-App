// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "client.h"
#include"afxsock.h"
#include"setText.h"
#include<string>
#include<conio.h>
#include<Windows.h>
#include <stdio.h>
#include <windows.h>
#include<ctime>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

CSocket client;

int getStringLength(string x){
	return x.length();
}

char *stringToCharx(string x){
	int temp = x.length();
	char* a = new char[temp];
	strcpy(a, x.c_str());
	return a;
}



void sendMess(CSocket &client, int length, char *mess){
	client.Send(&length, sizeof(length), 0);
	client.Send(mess, length, 0);
}

void receiveMess(CSocket &client, int &length, char *&mess){
	client.Receive((char*)&length, sizeof(int), 0);
	mess = new char[length + 1];
	client.Receive(mess, length, 0);
	mess[length] = '\0';
	TextColor(10);
	cout << "Server sent: " << mess << endl;
}


void inputAndSendString(CSocket &client){
	string x;
	int length;
	getline(cin, x);
	length = getStringLength(x);
	sendMess(client, length, stringToCharx(x));


}

string convertInt(int x){
	return to_string((long double)x);
}

void dangki(CSocket &client, int length, char *mess, int &deadline){
	
	int check;
	string tam;
	do{
		receiveMess(client, length, mess);
		do{
			fflush(stdin);
			cin.clear();
			getline(cin, tam);
			if (tam.length() < 7){
				TextColor(12);
				cout << "ten dang nhap phai co it nhat 7 ki tu, vui long nhap lai\n";
			}
		} while (tam.length() < 7);

		sendMess(client, tam.length(), stringToCharx(tam));
		//time
		client.Receive((char*)&deadline, sizeof(int), 0);
		if(deadline == 1)
		{
			check = 0;
			receiveMess(client, length, mess);
			return;
		}
		else
		{
			client.Receive((char*)&check, sizeof(check), 0);
			if (check == 1){
				receiveMess(client, length, mess);
		
			}
			else{
				break;
			}
		}
	} while (check == 1);
	
	//password
	receiveMess(client, length, mess);
	
	do{
		fflush(stdin);
		cin.clear();
		getline(cin, tam);
		if (tam.length() < 5){
			TextColor(12);
			cout << "mat khau phai co it nhat 5 ki tu, vui long nhap lai\n";
		}
	} while (tam.length() < 5);
	//gui password
	sendMess(client, tam.length(), stringToCharx(tam));
	//time
	client.Receive((char*)&deadline, sizeof(int), 0);
	if(deadline == 1)
	{
		check = 0;
		receiveMess(client, length, mess);
		return;
	}
	receiveMess(client, length, mess);
	receiveMess(client, length, mess);
}


void dangnhap(CSocket &client, int length, char *mess,int& deadline){
	int check;
	do{
		receiveMess(client, length, mess);
		string tam;
		fflush(stdin);
		getline(cin, tam);
		sendMess(client, tam.length(), stringToCharx(tam));
		//time
		client.Receive((char*)&deadline, sizeof(int), 0);
		if(deadline == 1)
		{
			check = 0;
			receiveMess(client, length, mess);
			return;
		}
		receiveMess(client, length, mess);
		getline(cin, tam);
		sendMess(client, tam.length(), stringToCharx(tam));
		//time
		client.Receive((char*)&deadline, sizeof(int), 0);
		if(deadline == 1)
		{
			check = 0;
			receiveMess(client, length, mess);
			return;
		}
		client.Receive((char*)&check, sizeof(check), 0);
		if (check == 0){
			receiveMess(client, length, mess);
		}
	} while (check == 0);
}
void datHang(CSocket &client, int length, char *mess, int &solan, int &deadline){
	solan = 0;
	int x;
	string tam;
	int cont;
	do{
		do{
			receiveMess(client, length, mess);
			fflush(stdin);
			getline(cin, tam);
			solan++;

			sendMess(client, tam.length(), stringToCharx(tam));
			//time
			client.Receive((char*)&deadline, sizeof(int), 0);
			if(deadline == 1)
			{
				receiveMess(client, length, mess);
				return;
			}
			do{

				fflush(stdin);
				cin.clear();

				receiveMess(client, length, mess);
				cin >> x;
			} while (x <= 0 || x > 9999);

			client.Send((char*)&x, sizeof(int), 0);
			//time
			client.Receive((char*)&deadline, sizeof(int), 0);
			if(deadline == 1)
			{
				receiveMess(client, length, mess);
				return;
			}
			client.Receive((char*)&x, sizeof(x), 0);
			receiveMess(client, length, mess);
		} while (x == 0);
		int temp;
		//receiveMess(client, length, mess);
		do{
			receiveMess(client, length, mess);
			fflush(stdin);
			cin.clear();
			cin >> cont;
			if (cont < 1 || cont >2){
				//cout << "gia tri vua nhap khong dung. vui long nhap lai";
				temp = -1;
				client.Send((char*)&temp, sizeof(int), 0);
				//time
				client.Receive((char*)&deadline, sizeof(int), 0);
				if(deadline == 1)
				{
					receiveMess(client, length, mess);
					return;
				}
				receiveMess(client, length, mess);

			}
			else{
				temp = 0;
				client.Send((char*)&temp, sizeof(int), 0);
				//time
				client.Receive((char*)&deadline, sizeof(int), 0);
				if(deadline == 1)
				{
					receiveMess(client, length, mess);
					return;
				}
				client.Send((char*)&cont, sizeof(int), 0);
			}
			
		} while (cont < 1 || cont > 2);
		

	} while (cont == 2);
}
void thanhToan(CSocket &client, int length, char *mess, int solan, int &deadline){
	int check;
	string tam;
	do{
		receiveMess(client, length, mess);
		receiveMess(client, length, mess);

		fflush(stdin);
		getline(cin, tam);
		sendMess(client, tam.length(), stringToCharx(tam));
		//time
		client.Receive((char*)&deadline, sizeof(int), 0);
		if(deadline == 1)
		{
			receiveMess(client, length, mess);
			return;
		}
		client.Receive((char*)&check, sizeof(check), 0);
		if (check == 1){
			receiveMess(client, length, mess);
		}
		else{
			receiveMess(client, length, mess);
		}
	} while (check == 0);
	//hoadon
	if (check == 1){
		receiveMess(client, length, mess);
		for (int i = 0; i < solan; i++){
			receiveMess(client, length, mess);
			receiveMess(client, length, mess);

		}
		receiveMess(client, length, mess);
	}
}


void xemChiTiet(CSocket &client, int length, char *mess, int &deadline){
	string tam;
	receiveMess(client, length, mess);
	fflush(stdin);
	getline(cin, tam);
	sendMess(client, tam.length(), stringToCharx(tam));
	//time
	client.Receive((char*)&deadline, sizeof(int), 0);
	if(deadline == 1)
	{
		receiveMess(client, length, mess);
		return;
	}
	receiveMess(client, length, mess);
}


BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		char mgs[4] = "CLS";
		int close = 1;
		sendMess(client, 4, mgs);
		closesocket(client);
		return TRUE;
	}

	return FALSE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.

			SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
			
			unsigned int port = 1234;
			AfxSocketInit(NULL);
			client.Create();
			char address[32];
			int sizeMesg;

			int length;
			char *mess;
			string tam;

			int id;
			int deadline = 0;
			TextColor(12);
			cout << "nhap dia chi IP cua server \t";
			gets(address);
			if (client.Connect(CA2W(address), port)){
				TextColor(11);
				cout << "da ket noi duoc den server! " << endl;

				//id cua moi client
				client.Receive((char*)&id, sizeof(id), 0);

				receiveMess(client, length, mess);
				receiveMess(client, length, mess);
				receiveMess(client, length, mess);
				int temp;
				int choosen;
				do{
					fflush(stdin);
					cin.clear();
					
					cin >> temp;
					if (temp < 1 || temp > 2){
						TextColor(12);
						cout << "gia tri vua nhap khong dung \nvui long nhap dung gia tri can chon\n";
					}
				} while (temp < 1 || temp > 2);
				client.Send((char*)&temp, sizeof(int), 0);
				//time
				client.Receive((char*)&deadline, sizeof(int), 0);
				if(deadline != 1)
				{

					if (temp == 1){
						dangki(client, length, mess,deadline);
					}
					else
					{
						dangnhap(client, length, mess,deadline);

					}
					if(deadline != 1)
					{
						
						do{
							receiveMess(client, length, mess);
							do{
								fflush(stdin);
								cin.clear();

								cin >> choosen;
								if (choosen < 1 || choosen > 3){
									TextColor(12);
									cout << "gia tri vua nhap khong dung \nvui long nhap dung gia tri can chon\n";
								}
							} while (choosen < 1 || choosen > 3);
							client.Send((char*)&choosen, sizeof(int), 0);
							//time
							client.Receive((char*)&deadline, sizeof(int), 0);
							if(deadline != 1)
							{
	
								if (choosen == 1){
									//xem chi tiet
									xemChiTiet(client, length, mess,deadline);
								}

								if (choosen == 2){
									int solan;
									datHang(client, length, mess, solan,deadline);
									if(deadline == 1)
									{
										break;
									}
									else
									{
										//thanh toan
										thanhToan(client, length, mess, solan,deadline);
									}
								}
								if(deadline == 1)
								{
									choosen = 3;
								}
							}
							else
							{
								choosen = 3;
								receiveMess(client,length, mess);
							}

						} while (choosen != 3);
					}
					else
					{
						choosen = 3;
					}
				}
				else
				{
					choosen = 3;
					receiveMess(client,length, mess);
				}

				if (choosen == 3){
					client.Close();
				}
			}

		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}
	system("pause");
	return nRetCode;
}
