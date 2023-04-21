#include "Teste.h"
#include "Consola.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	{
		srand((unsigned)time(0));
		Teste t;
		t.teste_domain();
		t.teste_validator();
		t.teste_repo();
		t.teste_service();
		t.teste_domain_contract();
		t.teste_repo_contract();
		t.teste_service_contract();

		RepoDisciplina repo;
		RepoContract repoC;
		ValidatorDisciplina validator;
		ServiceDisciplina srv{ repo, validator };
		ServiceContract srvc{ repoC, repo, validator };

		Consola c{ srv, srvc };
		c.run();
	}
	_CrtDumpMemoryLeaks();
}