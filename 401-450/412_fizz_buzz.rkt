(define/contract (fizz-buzz n)
  (-> exact-integer? (listof string?))
  (define (fb n)
    (let ([d3 (zero? (remainder n 3))]
          [d5 (zero? (remainder n 5))])
      (cond [(and d3 d5) "FizzBuzz"]
            [d3 "Fizz"]
            [d5 "Buzz"]
            [else (number->string n)])))
  (define (acc n res)
    (if (zero? n)
        res
        (acc (- n 1) (cons (fb n) res))))
  (acc n '()))
