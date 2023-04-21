#pragma once
#include "Disciplina.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Contract
{
private:
	string id;
	vector<Disciplina> discipline;
public:
	Contract() {};

	Contract(const string id) {
		this->id = id;
		this->discipline = {};
	}

	Contract(const string id,const vector<Disciplina>& discipline) {
		this->id = id;
		this->discipline = discipline;
	}
	string getId() {
		return this->id;
	}

	vector<Disciplina> getDiscipline() {
		return discipline;
	}

	void setDiscipline(vector<Disciplina> dis) {
		discipline = {};
		for (int i = 0; i < dis.size(); i++) {
			discipline.push_back(dis[i]);
		}
	}

	void adaugare_disciplina(Disciplina d) {
		discipline.push_back(d);
	}

	//Contract& operator=(const Contract& ot) {
		//this->id = ot.id;
		//for (int i = 0; i < ot.discipline.size(); i++) {
			//this->discipline[i] = ot.discipline[i];
		//}
		//return *this;
	//}

	bool operator==(const Contract& ot) {
		return this->id == ot.id;
	}
};

