#ifndef __RAGER_H__
#define __RAGER_H__

#include<iostream>
struct RaggedArray
{
	int** data;
	int rows;
};

int AskSize();

void CreateArraySelf(RaggedArray& mas);

void FillArray(RaggedArray& mas);

void PrintArray(RaggedArray mas);

void SaveTxt(RaggedArray mas);

void ReadTxt(RaggedArray& mas);

void SaveBin(RaggedArray& mas);

void ReadBin(RaggedArray& mas);

void FreeMas(RaggedArray& mas);

void Switcher(RaggedArray& mas);

#endif