//#include<stdio.h>
//#include<malloc.h>
//#include <stdlib.h>
//#include <string.h>
////Ignat Ramona - Inventar
//
//struct Inventar {
//	int cod;
//	char* denumireProdus;
//	int nrProduse;
//	float* preturi;
//};
//
//struct Inventar citireInventar()
//{
//	struct Inventar inv;
//	printf("Introduceti codul: ");
//	scanf_s("%d", &inv.cod);
//
//	char buffer[100];
//	printf("Introduceti denumirea produsului: ");
//	scanf_s(" %[^\n]", buffer, (unsigned int)sizeof(buffer));
//
//	inv.denumireProdus = malloc(sizeof(char) * (strlen(buffer) + 1));
//	strcpy_s(inv.denumireProdus, (strlen(buffer) + 1), buffer);
//
//	printf("Introduceti numarul de produse: ");
//	scanf_s("%d", &inv.nrProduse);
//
//	inv.preturi = malloc(sizeof(float) * inv.nrProduse);
//	for (int i = 0; i < inv.nrProduse; i++)
//	{
//		printf("Introduceti pretul produsului %d: ", i + 1);
//		scanf_s("%f", &inv.preturi[i]);
//	}
//
//	return inv;
//}
//
//
//float calculMediePreturi(struct Inventar inv)
//{
//	float suma = 0;
//	for (int i = 0; i < inv.nrProduse; i++)
//	{
//		suma += inv.preturi[i];
//	}
//	return suma / inv.nrProduse;
//}
//
//void modificareNumarProduse(struct Inventar* inv, int _nrProduse)
//{
//	inv->nrProduse = _nrProduse;
//	inv->preturi = realloc(inv->preturi, sizeof(float) * _nrProduse);
//	printf("Noul numar de produse este: %d", inv->nrProduse);
//}
//
//void afisareInventar(struct Inventar inv)
//{
//	printf("\nInventar:\n");
//	printf("Cod: %d\n", inv.cod);
//	printf("Denumire produs: %s\n", inv.denumireProdus);
//	printf("Numar produse: %d\n", inv.nrProduse);
//	printf("Preturi:");
//	for (int i = 0; i < inv.nrProduse; i++)
//	{
//		printf("%.2f ", inv.preturi[i]);
//	}
//	printf("\n");
//}
//
//void afisareVectorInventar(struct Inventar* vector, int dim)
//{
//	for (int i = 0; i < dim; i++)
//	{
//		afisareInventar(vector[i]);
//	}
//}
//
////Functie care creeaza un nou vector cu obiectele ce au mai mult de 5 produse
//struct Inventar* filtrareProduseDinInv(struct Inventar* vector, int dim, int* dimNoua)
//{
//	struct Inventar* inventar = malloc(sizeof(struct Inventar) * dim);
//	*dimNoua = 0;
//	for (int i = 0; i < dim; i++)
//	{
//		if (vector[i].nrProduse > 5)
//		{
//			inventar[*dimNoua] = vector[i];
//			(*dimNoua)++;
//		}
//		
//	}
//	return inventar;
//}
//
////functie care muta intr-un nou vector obiectele cu pretul mediu > 20
//struct Inventar* mutaPreturiMari(struct Inventar* vector, int* dim, int* dimNoua)
//{
//	struct Inventar* inventar = malloc(sizeof(struct Inventar) * (*dim));
//	*dimNoua = 0;
//	for (int i = 0; i < *dim; i++)
//	{
//		float suma = 0;
//		for (int j = 0; j < vector[i].nrProduse; i++)
//		{
//			suma += vector[i].preturi[j];
//		}
//		
//		float medie = suma / vector[i].nrProduse;
//
//		if (medie > 20)
//		{
//			inventar[*dimNoua] = vector[i];
//			(*dimNoua)++;
//		}
//	}
//
//}
//
////functie care concateneaza doi vectori
//struct Inventar* concateneazaVectori(struct Inventar* v1, int dim1, struct Inventar* v2, int dim2, int* dimNoua)
//{
//	*dimNoua = dim1 + dim2;
//	struct Inventar* inventar = malloc(sizeof(struct Inventar) * (*dimNoua));
//
//	for (int i = 0; i < dim1; i++)
//	{
//		inventar[i] = v1[i];
//	}
//	for (int i = 0; i < dim2; i++)
//	{
//		inventar[i] = v2[i];
//	}
//
//	return inventar;
//}
//
//void dezalocare(struct Inventar** vector, int* nrElemente) {
//	for (int i = 0; i < *nrElemente; i++)
//	{
//		free((*vector)[i].denumireProdus);
//		free((*vector)[i].preturi);
//	}
//
//	free(*vector);
//	*vector = NULL;
//	*nrElemente = 0;
//}
//int main()
//{
//	struct Inventar inv = citireInventar();
//	afisareInventar(inv);
//
//	printf("\nMedia preturilor este: %.2f", calculMediePreturi(inv));
//
//	int nrNou;
//	printf("\nIntroduceti noul numar de produse: ");
//	scanf_s("%d", &nrNou);
//	modificareNumarProduse(&inv, nrNou);
//
//	afisareInventar(inv);
//
//	//vector alocat dinamic de cel putin 5 obiecte 
//
//	int dim = 5;
//	struct Inventar* vector;
//	vector = malloc(sizeof(struct Inventar) * dim);
//
//	printf("Introduceti %d inventare: \n", dim);
//	for (int i = 0; i < dim; i++)
//	{
//		vector[i] = citireInventar();
//		printf("\n");
//	}
//
//	printf("\nVectorul initial: \n");
//	afisareVectorInventar(vector, dim);
//
//
//	int dimNoua;
//	struct Inventar* vectorFiltrat = filtrareProduseDinInv(vector, dim, &dimNoua);
//	printf("\nVector cu produse > 5: \n");
//	afisareVectorInventar(vectorFiltrat, dimNoua);
//
//
//	int dimMutare;
//	struct Inventar* vectorInvMutate = mutaPreturiMari(vector, &dim, &dimMutare);
//	printf("\nVector cu produse ramase dupa mutare: \n");
//	afisareVectorInventar(vector, dim);
//
//	printf("\nVector cu produse mutate (medie pret > 20): \n");
//	afisareVectorInventar(vector, dimMutare);
//
//
//	int dimConcat;
//	struct Inventar* vectorConcatenat = concateneazaVectori(vector, dim, vectorInvMutate, dimMutare, &dimConcat);
//	printf("\nVector concatenat: \n");
//	afisareVectorInventar(vectorConcatenat, dimConcat);
//
//	// Eliberare memorie
//	dezalocare(&vector, &dim);
//	dezalocare(&vectorFiltrat, &dimNoua);
//	dezalocare(&vectorInvMutate, &dimMutare);
//	dezalocare(&vectorConcatenat, &dimConcat);
//
//	return 0;
//}