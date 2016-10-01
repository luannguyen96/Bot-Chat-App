#pragma once
#include"MatHang.h"
#include<vector>


class CKhoHang
{
private:
	vector <CMatHang> khoHang;
	int soluongMH;
public:
	void input(istream &is);
	void output();
	string getDanhSach();
	bool ktraMonHang(char*);
	string getThongTinChiTiet(char*);
	bool checkTenVaId(char*);
	bool checkTonTai(int,char*);
	int getStt(char*);
	long getGia(int);
	string getHoaDon(int);

};

