#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
struct file {
	int id;
	int size;
	int pendrive;
};
void replace(file* var1, file* var2) {
	file tmp = *var1;
	*var1 = *var2;
	*var2 = tmp;
}
int part(file* array, int start, int end, int variation) {
	int pivot;
	if (variation == 0)
		pivot = array[end].size;
	else
		pivot = array[end].id;
	int index = start;
	for (int i = start; i < end; i++) {
		switch (variation)
		{
		case 0:
			if (array[i].size <= pivot) {
				replace(&array[i], &array[index]);
				index++;
			}break;
		case 1:
			if (array[i].id >= pivot) {
				replace(&array[i], &array[index]);
				index++;
			}break;
		}
	}
	replace(&array[index], &array[end]);
	return index;
}
void quicksort(file* array, int start, int end, bool variation) {
	if (start < end) {
		int index = part(array, start, end, variation);
		quicksort(array, start, index - 1, variation);
		quicksort(array, index + 1, end, variation);
	}
}
int copy_to_pendrive(file* array, int size, int space) {
	int pendriveID = 0;
	int freeSpace = space;
	int filesUploaded = 0;
	for (int i = 0; i < size; i++) {
		if (array[i].size <= freeSpace) {
			array[i].pendrive = pendriveID;
			filesUploaded++;
			freeSpace -= array[i].size;
		}
		else {
			pendriveID++;
			freeSpace = space;
			i--;
		}
		if (pendriveID > 1) break;
	}
	return filesUploaded;
}
int main() {
	int n, p;
	scanf("%d %d", &n, &p);
	file* files = new file[n];
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &files[i].id, &files[i].size);
	}
	quicksort(files, 0, n-1, 0);
	int filesUploaded = copy_to_pendrive(files, n, p);
	quicksort(files, 0, n - 1, 1);
	printf("%d\n", filesUploaded);
	for (int i = 0; i < 2; i++) {
		printf("%d: ", i+1);
		for (int j = 0; j < n; j++) {
			if (files[j].pendrive == i)
				printf("%d ", files[j].id);
		}
		printf("\n");
	}
}