# Day 3 Assignments

## Assignment 1: Arrays and Vectors
Please take a look at my code in [AssignArraysAndVectors](https://github.com/manoj-smoothstack/cpp_training/tree/main/Week1/Day3/AssignArraysAndVectors/) and its annotations.

## Assignment 2: Mixed Arrays
### 2.1 and 2.2
Please take a look at my code in [AssignMixedArrays](https://github.com/manoj-smoothstack/cpp_training/tree/main/Week1/Day3/AssignMixedArrays/) and its annotations

## Assignment 3: Array vs Vector
I would use an std::vector over an array whenever the size of a collection is ambiguous, I want to be able to index memory that may or may not be within the bounds of an array, or when I want to easily insert or append to a collection.
Here is an example program I generated where the user is polled for data and that data is inserted into a vector: [AssignArrayVsVector](https://github.com/manoj-smoothstack/cpp_training/tree/main/Week1/Day3/AssignArrayVsVector)
User generated data is often unformatted and of indefinite size which makes it a great example of when to use std::vector! However, if memory management or speed is of utmost importance to you - use an array or generate your own type of vector because we can't guarantee vectors will use memory 100% efficiently (they allocate more than they use) and will be index quickly (the `.at()` member function, though safe, isn't as fast as indexing an array).

## Assignment 4: Vector Performance
The `insert()` method is slower because, when inserting to the middle or beginning of a vector, the elements after the insert index have to be pushed one index forward. This copying of memory takes time, while it also performs the basic function of `push_back()` that is adding new data.
The `push_back()` method takes advantage of the fact that we are appending data to the end by not having to move around existing elements.
In the worst case scenario, either one of these may cause the vector to dynamically reallocate memory. Let's assume we used `std::vector::reserve()` to allocate a bunch of memory to our vector object.
Because of the nature of `push_back()`, there is no worst case scenario so long as memory is reserved for the object being inserted;
however, insert does have a worst- and best-case scenario. The worst case is when we are inserting data directly to the front of the vector, causing ALL existing elements of the vector to have to be copied one position forwards. The best case scenario is actually when we use `insert(last())` (`insert(size())`) which is the direct equivalent of `push_back()` because we are not copying any memory forwards.
