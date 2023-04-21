#pragma once
#include "ServiceDisciplina.h"
#include "ServiceContract.h"

#include <iostream>

class Consola
{
private:
	ServiceDisciplina& srv;
	ServiceContract& srvC;
public:
	Consola(ServiceDisciplina& srv, ServiceContract& srvc) :srv{ srv }, srvC{ srvc } {};

	void printMenu();
	void printDisciplineUI(vector<Disciplina> discipline);
	void addDisciplinaUI();
	void deleteDisciplinaUI();
	void updateDisciplinaUI();
	void filtrareDisciplineUI();
	void sortareDisciplineUI();
	void ContractUI();
	void run();
	
};

