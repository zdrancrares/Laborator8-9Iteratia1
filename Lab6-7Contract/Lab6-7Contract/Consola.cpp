#include "Consola.h"

using std::cout;
using std::cin;
using std::string;
using std::ws;

void Consola::printMenu() {
	cout << "Alegeti una dintre urmatoarele optiuni: \n";
	cout << "0. Exit.\n";
	cout << "1. Afisare discipline\n";
	cout << "2. Adaugare disciplina\n";
	cout << "3. Stergere disciplina\n";
	cout << "4. Modificare disciplina\n";
	cout << "5. Filtrare discipline\n";
	cout << "6. Sortare discipline\n";
	cout << "7. Optiuni contract\n";
	cout << "Optiunea dvs: ";
}

void Consola::printDisciplineUI(vector<Disciplina> discipline) {
	if (discipline.size() == 0)
		cout << "Nu exista nicio disciplina in contract.\n";
	else {
		cout << "---------------------------------------------------------------------------------------\n";
		printf("%15s%15s%15s%20s%20s\n", "ID", "Denumire", "Ore", "Tip", "Cadru Didactic");
		for (int i = 0; i < discipline.size(); i++) {
			printf("%15s%15s%15d%20s%20s\n", discipline[i].getId().c_str(), discipline[i].getDenumire().c_str(), discipline[i].getOre(), discipline[i].getTip().c_str(), discipline[i].getCadruDidactic().c_str());
		}
		cout << "---------------------------------------------------------------------------------------\n";
	}
}
void Consola::addDisciplinaUI() {
	int ore;
	string id, denumire, tip, cadruDidactic;
	cout << "Introduceti id-ul disciplinei: ";
	cin >> id;
	cout << "Introduceti denumirea disciplinei: ";
	cin >> denumire;
	cout << "Introduceti numarul de ore pe saptamana pentru aceasta disciplina: ";
	cin >> ore;
	
	while (cin.fail()) {
		cout << "Va rog introduceti un numar intreg\n";
		cin.clear();
		cin.ignore(256, '\n'); 
		cin >> ore;
	}
	while (ore <= 0) {
		cout << "Numarul de ore trebuie sa fie > 0\n";
		cin >> ore;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> ore;
		}
	}
	
	cout << "Introduceti tipul disciplinei: ";
	cin >> tip;
	cout << "Introduceti cadrul didactic ce preda aceasta disciplina: ";
	//cin >> cadruDidactic;
	getline(cin >> ws, cadruDidactic);

	srv.addDisciplina(id, denumire, ore, tip, cadruDidactic);
	cout << "Disciplina (" << id  << ") a fost adaugata cu succes!\n";
}
void Consola::deleteDisciplinaUI() {
	string id;
	cout << "Introduceti id-ul disciplinei pe care doriti sa o stergeti: ";
	cin >> id;
	srv.deleteDisciplinaSrv(id);
	cout << "Disciplina (" << id << ") a fost stearsa cu succes!\n";
}
void Consola::updateDisciplinaUI() {
	int ore;
	string id, denumire, tip, cadruDidactic;
	cout << "Introduceti id-ul disciplinei pe care doriti sa o modificati: ";
	cin >> id;
	cout << "Introduceti noua denumire a disciplinei: ";
	cin >> denumire;
	cout << "Introduceti noul numar de ore pe saptamana pentru aceasta disciplina: ";
	cin >> ore;

	while (cin.fail()) {
		cout << "Va rog introduceti un numar intreg\n";
		cin.clear();
		cin.ignore(256, '\n');  
		cin >> ore;
	}

	while (ore <= 0 || cin.fail()) {
		cout << "Numarul de ore trebuie sa fie > 0\n";
		cin >> ore;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> ore;
		}
	}

	cout << "Introduceti noul tip al disciplinei: ";
	cin >> tip;
	cout << "Introduceti noul cadru didactic ce preda aceasta disciplina: ";
	getline(cin >> ws, cadruDidactic);
	srv.updateDisciplina(id, denumire, ore, tip, cadruDidactic);
	cout << "Disciplina (" << id << ") a fost modificata cu succes!\n";
}

