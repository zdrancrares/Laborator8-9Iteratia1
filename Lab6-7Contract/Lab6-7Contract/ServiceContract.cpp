#include "ServiceContract.h"

#include <random>
#include <cstdlib>
#include <fstream>

void ServiceContract::export_contract(string id_contract, string nume_fisier, int optiune) {
	Contract c{};
	c = get_contract_id(id_contract);

	string file_path = "C:\\Users\\dorin\\OneDrive\\Desktop\\exportContracteLab8-9\\";
	file_path += nume_fisier;

	if (optiune == 1) {
		file_path += ".cvs";
	}
	else {
		file_path += ".html";
	}

	std::ofstream fout(file_path);

	if (optiune == 1) {
		for (auto& elem : c.getDiscipline()) {
			fout << elem.getId() << "," << elem.getDenumire() << "," << elem.getOre() << "," << elem.getTip() << "," << elem.getCadruDidactic() << "\n";
		}
	}
	else {
		for (auto& elem : c.getDiscipline()) {
			fout << elem.getId() << "|" << elem.getDenumire() << "|" << elem.getOre() << "|" << elem.getTip() << "|" << elem.getCadruDidactic() << "<br>";
		}
	}
	fout.close();
}

void ServiceContract::adaugare_contract_nou(string id) {
	Contract c{ id };
	if (find_contract(id)) {
		throw("Exista deja contract cu acest id!");
	}
	repoContract.add(c);
}

void ServiceContract::adaugare_disciplina_contract(string id_contract, string id_disciplina) {
	if (!find_contract(id_contract)) {
		throw("Nu exista contract cu acest id!");
	}
	if (!find_disciplina(id_disciplina)) {
		throw("Nu exista disciplina cu acest id!");
	}
	Contract c = {};
	for (auto& elem : repoContract.getAll()) {
		if (elem.getId() == id_contract) {
			c = elem;
			break;}}
	Disciplina d{};
	for (auto& elem : repoDisciplina.getAll()) {
		if (elem.getId() == id_disciplina) {
			d = elem;
			break;}}
	repoContract.adaugare_disciplina(c, d);
}

void ServiceContract::adaugare_discipline_random(string id, int numar) {
	Contract c = {};
	for (auto& elem : repoContract.getAll()) {
		if (elem.getId() == id) {
			c = elem;
			break;}}
	for (int i = 0; i < numar; i++) {

		int lungime_id = generare_lungime() % 8 + 2;
		int lungime_denumire = generare_lungime();
		int lungime_tip = generare_lungime();
		int lungime_cadru_didactic = generare_lungime();

		string id_nou = generare_alpha_numeric(lungime_id);
		string denumire_nou = generare_alpha(lungime_denumire);
		int ore_nou = generare_lungime();
		string tip_nou = generare_alpha(lungime_tip);
		string cadru_nou = generare_alpha(lungime_cadru_didactic);

		Disciplina d{ id_nou, denumire_nou, ore_nou, tip_nou, cadru_nou };

		repoContract.adaugare_disciplina(c, d);
	}
}

bool ServiceContract::find_contract(string id) {
	for (auto& elem : repoContract.getAll()) {
		if (elem.getId() == id)
			return true;
	}
	return false;
}

bool ServiceContract::find_disciplina(string id) {
	for (auto& elem : repoDisciplina.getAll()) {
		if (elem.getId() == id)
			return true;
	}
	return false;
}

Contract ServiceContract::get_contract_id(string id) {
	for (auto& elem : repoContract.getAll()) {
		if (elem.getId() == id)
			return elem;}}

int ServiceContract::generare_lungime() {

	int number = rand() % 10 + 5;

	return number;
}

string ServiceContract::generare_alpha(int length) {
	const string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	string random_string;

	for (int i = 0; i < length; ++i)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}

string ServiceContract::generare_alpha_numeric(int length) {
	const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	string random_string;

	for (int i = 0; i < length; ++i)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}
