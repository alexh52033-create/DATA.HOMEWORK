#include <iostream>

using namespace std;

// 第一題：遞迴版
int ack(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (m > 0 && n == 0) {
        return ack(m - 1, 1);
    }
    else {
        return ack(m - 1, ack(m, n - 1));
    }
}

// 第一題：非遞迴版
int ack_iter(int m, int n) {
    int stack[10000]; // 開一個夠大的陣列當作 stack
    int top = -1;     // 記錄堆疊最上面的位子，-1代表空的

    top++;
    stack[top] = m; // 把一開始的 m 丟進 stack

    while (top != -1) { // 只要 stack 裡面還有東西就繼續跑
        m = stack[top]; // 拿出最上面的 m
        top--;          // 拿出來後 top 往下減

        if (m == 0) {
            n = n + 1;
        }
        else if (m > 0 && n == 0) {
            top++;
            stack[top] = m - 1;
            n = 1;
        }
        else if (m > 0 && n > 0) {
            // 要先算內層，再算外層，所以外層的 m-1 先放進去
            top++;
            stack[top] = m - 1;

            // 內層的 m 後放進去
            top++;
            stack[top] = m;

            n = n - 1;
        }
    }
    return n;
}

// 第二題：Powerset 冪集
void powerset(char s[], bool sel[], int index, int n) {
    // 如果 index 走到 n，代表每個元素都決定好要不要選了，準備印出來
    if (index == n) {
        cout << "(";
        int print_count = 0; // 用來算印了幾個元素，解決逗號的問題

        for (int i = 0; i < n; i++) {
            if (sel[i] == true) { // 如果這個位子是 true 代表有選
                if (print_count > 0) {
                    cout << ","; // 第二個以後的元素前面要加逗號
                }
                cout << s[i];
                print_count++;
            }
        }
        cout << ") ";
        return;
    }

    // 情況一：不選現在這個元素
    sel[index] = false;
    powerset(s, sel, index + 1, n);

    // 情況二：要選現在這個元素
    sel[index] = true;
    powerset(s, sel, index + 1, n);
}

int main() {
    // 測試第一題
    cout << "--- Problem 1: Ackermann Function ---\n";
    int m = 2, n = 2;
    cout << "Recursive A(" << m << ", " << n << ") = " << ack(m, n) << "\n";
    cout << "Iterative A(" << m << ", " << n << ") = " << ack_iter(m, n) << "\n\n";

    // 測試第二題
    cout << "--- Problem 2: Powerset ---\n";
    char s[3] = { 'a', 'b', 'c' };
    bool sel[3] = { false, false, false }; // 紀錄 a,b,c 有沒有被選到

    cout << "powerset(S) = { ";
    powerset(s, sel, 0, 3); // 從第 0 個位子開始找，總共有 3 個元素
    cout << "}\n";

    return 0;
}