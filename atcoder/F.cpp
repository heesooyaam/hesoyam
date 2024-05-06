#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ss second
#define ff first
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'
using namespace std;

// Функция для выполнения Гауссова исключения
void gaussianElimination(vector<vector<int>>& mat) {
    int n = mat.size();

    for (int i = 0; i < n; i++) {
        // Поиск максимума в текущем столбце
        int maxEl = abs(mat[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(mat[k][i]) > maxEl) {
                maxEl = abs(mat[k][i]);
                maxRow = k;
            }
        }

        // Перестановка максимальной строки с текущей
        for (int k = i; k < n + 1; k++) {
            swap(mat[maxRow][k], mat[i][k]);
        }

        // Обнуление всех элементов ниже i-го элемента в i-м столбце
        for (int k = i + 1; k < n; k++) {
            int c = -mat[k][i] / mat[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j) {
                    mat[k][j] = 0;
                } else {
                    mat[k][j] += c * mat[i][j];
                }
            }
        }
    }
}

// Функция обратной подстановки
vector<int> backSubstitution(vector<vector<int>>& mat) {
    int n = mat.size();
    vector<int> x(n, -1); // Инициализация всех переменных значением -1

    for (int i = n - 1; i >= 0; i--) {
        if (mat[i][i] != 0) { // Проверка на ненулевой пивот
            x[i] = mat[i][n] / mat[i][i];
            for (int k = i - 1; k >= 0; k--) {
                mat[k][n] -= mat[k][i] * x[i];
            }
        }
    }
    return x;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(n + 1));

//    cout << "Enter augmented matrix (coefficients and constants):" << endl;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        mat[i][a - 1] = 1;
        mat[i][b - 1] = 1;
        mat[i].back() = c;
    }

    gaussianElimination(mat);
    vector<int> solution = backSubstitution(mat);

    cout << "Solution:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i << " = " << solution[i] << endl;
    }

    return 0;
}