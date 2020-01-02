/**
 * @file   ArrayList.h
 * @author Wang Heyu
 * @date   Fri Aug 30 15:54:20 2019
 *
 * @brief  An implementation of the static ADT List.
 * This is a demo for teaching, Not recommended for
 * any practical job.
 *
 */

#ifndef __CRAZYFISH__ArrayList__
#define __CRAZYFISH__ArrayList__

#include <iostream>
#include <limits>
#include <cstdlib>
#include <math.h>

namespace CRAZYFISH{

  template<class TYPE> class ArrayList;

  /**
   * To print out the content in streams.
   * 
   * @param os an output stream followed.
   * @param _obj the List to output.
   *
   * @return the stream to output.
   */
  template <class TYPE> std::ostream& operator<<(std::ostream &os,
						 const ArrayList<TYPE> &_obj);

  /**
   * Using standard array in C++ to implement List ADT. TYPE can be 
   * char, int, long, double or long double.
   */
  template <class TYPE>
  class ArrayList
  {
  private:
    TYPE *__data;               /**< The data stored. */
    int __length;               /**< The length of the List. */
  
    /**
     * Merge two parts of the List, which are [_p, _q] and [_q + 1, _r],
     * the two parts should have already sorted, then the result of merging
     * [_p, _r] will be also sorted. This function is for the implementation
     * of function __merge_sort() only.
     *
     * @param _p Stard index of part one.
     * @param _q The index before the start of part two, and _q + 1
     *           is actually the start of part two.
     * @param _r The end of part two, caution, _r - 1 is the index of the last 
     *           element.
     * @return   If the List with its part [p, r] has already sorted, then 
     *           return 0, otherwise -1.
     */
    int __merge( int _p,
		 int _q,
		 int _r);

    /**
     * Merge sort the part [_p, _r] of the List.
     *
     * @param _p The start index.
     * @param _r Caution: the index of the last element is _r - 1.
     *
     * @return If everything is fine, return 0, otherwise -1.
     */
    int __merge_sort(int _p, int _r);

  public:
    /**
     * Default constructor. Build an empty List.
     *
     */
    ArrayList()
    {
      __data = NULL;
      __length = 0;
    };

    /**
     * Constructor, build a List with _s elements.
     *
     * @param _s The length of the List.
     */
    ArrayList(int _s);

    /**
     * Constructor, build a List with _s elements, and all fill in
     * with valur _d.
     *
     * @param _s The length of the List.
     * @param _d The initial value for all elements.
     */
    ArrayList(int _s, TYPE _d);

    /**
     * Default destructor.
     *
     */
    ~ArrayList();

    /**
     * Print out all elements of the List. For debug using.
     *
     *
     * @return If everything is fine, return 0, otherwise -1.
     */
    int printArrayList();

    /**
     * Find if the List contains value _d.
     *
     * @param _d The value to find.
     *
     * @return The index of the last element with value _d if found,
     * otherwise -1.
     */
    int find(TYPE _d);

    /**
     * Find if the List[p,q] contains value _d, using bisection
     * searching algorithm.
     *
     * @param _p The start index.
     * @param _q Caution: the index of the last element is _r - 1.
     * @param _d The value to find.
     *
     * @return The index of the first element with value _d if found,
     * otherwise -1.
     */
    int __fast_find(TYPE _d, int _p, int _q);

    /**
     * Find if the List contains value _d, using bisection
     * searching algorithm.
     *
     * @param _d The value to find.
     *
     * @return The index of the first element with value _d if found,
     * otherwise -1.
     */
    int fast_find(TYPE _d);

    /**
     * Sort the List by merge-sort algorithm.
     *
     *
     * @return If everything is fine, return 0, otherwise -1.
     */
    int merge_sort();

    /**
     * Reload operator [] for read/write the value of elements.
     *
     * @param _i The index of the element.
     *
     * @return If everything is fine, return 0, otherwise -1.
     */
    TYPE& operator[](int _i);

    /**
     * Reload operator [] for read the value of elements only.
     *
     * @param _i The index of the element.
     *
     * @return If everything is fine, return 0, otherwise -1.
     */
    const TYPE& operator[](int _i) const;

    friend std::ostream& operator<< <> (std::ostream&, const ArrayList<TYPE>&);
  };
}
#else

#endif

		    
