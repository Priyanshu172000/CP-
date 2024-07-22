#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
void build(int a[], int seg[], int i, int lo, int hi)
{
    if (lo == hi)
    {
        seg[i] = a[lo];
        return;
    }
    int mid = (lo + hi) / 2;
    build(a, seg, 2 * i + 1, lo, mid);
    build(a, seg, 2 * i + 2, mid + 1, hi);
    seg[i] = min(seg[2 * i + 1], seg[2 * i + 2]);
}
void update(int seg[], int i, int lo, int hi, int k, int v)
{
    if (lo == hi && lo == k)
    {
        seg[i] = v;
        return;
    }
    if (k < lo || k > hi)
        return;
    int mid = (lo + hi) / 2;
    update(seg, 2 * i + 1, lo, mid, k, v);
    update(seg, 2 * i + 2, mid + 1, hi, k, v);
    seg[i] = min(seg[2 * i + 1], seg[2 * i + 2]);
}
int query(int seg[], int i, int lo, int hi, int l, int r)
{
    if (l <= lo && r >= hi)
        return seg[i];
    if (r < lo || l > hi)
        return INT_MAX;
    int mid = (lo + hi) / 2;
    int left = query(seg, 2 * i + 1, lo, mid, l, r);
    int right = query(seg, 2 * i + 2, mid + 1, hi, l, r);
    return min(left, right);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int seg[4 * n];
    build(a, seg, 0, 0, n - 1);

    while (q--)
    {
        int x, l, r;
        cin >> x >> l >> r;
        if (x == 1)
        {
            update(seg, 0, 0, n - 1, l - 1, r);
        }
        else
        {

            l--;
            r--;
            cout << query(seg, 0, 0, n - 1, l, r) << endl;
        }
    }

    return 0;
}
