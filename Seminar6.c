//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//struct HashTable {
//	int dim;
//	Nod** vector;
//};
//typedef struct HashTable HashTable;
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
//	m1.pret = atof(strtok(NULL, sep));
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
//	while (cap)
//	{
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod* cap, Masina masinaNoua) {
//	Nod* p = cap;
//	while (p->next)
//	{
//		p = p->next;
//	}
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	p->next = nou;
//}
//
//
//HashTable initializareHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
//	for (int i = 0; i < dimensiune; i++) {
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(const char* nume, int dimensiune) {
//	int suma = 0;
//	for (int i = 0; i < strlen(nume); i++) {
//		suma += nume[i];
//	}
//	return suma % dimensiune;
//}
//
//void inserareMasinaInTabela(HashTable hash, Masina masina) {
//	int pozitie = calculeazaHash(masina.numeSofer, hash.dim);
//	if (hash.vector[pozitie] == NULL) {
//
//		hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
//		hash.vector[pozitie]->info = masina;
//		hash.vector[pozitie]->next = NULL;
//	}
//	else
//	{
//		adaugaMasinaInLista(hash.vector[pozitie], masina);
//	}
//}
//
//HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) {
//	HashTable hash = initializareHashTable(dimensiune);
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f))
//	{
//		inserareMasinaInTabela(hash, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return hash;
//}
//
//void afisareTabelaDeMasini(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		if (ht.vector[i] != NULL) {
//			printf("\nMasinile de pe pozitia %d sunt: \n", i);
//			afisareListaMasini(ht.vector[i]);
//		}
//		else
//		{
//			printf("Pe pozitia %d nu avem masini\n", i);
//		}
//	}
//}
//
//void dezalocareLista(Nod** cap) {
//	while ((*cap))
//	{
//		Nod* aux = (*cap);
//		(*cap) = (*cap)->next;
//		free(aux->info.model);
//		free(aux->info.numeSofer);
//		free(aux);
//	}
//}
//
//void dezalocareTabelaDeMasini(HashTable* ht) {
//	for (int i = 0; i < ht->dim; i++) {
//		dezalocareLista(&(ht->vector[i]));
//	}
//	free(ht->vector);
//	ht->vector = NULL;
//	ht->dim = 0;
//}
//
//
//float mediePreturiLista(Nod* cap) {
//	float suma = 0;
//	int count = 0;
//	while (cap)
//	{
//		suma += cap->info.pret;
//		count++;
//		cap = cap->next;
//	}
//	if (count > 0) {
//		return suma / count;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
//	float* preturi = NULL;
//	*nrClustere = 0;
//	for (int i = 0; i < ht.dim; i++) {
//		if (ht.vector[i] != NULL) {
//			(*nrClustere)++;
//		}
//	}
//
//	preturi = (float*)malloc(sizeof(float) * (*nrClustere));
//	int contor = 0;
//	for (int i = 0; i < ht.dim; i++) {
//		if (ht.vector[i] != NULL) {
//			preturi[contor] = mediePreturiLista(ht.vector[i]);
//			contor++;
//		}
//	}
//	return preturi;
//	return NULL;
//}
//
//Masina getMasinaDupaNume(Nod* cap, const char* numeC) {
//	Masina m;
//	m.id = -1;
//	while (cap && strcmp(cap->info.numeSofer, numeC) != 0)
//	{
//		cap = cap->next;
//	}
//	if (cap) {
//		m = cap->info;
//		m.model = (char*)malloc(strlen(cap->info.model) + 1);
//		strcpy_s(m.model, strlen(cap->info.model) + 1, cap->info.model);
//
//		m.numeSofer = (char*)malloc(strlen(cap->info.numeSofer) + 1);
//		strcpy_s(m.numeSofer, strlen(cap->info.numeSofer) + 1, cap->info.numeSofer);
//	}
//	return m;
//}
//
//Masina getMasinaDupaCheie(HashTable ht, const char* numeCautat) {
//	Masina m;
//	m.id = -1;
//	int poz = calculeazaHash(numeCautat, ht.dim);
//	if (poz >= 0 && poz < ht.dim) {
//		return getMasinaDupaNume(ht.vector[poz], numeCautat);
//	}
//	return m;
//}
//
//int main() {
//	HashTable ht = citireMasiniDinFisier("masini.txt", 7);
//	afisareTabelaDeMasini(ht);
//
//	int nrClustere = 0;
//	float* preturi = calculeazaPreturiMediiPerClustere(ht, &nrClustere);
//	printf("\nPreturile medii per clustere:\n");
//	for (int i = 0; i < nrClustere; i++) {
//		printf("%.2f  ", preturi[i]);
//	}
//	printf("\n");
//
//	Masina masina = getMasinaDupaCheie(ht, "Gheorghe Marcel");
//	printf("\nMasina cautata este:\n");
//	afisareMasina(masina);
//
//	//pentru ca am facut deep copy
//	free(masina.model);
//	free(masina.numeSofer);
//
//	printf("\nAm sters tabela");
//	dezalocareTabelaDeMasini(&ht);
//	afisareTabelaDeMasini(ht);
//	return 0;
//}