# 41443144 黃學宏

作業二：多項式運算系統

---

## 1. 解題說明

### 問題描述
寫一個多項式(Polynomial)運算系統，系統要可以多項式的加法、乘法以及代入變數 $x$ 計算數值，並妥善管理動態記憶體。

### 解題策略
1. 建立 Term 類別來儲存係數與指數，並在 Polynomial 類別中使用動態陣列來存放所有的非零項。
2. 當陣列空間滿時，自動將容量加倍，配置新記憶體並複製舊資料，避免記憶體溢位。
3. 運算邏輯：
   * 加法：用雙指標掃描兩個多項式，然後看指數大小進行對應的係數相加或合併。
   * 乘法：透過雙層迴圈將各項相乘產生暫存多項式，再逐步呼叫加法功能將結果合併。
## 2. 程式實作

以下為主要程式碼:

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial {
private:
    Term* termArray; // 動態陣列儲存非零項
    int capacity;    // 容量
    int terms;       // 有幾項
public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }
    
    // 新增非零的係數指數，然後記憶體滿的時候增加記憶體容量
    void newTerm(const float theCoef, const int theExp) {
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

    // 多項式加法
    Polynomial Add(const Polynomial& b) {
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
        for (; aPos < terms; aPos++) c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
        for (; bPos < b.terms; bPos++) c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
        return c;
    }

    // 多項式乘法
    Polynomial Mult(const Polynomial& b) {
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
};

int main() {
    Polynomial p1, p2, p3;
    // 呼叫程式的邏輯 跟互動選單
    return 0;
}
```
## 3. 效能分析與檢討

1. **時間複雜度**：
    **加法**：$O(M + N)$，利用雙指標線性掃描兩個多項式的非零項。
   
    **乘法**：$O(M \times N)$，透過雙層迴圈將各項相乘後再逐步合併。
   
    **求值**：$O(N \times k)$，依據各項指數進行 $x$ 的乘法計算。

3. **空間複雜度**：
   * $O(N)$。利用動態陣列只儲存非零項，並透過 `capacity *= 2` 的倍增擴容機制來管理記憶體。

4. **效能檢討與優化方向**：
   * **初期頻繁擴容的問題**：程式中 `Polynomial` 的初始容量設為 `2`。如果輸入的非零項較多，在剛開始輸入時就會一直觸發容量不足，導致頻繁進行 `capacity *= 2`、配置新記憶體與資料複製（`copy`）。**優化方案**：未來可以把初始容量設大一點（例如 10 或 20），減少初期記憶體搬移的次數。
   * **乘法中的記憶體開銷**：在 `Mult` 乘法函式中，因為使用迴圈不斷疊加，每次相加都會重新 `new` 與 `delete` 動態陣列。**優化方案**：可以改用「先用暫存空間把所有相乘的項收集起來，最後再一次排序合併」的方式，避免在迴圈中頻繁配置記憶體。
