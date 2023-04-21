#include "RepoContract.h"


void RepoContract::goleste_contract(const string& id) {
	for (auto& elem : contracte) {
		if (elem.getId() == id) {
			elem.setDiscipline({});
		}
	}
}

void RepoContract::adaugare_disciplina(Contract& c, Disciplina& d) {
	for (auto& elem : c.getDiscipline()) {
		if (elem.getId() == d.getId())
			throw("Exista deja aceasta disciplina in contract!");
	}

	for (auto& elem : contracte) {
		if (elem.getId() == c.getId()) {
			elem.adaugare_disciplina(d);
			break;}}
}
