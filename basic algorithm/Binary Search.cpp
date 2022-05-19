int l = 0, r = n;
while (l < r) {
    int mid = l + r >> 1;
    if (check(mid)) {
        l = mid + 1;
    } else {
        r = mid;
    }
}

int l = 0, r = n;
while (l < r) {
    int mid = l + r + 1 >> 1;
    if (check(mid)) {
        l = mid;
    } else {
        r = mid - 1;
    }
}
