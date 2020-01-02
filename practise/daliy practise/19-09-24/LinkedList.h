##ifndef __CRAZYFISH__LinkedList__
#define __CRAZYFISH__LinkedList__

#include <iostream>
#include <limits>
#include <cstdlib>

namespace CRAZYFISH
{
template<class TYPE> class LinkedList;
/**
 * To print out the content in streams.
 *
 * @param os an output stream followed.
 * @param _obj the List to output.
 *
 * @return the stream to output.
 */

template<class TYPE> std::ostream& operator<<(std::ostream &os,
                                              const LinkedList<TPYE> &_obj);

/**
 * Using standard array in C++ to implement List ADT. TYPE can be
 * char, int, long, double or long double.
 *
 */
template<class TYPE>
class LinkedList
{
public:
    /**
     * A node of the linked  List.
     *
     */
    class Node
    {
    public:
        TYPE value;        /**< The stored value.*/
        Node* next;        /**< The address of the next node
                              of the linked List. */
        /**
         * The default constructor.
         *
         */
        Node()
            {
                next = NULL;
            };

        /**
         * Constructor, with the value is _d.
         *
         * @param _d The value to set.
         */
        Node(TYPE _d) : value(_d)
            {
                next = NULL;
            }

        /**
         * The default destuctor.
         *
         */
        ~Node(){}
    };
private:
    Node *__head;          /**< The head pointer of the List. */
    Node *__current;       /**< The address of current node.  */
    int __length;          /**< The length of the List.       */

public:
    /**
     * The default constructor. Build an empty List.
     *
     */
    LinkedList()
        {
            __head = NULL;
            __length = 0;
        }

    /**
     * Constructor, build a List with the first nude
     * is _new.
     *
     * @param -new An assigned node.
     */
    LinkedList(Node &_new);

    /**
     * Constructor, build a List with the value of the first
     * node is _val.
     *
     * @param _new An assigned node.
     */
    LinkedList(TYPE _val);

    /**
     * Default destructor.
     *
     */
    ~LinkedList();

    /**
     *
     * Print out all nodes of the List. For debug using.
     *
     * @return If everything is fine. return 0. otherwise -1.
     */
    int printLinkedList() const;

    /**
     * Find if the List contains value _d.
     *
     * @param _d The value to find.
     *
     * @return The address of the first node
     * with value _d if found, otherwise NULL.
     */
    Node* find(TYPE _d) const;

    /**
     * Insert a new node after the current pointer. If the List is
     * empty, then add it as the first node.
     *
     * @param _val The value in the new node.
     *
     * #return 0 for OK -1 for else.
     */
    int insert(TYPE _val);

    /**
