#ifndef _DVECTOR_H_
#define _DVECTOR_H_
#include "stdio.h"
/** \mainpage Dynamic Vector
*
6 * This library implements a vector with dynamic size.
7 *
8 */

/**
11 * Data type of the vector elements.
12 */
typedef int vdata_t;

/**
16 * The Dynamic Vector data type.
6
17 */
typedef struct vector vector_t;
struct vector {
    /** The number of elements in the vector */
    size_t size;
    /** The amount of allocated memory */
    size_t capacity;
    /** The allocated memory */
    vdata_t *data;
};
/**
21 * Allocates an empty vector.
22 * @return empty vector.
23 */
vector_t *v_create();

/**
27 * Clones a vector (deep copy).
28 * @return vector.
29 */
vector_t *v_clone(const vector_t *v);

/**
33 * Frees a vector and the memory it uses.
34 * @param v The vector to be freed.
35 */
void v_free(vector_t *v);

/**
39 * Prints a vector.
40 * @param v The vector to be printed.
41 */
void v_print(const vector_t *v);

/**
45 * Checks if a vector is empty.
46 * @param v The vector.
47 * @return 1 if empty, 0 otherwise.
48 */
int v_is_empty(const vector_t *v);

/**
52 * Returns the size of a given vector.
53 * @param v The vector.
54 * @return The number of elements stored in the vector.
55 */
size_t v_size(const vector_t *v);

/**
59 * Returns element at a given index.
60 * Program exits if index is out of bounds.
61 * @param v The vector.
62 * @param index The desired index.
63 * @return the value stored at the corresponding index.
64 */
vdata_t v_get(const vector_t *v, size_t index);


/**
69 * Stores a value at a given index.
70 * Program exits if index is out of bounds.
71 * @param v The vector.
72 * @param index The desired index.
7
73 * @param value The value to be stored.
74 */
void v_set(vector_t *v, size_t index, vdata_t value);

/**
78 * Inserts a new value after the last element of the vector.
79 * @param v The vector.
80 * @param value The value to be inserted.
81 */
void v_push_back(vector_t *v, vdata_t value);

/**
85 * Removes the last element in the vector and returns its value.
86 * Program exists if vector is empty.
87 * @param v The vector.
88 * @return The value previously stored in the last position.
89 */
vdata_t v_pop_back(vector_t *v);

/**
93 * Inserts a new value before the first element of the vector.
94 * @param v The vector.
95 * @param value The value to be inserted.
96 */
void v_push_front(vector_t *v, vdata_t value);

/**
100 * Removes the first element in the vector and returns its value.
101 * Program exists if vector is empty.
102 * @param v The vector.
103 * @return The value previously stored in the first position.
104 */
vdata_t v_pop_front(vector_t *v);

/**
108 * Inserts a new value at given position by shifting existing elements to the right.
109 * Program exits if index is out of bounds.
110 * @param v The vector.
111 * @param value The value to be inserted.
112 * @param index The position where to insert the value.
113 */
void v_insert_at(vector_t *v, vdata_t value, size_t index);

/**
117 * Deletes element at given position by shifting existing elements to the left.
118 * Program exits if index is out of bounds.
119 * @param v The vector.
120 * @param index The position to be removed.
121 */
void v_delete_at(vector_t *v, size_t index);

#endif