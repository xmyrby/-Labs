#ifndef DYNARRAY_H
#define DYNARRAY_H
// Прототипы своих функций
void PrintArray(double** p);
double** ConstructArray(int m, int* n);
void DestructArray(double** p);
void HandsArray(int& m, int n[100]);
struct Numbersforfile
{
	double numb[100];
};
void inputfile(int& m, int n[100], Numbersforfile* s);
double** ConstructArrayfile(int m, int* n, Numbersforfile* s);
void outputfile(double** p, int const m);
void inputfilebin(int& m, int n[100], Numbersforfile* s);
void outputfilebin(double** p, int const m);
#endif

