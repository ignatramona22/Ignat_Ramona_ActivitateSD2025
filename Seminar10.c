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
////creare structura pentru un nod dintr-un arbore binar de cautare
//struct Nod {
//	Masina info;
//	struct Nod* st;
//	struct Nod* dr;
//};
//
//typedef struct Nod Nod;
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
//int calculeazaInaltimeArbore(Nod* radacina) {
//	if (radacina != NULL) {
//		int inaltimeStanga = calculeazaInaltimeArbore(radacina->st);
//		int inaltimeDreapta = calculeazaInaltimeArbore(radacina->dr);
//		return 1 + (inaltimeStanga > inaltimeDreapta ? inaltimeStanga : inaltimeDreapta);
//	}else
//	{
//		return 0;
//	}
//	
//}
//
////ALTE FUNCTII NECESARE:
//// - aici veti adauga noile functii de care aveti nevoie.
//void rotireStanga(Nod** radacina) {
//	Nod* nod;
//	nod = (*radacina)->dr;
//	(*radacina)->dr = nod->st;
//	nod->st = (*radacina);
//	(*radacina) = nod;
//}
//void rotireDreapta(Nod** radacina) {
//	Nod* nod;
//	nod = (*radacina)->st;
//	(*radacina)->st = nod->dr;
//	nod->st = (*radacina);
//	(*radacina) = nod;
//}
//
//int gradEchilibru(Nod* radacina) {
//	if(radacina !=NULL)
//	{
//		int gradEchilibru = calculeazaInaltimeArbore(radacina->st) - calculeazaInaltimeArbore(radacina->dr);
//		return gradEchilibru;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
//	if ((*radacina != NULL)) {
//		if ((*radacina)->info.id > masinaNoua.id) {
//			adaugaMasinaInArboreEchilibrat(&((*radacina)->st), masinaNoua);
//		}
//		else
//		{
//			adaugaMasinaInArboreEchilibrat(&((*radacina)->dr), masinaNoua);
//		}
//		int grad = gradEchilibru((*radacina));
//		if (grad  == 2) { //dezechilibru stanga
//			if (gradEchilibru((*radacina)->st) == 1) {
//				rotireDreapta(radacina);
//			}
//		}
//		else
//		{
//			rotireStanga(&((*radacina)->st));
//			rotireDreapta(radacina);
//		}
//		if (grad == -2) { //dezechilibru stanga
//			if (gradEchilibru((*radacina)->dr) == 1) {
//				rotireDreapta(&((*radacina)->dr));
//			}
//		}
//		else
//		{
//			rotireStanga(radacina);
//		}
//
//	}
//	else
//	{
//		Nod* nod = (Nod*)malloc(sizeof(Nod));
//		nod->info = masinaNoua;
//		nod->dr = NULL;
//		nod->st = NULL;
//		(*radacina) = nod;
//	}
//}
//
//Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Nod* radacina = NULL;
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		adaugaMasinaInArboreEchilibrat(&radacina, m);
//		free(m.model);
//		free(m.numeSofer);
//	}
//	fclose(file);
//	return radacina;
//}
//
//void afisareArborePreOrdine(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareMasina(radacina->info);
//		afisareArborePreOrdine(radacina->st);
//		afisareArborePreOrdine(radacina->dr);
//	}
//}
//void dezalocareArboreDeMasini(Nod** radacina) {
//	if ((*radacina) != NULL) {
//		dezalocareArboreDeMasini(&((*radacina)->st));
//		dezalocareArboreDeMasini(&((*radacina)->dr));
//		free((*radacina)->info.model);
//		free((*radacina)->info.numeSofer);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
////Preluati urmatoarele functii din laboratorul precedent.
////Acestea ar trebuie sa functioneze pe noul arbore echilibrat.
//Masina getMasinaByID(Nod* radacina, int id) {
//	Masina m;
//	m.id = -1;
//	if (id > radacina->info.id) {
//		return getMasinaByID(radacina->dr, id);
//	}
//	else if (id < radacina->info.id) {
//		return getMasinaByID(radacina->st, id);
//	}
//	else {
//		m = radacina->info;
//		m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
//		strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
//		m.model = (char*)malloc(strlen(radacina->info.model) + 1);
//		strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
//		return m;
//	}
//	return m;
//}
//
//int determinaNumarNoduri(Nod* radacina) {
//	if (radacina != NULL) {
//		return 1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
//	}
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* radacina) {
//	if(radacina!=NULL)
//	{
//		float sumaArbStang = calculeazaInaltimeArbore(radacina->st);
//		float sumaArbDrept = calculeazaInaltimeArbore(radacina->dr);
//		float arboreTotal = sumaArbStang + sumaArbDrept + radacina->info.pret;
//		return  arboreTotal;
//	}
//	else
//	{
//		return 0.0;
//	}
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer);
//
//int main() {
//	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
//	afisareArborePreOrdine(arbore);
//
//	printf("\nPretul total al masinilor: %.2f", calculeazaPretTotal(arbore));
//	return 0;
//}