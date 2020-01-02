#ifndef __ArrayList__
#define __ArrayList__

#include <iostream>
#include <limits>
#include <cstdlib>

namespace CRAZYFISH{
template<class TYPE> class ArrayList;

/**
 * To print out the content in streams.
 *
 * @param os an output stream followed.
 * @param _obj teh List to output .
 *
 * #return the stream to output.
 */
template <class TYPE> std::ostream& operator<<(std::ostream &os,
                                               const ArrayList<TYPE> &_obj);

/**
 * Using standard array in C++ to implement List ADT. TYPE can be
 * char, int, long, double or long double.
 *
 */
template<class TYPE>
class ArrayList
{
private:
    TYPE *__data;  // The data stored.
    int __length;  // The length of teh List.

    int __merge(int _p, int _q, int _r);

    int __merge_sort(int _p, int _r);

public:
    ArrayList()
        {
            __data = NULL;
            __length = 0;
        }
    ArrayList(int _s);
    ArrayList(int _s, TYPE _d);
    ~ArrayList();
    int printArrayList();
    int find(TYPE _d);
    int fast_find(TYPE _d);
    int merge_sort();
    TYPE &operator[](int _i);
    const TYPE &operator[](int _i) const;
    friend std::ostream& operator<< <> (std::ostream&,
                                        const ArrayList<TYPE>&);
};
}

#endif
