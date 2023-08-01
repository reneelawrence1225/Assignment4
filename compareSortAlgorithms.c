#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int array[], int h, int i, int r)
{
	int s, j, k;

	int t1 = i - h + 1;
	int t2 = r - i;

	int L[t1], R[t1];

	for(s = 0; s < t1; s++){
		L[s] = array[h + s];
	}

	for(j = 0; j < t2; j++){
		R[j] = array[i + 1 + j];
	}

	s = 0;
	j = 0;
	k = h;

	while(s < t1 && j < t2){
		if(L[s] <= R[j]){
			array[k] = L[s];
			s++;
		}
		else{
			array[k] = R[j];
			j++;
		}
		k++;
	}

	while(s < t1){
		array[k] = L[s];
		s++;
		k++;
	}

	while(j < t2){
		array[k] = R[j];
		j++;
		k++;
	}


}

void mergeSort(int pData[], int l, int r)
{
	if(l < r){
		//get the mid point
		int m = l + (l + r) / 2;

		//sorting
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);

		merge(pData, l, m, r);

	}
}
//end of merge sort

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int r, l, cle;

	for(r = 1; r < n; r++){
		cle = pData[r];
		l = r - 1;

		while(l >= 0 && pData[l] > cle){
			pData[l + 1] = pData[l];
			l = l - 1;
		}
		pData[l + 1] = cle;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int r, l;
	for(r = 0; r < n - 1; r++){
		for(l = 0; l < n - r - 1; l){
			if(pData[l] > pData[l + 1]){
				int t = pData[l];
				pData[l] = pData[l + 1];
				pData[l + 1] = t;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int r, l, min;

	for(r = 0; r < n - 1; r++){
		min = r;
		for(l = r + 1; l < n; l++){
			if(pData[l] < pData[min]){
				min = l;
			}
		}
		int t = pData[min];
		pData[min] = pData[r];
		pData[r] = t;
	}

}
//end of selection sort

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		
		// Implement parse data block
		if(*ppData){
			for(int i = 0; i < dataSz; i++){
				fscanf(inFile, "%d\n", &((*ppData)[i]));
			}
		}

	}
	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}