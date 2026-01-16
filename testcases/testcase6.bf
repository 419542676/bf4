int square(int n) {
    return n * n;
}

int cube(int n) {
    return n * square(n);
}

int main() {
    int result = cube(3);
    return result;
}