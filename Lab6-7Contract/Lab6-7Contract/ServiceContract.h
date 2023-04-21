#pragma once
#include "RepoContract.h"
#include "RepoDisciplina.h"
#include "ValidatorDisciplina.h"

class ServiceContract
{
private:
	RepoContract& repoContract;
	RepoDisciplina& repoDisciplina;
	ValidatorDisciplina& validator;
public:
	ServiceContract(RepoContract& repoC, RepoDisciplina& repoD, ValidatorDisciplina& val) :repoContract{ repoC }, repoDisciplina{ repoD }, validator{ val } {};

	void adaugare_contract_nou(string id);

	void golire_contract(string id) {
		repoContract.goleste_contract(id);
	}

	void adaugare_disciplina_contract(string id_contract, string id_disciplina);

	void adaugare_discipline_random(string id, int numar);

	bool find_contract(string id);

	bool find_disciplina(string id);

	vector<Contract> getAll() {
		return repoContract.getAll();
	}

	Contract get_contract_id(string id);

	string generare_alpha(int length);

	string generare_alpha_numeric(int length);

	int generare_lungime();

	void export_contract(string id_contract, string nume_fisier, int optiune);
};

