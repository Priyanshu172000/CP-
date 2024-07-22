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
    seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
}
void update(int seg[], int lazy[], int i, int lo, int hi, int l, int r, int v)
{
    if (lazy[i])
    {
        seg[i] += (hi - lo + 1) * lazy[i];
        if (lo != hi)
        {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        lazy[i] = 0;
    }
    if (hi < l || lo > r || lo > hi)
        return;
    if (lo >= l && hi <= r)
    {
        seg[i] += (hi - lo + 1) * v;
        if (lo != hi)
        {
            lazy[2 * i + 1] += v;
            lazy[2 * i + 2] += v;
        }
        return;
    }
    int mid = (lo + hi) / 2;
    update(seg, lazy, 2 * i + 1, lo, mid, l, r, v);
    update(seg, lazy, 2 * i + 2, mid + 1, hi, l, r, v);
    seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
}
int query(int seg[], int lazy[], int i, int lo, int hi, int l)
{
    if (lazy[i])
    {
        seg[i] += (hi - lo + 1) * lazy[i];
        if (lo != hi)
        {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        lazy[i] = 0;
    }
    if (hi < l || lo > l)
        return 0;
    if (lo == hi && lo == l)
    {
        return seg[i];
    }
    int mid = (lo + hi) / 2;
    int left = query(seg, lazy, 2 * i + 1, lo, mid, l);
    int right = query(seg, lazy, 2 * i + 2, mid + 1, hi, l);
    return left + right;
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
    int lazy[4 * n];
    for (int i = 0; i < 4 * n; i++)
        lazy[i] = 0;

    while (q--)
    {
        int k, l, r, v;
        cin >> k >> l;

        if (k == 1)
        {
            cin >> r >> v;
            update(seg, lazy, 0, 0, n - 1, --l, --r, v);
        }
        else
        {
            cout << query(seg, lazy, 0, 0, n - 1, --l) << endl;
        }
    }
    return 0;
}
