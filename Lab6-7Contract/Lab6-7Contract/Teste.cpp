#include "Teste.h"

#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;

void Teste::teste_domain() {
	Disciplina d1( "AAA1", "OOP", 6, "Obligatorie", "Stan Maria" );

	assert(d1.getId() == "AAA1");
	assert(d1.getDenumire() == "OOP");
	assert(d1.getOre() == 6);
	assert(d1.getTip() == "Obligatorie");
	assert(d1.getCadruDidactic() == "Stan Maria");

	d1.setId("BBB2");
	d1.setDenumire("FP");
	d1.setOre(8);
	d1.setTip("Optionala");
	d1.setCadruDidactic("Stan Maria-Elena");

	assert(d1.getId() == "BBB2");
	assert(d1.getDenumire() == "FP");
	assert(d1.getOre() == 8);
	assert(d1.getTip() == "Optionala");
	assert(d1.getCadruDidactic() == "Stan Maria-Elena");

	Disciplina d2("BBB2", "OOP2", 6, "Obligatorie", "Stan Maria-Elena");

	assert(d1 == d2);

	Disciplina d3{ "BBB3", "OOP", 6, "Obligatorie", "Alexandrescu Marius" };

	bool testare_egalitate = (d1 == d3);

	assert(testare_egalitate == false);

	Disciplina d4 = d1;
	
	assert(d4.getId() == "BBB2");
	assert(d4.getDenumire() == "FP");
	assert(d4.getOre() == 8);
	assert(d4.getTip() == "Optionala");
	assert(d4.getCadruDidactic() == "Stan Maria-Elena");

	d2 = d3;

	assert(d2.getId() == "BBB3");
	assert(d2.getDenumire() == "OOP");
	assert(d2.getOre() == 6);
	assert(d2.getTip() == "Obligatorie");
	assert(d2.getCadruDidactic() == "Alexandrescu Marius");

}


void Teste::teste_repo() {
	RepoDisciplina repo;
	Disciplina d1{"ABCD1234", "OOP", 10, "Oblig.", "Popescu Marian"};
	repo.store(d1);
	vector<Disciplina> D = repo.getAll();
	assert(D.size() == 1);
	assert(D[0].getId() == "ABCD1234");
	assert(D[0].getDenumire() == "OOP");
	assert(D[0].getOre() == 10);
	assert(D[0].getTip() == "Oblig.");
	assert(D[0].getCadruDidactic() == "Popescu Marian");

	Disciplina d2{"ABCD1234", "OOP2", 10, "Oblig.", "Popescu Marian-Alexandru"};
	try {
		repo.store(d2);
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}

	Disciplina d3{ "ZZZZ8", "ASC", 12, "Obligatorie", "Vancea Alexandru" };
	repo.store(d3);
	D = repo.getAll();
	assert(D.size() == 2);

	Disciplina d4{ "ZZZYYY1", "Logica Computationala", 8, "Obligatorie", "Pop Malina" };

	try {
		repo.deleteDisciplina(d4);
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}
	
	repo.store(d4);
	D = repo.getAll();
	assert(D.size() == 3);

	repo.deleteDisciplina(d1);
	try {
		repo.find(d1.getId());
		assert(false);
	}
	catch (RepoExceptions& e) {
		stringstream os;
		os << e;
		assert(true);
	}
	D = repo.getAll();
	assert(D.size() == 2);
	repo.deleteDisciplina(d3);
	D = repo.getAll();
	assert(D.size() == 1);

	repo.deleteDisciplina(d4);
	D = repo.getAll();
	assert(D.size() == 0);

	try {
		repo.update(d1);
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}

	Disciplina d5{"ABK240","SDA", 8, "Oglibatorie2", "Matei Filipescu"};
	repo.store(d5);
	Disciplina d6{ "ABK240", "SDA2", 10, "ObligatorieSem2", "Matei Filipescu-Razvan" };
	repo.update(d6);
	assert(d6.getDenumire() == "SDA2");
	assert(d6.getOre() == 10);
	assert(d6.getTip() == "ObligatorieSem2");
	assert(d6.getCadruDidactic() == "Matei Filipescu-Razvan");

	RepoDisciplina r;
	r.goleste_contract();
}

