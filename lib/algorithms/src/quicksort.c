void swap(int *a, int *b) {
  int t = *a;

  *a = *b;
  *b = t;
}

int partition(int *arr, int si, int len) {
  int p = arr[len - 1];
  int i = (si - 1);

  for (int j = si; j < len - 1; j++) {
    if (arr[j] < p) {
      i++;

      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[len - 1]);

  return (i + 1);
}

void quicksort(int *arr, int i, int len) {
  if (i >= len) {
    return;
  }

  int pi = partition(arr, i, len);

  quicksort(arr, i, pi);
  quicksort(arr, pi + 1, len);
}
