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
////creare structura pentru Heap
////un vector de elemente, lungimea vectorului si numarul de elemente din vector
//struct Heap {
//	int lungime; //toate, inclusiv cele ascunse
//	Masina* vector;
//	int nrMasini; //elementele vizibile din heap
//};
//typedef struct Heap Heap;
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
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrMasini = 0;
//	heap.vector = (Masina*)malloc(sizeof(Masina) * lungime);
//	return heap;
//}
//
////poz = 1
////fiuStanga = 2 * pozR + 1
////fiuDreapta = 2 * pozR + 2
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
//	int pozFiuStanga = 2 * pozitieNod + 1;
//	int pozFiuDreapta = 2 * pozitieNod + 2;
//	int pozMaxim = pozitieNod;
//	if (pozFiuStanga < heap.nrMasini && heap.vector[pozMaxim].id < heap.vector[pozFiuStanga].id) {
//		pozMaxim = pozFiuStanga;
//	}
//	if (pozFiuDreapta < heap.nrMasini && heap.vector[pozMaxim].id < heap.vector[pozFiuDreapta].id) {
//		pozMaxim = pozFiuDreapta;
//	}
//	if (pozMaxim != pozitieNod) {
//
//		Masina aux = heap.vector[pozMaxim];
//		heap.vector[pozMaxim] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//		//if(2 * pozMaxim + 1 <= heap.nrMasini - 1)
//		if (pozMaxim <= (heap.nrMasini - 2) / 2) {
//			filtreazaHeap(heap, pozMaxim);
//		}
//	}
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(10);
//	while (!feof(file))
//	{
//		heap.vector[heap.nrMasini++] = citireMasinaDinFisier(file);
//	}
//	fclose(file);
//	for (int i = (heap.nrMasini - 2) / 2; i >= 0; i--) {
//		filtreazaHeap(heap, i);
//	}
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrMasini; i++) {
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	for (int i = heap.nrMasini; i < heap.lungime; i++) {
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//Masina extrageMasina(Heap* heap) { //extragere cu ascundere
//	if (heap->nrMasini > 0)
//	{
//		Masina aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrMasini - 1];
//		heap->vector[heap->nrMasini - 1] = aux;
//		heap->nrMasini--;
//		for (int i = (heap->nrMasini - 2) / 2; i >= 0; i--) {
//			filtreazaHeap(*heap, i);
//		}
//		return aux;// shallow copy
//	}
//
//}
//
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++) {
//		free(heap->vector[i].model);
//		free(heap->vector[i].numeSofer);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrMasini = 0;
//}
//
//int main() {
//	Heap heap = citireHeapDeMasiniDinFisier("masini.txt");
//	afisareHeap(heap);
//
//	printf("\nMasini Extrase:\n");
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//
//	printf("\nHeap ascuns:\n");
//	afiseazaHeapAscuns(heap);
//
//	dezalocareHeap(&heap);
//	afisareHeap(heap);
//	return 0;
//}