int doWork() {
    int count = 0;
    while (count < 5) {
        count = count + 1;
    }
    return count;
}

int main() {
    int sum = doWork();
    return sum;
}