void Consola::filtrareDisciplineUI() {
	cout << "Introduceti criteriul dupa care doriti sa filtrati: \n";
	cout << "1. Numarul de ore din saptamana\n";
	cout << "2. Cadru didactic\n";
	int option;
	cin >> option;
	if (option == 1) {
		int inceput, sfarsit;
		cout << "Introduceti limita inferioara de ore: ";
		cin >> inceput;

		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> inceput;
		}

		cout << "Introduceti limita superioara de ore: ";
		cin >> sfarsit;

		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> sfarsit;
		}

		vector<Disciplina> rez = srv.filtrareOre(inceput, sfarsit);
		printDisciplineUI(rez);
	}
	else if (option == 2) {
		string cadruDidactic;
		cout << "Introduceti numele cadrului didactic dupa care doriti sa filtrati: ";
		getline(cin >> ws, cadruDidactic);
		vector<Disciplina> rez = srv.filtrareCadruDidactic(cadruDidactic);
		printDisciplineUI(rez);
	}
	else {
		cout << "Nu ati introdus o optiune valida.\n";
	}
}

void Consola::sortareDisciplineUI() {
	cout << "Alegeti dupa ce doriti sa sortati: \n";
	cout << "1. Denumire\n";
	cout << "2. Numarul de ore\n";
	cout << "3. Tip + cadru didactic\n";
	cout << "Optiunea dvs: ";

	int option;
	cin >> option;
	while (cin.fail()) {
		cout << "Va rog introduceti un numar intreg valid\n";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> option;
	}
	if (option == 1) {
		cout << "Alegeti cum doriti sa sortati: \n";
		cout << "1. Crescator\n";
		cout << "2. Descrescator\n";
		cout << "Optiunea dvs: ";
		cin >> option;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg valid\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> option;
		}
		bool reverse = false;
		if (option == 2)
			reverse = true;
		printDisciplineUI(srv.sortByDenumire(reverse));
	}
	else if (option == 2) {
		cout << "Alegeti cum doriti sa sortati: \n";
		cout << "1. Crescator\n";
		cout << "2. Descrescator\n";
		cout << "Optiunea dvs: ";
		cin >> option;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg valid\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> option;
		}
		bool reverse = false;
		if (option == 2)
			reverse = true;
		printDisciplineUI(srv.sortByOre(reverse));
	}
	else if (option == 3) {
		cout << "Alegeti cum doriti sa sortati: \n";
		cout << "1. Crescator\n";
		cout << "2. Descrescator\n";
		cout << "Optiunea dvs: ";
		cin >> option;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg valid\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> option;
		}
		bool reverse = false;
		if (option == 2)
			reverse = true;
		printDisciplineUI(srv.sortByTipCadruDidactic(reverse));
	}
	else {
		cout << "Nu ati introdus o optiune valida.";
	}
}

