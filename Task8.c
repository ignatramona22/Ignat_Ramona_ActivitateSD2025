//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraCladire {
//	int id;
//	int anConstructie;
//	char* denumireCladire;
//
//};
//typedef struct StructuraCladire Cladire;
//
//struct Nod {
//	Cladire info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//struct HashTable
//{
//	int dim;
//	Nod** vector;
//};
//typedef struct HashTable HashTable;
//
//
//Cladire citesteCladireDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Cladire c;
//	aux = strtok(buffer, sep);
//	c.id = atoi(aux);
//	c.anConstructie = atoi(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	c.denumireCladire = malloc(strlen(aux) + 1);
//	strcpy_s(c.denumireCladire, strlen(aux) + 1, aux);
//	return c;
//}
//
//void afisareCladire(Cladire c) {
//	printf("ID: %d\n", c.id);
//	printf("\nAn constructie: %d\n", c.anConstructie);
//	printf("\nDenumire cladire: %s\n", c.denumireCladire);
//}
//
//void afisareListaCladiri(Nod* cap) {
//	while (cap)
//	{
//		afisareCladire(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaCladireInLista(Nod* cap, Cladire cladire) {
//	Nod* p = cap;
//	while (p->next)
//	{
//		p = p->next;
//	}
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = cladire;
//	nou->next = NULL;
//	p->next = nou;
//}
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
//int calculeazaHash(int anContructie, int dimendiune) {
//	return anContructie % dimendiune;
//}
//
//void inserareCladireInTabela(HashTable hash, Cladire cladire) {
//	int pozitie = calculeazaHash(cladire.anConstructie, hash.dim);
//	if (hash.vector[pozitie] == NULL) {
//		hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
//		hash.vector[pozitie]->info = cladire;
//		hash.vector[pozitie]->next = NULL;
//	}
//	else
//	{
//		adaugaCladireInLista(hash.vector[pozitie], cladire);
//	}
//}
//
//
//HashTable citireListaCladiriDinFisier(const char* numeFisier, int dimensiune) {
//	HashTable hash = initializareHashTable(dimensiune);
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		Cladire cladire = citesteCladireDinFisier(f);
//		inserareCladireInTabela(hash, cladire);
//	}
//	fclose(f);
//	return hash;
//}
//
//void afisareTabelaCladiri(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		if (ht.vector[i] != NULL) {
//			printf("\Cladirile de pe pozitia %d sunt:\n", i);
//			afisareListaCladiri(ht.vector[i]);
//		}
//		else {
//			printf("\nPe pozitia %d nu avem cladiri\n", i);
//		}
//	}
//}
//
//void dezalocareListaCladiri(Nod** cap) {
//	Nod* p = *cap;
//	while (p) {
//		Nod* temp = p;
//		p = p->next;
//		if (temp->info.denumireCladire != NULL) {
//			free(temp->info.denumireCladire);
//		}
//		free(temp);
//	}
//	*cap = NULL;
//}
//
//void dezalocareTabelaDeMasini(HashTable* ht) {
//	for (int i = 0; i < ht->dim; i++) {
//		dezalocareListaCladiri(&(ht->vector[i]));
//	}
//	free(ht->vector);
//	ht->vector = NULL;
//	ht->dim = 0;
//}
//
//
//int main() {
//	HashTable ht = citireListaCladiriDinFisier("cladiri.txt", 10);
//	afisareTabelaCladiri(ht);
//
//}