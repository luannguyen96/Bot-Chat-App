#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class CMatHang
{
private:
	string tenSanPham;
	string maHang;
	int soluong;
	long gia;
	string chiTiet;
public:
	void nhap(istream &is);
	void xuat();
	string getTenSanPham();
	string getMaHang();
	int getSoLuong();
	string getChiTiet();
	long getGia();
};
