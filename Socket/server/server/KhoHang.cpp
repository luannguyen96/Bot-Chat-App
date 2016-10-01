#include "stdafx.h"
#include "KhoHang.h"


void CKhoHang::input(istream &is){
	string buff;
	is >> soluongMH;
	getline(is, buff);
	for (int i = 0; i < soluongMH; i++){
		CMatHang a;
		a.nhap(is);
		khoHang.push_back(a);
	}
}

void CKhoHang::output(){
	for (int i = 0; i < khoHang.size(); i++){
		khoHang[i].xuat();
	}
	
}


string CKhoHang::getDanhSach(){

	string temp = "\n";

	for (int i = 0; i < khoHang.size(); i++){
		temp += "ten san pham: " + khoHang[i].getTenSanPham() + "\n";
		temp += "ma hang: " + khoHang[i].getMaHang() + "\n";
		temp += "so luong: " + to_string(khoHang[i].getSoLuong());
		temp += "\n";
		temp += "thong tin chi tiet: " + khoHang[i].getChiTiet() + "\n";
		temp += "gia: " + to_string(khoHang[i].getGia()) + "\n\n\n";
	}
	return temp;
}

bool CKhoHang::ktraMonHang(char* x){
	for (int i = 0; i < khoHang.size(); i++){
		string tam = khoHang[i].getTenSanPham();
		if (strcmp(tam.c_str(), x)){
			return true;
		}
	}
	return false;
}


string CKhoHang::getThongTinChiTiet(char* x){
	string temp = "\n";
	for (int i = 0; i < khoHang.size(); i++){
		string tam = khoHang[i].getTenSanPham();
		string tam_2 = khoHang[i].getMaHang();
		if ((strcmp(tam.c_str(), x) == 0) || (strcmp(tam_2.c_str(), x) == 0)){
			temp += khoHang[i].getTenSanPham() + "\n";
			temp += khoHang[i].getMaHang() + "\n";
			temp += to_string((long double)khoHang[i].getSoLuong()) + "\n";
			temp += to_string((long double)khoHang[i].getGia()) + "\n";
			temp += khoHang[i].getChiTiet() + "\n";
		}
	}
	return temp;
}

bool CKhoHang::checkTenVaId(char *x){
	for (int i = 0; i < khoHang.size(); i++){
		string tam = khoHang[i].getTenSanPham();
		string tam_2 = khoHang[i].getMaHang();
		if ((strcmp(tam.c_str(), x) == 0) || (strcmp(tam_2.c_str(), x) == 0)){
			return true;
		}
	}
	return false;
}


bool CKhoHang::checkTonTai(int x, char* y){
	for (int i = 0; i < khoHang.size(); i++){
		string tam = khoHang[i].getTenSanPham();
		string tam_2 = khoHang[i].getMaHang();
		int sl = khoHang[i].getSoLuong();
		if (x > sl){
			return false;
		}
		if (((strcmp(tam.c_str(), y) == 0) || (strcmp(tam_2.c_str(), y) == 0)) && (x <= sl)){
			return true;
		}
	}
	return false;
}

int CKhoHang::getStt(char *x){
	for (int i = 0; i < khoHang.size(); i++){
		string tam = khoHang[i].getTenSanPham();
		string tam_2 = khoHang[i].getMaHang();
		if ((strcmp(tam.c_str(), x) == 0) || (strcmp(tam_2.c_str(), x) == 0)){
			return i ;
		}
	}
	return -1;
}

long CKhoHang::getGia(int i){
	return khoHang[i].getGia();
}


string CKhoHang::getHoaDon(int i){
	string temp = "";
	temp += khoHang[i].getTenSanPham() + "\n";
	temp += khoHang[i].getMaHang() + "\n";
	temp += khoHang[i].getChiTiet() + "\n";
	return temp;
}