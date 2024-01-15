#include <condition_variable>

/**
  * https://leetcode.com/problems/print-in-order/
  */
class Foo {
public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        {
            std::unique_lock<std::mutex> lk(m);
            // printFirst() outputs "first". Do not change or remove this line.
            printFirst();
            last = 1;
        }
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [this]{ return last == 1; });
            // printSecond() outputs "second". Do not change or remove this line.
            printSecond();
            last = 2;
        }
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [this]{ return last == 2; });
            // printThird() outputs "third". Do not change or remove this line.
            printThird();
            last = 3;
        }
        cv.notify_all();
    }

private:
    std::mutex m;
    std::condition_variable cv;
    int last;
};
