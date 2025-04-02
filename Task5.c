//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date
//
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//
//struct Nod
//{
//	Masina info;
//	Nod* next;
//};
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret= atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* cap) {
//	while (cap != NULL)
//	{
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//
//	if ((*cap) == NULL)
//	{
//		*cap = nou;
//	}
//	else 
//	{
//		Nod* p = *cap;
//		while (p->next)
//		{
//			p = p->next;
//		}
//		p->next = nou;
//	}
//	
//}
//
//void adaugaLaInceputInLista(Nod** cap,  Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	prin apelul repetat al functiei citireMasinaDinFisier()
//	ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* f = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(f))
//	{
//		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f)); //daca am fi facut deep copy ar fi trebuit sa stergem aici 
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocareListaMasini(Nod** cap) {
//	while (*cap!=NULL)
//	{
//		Nod* aux = (*cap);
//		(*cap) = (*cap)->next;
//		free(aux->info.model);
//		free(aux->info.numeSofer);
//		free(aux);
//	}
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	calculeaza pretul mediu al masinilor din lista.
//	if (!lista) return 0;
//
//	int count = 0;
//	float suma = 0;
//	while (lista)
//	{
//		suma += lista->info.pret;
//		count++;
//		lista = lista->next;
//	}
//	
//	if (count > 0)
//	{
//		return suma / count;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//void stergeMasiniDinSeria(Nod** cap,  const char* serieCautata) {
//	sterge toate masinile din lista care au seria primita ca parametru.
//	tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//
//
//	while ((*cap) != NULL && (*cap)->info.serie == serieCautata)
//	{
//		Nod* p = (*cap);
//		(*cap) = (*cap)->next;
//		free(p->info.model);
//		free(p->info.numeSofer);
//		free(p);
//	}
//
//
//	Nod* p = (*cap);
//	while ( p !=NULL)
//	{
//		while (p->next && p->next->info.serie != serieCautata)
//		{
//			p = p->next;
//		}
//		if (p->next!= NULL)
//		{
//			Nod* temp = p->next;
//			p->next = temp->next;
//			free(temp->info.model);
//			free(temp->info.numeSofer);
//			free(temp);
//		}
//		else
//		{
//			p = p->next;
//		}
//	}
//
//
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
//	calculeaza pretul tuturor masinilor unui sofer.
//	if (!lista) return 0;
//
//	float suma = 0;
//	while (lista)
//	{
//		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
//		{
//			suma += lista->info.pret;
//		}
//		lista = lista->next;
//	}
//
//	return suma;
//}
//
//
//void stergeNodPePozitie(Nod** cap, int pozitie) {
//	if (*cap == NULL || pozitie < 0) return NULL;
//
//	Caz 1 - stergem primul nod
//	Nod* temp = *cap;
//	if (pozitie == 0) {
//		*cap = temp->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//		return;
//	}
//
//	Caz 2 - stergem un nod intermediar sau final
//	Nod* p = *cap;
//	int index = 0;
//	while (p!=NULL)
//	{
//		while (p->next && index + 1 != pozitie) {
//			p = p->next;
//			index++;
//		}
//		if (p->next != NULL) {
//			Nod* temp = p->next;
//			p->next = temp->next;
//			free(temp->info.model);
//			free(temp->info.numeSofer);
//			free(temp);
//			return;
//		}
//		else
//		{
//			p = p->next;
//		}
//	}
//}
//
//void inserareSortataDupaPret(Nod** cap, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	if (!nou) {
//		printf("Eroare la alocarea memoriei!\n");
//		return;
//	}
//
//	 Deep copy
//	nou->info.id = masinaNoua.id;
//	nou->info.nrUsi = masinaNoua.nrUsi;
//	nou->info.pret = masinaNoua.pret;
//	nou->info.serie = masinaNoua.serie;
//
//	nou->info.model = malloc(strlen(masinaNoua.model) + 1);
//	if (nou->info.model == NULL) exit(1);
//	strcpy(nou->info.model, masinaNoua.model);
//
//	nou->info.numeSofer = malloc(strlen(masinaNoua.numeSofer) + 1);
//	if (nou->info.numeSofer == NULL) exit(1);
//	strcpy(nou->info.numeSofer, masinaNoua.numeSofer);
//
//	nou->next = NULL;
//
//	if (*cap == NULL || (*cap)->info.pret >= masinaNoua.pret) {
//		nou->next = *cap;
//		*cap = nou;
//		return;
//	}
//
//	Nod* temp = *cap;
//	while (temp->next != NULL && temp->next->info.pret < masinaNoua.pret) {
//		temp = temp->next;
//	}
//
//	nou->next = temp->next;
//	temp->next = nou;
//}
//
//Masina* salveazaMasiniPretMare(Nod* lista, int* dimensiune) {
//	*dimensiune = 0;
//	Nod* temp = lista;
//
//	while (temp) {
//		if (temp->info.pret > 20000.0) {
//			(*dimensiune)++;
//		}
//		temp = temp->next;
//	}
//
//	if (*dimensiune == 0) return NULL;
//
//	Masina* vector = (Masina*)malloc((*dimensiune) * sizeof(Masina));
//	temp = lista;
//	int index = 0;
//
//	while (temp) {
//		if (temp->info.pret > 20000.0) {
//			vector[index].id = temp->info.id;
//			vector[index].nrUsi = temp->info.nrUsi;
//			vector[index].pret = temp->info.pret;
//			vector[index].serie = temp->info.serie;
//
//			vector[index].model = (char*)malloc(strlen(temp->info.model) + 1);
//			strcpy(vector[index].model, temp->info.model);
//
//			vector[index].numeSofer = (char*)malloc(strlen(temp->info.numeSofer) + 1);
//			strcpy(vector[index].numeSofer, temp->info.numeSofer);
//
//			index++;
//		}
//		temp = temp->next;
//	}
//
//	return vector;
//}
//
//
//void interschimbaElemente(Nod** cap, int pos1, int pos2) {
//	if (pos1 == pos2) return;
//
//	Nod* prev1 = NULL, * prev2 = NULL, * nod1 = *cap, * nod2 = *cap;
//	int index = 0;
//
//	while (nod1 && index < pos1) {
//		prev1 = nod1;
//		nod1 = nod1->next;
//		index++;
//	}
//
//	index = 0;
//	while (nod2 && index < pos2) {
//		prev2 = nod2;
//		nod2 = nod2->next;
//		index++;
//	}
//
//	if (!nod1 || !nod2) return;
//
//	if (prev1) prev1->next = nod2;
//	else *cap = nod2;
//
//	if (prev2) prev2->next = nod1;
//	else *cap = nod1;
//
//	Nod* temp = nod2->next;
//	nod2->next = nod1->next;
//	nod1->next = temp;
//}
//
//
//int main() {
//	Nod* lista = NULL;
//	lista = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//
//	printf("\n=== Stergere nod de pe pozitia 1 ===\n");
//	stergeNodPePozitie(&lista, 1);
//	afisareListaMasini(lista);
//
//	printf("\n=== Lista dupa inserare sortata ===\n");
//	Masina m1 = { 11, 4, 25000, "BMW", "Andrei", 'A' };
//	Masina m2 = { 12, 2, 15000,"Ford","Maria", 'B' }; 
//	Masina m3 = { 13, 5, 30000,  "Audi", "Ion", 'C' };
//	inserareSortataDupaPret(&lista, m1);
//	inserareSortataDupaPret(&lista, m2);
//	inserareSortataDupaPret(&lista, m3);
//	afisareListaMasini(lista);
//
//	printf("\n=== Salvare in vector (masini cu pret > 20000) ===\n");
//	int dim;
//	Masina* masiniScumpe = salveazaMasiniPretMare(lista, &dim);
//	for (int i = 0; i < dim; i++) {
//		afisareMasina(masiniScumpe[i]);
//		free(masiniScumpe[i].model);
//		free(masiniScumpe[i].numeSofer);
//	}
//	free(masiniScumpe);
//
//
//	printf("\n=== Inter-schimbare elemente pozitiile 0 si 1 ===\n");
//	interschimbaElemente(&lista, 0, 1);
//	afisareListaMasini(lista);
//
//	dezalocareListaMasini(&lista);
//	return 0;
//}