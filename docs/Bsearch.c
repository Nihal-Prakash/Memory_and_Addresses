#include <stdio.h>
#include <stdlib.h>

#define FAILURE -1; 

int binsearch(int sorrted_array[],int left, int right, int findMe) {
    if(left > right) {
        return FAILURE;
    }

    int mid = (left + right) / 2;
    if(findMe == sorrted_array[mid]) {
        return mid;
    }else if(findMe < sorrted_array[mid]) {
        return binsearch(sorrted_array, left, mid - 1, findMe);
    } else {
        return binsearch(sorrted_array, mid + 1, right, findMe);
    }
}

int main(void) {
    int data[] = {1,2,3,4,5,6,7,8,9,10,11};
    int index = binsearch(data,0,10,4);
    printf(" %d\n", index);
    return 0;
}