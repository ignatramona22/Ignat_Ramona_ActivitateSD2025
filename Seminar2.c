#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	char* model;
	float tonaj;
	char serie;
};

struct Masina initializare(int _id, const char* _model, float _tonaj, char _serie) {
	struct Masina m;
	m.id = _id;
	m.model = malloc(sizeof(char) * (strlen(_model) + 1));
	strcpy_s(m.model, (strlen(_model) + 1), _model);
	m.tonaj = _tonaj;
	m.serie = _serie;
	return m;
}

void afisare(struct Masina m) {
	printf("Id: %d\n Model: %s\n Tonaj: %.2f\n Serie: %c\n", m.id, m.model, m.tonaj, m.serie);

}

void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
	}
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Masina* vectorNou = malloc(sizeof(struct Masina) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = vector[i];
		vectorNou[i].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
		strcpy_s(vectorNou[i].model, (strlen(vector[i].model) + 1), vector[i].model);
	}


	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++)
	{
		free((*vector)[i].model);
	}

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaMasiniCuTonajMic(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	(*dimensiune) = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].tonaj < prag)
		{
			(*dimensiune)++;

		}
	}

	(*vectorNou) = malloc(sizeof(struct Masina) * (*dimensiune));

	int k = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].tonaj < prag)
		{
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
			strcpy_s((*vectorNou)[k].model, (strlen(vector[i].model) + 1), vector[i].model);
			k++;
		}
	}
}

struct Masina getPrimaMasinaDupaModel(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.

	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].model, conditie) == 0) {
			struct Masina m;
			m.id = vector[i].id;
			m.tonaj = vector[i].tonaj;
			m.serie = vector[i].serie;

			// Alocare memorie pentru model și copierea acestuia
			m.model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
			strcpy_s(m.model, (strlen(vector[i].model) + 1), vector[i].model);

			return m;
		}
	}

	struct Masina m;
	m.id = 1;
	m.model = NULL;
	m.tonaj = 0;
	m.serie = '\0';

	return m;

}



int main() {
	struct Masina m;
	m = initializare(1, "BMW", 100.5, 'A');
	afisare(m);

	struct Masina* vectorMasini;
	int nrMasini = 3;
	vectorMasini = malloc(sizeof(struct Masina) * nrMasini);
	vectorMasini[0] = initializare(2, "Mercedes", 2.2, 'C');
	vectorMasini[1] = initializare(3, "Audi", 7.2, 'S');
	vectorMasini[2] = initializare(4, "Dacia", 8.2, 'L');

	afisareVector(vectorMasini, nrMasini);

	struct Masina* vectorMasiniCopiate;
	vectorMasiniCopiate = NULL;
	int nrMasiniCopiate = 2;

	printf("\nMASINI COPIATE\n");
	vectorMasiniCopiate = copiazaPrimeleNElemente(vectorMasini, nrMasini, nrMasiniCopiate);
	afisareVector(vectorMasiniCopiate, nrMasiniCopiate);

	dezalocare(&vectorMasiniCopiate, &nrMasiniCopiate);


	printf("\n COPIAZA MASINI USOARE\n");

	copiazaMasiniCuTonajMic(vectorMasini, nrMasini, 5, &vectorMasiniCopiate, &nrMasiniCopiate);
	afisareVector(vectorMasiniCopiate, nrMasiniCopiate);
	dezalocare(&vectorMasiniCopiate, &nrMasiniCopiate);


	printf("\nCAUTARE MASINA DUPA MODEL\n");
	struct Masina masinaGasita = getPrimaMasinaDupaModel(vectorMasini, nrMasini, "Audi");
	afisare(masinaGasita);
	free(masinaGasita.model);

	printf("\n");
	struct Masina masinaGasita_ = getPrimaMasinaDupaModel(vectorMasini, nrMasini, "Toyota");
	afisare(masinaGasita_);
	free(masinaGasita_.model);
	return 0;
}