void Teste::teste_validator() {
	ValidatorDisciplina v{};
	Disciplina d1{ "ABCD1234", "", 10, "Oblig.", "Popescu Marian" };
	try {
		v.validate(d1);
		assert(false);
	}
	catch (ValidateExceptions& e) {
		stringstream os;
		os << e;
		assert(true);
	}
	Disciplina d2{ "ABCD1234", "OOP", 0, "Oblig.", "Popescu Marian" };
	try {
		v.validate(d2);
		assert(false);
	}
	catch (ValidateExceptions&) {
		assert(true);
	}
	Disciplina d3{ "ABCD1234", "OOP", 10, "Obligatorie", "Ana" };
	try {
		v.validate(d3);
		assert(false);
	}
	catch (ValidateExceptions&) {
		assert(true);
	}
}

void Teste::teste_service() {
	RepoDisciplina r{};
	ValidatorDisciplina val;
	ServiceDisciplina srvv{ r, val };
	srvv.golire_contract();
	srvv.addDisciplina("ABC", "OOP", 14, "Facultativa", "Marius Alexandrescu");
	assert(srvv.filtrareDenumire("OOP").size() == 1);

	RepoDisciplina repo{};
	ValidatorDisciplina validator;
	ServiceDisciplina srv{ repo, validator };

	srv.addDisciplina("ABC", "OOP", 14, "Facultativa", "Marius Alexandrescu");
	vector<Disciplina>discipline = srv.getAll();
	assert(discipline.size() == 1);
	assert(discipline[0].getId() == "ABC");
	assert(discipline[0].getTip() == "Facultativa");
	assert(discipline[0].getCadruDidactic() == "Marius Alexandrescu");

	srv.addDisciplina("ABCDEF", "OOP2", 16, "Obligatorie", "Marius Alexandrescu");
	discipline = srv.getAll();
	assert(discipline.size() == 2);
	assert(discipline[1].getId() == "ABCDEF");

	srv.deleteDisciplinaSrv("ABC");
	discipline = srv.getAll();
	assert(discipline.size() == 1);
	assert(discipline[0].getId() == "ABCDEF");

	srv.updateDisciplina("ABCDEF", "OOP3", 8, "Oblig.", "Marius Alex.");
	discipline = srv.getAll();
	assert(discipline.size() == 1);
	assert(discipline[0].getDenumire() == "OOP3");
	assert(discipline[0].getOre() == 8);
	assert(discipline[0].getTip() == "Oblig.");
	assert(discipline[0].getCadruDidactic() == "Marius Alex.");

	try {
		srv.addDisciplina("ABCDEF", "OOP", 8, "Obligatorie", "Marius");
		assert(false);
	}
	catch (RepoExceptions&) {
		assert(true);
	}

	try {
		srv.deleteDisciplinaSrv("ABC");
		assert(false);
	}
	catch (ServiceExceptions& e) {
		stringstream os;
		os << e;
		assert(true);
	}

	try {
		srv.addDisciplina("ABCDEFGHI1", "", 10, "Facultativa", "Anamaria Alexandra");
		assert(false);
	}
	catch (ValidateExceptions&) {
		assert(true);
	}

	srv.addDisciplina("abc1234", "ASC", 12, "Obligatorie", "Marius Vanta");
	srv.addDisciplina("pqro8888", "SDA", 8, "Optionala", "Ramona Mariana");
	srv.addDisciplina("lmn4321", "FP", 14, "Obligatorie", "Popescu Alexandru");

	assert(srv.filtrareOre(12, 14).size() == 2);
	assert(srv.filtrareOre(8, 8).size() == 2);
	assert(srv.filtrareCadruDidactic("Marius Vanta").size() == 1);
	assert(srv.filtrareCadruDidactic("Popescu Alexandru").size() == 1);

	srv.updateDisciplina("pqro8888", "SDA", 10, "Obligatorie", "Marius Alex");
	srv.deleteDisciplinaSrv("lmn4321");

	srv.addDisciplina("aaa", "AAlgoritmica Grafelor", 5, "Oblig.", "Aaron Andrei");
	srv.addDisciplina("zzz", "ZZZ", 1000, "ZZZZZ", "Zdranc Rares");

	vector<Disciplina>DD = srv.sortByDenumire(false);
	assert(DD[0].getId() == "aaa");
	DD = srv.sortByOre(false);
	assert(DD[0].getId() == "aaa");
	DD = srv.sortByTipCadruDidactic(false);
	assert(DD[0].getId() == "aaa");

	DD = srv.sortByDenumire(true);
	assert(DD[0].getId() == "zzz");
	DD = srv.sortByOre(true);
	assert(DD[0].getId() == "zzz");
	DD = srv.sortByTipCadruDidactic(true);
	assert(DD[0].getId() == "zzz");
}

