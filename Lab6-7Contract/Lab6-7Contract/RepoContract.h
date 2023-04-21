#pragma once
#include "Contract.h"
#include <vector>

using std::vector;

class RepoContract
{private:
	vector<Contract> contracte;
public:
	RepoContract() {};

	void add(Contract c) {
		contracte.push_back(c);
	}

	void goleste_contract(const string& id);

	void adaugare_disciplina(Contract& c, Disciplina& d);

	vector<Contract>& getAll() {
		return this->contracte;
	}

	int dim(string id) {
		for (auto& elem : contracte) {
			if (elem.getId() == id) {
				return elem.getDiscipline().size();
			}
		}
	}
};

