#include"KhoHang.h"

int getDoDaiThongTinKhoHang(CKhoHang a){
	int length = a.getDanhSach().size();
	return length + 1;
}

char *getThongTinKhoHang(CKhoHang a){
	char *temp;

	string tam = a.getDanhSach();
	int length = tam.size();
	temp = new char[length + 1];
	strcpy(temp, tam.c_str());
	return temp;
}



void xuatThongTinKho(){
	ifstream f("Text.txt");
	CKhoHang a;
	if (f.is_open()){
	
		a.input(f);
		//a.output();
		
		f.close();
	}
	else{
		cout << "can't open this file" << endl;
	}

}

