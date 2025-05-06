#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraPacient
{
	int  id;
	char* numePacient;
	int varsta;
	int gradUrgenta;
};

typedef struct StructuraPacient Pacient;

struct Heap {
	int lungime;
	Pacient* vector;
	int nrPacienti;
};

typedef struct Heap Heap;

Pacient citirePacientDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Pacient p;
	aux = strtok(buffer, sep);
	p.id = atoi(aux);

	aux = strtok(NULL, sep);
	p.numePacient = malloc(strlen(aux) + 1);
	strcpy_s(p.numePacient, strlen(aux) + 1, aux);

	p.varsta = atoi(strtok(NULL, sep));
	p.gradUrgenta = atoi(strtok(NULL, sep));
	return p;

}

void afisarePacient(Pacient p) {
	printf("ID: %d, Nume: %s, Varsta: %d, Grad Urgenta: %d\n",
		p.id, p.numePacient, p.varsta, p.gradUrgenta);
}

Heap initializareHeap(int dimensiune) {
	Heap h;
	h.lungime = dimensiune;
	h.nrPacienti = 0;
	h.vector = (Pacient*)malloc(dimensiune * sizeof(Pacient));
	return h;
}

void filtreazaHeap(Heap heap, int pozitie) {
	int pozStanga = 2 * pozitie + 1;
	int pozDreapta = 2 * pozitie + 2;
	int pozMax = pozitie;

	if (pozStanga < heap.nrPacienti && heap.vector[pozMax].gradUrgenta < heap.vector[pozStanga].gradUrgenta) {
		pozMax = pozStanga;
	}
	if (pozDreapta < heap.nrPacienti && heap.vector[pozMax].gradUrgenta < heap.vector[pozDreapta].gradUrgenta) {
		pozMax = pozDreapta;
	}
	if (pozMax != pozitie) {
		Pacient aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitie];
		heap.vector[pozitie] = aux;
		if (pozMax <= (heap.nrPacienti - 2) / 2) {
			filtreazaHeap(heap, pozMax);
		}
	}
}


Heap citireHeapDePacientiDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(5);

	while (!feof(file)) {
		heap.vector[heap.nrPacienti++] = citirePacientDinFisier(file);
	}
	fclose(file);
	for (int i = (heap.nrPacienti - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrPacienti; i++) {
		afisarePacient((heap.vector[i]));
	}
}


Pacient extragePagientPrioritateMax(Heap* heap) {
	if (heap->nrPacienti > 0) {
		Pacient aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrPacienti - 1];
		heap->vector[heap->nrPacienti - 1] = aux;
		heap->nrPacienti--;
		for (int i = (heap->nrPacienti - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
		return aux; 
	}
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].numePacient);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrPacienti = 0;
}
int main() {
	Heap heap = citireHeapDePacientiDinFisier("pacienti.txt");
	afisareHeap(heap);

	printf("\nPacientii in stare grava\n");
	afisarePacient(extragePagientPrioritateMax(&heap));

	dezalocareHeap(&heap);
	return 0;
}
