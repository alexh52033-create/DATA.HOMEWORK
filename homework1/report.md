# Homework 1 報告

## 1. 解題說明
需撰寫「解題方法」：
1. **問題描述**： 
   - 第一題要實作 Ackermann 函數，並且分別寫出遞迴跟非遞迴的版本。
   - 第二題要寫一個遞迴程式，印出集合所有的子集（Powerset）。
2. **解題策略**：
   - 第一題（遞迴）：直接照著題目的條件寫 if-else 分支。
   - 第一題（非遞迴）：因為規定不能用內建的堆疊函式庫，所以我宣告了一個大小為 10000 的陣列 `stack`，並用一個變數 `top` 來記錄最上面的索引位置，藉此模擬堆疊的 push 和 pop 動作。
   - 第二題：用一個布林陣列 `sel` 來記錄每個元素「選」或「不選」。每次遞迴都有兩種情況，走到最後時再把標記為 true 的元素印出來。

## 2. 程式實作
以下為主要的非遞迴版 Ackermann 函數實作片段：

```cpp
int ack_iter(int m, int n) {
    int stack[10000]; 
    int top = -1;     
    top++;
    stack[top] = m; 
    while (top != -1) { 
        m = stack[top]; 
        top--;          
        if (m == 0) {
            n = n + 1;
        } else if (m > 0 && n == 0) {
            top++;
            stack[top] = m - 1;
            n = 1;
        } else if (m > 0 && n > 0) {
            top++;
            stack[top] = m - 1;
            top++;
            stack[top] = m;
            n = n - 1;
        }
    }
    return n;
}
```

## 3. 效能分析
- **第一題 (Ackermann)**:
  1. 時間複雜度：$O(A(m,n))$。因為 Ackermann 函數成長極快，計算次數會跟最終結果成正比。
  2. 空間複雜度：$O(m)$。在非遞迴中我開了陣列當作堆疊，消耗的空間跟 $m$ 的遞迴深度有關。
- **第二題 (Powerset)**:
  1. 時間複雜度：$O(2^n)$。集合有 $n$ 個元素，每個元素都有選跟不選兩種可能，所以總共會產生 $2^n$ 個子集。
  2. 空間複雜度：$O(n)$。遞迴最大的深度最多就是集合的大小 $n$。

  ## 4. 測試與驗證
程式的輸入與輸出：

```shell
$ g++ src/main.cpp --std=c++21 -o main.exe
$ .\main.exe
--- Problem 1: Ackermann Function ---
Recursive A(2, 2) = 7
Iterative A(2, 2) = 7

--- Problem 2: Powerset ---
powerset(S) = { () (c) (b) (b,c) (a) (a,c) (a,b) (a,b,c) }
```

## 5. 申論及開發報告
寫下使用到某資料結構、演算法的原因：

寫第一題非遞迴的時候，因為規定不能用內建的 `<stack>`，我就自己開了一個 `int stack[10000]` 陣列。

接著搭配 `top` 變數來當作堆疊用，利用 `top++` 和 `top--` 來模擬 push 和 pop 的動作。

功課做完比較懂原來遞迴就是用這種「後進先出」的方式，把變數存起來再拿出來算的。

雖然用陣列自己寫比較麻煩，但也算確實弄懂了堆疊的原理。