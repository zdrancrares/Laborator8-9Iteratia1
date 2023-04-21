#include "RepoDisciplina.h"

#include <iostream>
#include <sstream>

using std::string;


void RepoDisciplina::store(const Disciplina& d) {
	if (exists(d)) {
		throw RepoExceptions("Exista deja disciplina cu id: " + d.getId());
	}
	discipline.push_back(d);
}

void RepoDisciplina::deleteDisciplina(const Disciplina& d) {
	if (!exists(d)) {
		throw RepoExceptions("Nu exista disciplina cu id: " + d.getId());
	}

	if (discipline.size() == 1) {
		discipline.clear();
	}
	else {
		int index = 0;
		for (auto& elem : discipline) {
			if (elem.getId() == d.getId()) {
				break;
			}
			index += 1;
		}
		discipline.erase(discipline.begin()+index);
	}
}

void RepoDisciplina::update(const Disciplina& d) {
	if (!exists(d)) {
		throw RepoExceptions("Nu exista disciplina cu id: " + d.getId());
	}
	int index = 0;
	for (auto& elem : discipline) {
		if (elem.getId() == d.getId()) {
			break;
		}
		index += 1;
	}
	discipline[index] = d;
}

const Disciplina& RepoDisciplina::find(string id) {
	for (auto& elem : discipline) {
		if (elem.getId() == id) {
			return elem;
		}
	}
	throw RepoExceptions("Nu exista disciplina cu id: " + id);}

const vector<Disciplina>& RepoDisciplina::getAll() {
	return discipline;
}

bool RepoDisciplina::exists(const Disciplina& d) {
	try {
		find(d.getId());
		return true;
	}
	catch (RepoExceptions&) {
		return false;}
}

ostream& operator<<(ostream& out, const RepoExceptions& ex) {
	out << ex.msg;
	return out;
}

void RepoDisciplina::goleste_contract() {
	discipline.clear();
}