/*
void Teste::teste_dynamicArray() {
	vector<int> a{ 3 };

	assert(a.size() == 0);
	
	for (int i = 1; i <= 10; i++)
		a.push_back(i);

	for (int i = 1; i <= 10; i++)
		assert(a.get(i - 1) == i);

	assert(a.size() == 10);

	a.remove_element(4);
	assert(a.get(4) != 5);

	for (int i = 1; i <= 3; i++)
		a.remove_element(i);

	assert(a.size() == 6);

}
*/


void Teste::teste_domain_contract() {
	Contract c{};
	Contract c1{ "ABC1234"};
	Disciplina d1{ "ZZZ", "OOP", 10, "Oblig.", "Popescu Marian" };
	vector<Disciplina> discipline;
	discipline.push_back(d1);
	Contract c2{ "ABC1234", discipline};
	assert(c1 == c2);
	string id = c1.getId();
	assert(id == "ABC1234");
	vector<Disciplina> Dis = c2.getDiscipline();
	assert(Dis.size() == 1);
	assert(Dis[0].getId() == "ZZZ");
	Disciplina d2{ "AAA", "OOP", 12, "Facultativa", "Istvan Czibula" };
	c2.adaugare_disciplina(d2);
	assert(c2.getDiscipline().size() == 2);
	Dis.clear();
	Dis.push_back(d2);
	c2.setDiscipline(Dis);
	assert(c2.getDiscipline().size() == 1);
}

void Teste::teste_repo_contract() {
	RepoContract repoC;
	Disciplina d1{ "ZZZ", "OOP", 10, "Oblig.", "Popescu Marian" };
	Contract c{ "ABCXYZ" };
	repoC.add(c);
	repoC.adaugare_disciplina(repoC.getAll()[0], d1);


	assert(repoC.dim(c.getId()) == 1);
	repoC.goleste_contract("ABCXYZ");
	assert(repoC.dim(c.getId()) == 0);

	repoC.adaugare_disciplina(c, d1);

	vector<Contract> contracte = repoC.getAll();
	assert(contracte.size() == 1);
	Disciplina d2{ "PPP", "ASC", 18, "Obligatorie", "Vancea Alexandru" };

	repoC.adaugare_disciplina(repoC.getAll()[0], d2);

	try {
		repoC.adaugare_disciplina(repoC.getAll()[0], d2);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	repoC.dim("aa");
}

void Teste::teste_service_contract() {
	RepoContract repoC;
	RepoDisciplina repoD;
	ValidatorDisciplina validator;
	ServiceContract serv{ repoC, repoD, validator };

	Disciplina d1{ "ZZZ", "OOP", 10, "Oblig.", "Popescu Marian" };
	repoD.store(d1);
	
	serv.adaugare_contract_nou("ABCXYZ");
	assert(serv.getAll().size() == 1);

	try {
		serv.adaugare_contract_nou("ABCXYZ");
		assert(false);
	}
	catch (...) {
		assert(true);
	}


	try {
		serv.adaugare_disciplina_contract("aaa", "ZZZ");
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		serv.adaugare_disciplina_contract("ABCXYZ", "ppp");
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	serv.adaugare_disciplina_contract(serv.getAll()[0].getId(), repoD.getAll()[0].getId());
	assert(serv.getAll()[0].getDiscipline().size() == 1);

	serv.adaugare_discipline_random(serv.getAll()[0].getId(), 6);

	serv.export_contract(serv.getAll()[0].getId(), "rares.txt", 1);
	serv.export_contract(serv.getAll()[0].getId(), "zdranc.txt", 2);

	serv.golire_contract(serv.getAll()[0].getId());
}