void Consola::ContractUI() {
	cout << "Alegeti una dintre urmatoarele optiuni: \n";
	cout << "1. Adaugare contract nou\n";
	cout << "2. Golire contract\n";
	cout << "3. Adaugare disciplina in contract\n";
	cout << "4. Adaugare discipine generate aleator in contract\n";
	cout << "5. Afisare discipline dintr-un contract\n";
	cout << "6. Afisare contracte\n";
	cout << "7. Export contract\n";
	int optiune;
	cin >> optiune;

	while (cin.fail()) {
		cout << "Va rog introduceti un numar intreg\n";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> optiune;
	}
	while (optiune <= 0) {
		cout << "Numarul trebuie sa fie > 0\n";
		cin >> optiune;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> optiune;
		}
	}

	if (optiune == 1) {
		cout << "Introduceti id-ul noului contract: \n";
		string id;
		getline(cin >> ws, id);
		srvC.adaugare_contract_nou(id);
		cout << "Contractul(" << id << ") a fost adaugat cu succes\n";
	}

	else if (optiune == 2) {
		cout << "Introduceti id-ul contractului pe care doriti sa-l goliti: \n";
		string id;
		getline(cin >> ws, id);
		srvC.golire_contract(id);
		cout << "Contractul(" << id << ") a fost golit cu succes\n";
	}

	else if (optiune == 3) {
		cout << "Introduceti id-ul contractului in care doriti sa adaugati: \n";
		string id_contract;
		getline(cin >> ws, id_contract);
		Contract c = srvC.get_contract_id(id_contract);

		cout << "Introduceti denumire disciplinei pe care doriti sa o adaugati: \n";
		string denumire;
		getline(cin >> ws, denumire);
		vector<Disciplina> dis = srv.filtrareDenumire(denumire);
		printDisciplineUI(dis);
		cout << "Alegeti id-ul disciplinei pe care doriti sa o adaugati: \n";
		string id;
		getline(cin >> ws, id);

		srvC.adaugare_disciplina_contract(id_contract, id);
		cout << "Disciplina(" << id << ") a fost adaugata in contract(" << id_contract << ") cu succes!\n";

	}

	else if (optiune == 4) {
		cout << "Introduceti id-ul contractului in care doriti sa adaugati: \n";
		string id_contract;
		getline(cin >> ws, id_contract);

		cout << "Introduceti numarul de discipline pe care doriti sa le adaugati in contract: \n";
		int numar;
		cin >> numar;

		srvC.adaugare_discipline_random(id_contract, numar);
		cout << "Au fost adaugate " << numar << " discipline in contractul " << id_contract << "\n";
	}

	else if(optiune == 5) {
		cout << "Introduceti id-ul contractului de afisat: \n";
		string id;
		getline(cin >> ws, id);
		Contract c = srvC.get_contract_id(id);
		printDisciplineUI(c.getDiscipline());
	}

	else if (optiune == 6) {
		if (srvC.getAll().size() == 0) {
			cout << "Nu exista niciun contract!\n";
			return;
		}
		cout << "-------------------------------------------------------";
		for (auto& elem : srvC.getAll()) {
			cout << elem.getId() << '\n';
		}
		cout << "-------------------------------------------------------";
	}
	
	else if (optiune == 7) {
		cout << "Introduceti id-ul contractului pe care doriti sa-l exportati: \n";
		string id_contract;
		getline(cin >> ws, id_contract);

		cout << "Introduceti numele fisierului unde doriti sa exportati: \n";
		string nume_fisier;
		getline(cin >> ws, nume_fisier);

		cout << "Introduceti formatul sub care doriti sa exportati: \n";
		cout << "1. CSV\n";
		cout << "2. HTML\n";

		int op;
		cin >> op;
		
		srvC.export_contract(id_contract, nume_fisier, op);
		cout << "Disciplinele au fost exportate cu succes!\n";
	}
}

void Consola::run() {
	while (true) {
		printMenu();
		int optiune;
		cin >> optiune;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n'); 
			cin >> optiune;
		}
		try {
			switch (optiune){
			case 1:
				printDisciplineUI(srv.getAll());
				break;
			case 2:
				addDisciplinaUI();
				break;
			case 3:
				deleteDisciplinaUI();
				break;
			case 4:
				updateDisciplinaUI();
				break;
			case 5:
				filtrareDisciplineUI();
				break;
			case 6:
				sortareDisciplineUI();
				break;
			case 7:
				ContractUI();
				break;
			case 0:
				return;
			default:
				cout << "Ati introdus o comanda invalida.\n";
			}
		}
		catch (const RepoExceptions& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateExceptions& ex) {
			cout << ex << '\n';
		}
		catch (const ServiceExceptions& ex) {
			cout << ex << '\n';
		}
		catch (const std::exception& e) {
			std::cout << "Caught " << e.what() << "\n";
		}
	}
}