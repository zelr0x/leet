// Problem: https://leetcode.com/problems/print-foobar-alternately/description/
// Solution: https://leetcode.com/problems/print-foobar-alternately/solutions/6382046/let-it-spin-and-beat-100-in-cpu-and-memory/
final class FooBar {
    private final int n;
    private volatile boolean fooNext = true;

    public FooBar(int n) {
        this.n = n;
    }

    public void foo(Runnable printFoo) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            while (!fooNext) {
            }
            printFoo.run();
            fooNext = false;
        }
    }

    public void bar(Runnable printBar) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            while (fooNext) {
            }
            printBar.run();
            fooNext = true;
        }
    }
}
