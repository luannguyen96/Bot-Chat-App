#include "stdafx.h"
#include "MatHang.h"


void CMatHang::nhap(istream &is){
	string buff;

	getline(is, tenSanPham);
	getline(is, maHang);
	is >> soluong;

	getline(is, buff);
	getline(is, chiTiet);

	is >> gia;
	getline(is, buff);
}

void CMatHang::xuat(){
	cout << "ten san pham: \t" << tenSanPham << endl;
	cout << "ma san pham: \t" << maHang << endl;
	cout << "so luong: \t" << soluong << endl;
	cout << "thong tin chi tiet san pham: \t" << chiTiet << endl;
	cout << "gia san phan: \t" << gia << endl;
}

string CMatHang::getTenSanPham(){
	return tenSanPham;
}

string CMatHang::getMaHang(){
	return maHang;
}

int CMatHang::getSoLuong(){
	return soluong;
}

string CMatHang::getChiTiet(){
	return chiTiet;
}

long CMatHang::getGia(){
	return gia;
}