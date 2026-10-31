# 41443144

作業二：多項式運算系統

---

##  解題說明

### 問題描述
寫一個多項式(Polynomial)運算系統，系統要可以多項式的加法、乘法以及代入變數 $x$ 計算數值，並妥善管理動態記憶體。

### 解題策略
1. 建立 Term 類別來儲存係數與指數，並在 Polynomial 類別中使用動態陣列來存放所有的非零項。
2. 當陣列空間滿時，自動將容量加倍，配置新記憶體並複製舊資料，避免記憶體溢位。
3. 運算邏輯：
   
   加法：用雙指標掃描兩個多項式，然後看指數大小進行對應的係數相加或合併。
   
   乘法：透過雙層迴圈將各項相乘產生暫存多項式，再逐步呼叫加法功能將結果合併。
##  程式實作

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
##  效能分析

1. **時間複雜度**：

    **加法**： $O(M + N)$ ，利用雙指標線性掃描兩個多項式的非零項。
   
    **乘法**： $O(M \times N)$ ，透過雙層迴圈將各項相乘後再逐步合併。
   
    **求值**： $O(N \times k)$(（ $k$ 是 $N$ 的指數大小）) ，依據各項指數進行 $x$ 的乘法計算。

3. **空間複雜度**： $O(N)$。利用動態陣列只儲存非零項，並透過capacity *= 2 滿了乘二空間來管理記憶體。

4. **效能檢討與優化方向**：

   **問題**：程式中Polynomial的一開始容量設為2。如果輸入的非零項較多，在剛開始輸入時就會一直觸發容量不足，導致頻繁進行 capacity *= 2 ，浪費記憶體空間。
   
   **優化方案**：一開始把初始容量設大一點，這樣就可以減少初期記憶體搬移的次數。

##  測試與驗證


```shell
$ g++ main.cpp --std=c++21 -o main.exe
$ .\main.exe

多項式運算系統
1. 多項式加法
2. 多項式乘法
3. 代入 x 計算數值
//測試一 多項式加法
請選擇功能: 1

 輸入第一個多項式 (P1) 
請輸入非零項數量: 2
請依指數從大到小輸入 (係數 指數):
3 2
5 0

輸入第二個多項式 (P2) 
請輸入非零項數量: 2
請依指數從大到小輸入 (係數 指數):
2 2
1 1
相加結果:5x^2 + 1x^1 + 5x^0

//測試二 多項式乘法
請選擇功能: 2

請輸入第一個多項式 (P1)
請輸入非零項數量: 1
請依指數從大到小輸入 (係數 指數):
2 1

請輸入第二個多項式 (P2)
請輸入非零項數量: 1
請依指數從大到小輸入 (係數 指數):
3 2
相乘結果: 6x^3

//測試三 代入X計算數值
請選擇功能: 3

請輸入多項式 (P1)
請輸入非零項數量: 1
請依指數從大到小輸入 (係數 指數):
2 1
請輸入 x 的值: 3
計算結果: 6
```
$ 代表使用者在 shell 中的輸入。

g++ main.cpp --std=c++21 -o main.exe 是編譯指令。

.\main.exe 是執行指令。

最後沒有 $ 的部分代表程式實際輸出的結果。

## 效能量測

###  記憶體動態擴充測量:

程式剛建立時，預設的陣列容量是 capacity = 2。

當輸入的多項式項數超過容量時，會自動觸發 capacity *= 2（容量翻倍）的機制。

隨著項數增加，容量只需要翻倍個幾次（ex: $2 >> 4 >> 8$）就能輕鬆容納，整個過程只進行了少數幾次記憶體搬移，沒有浪費多餘效能。

###  實際執行反應測量:

**加法運算**：用雙指標對齊指數相加，因為是一步一步順序處理的所以跑起來幾乎是瞬間完成，感覺上是沒有延遲的。

**乘法運算**：因為用雙層迴圈把各項相乘，當項數較多時計算次數會變多，但在一般的輸入規模下，電腦依然能在瞬間計算完畢並印出結果。

**代入 $x$ 求值**：用的是迴圈計算 $x$ 的次方再相加，運算邏輯很單純，輸入數字後立刻就能得到答案。

##  心得討論

### 記憶體效能優化
**問題**:程式中Polynomial的初始容量設為2。如果輸入的非零項較多，在剛開始輸入時就會一直觸發容量不足，導致頻繁進行 capacity *= 2，浪費記憶體空間。

**優化方案**：可以把初始容量設大一點（例如 10 或 20），減少初期記憶體搬移的次數可以優化記憶體空間的使用。

###  演算法邏輯
在實作多項式加法與乘法時，雙指標的線性掃描與雙層迴圈的係數合併邏輯是我這次程式的演算法邏輯。在處理同次項相加、係數抵消為零（例如 $3x^2$ 與 $-3x^2$ 相加）的狀況時，如果沒有把係數變成0的項目清乾淨，它就會一直留在陣列裡。所以用只存非零項的動態陣列的方法來解決就好了。
