void matrix_multiplication(int *a, int *b, int *output, int i, int k, int j) {
    for (int x = 0; x < i; x += 2) {
        for (int y = 0; y < j; y += 2) {
            int acc00 = 0, acc01 = 0, acc10 = 0, acc11 = 0;
            for (int z = 0; z < k; z++) {
                acc00 += a[x * k + z] * b[z * j + y];
                acc01 += a[x * k + z] * b[z * j + y + 1];
                acc10 += a[(x + 1) * k + z] * b[z * j + y];
                acc11 += a[(x + 1) * k + z] * b[z * j + y + 1];
            }
            output[x * j + y] = acc00;
            output[x * j + y + 1] = acc01;
            output[(x + 1) * j + y] = acc10;
            output[(x + 1) * j + y + 1] = acc11;
        }
    }
}

