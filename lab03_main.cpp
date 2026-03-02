#include <bits/stdc++.h>
using namespace std;

struct Frame {
    int n;
    int from, to, aux;
    int stage; // 0 = before first call, 1 = after first call (do move), 2 = after second call
};

// Recursive: simulate moves without I/O; counts moves.
static void hanoi_recursive(int n, int from, int to, int aux, unsigned long long &moves) {
    if (n <= 0) return;
    hanoi_recursive(n-1, from, aux, to, moves);
    moves++; // move largest disk
    hanoi_recursive(n-1, aux, to, from, moves);
}

// Iterative: explicit stack simulating recursion; counts moves.
static void hanoi_iterative(int n, int from, int to, int aux, unsigned long long &moves) {
    vector<Frame> st;
    st.push_back({n, from, to, aux, 0});
    while (!st.empty()) {
        Frame &f = st.back();
        if (f.n <= 0) {
            st.pop_back();
            continue;
        }
        if (f.stage == 0) {
            // first recursive call: (n-1, from -> aux)
            f.stage = 1;
            st.push_back({f.n - 1, f.from, f.aux, f.to, 0});
        } else if (f.stage == 1) {
            // do the move
            moves++;
            f.stage = 2;
            // second recursive call: (n-1, aux -> to)
            st.push_back({f.n - 1, f.aux, f.to, f.from, 0});
        } else {
            st.pop_back();
        }
    }
}

// Print actual move list (for small n) using recursion.
static void hanoi_recursive_print(int n, int from, int to, int aux) {
    if (n <= 0) return;
    hanoi_recursive_print(n-1, from, aux, to);
    cout << "Move disk " << n << " from peg " << from << " to peg " << to << "\n";
    hanoi_recursive_print(n-1, aux, to, from);
}

class LCG {
public:
    using u64 = uint64_t;
    LCG(u64 seed, u64 a, u64 c, u64 m) : state(seed), a(a), c(c), m(m) {}

    u64 next() {
        state = (a * state + c) % m;
        return state;
    }

    // normalized in [0,1)
    double next01() {
        return static_cast<double>(next()) / static_cast<double>(m);
    }

private:
    u64 state;
    u64 a, c, m;
};

static double seconds_now() {
    using clock = chrono::high_resolution_clock;
    return chrono::duration<double>(clock::now().time_since_epoch()).count();
}

template <class Fn>
static double time_seconds(Fn fn, int repeats=5) {
    // warmup
    fn();
    double best = 1e100;
    for (int i=0;i<repeats;i++) {
        auto t0 = chrono::high_resolution_clock::now();
        fn();
        auto t1 = chrono::high_resolution_clock::now();
        double dt = chrono::duration<double>(t1-t0).count();
        best = min(best, dt);
    }
    return best;
}

static void run_hanoi_benchmark() {
    cout << "=== Towers of Hanoi: empirical time (no printing) ===\n";
    cout << "n,moves_rec,moves_it,time_rec_s,time_it_s\n";

    for (int n=1; n<=25; n++) {
        unsigned long long mr=0, mi=0;

        auto tr = time_seconds([&](){ mr=0; hanoi_recursive(n,1,3,2,mr); });
        auto ti = time_seconds([&](){ mi=0; hanoi_iterative(n,1,3,2,mi); });

        cout << n << "," << mr << "," << mi << "," << fixed << setprecision(9)
             << tr << "," << ti << "\n";

        // Safety: if it gets too slow, stop
        if (tr > 2.0 || ti > 2.0) break;
    }
}

static void run_lcg_benchmark() {
    cout << "\n=== Linear Congruential Generator (LCG): empirical analysis ===\n";
    // Common parameters (Numerical Recipes):
    // X_{k+1} = (1664525*X_k + 1013904223) mod 2^32
    const uint64_t a = 1664525ULL;
    const uint64_t c = 1013904223ULL;
    const uint64_t m = 4294967296ULL; // 2^32

    vector<size_t> Ns = {1000, 10000, 100000, 1000000, 5000000};

    cout << "N,time_s,mean_0_1,chi2_10bins\n";

    for (size_t N : Ns) {
        LCG gen(123456789ULL, a, c, m);

        double mean = 0.0;
        const int B = 10;
        array<size_t, B> bins{};
        bins.fill(0);

        auto t = time_seconds([&](){
            LCG g2(123456789ULL, a, c, m);
            double s = 0.0;
            array<size_t, B> b2{}; b2.fill(0);
            for (size_t i=0;i<N;i++) {
                double u = g2.next01();
                s += u;
                int idx = min(B-1, (int)(u * B));
                b2[idx]++;
            }
            mean = s / (double)N;
            bins = b2;
        });

        // Chi-square vs uniform with B bins (expected N/B each)
        double expected = (double)N / B;
        double chi2 = 0.0;
        for (int i=0;i<B;i++) {
            double diff = (double)bins[i] - expected;
            chi2 += diff*diff/expected;
        }

        cout << N << "," << fixed << setprecision(9) << t << "," << setprecision(6)
             << mean << "," << setprecision(3) << chi2 << "\n";
    }

    cout << "\n(Interpretation) Mean should be ~0.5 for a decent uniform generator; chi2 should be in a reasonable range for 10 bins (not extreme).\n";
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc >= 2 && string(argv[1]) == "print") {
        int n = (argc >= 3) ? stoi(argv[2]) : 3;
        cout << "Printing moves for n=" << n << " (recursive):\n";
        hanoi_recursive_print(n, 1, 3, 2);
        return 0;
    }

    run_hanoi_benchmark();
    run_lcg_benchmark();
    return 0;
}
