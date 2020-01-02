#ifndef __CRAZYFISH__IntCell__
#define __CRAZYFISH__IntCell__

#include <iostream>
#include <vector>
using namespace std;

template <int DIM> class Point;

/*
  Reload << operator to out put the coordinate of the point.

  @param os standard output stream.
  @param _pnt The point to output stream.
*/
template <int DIM> ostream& operator<<(ostream & os, const Point<DIM> &_pnt);

/*
  Reload + operator.
  \f[
  (p_1 jp_2)_i = {p_1}_i + {p_2}_i, i = 1, 2, \cdots, DIM>
  \f]

  @param _p1 The first point.
  @param _p2 The second point.

  #return the sum point of the above two.
*/

/**
 * A template class design for DIM-dimension points.
 *
 */
template <int DIM> Point<DIM> operator+(const Point<DIM> &_p1,
                                        const Point<DIM> &_p2);
/**
 * A template class design for DIM-dimension points.
 *
 */

template <int DIM>
class Point
{
private:
    double coordinate[DIM]; /**< Coordinate of the point.*/
public:
    /**
     * Default constructor.
     *
     */
    Point(){};

    /**
     * Special constructor for 2D.
     *
     * @param x
     * @param y
     */
    Point(double x, double y);

    /**
     * Special constructor for 3D.
     *
     * @param x
     * @param y
     * @param z
     */
    Point(double x, double y, double z);

    /**
     * Copy constructor.
     *
     * @param _pnt The source point.
     */
    Point(const Point<DIM> &_pnt);

    /**
     * Read coordinate of the point.
     *
     *
     * @return The coordinate in a double array.
     */
    const double *read() const;

    /**
     * Reload [] operator to get the i-th coordinate of the point.
     * This is a read-write version.
     *
     * @param i the i-th component.
     *
     * #param The i-th coordinate value.
     */
    double &operator[](int i);

    /**
     * Reload [] operator to get the i-th coordinate of the point.
     * This is  a read- only version.
     *
     *
     *@param i The i-th component.
     *
     * @return the i-th coordinate value.
     */
    const double &operator[](int i) const;

    /**
     * Reload += operator, the rule of plus is same as @ref operator+.
     *
     * @param _pnt The point will be added.
     *
     * @return The sum will replace the pint in the left.
     */
    Point<DIM> &operator+=(const Point<DIM> &_pnt);

    /**
     * Reload = operator.
     *
     * @param _pnt
     *
     * @return
     */
    Point<DIM> &operator=(const Point<DIM> &_pnt);

    friend ostream& operator<< <> (ostream&, const Point<DIM>&);
    friend Point<DIM> operator+ <> (const Point<DIM>&, const Point<DIM>&);
};
#else

// Do nothing.


#endif
