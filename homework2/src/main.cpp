#include <iostream>
#include <algorithm>
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
private:
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;
public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }

    // 複製建構子 (深複製，避免動態陣列指標出問題)
    Polynomial(const Polynomial& other) {
        capacity = other.capacity;
        terms = other.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termArray[i] = other.termArray[i];
        }
    }

    // 解構子
    ~Polynomial() {
        delete[] termArray;
    }

    // 指定運算子多載
    Polynomial& operator=(const Polynomial& other) {
        if (this == &other) return *this;
        delete[] termArray;
        capacity = other.capacity;
        terms = other.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termArray[i] = other.termArray[i];
        }
        return *this;
    }

    void newTerm(const float theCoef, const int theExp);
    Polynomial Add(const Polynomial& b);
    Polynomial Mult(const Polynomial& b);
    float Eval(float x);
    void Input();
    void Output();
};

void Polynomial::newTerm(const float theCoef, const int theExp) {
    if (theCoef == 0) return;
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoef;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Add(const Polynomial& b) {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t != 0) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos < terms; aPos++)
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    
    return c;
}

// 多項式乘法範本
Polynomial Polynomial::Mult(const Polynomial& b) {
    Polynomial c;
    // 提示：可雙層迴圈將各項相乘，再利用 newTerm 或相加整合
    return c;
}

// 代入 x 計算數值
float Polynomial::Eval(float x) {
    float result = 0;
    // 提示：遍歷 termArray 計算 coef * (x^exp) 的總和
    return result;
}

// 輸入介面
void Polynomial::Input() {
    terms = 0; // 重置
    int n;
    cout << "請輸入多項式的非零項數量: ";
    cin >> n;
    cout << "請依指數從大到小輸入各項的 (係數 指數):\n";
    for (int i = 0; i < n; i++) {
        float c;
        int e;
        cin >> c >> e;
        newTerm(c, e);
    }
}

// 輸出介面
void Polynomial::Output() {
    if (terms == 0) {
        cout << "0" << endl;
        return;
    }
    for (int i = 0; i < terms; i++) {
        cout << termArray[i].coef << "x^" << termArray[i].exp;
        if (i < terms - 1 && termArray[i + 1].coef > 0) cout << " + ";
    }
    cout << endl;
}

int main() {
    Polynomial p1, p2, p3;
    int choice;
    do {
        cout << "\n===== 多項式運算系統 =====\n";
        cout << "1. 輸入多項式 P1 與 P2\n";
        cout << "2. 執行多項式加法 (P1 + P2)\n";
        cout << "3. 執行多項式乘法 (P1 * P2)\n";
        cout << "4. 代入 x 計算 P1 數值\n";
        cout << "0. 離開\n";
        cout << "請選擇功能: ";
        cin >> choice;

        switch (choice) {
        cout << "--- 輸入第一個多項式 ---\n";
            case 1:
                cout << "--- 輸入第一個多項式 (P1) ---\n";
                p1.Input();
                cout << "--- 輸入第二個多項式 (P2) ---\n";
                p2.Input();
                break;
            case 2:
                p3 = p1.Add(p2);
                cout << "相加結果: ";
                p3.Output();
                break;
            case 3:
                p3 = p1.Mult(p2);
                cout << "相乘結果: ";
                p3.Output();
                break;
            case 4: {
                float x;
                cout << "請輸入 x 的值: ";
                cin >> x;
                cout << "代入結果: " << p1.Eval(x) << endl;
                break;
            }
            case 0:
                cout << "離開程式。\n";
                break;
            default:
                cout << "選項錯誤，請重新輸入。\n";
        }
    } while (choice != 0);

    return 0;
}
