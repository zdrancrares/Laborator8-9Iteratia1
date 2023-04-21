#pragma once
#include <assert.h>
#include "Disciplina.h"
#include "RepoDisciplina.h"
#include "ValidatorDisciplina.h"
#include "ServiceDisciplina.h"
#include "ServiceContract.h"
//#include "DynamicArray.h"

class Teste
{
public:
	Teste() {
	}

	void teste_domain();

	void teste_repo();

	void teste_service();

	void teste_validator();

	//void teste_dynamicArray();

	void teste_domain_contract();

	void teste_repo_contract();

	void teste_service_contract();

};

