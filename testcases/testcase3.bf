int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int i = 0;
    while (i < 3) {
        i = i+1;
        arr[3] = arr[3] + 1;
    }
    return arr[3];
}
