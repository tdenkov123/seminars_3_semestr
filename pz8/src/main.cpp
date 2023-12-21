#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <cassert>

#define PI 3.14159265359


struct Element {
	std::string id;
	bool isRadial;
	int sizeX;
	int sizeY;
	Element(std::string p_id, bool p_rad, int s_x, int s_y) : id(p_id), isRadial(p_rad), sizeX(s_x), sizeY(s_y) {};
};

const Element R01005("R01005", false, 4, 2);
const Element R0201("R0201", false, 6, 3);
const Element R0402("R0402", false, 10, 5);
const Element R0603("R0603", false, 16, 8);
const Element R0805("R0805", false, 20, 12);
const Element R0808("R0808", false, 20, 20);
const Element R1020("R1020", false, 25, 50);
const Element R1206("R1206", false, 32, 16);
const Element R1210("R1210", false, 32, 25);
const Element R1812("R1812", false, 45, 32);
const Element R2010("R2010", false, 50, 25);
const Element R2512("R2512", false, 63, 32);

const Element L2835("L2835", false, 28, 35);
const Element L3014("L3014", false, 30, 14);
const Element L3528("L3528", false, 35, 28);
const Element L5050("L5050", false, 50, 50);
const Element L5630("L5630", false, 56, 30);
const Element L5730("L5730", false, 57, 30);
const Element L5("L5", true, 50, 50);

const Element C5("C5", true, 50, 50);
const Element C8("C8", true, 80, 80);
const Element C10("C10", true, 100, 100);
const Element C16("C16", true, 160, 160);
const Element C18("C18", true, 180, 180);
const Element C20("C20", true, 200, 200);
const Element C22("C22", true, 220, 220);
const Element C25("C25", true, 250, 250);

std::vector<Element> elements{ R01005, R0201, R0402, R0603, R0805, R0808, R1020, R1206, R1210, R1812, R2010, R2512,L2835, L3014, L3528, L5050, L5630, L5730, L5,C5, C8, C10, C16, C18, C20, C22, C25 };


bool checkBorders(const Element& elem, double posX, double posY, int borderX, int borderY) {
	if (elem.id[0] == 'R')  return (posX - elem.sizeX > 0 && posX + elem.sizeX && 2 < borderX && posY - elem.sizeY > 0 && posY + elem.sizeY / 2 < borderY);
	else return (posX - elem.sizeX / 2 > 0 && posX + elem.sizeX / 2 < borderX && posY - elem.sizeY / 2 > 0 && posY + elem.sizeY / 2 < borderY);
}

bool checkCollision(const Element& elem1, double x1, double y1, const Element& elem2, double x2, double y2) {
	if (elem1.isRadial && elem2.isRadial) {
		return (elem1.sizeX + elem2.sizeX < sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));

	}
	else if (!elem1.isRadial && !elem2.isRadial) {
		if (elem1.id[0] == 'R') return (abs(x1 - x2) > (elem1.sizeX + elem2.sizeX) || abs(y1 - y2) > (elem1.sizeY + elem2.sizeY));
		else return (abs(x1 - x2) > (elem1.sizeX + elem2.sizeX) / 2  || abs(y1 - y2) > (elem1.sizeY + elem2.sizeY) / 2);
	}
	else if (elem1.isRadial && !elem2.isRadial) {
		double angle = abs(atan((x2 - x1) / (y2 - y1)));
		double vert = elem1.sizeX * cos(angle * PI / 180.0);
		double hor = elem1.sizeX * sin(angle * PI / 180.0);
		return (vert < abs(y1 - y2) - elem2.sizeY / 2.0 && hor < abs(x1 - x2) - elem2.sizeX / 2.0);
	}
	else if (!elem1.isRadial && elem2.isRadial) {
		double angle = abs(atan((x2 - x1) / (y2 - y1)));
		double vert = elem2.sizeX * cos(angle * PI / 180);
		double hor = elem2.sizeX * sin(angle * PI / 180);
		return (vert < abs(y1 - y2) - elem1.sizeY / 2.0 && hor < abs(x1 - x2) - elem1.sizeX / 2.0);
	}
}


int main(int argc, char** argv) {
	int boardsizeX, boardsizeY, elemCount;
	std::cin >> boardsizeX >> boardsizeY;
	boardsizeX *= 10;
	boardsizeY *= 10;
	std::cin >> elemCount;

	std::vector<std::tuple<std::string, Element, double, double>> elems;
	std::vector<std::string> errors;
	for (int i = 0; i < elemCount; i++) {
		std::string name;
		std::string type;
		double x, y;
		std::cin >> name >> type >> x >> y;
		for (int j = 0; j < elements.size(); j++) {
			if ((elements[j]).id == type) {
				elems.push_back({ name, elements[j], x, y});
			}
		}
		
	}

	for (std::tuple el : elems) {
		if (!checkBorders(std::get<1>(el), std::get<2>(el), std::get<3>(el), boardsizeX, boardsizeY)) {
			errors.push_back("out_of_bounds " + std::get<0>(el));
		}
	}

	for (int i = 0; i < elems.size(); i++) {
		for (int j = i + 1; j < elems.size(); j++) {
			if (!checkCollision(std::get<1>(elems[i]), std::get<2>(elems[i]), std::get<3>(elems[i]), std::get<1>(elems[j]), std::get<2>(elems[j]), std::get<3>(elems[j]))) {
				errors.push_back("intersection " + std::get<0>(elems[i]) + " " + std::get<0>(elems[j]));
			}
		}
	}

	if (errors.size() == 0) {std::cout << "OK\n";}
	else {
		std::cout << "ERROR\n";
		for (const std::string err : errors) {std::cout << err << '\n';}
	}
	
	return 0;
}
