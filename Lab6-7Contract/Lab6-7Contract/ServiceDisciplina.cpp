#include "ServiceDisciplina.h"

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::vector;
using std::string;
using std::ostream;


void ServiceDisciplina::addDisciplina(const string& id, const string& denumire, int ore, const string& tip, const string& cadruDidactic) {
	Disciplina d( id, denumire, ore, tip, cadruDidactic );
	validator.validate(d);
	repo.store(d);
}

void ServiceDisciplina::deleteDisciplinaSrv(const string& id) {
	vector<Disciplina> discipline = repo.getAll();
	bool gasit = 0;
	for (auto& elem : discipline) {
		if (elem.getId() == id) {
			repo.deleteDisciplina(elem);
			gasit = 1;
			break;
		}
	}
	if (!gasit) {
		throw ServiceExceptions("Nu exista disciplina cu acest id.");
	}
}

void ServiceDisciplina::updateDisciplina(const string& id, const string& denumireNou, int oreNou, const string& tipNou, const string& cadruDidacticNou) {
	Disciplina dNou{id, denumireNou, oreNou, tipNou, cadruDidacticNou};
	validator.validate(dNou);
	repo.update(dNou);
}

vector<Disciplina> ServiceDisciplina::filtrare(function<bool(const Disciplina&)> fct) {
	vector<Disciplina> rez{};
	vector<Disciplina> v = repo.getAll();
	for (const auto& elem : v) {
		if (fct(elem)) {
			rez.push_back(elem);
		}
	}
	return rez;
}

vector<Disciplina> ServiceDisciplina::filtrareOre(int nrOreInceput, int nrOreSfarsit) {
	return filtrare([nrOreInceput, nrOreSfarsit](const Disciplina& d){
		return d.getOre() >= nrOreInceput && d.getOre() <= nrOreSfarsit;
	});
}

vector<Disciplina> ServiceDisciplina::filtrareCadruDidactic(const string& cadruDidactic) {
	return filtrare([cadruDidactic](const Disciplina& d) {
		return d.getCadruDidactic() == cadruDidactic;
	});
}

vector<Disciplina> ServiceDisciplina::filtrareDenumire(const string& denumire) {
	return filtrare([denumire](const Disciplina& d) {
		return d.getDenumire() == denumire;
	});
}

ostream& operator<<(ostream& out, const ServiceExceptions& ex) {
	out << ex.msg;
	return out;
}


vector<Disciplina> ServiceDisciplina::generalSort(int(*maiMicF)(const Disciplina&, const Disciplina&)) {
	vector<Disciplina> v{ repo.getAll() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (maiMicF(v[i], v[j]) == 1) {
				Disciplina aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

vector<Disciplina> ServiceDisciplina::sortByDenumire(bool reverse = false) {
	if (reverse) {
		return generalSort([](const Disciplina& d1, const Disciplina& d2) {
			if (d1.getDenumire() < d2.getDenumire())
				return 1;
			return 0;
			});
	}
	return generalSort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.getDenumire() > d2.getDenumire())
			return 1;
		return 0;
	});
}


vector<Disciplina> ServiceDisciplina::sortByOre(bool reverse = false) {
	if (reverse) {
		return generalSort([](const Disciplina& d1, const Disciplina& d2) {
			if (d1.getOre() < d2.getOre())
				return 1;
			return 0;
			});
	}
	return generalSort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.getOre() > d2.getOre())
			return 1;
		return 0;
		});
}

vector<Disciplina> ServiceDisciplina::sortByTipCadruDidactic(bool reverse = false) {
	if (reverse) {
		return generalSort([](const Disciplina& d1, const Disciplina& d2) {
			if (d1.getTip() < d2.getTip() || d1.getTip() == d2.getTip() && d1.getCadruDidactic() < d2.getCadruDidactic())
				return 1;
			return 0;
			});
	}
	return generalSort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.getTip() > d2.getTip() || d1.getTip() == d2.getTip() && d1.getCadruDidactic() > d2.getCadruDidactic())
			return 1;
		return 0;
		});
}

void ServiceDisciplina::golire_contract() {
	repo.goleste_contract();
}
