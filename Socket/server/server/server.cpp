// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "server.h"
#include"ThongTinKhoHang.h"
#include"afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only application object

CWinApp theApp;

using namespace std;
CSocket server;
int n;

bool tatNong(CSocket *sockClient, int i, char*mess){
	
	string str(mess);
	string close = "CLS";
	if (str.compare(close) == 0){
		//sockClient[i].Close();
		return true;
	}
	return false;
}

int getStringLength(string x){
	return x.length();
}

char *stringToCharx(string x){
	int temp = x.length();
	char* a = new char[temp];
	strcpy(a, x.c_str());
	return a;
}

void sendMess(CSocket *sockClient, int length, char *mess, int pos){
	sockClient[pos].Send(&length, sizeof(length), 0);
	sockClient[pos].Send(mess, length, 0);

}
void dongToanBo(CSocket &server){
	server.Close();
}
void ketThuc(CSocket *sockClient, int i){
	
	sockClient[i].Close();
	if (i == n - 1){
		dongToanBo(server);
	}

}



void receiveMess(CSocket *sockClient, int &length, char *&mess, int pos, bool &closed){

	sockClient[pos].Receive((char*)&length, sizeof(int), 0);
	mess = new char[length + 1];
	sockClient[pos].Receive(mess, length, 0);
	mess[length] = '\0';
	if (tatNong(sockClient, pos, mess) == true){
		cout << "Client " << pos + 1 << " da dong ket noi" << endl;
		ketThuc(sockClient, pos);
		closed = true;
		
		
	}
	else{
		cout << "Client " << pos + 1 << " sent: " << mess << endl;
	}
}

void receiveAllClient(CSocket *sockClient, int &length, char *&mess, int quantity, bool &closed){
	for (int i = 0; i < quantity; i++){
		receiveMess(sockClient, length, mess, i, closed);


	}
}


void sendAllClient(CSocket *sockClient, int length, char *mess, int quantity){
	for (int i = 0; i < quantity; i++){
		sendMess(sockClient, length, mess,i);
	}
}

struct TaiKhoan{
	char* tentk;
	char* mk;
};

int hetthoigian(const clock_t start_time)
{
	clock_t now_time = clock();
	if(now_time - start_time < 600000)
	{
		return 0;
	}
	return 1;
}

void dangki(CSocket *sockClient, int mesgSize, char *serverMsg, int i, bool &closed, int& deadline, clock_t start_time){
	if (closed == false){
		char *fullname;
		bool flag;
		do{
			int tam = 0;
			flag = true;
			serverMsg = "vui long nhap ten tai khoan dang ki";
			mesgSize = strlen(serverMsg);
			sendMess(sockClient, mesgSize, serverMsg, i);
			receiveMess(sockClient, mesgSize, serverMsg, i, closed);
			//time
			deadline = hetthoigian(start_time);
			sockClient[i].Send((char*)&deadline, sizeof(int), 0);
			if(deadline == 1)
			{
				string tam("Thoi gian mua hang cua ban da het");
				sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
				closed = true;
				cout << "Client " << i << " da het thoi gian mua hang." << endl;
				return;
			}
			else
			{
				if (closed == true){

					break;
				}
				else{
					char *x = "@gmail.com";

					fullname = new char[strlen(x) + strlen(serverMsg)];
					fullname = strcat(serverMsg, x);

					ifstream f("profile.txt");
					if (f.is_open()){

						while (!f.eof()){
							string temp;
							fflush(stdin);
							getline(f, temp);
							temp += "@gmail.com";
							if (strcmp(temp.c_str(), fullname) == 0){
								flag = false;
								tam = 1;
								break;
							}

						}
					}
					else
					{
						cout << "file can't open" << endl;
					}
					f.close();


					if (flag == false){
						serverMsg = "ten dang nhap da ton tai, vui long chon ten dang nhap khac";
						mesgSize = strlen(serverMsg);

						sockClient[i].Send((char*)&tam, sizeof(int), 0);
						sendMess(sockClient, mesgSize, serverMsg, i);
					}
					else{
						tam = 0;
						sockClient[i].Send((char*)&tam, sizeof(int), 0);
					}
				}
			}
		} while (flag == false);

		//password
		if (closed == false){
			ofstream f("profile.txt", ios::app);
			if (f.is_open()){
				f << serverMsg << '\n';
				if(hetthoigian(start_time) == 1)
				{
					f << "123456" << '\n' ;
				}
			}
			else{
				cout << "can't open this file" << endl;
			}

			serverMsg = "vui long nhap mat khau dang ki";
			mesgSize = strlen(serverMsg);
			sendMess(sockClient, mesgSize, serverMsg, i);
			// nhan password
			receiveMess(sockClient, mesgSize, serverMsg, i, closed);
			//time
			deadline = hetthoigian(start_time);
			sockClient[i].Send((char*)&deadline, sizeof(int), 0);
			if(deadline == 1)
			{
				f << serverMsg << '\n';
				f.close();
				string tam("Thoi gian mua hang cua ban da het");
				sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
				closed = true;
				cout << "Client " << i << " da het thoi gian mua hang." << endl;
				return;
			}
			if (closed == false){

				f << serverMsg << '\n';
				f.close();


				//response lai thong tin tai khoan
				char *temp = "email moi cua ban la \t";
				sendMess(sockClient, strlen(temp), temp, i);
				sendMess(sockClient, strlen(fullname), fullname, i);
			}
		}
	}
	
}



