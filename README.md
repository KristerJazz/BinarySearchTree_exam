# Advanced Programming Exam Solution - JAZZ


A templated binary search tree can be inspected in this [code](bst.cpp)

## Running the codes

First you have to download the `bst.cpp` and `makefile` then run,

```
make
```

The latest version of the code makes the benchmarking executable.
The benchmark code can be run by providing the number of nodes in which you want to benchmark.
```
./bst.x 10 # number of nodes to be inserted and find
```

A [jobscript](job.sh) is also uploaded to run the benchmarking code for increasing number of nodes.

```
./job.sh
```

## Testing of functions
By commenting out the benchmarking code and uncommenting the testing section of the main function.

We will be able to see the following results.

![](function_test_results.png)



No memory leaks is observed using the following code and shown by the screenshot.
```
valgrind --leak-check=full --verbose --show-leak-kinds=all ./bst.x 100
```
![](noleak.png)

## Benchmarking
I used a naive way of implementing 

### Straight Line tree
![](benchmark_results/benchmark.png)

### Naive balance algorithm
![](benchmark_results/benchmark_balance.png)

### Random  vs std::map
![](benchmark_results/benchmark_random.png)

## Summary
Overall, the main take aways for me in this exam are the concepts of `templates`, c++ `struct` and `class` datatypes, and of course `ITERATORS`, `pointer` handling, and "overloading" (maybe there is a better term) of different operators such as the `subscripting` and `put-to operator` as well as the `copy` and `move` semantics.


### A more organized - similar version of this code will be uploaded in the [reorganized folder](reorganized/).

