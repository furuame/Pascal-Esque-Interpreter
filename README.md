# A Pascal-Like Interpreter
This is a simple Pascal-like interpreter referenced from [Ruslan's Blog](https://ruslanspivak.com).

## Build
* ```$ make main```
* ```$ ./main test_program.ps```

## Limits
* Number in the interpreter is handled with integer

## Test Program to interpreter
```
BEGIN
    a := 3;
    b := 6;
    c := a + b;
    BEGIN
        d := 5;
        e := 9;
        f := d + e + c;
    END;
    a := a + f + 3;
END.
```

## Result
```
a: 29
b: 6
c: 9
d: 5
e: 9
f: 23
```