void dangnhap(CSocket *sockClient, int mesgSize, char *serverMsg, int i, bool &closed,int& deadline, clock_t start_time){
	if (closed == false){
		bool flag;
		char *fullname;
		do{
			int tam = 0;
			flag = false;
			serverMsg = "vui long nhap ten tai khoan dang nhap";
			mesgSize = strlen(serverMsg);
			sendMess(sockClient, mesgSize, serverMsg, i);


			receiveMess(sockClient, mesgSize, serverMsg, i, closed);
			//time
			deadline = hetthoigian(start_time);
			sockClient[i].Send((char*)&deadline, sizeof(int), 0);
			if(deadline == 1)
			{
				string tam("Thoi gian mua hang cua ban da het");
				sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
				closed = true;
				cout << "Client " << i << " da het thoi gian mua hang." << endl;
				return;
			}
			if (closed == false){

				fullname = new char[strlen(serverMsg)];
				strcpy(fullname, serverMsg);

				serverMsg = "vui long nhap mat khau dang nhap";
				mesgSize = strlen(serverMsg);
				sendMess(sockClient, mesgSize, serverMsg, i);

				receiveMess(sockClient, mesgSize, serverMsg, i, closed);
				//time
				deadline = hetthoigian(start_time);
				sockClient[i].Send((char*)&deadline, sizeof(int), 0);
				if(deadline == 1)
				{
					string tam("Thoi gian mua hang cua ban da het");
					sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
					closed = true;
					cout << "Client " << i << " da het thoi gian mua hang." << endl;
					return;
				}
				if (closed == false){
					char *k = new char[strlen(serverMsg) + strlen(fullname)];
					k = strcat(fullname, serverMsg);

					ifstream f("profile.txt");
					if (f.is_open()){

						while (!f.eof()){
							string temp;
							fflush(stdin);
							getline(f, temp);
							string temp2;
							fflush(stdin);
							getline(f, temp2);
							temp += temp2;
							if (strcmp(temp.c_str(), k) == 0){
								flag = true;
								tam = 1;
								break;
							}

						}
					}
					else
					{
						cout << "file can't open" << endl;
					}
					f.close();
					if (flag == false){
						sockClient[i].Send((char*)&tam, sizeof(int), 0);
						serverMsg = "sai ten dang nhap hoac mat khau, vui long thu lai";
						mesgSize = strlen(serverMsg);
						sendMess(sockClient, mesgSize, serverMsg, i);
					}
					else{
						tam = 1;
						sockClient[i].Send((char*)&tam, sizeof(int), 0);
					}
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		} while (flag == false);
	}
}


void xemChiTietMonHang(CSocket *sockClient, int mesgSize, char* serverMsg, int i, CKhoHang a, bool &closed,int &deadline, clock_t start_time){
	if (closed == false){
		serverMsg = "vui long nhap ten mon hang can xem";
		mesgSize = strlen(serverMsg);
		sendMess(sockClient, mesgSize, serverMsg, i);
		receiveMess(sockClient, mesgSize, serverMsg, i,closed);
		//time
		deadline = hetthoigian(start_time);
		sockClient[i].Send((char*)&deadline, sizeof(int), 0);
		if(deadline == 1)
		{
			string tam("Thoi gian mua hang cua ban da het");
			sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
			closed = true;
			cout << "Client " << i << " da het thoi gian mua hang." << endl;
			return;
		}
		if (closed == false){
			if (a.ktraMonHang(serverMsg) == false){
				serverMsg = "khong ton tai mon hang vua nhap";
				mesgSize = strlen(serverMsg);
				sendMess(sockClient, mesgSize, serverMsg, i);
			}
			else{
				string getMH = a.getThongTinChiTiet(serverMsg);
				sendMess(sockClient, getMH.length(), stringToCharx(getMH), i);
			}
		}
	}
}

bool checkTaiKhoan(char *x){
	string tam(x);
	string maNganHang = tam.substr(0, 3);
	int lengthMaThe = tam.size();
	if (lengthMaThe == 13){
		string dsNganHang[4] = { "ACB", "SCB" ,"VTB", "AGB" };
		for (int i = 0; i < 4; i++){
			if (maNganHang.compare(dsNganHang[i]) == 0){
				return true;
			}
		}
	}
	return false;
}

void xuatHoaDon(CSocket *sockClient, int mesgSize, char* serverMsg, int i, CKhoHang a, vector<int> donhang, long donGia){
	serverMsg = "Hoa don cua khach hang la \n" ;
	mesgSize = strlen(serverMsg);
	sendMess(sockClient, mesgSize, serverMsg, i);
	for (int j = 0; j < donhang.size(); j += 2){
		serverMsg = stringToCharx(a.getHoaDon(donhang[j]));
		mesgSize = strlen(serverMsg);
		sendMess(sockClient, mesgSize, serverMsg, i);

		string tam = "so luong: " + to_string((long double)donhang[j + 1]);
		serverMsg = stringToCharx(tam);
		mesgSize = strlen(serverMsg);
		sendMess(sockClient, mesgSize, serverMsg, i);

	}

	string temp = "\n\t\t============TONG CONG: \t" + to_string((long double)donGia);
	serverMsg = stringToCharx(temp);
	mesgSize = strlen(serverMsg);
	sendMess(sockClient, mesgSize, serverMsg, i);
}

void thanhtoan(CSocket *sockClient, int mesgSize, char* serverMsg, int i, CKhoHang a, vector<int> donhang, bool closed, int& deadline, clock_t start_time){
	if (closed == false){
		int check = 0;
		do{
			serverMsg = "vui long nhap ma tai khoan ngan hang";
			mesgSize = strlen(serverMsg);
			sendMess(sockClient, mesgSize, serverMsg, i);
			serverMsg = "hien tai cua hang chap nhan thanh toan cac loai the cua cac ngan hang sau: \n Agribank <AGB> \t Sacombank <SCB> \t ViettinBank <VTB> \t ACB <ACB>\n";
			mesgSize = strlen(serverMsg);
			sendMess(sockClient, mesgSize, serverMsg, i);


			receiveMess(sockClient, mesgSize, serverMsg, i, closed);
			//time
			deadline = hetthoigian(start_time);
			sockClient[i].Send((char*)&deadline, sizeof(int), 0);
			if(deadline == 1)
			{
				string tam("Thoi gian mua hang cua ban da het");
				sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
				closed = true;
				cout << "Client " << i << " da het thoi gian mua hang." << endl;
				return;
			}
			if (closed == false){

				unsigned long dongia = 0;
				if (checkTaiKhoan(serverMsg) == true){
					check = 1;
					sockClient[i].Send((char*)&check, sizeof(int), 0);
					serverMsg = "tai khoan hop le. Quy khach vui long doi thanh toan";
					mesgSize = strlen(serverMsg);
					sendMess(sockClient, mesgSize, serverMsg, i);
					for (int i = 0; i < donhang.size(); i += 2){
						dongia += a.getGia(donhang[i]) *  donhang[i + 1];
					}
					//send hoa don
					xuatHoaDon(sockClient, mesgSize, serverMsg, i, a, donhang, dongia);

				}
				else{
					check = 0;
					sockClient[i].Send((char*)&check, sizeof(int), 0);
					serverMsg = "tai khoan khong hop le. Quy khach vui long nhap lai tai khoan";
					mesgSize = strlen(serverMsg);
					sendMess(sockClient, mesgSize, serverMsg, i);
				}
			}
			else{
				break;
			}
		} while (check == 0);
	}
}
void datHang(CSocket *sockClient, int mesgSize, char* serverMsg, int i, CKhoHang a, bool &closed, int &deadline, clock_t start_time){
	if (closed == false){
		int cont;
		int k = 0;
		int sl;
		int temp;
		vector<int> donhang;
		do{
			do{
				fflush(stdin);
				cin.clear();
				serverMsg = "vui long nhap ten mon hang hoac ID mon hang muon dat hang";
				mesgSize = strlen(serverMsg);
				sendMess(sockClient, mesgSize, serverMsg, i);

				receiveMess(sockClient, mesgSize, serverMsg, i, closed);


				//time
				deadline = hetthoigian(start_time);
				sockClient[i].Send((char*)&deadline, sizeof(int), 0);
				if(deadline == 1)
				{
					string tam("Thoi gian mua hang cua ban da het");
					sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
					closed = true;
					cout << "Client " << i << " da het thoi gian mua hang." << endl;
					return;
				}
				if (closed == false){

					char *x = new char[strlen(serverMsg)];
					strcpy(x, serverMsg);
					serverMsg = "vui long chon so luong cua mon hang vua chon";
					mesgSize = strlen(serverMsg);
					sendMess(sockClient, mesgSize, serverMsg, i);


					sockClient[i].Receive((char*)&sl, sizeof(sl), 0);
					//time
					deadline = hetthoigian(start_time);
					sockClient[i].Send((char*)&deadline, sizeof(int), 0);
					if(deadline == 1)
					{
						string tam("Thoi gian mua hang cua ban da het");
						sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
						closed = true;
						cout << "Client " << i << " da het thoi gian mua hang." << endl;
						return;
					}
					if (sl == 4){
						closed = true;
						serverMsg = new char[sl + 1];
						sockClient[i].Receive(serverMsg, mesgSize, 0);
						serverMsg[sl] = '\0';
						if (tatNong(sockClient, i, serverMsg) == true){
							ketThuc(sockClient, i);
						}
						cout << "Client " << i << " da ngat ket noi" << endl;
						break;
					
					}
					else{

						int soluongtt = sl;

						if (a.checkTonTai(sl, x) == false){
							serverMsg = "ten hoac id hoac so luong cua mon hang vua nhap khong dung. Vui long nhap lai";
							mesgSize = strlen(serverMsg);
							sl = 0;

							sockClient[i].Send((char*)&sl, sizeof(int), 0);
							sendMess(sockClient, mesgSize, serverMsg, i);

						}
						else{
							sl = 1;

							sockClient[i].Send((char*)&sl, sizeof(int), 0);
							string getMH = a.getThongTinChiTiet(x);

							donhang.push_back(a.getStt(x));
							donhang.push_back(soluongtt);
							sendMess(sockClient, getMH.length(), stringToCharx(getMH), i);
							do{
								
								serverMsg = "ban co muon \t1-thanh toan don hang? \t2-Tiep tuc mua hang ?";
								mesgSize = strlen(serverMsg);
								sendMess(sockClient, mesgSize, serverMsg, i);
								sockClient[i].Receive((char*)&temp, sizeof(temp), 0);
								//time
								deadline = hetthoigian(start_time);
								sockClient[i].Send((char*)&deadline, sizeof(int), 0);
								if(deadline == 1)
								{
									string tam("Thoi gian mua hang cua ban da het");
									sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
									closed = true;
									cout << "Client " << i << " da het thoi gian mua hang." << endl;
									return;
								}
								if (temp == 4){
									closed = true;
									serverMsg = new char[sl + 1];
									sockClient[i].Receive(serverMsg, mesgSize, 0);
									serverMsg[sl] = '\0';
									if (tatNong(sockClient, i, serverMsg) == true){
										ketThuc(sockClient, i);
									}
									cout << "Client " << i << " da ngat ket noi" << endl;
									break;

								}
								else{


									if (temp == -1){



										serverMsg = "gia tri vua nhap khong dung. vui long nhap lai";
										mesgSize = strlen(serverMsg);
										sendMess(sockClient, mesgSize, serverMsg, i);

									}
									else{

										sockClient[i].Receive((char*)&cont, sizeof(cont), 0);
									}
								}
							} while (temp == -1);
						}
					}
				}
				else{
					break;
				}
				
			} while (sl == 0);
			
			if (closed == true){
				break;
			}

		} while (cont == 2 || sl == 0);
		if (closed == false){
			if (cont == 1){
				//thanh toan don hang
				thanhtoan(sockClient, mesgSize, serverMsg, i, a, donhang, closed,deadline,start_time);
				if(deadline == 1)
				{
					return;
				}
			}
		}
	}
	
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

			

			
			unsigned int port = 1234;
			
			AfxSocketInit(NULL);
			server.Create(port);
			server.Listen();

			cout << "nhap so luong client \t";
			cin >> n;
			cin.clear();
			//testing
			
			//mo file doc de gui toan bo don hang qua client
			char *list;
			int listSize;
			ifstream f("Text.txt");
			CKhoHang a;
			if (f.is_open()){

				a.input(f);
				
				listSize = getDoDaiThongTinKhoHang(a);
				list = new char[listSize];
				strcpy(list, getThongTinKhoHang(a));

				f.close();
			}
			else{
				cout << "can't open this file" << endl;
			}
			
			
			char *serverMsg = "chao mung den voi cua hang ABCD \n";
			int mesgSize = strlen(serverMsg);
			CSocket *sockClient = new CSocket[n];
			for (int i = 0; i < n; i++){
				if (server.Accept(sockClient[i])){
					cout << "da ket noi client " << i << endl;
					sockClient[i].Send((char*)&i, sizeof(int), 0);

					
				}
			
			}
		

			sendAllClient(sockClient, mesgSize, serverMsg, n);

			//gui don hang
			sendAllClient(sockClient, listSize, list, n);
			clock_t start_time = clock();
			
			int id;
			int deadline = 0;
			for (int i = 0; i < n; i++){
				deadline = 0;
				bool closed = false;
				serverMsg = "1- dang ki \t 2- dang nhap \n";
				mesgSize = strlen(serverMsg);
				sendMess(sockClient, mesgSize, serverMsg, i);
				
				sockClient[i].Receive((char*)&id, sizeof(id), 0);
				//time
				deadline = hetthoigian(start_time);
				sockClient[i].Send((char*)&deadline, sizeof(int), 0);
				if(deadline == 1)
				{
					string tam("Thoi gian mua hang cua ban da het");
					sendMess(sockClient, getStringLength(tam),stringToCharx(tam),i);
					closed = true;
					sockClient[i].Close();
					cout << "Client " << i + 1 << " da het thoi gian mua hang." << endl;
				}
				if (id == 4){
					closed = true;
					serverMsg = new char[id + 1];
					sockClient[i].Receive(serverMsg, mesgSize, 0);
					serverMsg[id] = '\0';
					if (tatNong(sockClient, i, serverMsg) == true){
						ketThuc(sockClient, i);
						cout << "Client " << i + 1<< " da ngat ket noi" << endl;
					
					}
				}
				else{

					if (id == 1){
						dangki(sockClient, mesgSize, serverMsg, i, closed,deadline,start_time);
					}
					else{
						dangnhap(sockClient, mesgSize, serverMsg, i, closed,deadline, start_time);
					}
					if(deadline != 1)
					{
						do{
							serverMsg = "\n\n\t============= MENU ============== \n1- xem thong tin chi tiet mon hang \n2- dat hang \n3- thoat";
							mesgSize = strlen(serverMsg);
							sendMess(sockClient, mesgSize, serverMsg, i);
							sockClient[i].Receive((char*)&id, sizeof(id), 0);
							
							if (id == 4){
								closed = true;
								serverMsg = new char[id + 1];
								sockClient[i].Receive(serverMsg, mesgSize, 0);
								serverMsg[id] = '\0';
								if (tatNong(sockClient, i, serverMsg) == true){
									ketThuc(sockClient, i);
									cout << "Client " << i << " da ngat ket noi" << endl;
									break;
								}
							}
							else{
								//time
								deadline = hetthoigian(start_time);
								sockClient[i].Send((char*)&deadline, sizeof(int), 0);
								if (deadline == 1)
								{
									string tam("Thoi gian mua hang cua ban da het");
									sendMess(sockClient, getStringLength(tam), stringToCharx(tam), i);
									closed = true;
									sockClient[i].Close();
									cout << "Client " << i << " da het thoi gian mua hang." << endl;
								}

								if (id == 1){
									//xem thong tin
									xemChiTietMonHang(sockClient, mesgSize, serverMsg, i, a, closed, deadline, start_time);
								

								}
								if (id == 2){
									//order
									datHang(sockClient, mesgSize, serverMsg, i, a, closed, deadline, start_time);
								}
								if(deadline == 1)
								{
									id = 3;
								}
								if (closed == true){
									break;
								}
							}
						} while (id != 3);
					}
					else
					{
						id = 3;
					}
					if (id == 3){
						sockClient[i].Close();
					}
				}
				Sleep(1000);
					
			}

	
			
			
			delete[]list;
			server.Close();
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
