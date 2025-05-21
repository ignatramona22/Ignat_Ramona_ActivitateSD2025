//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
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
////STACK
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector
//void pushStack(Nod** stiva,  Masina masina) {
//	if ((*stiva) != NULL) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = masina;
//		nou->next = *stiva;
//		(*stiva) = nou;
//	}
//}
//
//Masina popStack(Nod** stiva) {
//	if ((*stiva) != NULL) {
//		Masina nou = (*stiva)->info;
//		Nod* prev = (*stiva);
//		(*stiva) = (*stiva)->next;
//		free(prev);
//		return nou;
//	}
//	else
//	{
//		Masina m;
//		m.id = -1;
//		return m;
//	}
//	
//
//}
//
//unsigned char emptyStack(Nod* stiva) {
//	return stiva == NULL;
//}
//
//Nod* citireStackMasiniDinFisier(const char* numeFisier) {
//	Nod* stiva = (Nod*)malloc(sizeof(Nod));
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f))
//	{
//		Masina masina = citireMasinaDinFisier(f);
//		pushStack(&stiva, masina);
//	}
//	fclose(f);
//	return stiva;
//}
//
////deplasarea in cadrul stivei se face doar prin pop
//
//void dezalocareStivaDeMasini(Nod** stiva) {
//	while ((*stiva) != NULL) {
//		Masina m = popStack(stiva);
//		free(m.numeSofer);
//		free(m.model);
//	}
//	
//}
//
//int size(Nod* stiva) {
//	int count = 0;
//	while (stiva!=NULL)
//	{
//		count++;
//		stiva = stiva->next;
//	}
//	return count;
//}
//
////QUEUE
////Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
////putem reprezenta o coada prin LSI, LDI sau vector
//
//typedef struct NodDublu NodDublu;
//typedef struct ListaDubla ListaDubla;
//struct NodDublu {
//	Masina info;
//	NodDublu* next;
//	NodDublu* prev;
//};
//
//struct ListaDubla {
//	Nod* prim;
//	Nod* ultim;
//};
//
//
//void enqueue(ListaDubla* coada, Masina masina) {
//	NodDublu* nou = (NodDublu*)malloc(sizeof(Nod));
//	nou->info = masina;
//	nou->prev = coada->ultim;
//	nou->next = NULL;
//	if (coada->ultim != NULL) {
//		coada->ultim->next = nou;
//		coada->ultim = nou;
//	}
//	else
//	{
//		coada->prim = nou;
//	}
//	coada->ultim = nou;
//
//}
//
//Masina dequeue(ListaDubla* coada) {
//	Masina m;
//	m.id = -1;
//	if (coada->prim != NULL) {
//		m = coada->ultim->info;
//		NodDublu* aux = coada->prim;
//		if (coada->prim->next != NULL) {
//			coada->prim = coada->prim->next;
//			//coada->prim->prev = NULL;
//		}
//		else
//		{
//			coada->prim = NULL;
//			coada->ultim = NULL;
//		}
//		free(aux);
//		
//		free(aux);
//	}
//	return m;
//}
//
//ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//	ListaDubla lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f))
//	{
//		Masina m;
//		enqueue(&lista, m);
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocareCoadaDeMasini(ListaDubla lista) {
//	NodDublu* aux = lista.ultim;
//	while (aux)
//	{
//		NodDublu* temp = aux;
//		aux = aux->prev;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//	lista.prim = NULL;
//	lista.ultim = NULL;
//}
//
//
////metode de procesare
//Masina getMasinaByID(/*stiva sau coada de masini*/int id);
//
//float calculeazaPretTotal(ListaDubla* coada) {
//	float suma = 0;
//	ListaDubla nod;
//	nod.prim = NULL;
//	nod.ultim = NULL;
//	while ((*coada).prim)
//	{
//		Masina m = dequeue(coada);
//		suma += m.pret;
//		enqueue(&nod, m);
//	}
//	coada->prim = nod.prim;
//	return suma;
//}
//
//int main() {
//	/*Nod* stiva = citireStackMasiniDinFisier("masini.txt");
//	int nr = size(stiva);
//
//	printf("Numar masini %d", nr);
//	Masina m = popStack(&stiva);
//	afisareMasina(m);
//	free(m.numeSofer);
//	free(m.model);
//
//	Masina m1 = popStack(&stiva);
//	afisareMasina(m1);
//	free(m1.numeSofer);
//	free(m1.model);*/
//
//	
//
//	ListaDubla lista = citireCoadaDeMasiniDinFisier("masini.txt");
//	Masina m = dequeue(&lista);
//	afisareMasina(m);
//	free(m.numeSofer);
//	free(m.model);
//
//	
//	return 0;
//}
