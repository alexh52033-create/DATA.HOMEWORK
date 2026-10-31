#include <iostream>
#include <algorithm>
using namespace std;

class Polynomial;

class Term
{
    friend Polynomial;
private:
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial
{
private:
    Term* termArray; // 存係數指數
    int capacity;    // 容量
    int terms;       // 有幾項
public:
    Polynomial() : capacity(2), terms(0)
    {
        termArray = new Term[capacity];
    }

    // 複製建構子
    Polynomial(const Polynomial& other) {
        capacity = other.capacity;
        terms = other.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termArray[i] = other.termArray[i];
        }
    }

    // 解構子 (釋放動態記憶體)
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

// 新增一項 若容量滿了就把容量加備空間
void Polynomial::newTerm(const float theCoef, const int theExp)
{
    if (theCoef == 0) return;
    if (terms == capacity)
    {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoef;
    termArray[terms++].exp = theExp;
}

// 多項式加法 (用雙指標來比對指數大小)
Polynomial Polynomial::Add(const Polynomial& b)
{
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms))
    {
        if (termArray[aPos].exp == b.termArray[bPos].exp)
        {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t != 0) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp)
        {
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else
        {
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

// 多項式乘法(用雙層迴圈相乘然後相加)
Polynomial Polynomial::Mult(const Polynomial& b) {
    Polynomial c;
    for (int i = 0; i < terms; i++) {
        Polynomial temp;
        for (int j = 0; j < b.terms; j++) {
            float newCoef = termArray[i].coef * b.termArray[j].coef;
            int newExp = termArray[i].exp + b.termArray[j].exp;
            temp.newTerm(newCoef, newExp);
        }
        c = c.Add(temp);
    }
    return c;
}

// 把x丟進去計算
float Polynomial::Eval(float x) {
    float total = 0;
    for (int i = 0; i < terms; i++) {
        float p = 1;
        for (int j = 0; j < termArray[i].exp; j++) {
            p *= x;
        }
        total += termArray[i].coef * p;
    }
    return total;
}

// 輸入用函式
void Polynomial::Input() {
    terms = 0;
    int n;
    cout << "請輸入非零項數量: ";
    cin >> n;
    cout << "請依指數從大到小輸入(係數 指數):\n";
    for (int i = 0; i < n; i++) {
        float coef;
        int exp;
        cin >> coef >> exp;
        newTerm(coef, exp);
    }
}

// 輸出用函式
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

int main()
{
    Polynomial p1, p2, p3;
    int choice;

    cout << "多項式運算系統\n";
    cout << "1. 多項式加法\n";
    cout << "2. 多項式乘法\n";
    cout << "3. 代入x計算 P1 數值\n";
    cout << "請選擇功能: ";
    cin >> choice;

    if (choice == 1 || choice == 2) {
        cout << "\n請輸入第一個多項式(P1)\n";
        p1.Input();
        cout << "\n請輸入第二個多項式(P2)\n";
        p2.Input();

        if (choice == 1) {
            p3 = p1.Add(p2);
            cout << "相加結果: ";
            p3.Output();
        }
        else {
            p3 = p1.Mult(p2);
            cout << "相乘結果: ";
            p3.Output();
        }
    }
    else if (choice == 3) {
        cout << "\n請輸入多項式 (P1)\n";
        p1.Input();
        float x;
        cout << "請輸入 x 的值: ";
        cin >> x;
        cout << "計算結果: " << p1.Eval(x) << endl;
    }

    return 0;
}