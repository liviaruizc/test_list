// List.h
// Livia Correia
// FGCU Computing and Software Engineering
// List ADT implemented as a dynamic single-linked list of objects
// ------------------------------------------------------------
#include <iostream>     // for debugging only
#include <algorithm>    // swap

// Uncomment the following #define to turn on debug messages and
// recompile your code, or add the following instruction to
// the CMakeList.txt script if using CLion
//      add_compile_definitions(_DEBUG_CONSTRUCTORS)
#define _DEBUG_CONSTRUCTORS

// Header-Guard definition
// ------------------------------------------------------------
#ifndef FGCU_LIST_H
#define FGCU_LIST_H


namespace fgcu {


    template<typename Object>
    class List {
    private:

        // internal payload that holds user-provided
        // element values and links each element to
        // the next one in the list
        struct Node{
            Object value;
            Node* next;
            Node* previous;

            // Constructor to initialize value and set next to nullptr
            Node(const Object& value) : value(value), next(nullptr), previous(nullptr) {}
        };

    public:
        const static int APPEND = -1;

        /**
         * Defines an empty list
         */
        List() : head{nullptr}, size{0}, tail{nullptr} {

#ifdef _DEBUG_CONSTRUCTORS
            std::cout << "fgcu::List - Default constructor" << std::endl;
#endif // _DEBUG_CONSTRUCTORS
        }

        [[nodiscard]] long getSize() const { return size; }

        /**
         * Check to see if the list is empty
         * @return - true if list is empty
         */
        bool isEmpty() { return size == 0; }

        /**
         * Insert a new value into the list at a given position
         * @param value - value to add to the list
         * @param position - position from 0 to size-1 (default -1 to append)
         */
        void insert(const Object &value, long position=APPEND) {
            // fix invalid positions to append to end of list at size
            if (position < 0 || position > size) { // If position is below zero or more than size, insert in the end.
				position = size;
			}

            // create new element for user value
            Node *newNode = new Node(value); // Creating a new node
			Node *pNode = nullptr; // Transitator pointer
            Node *temp = newNode;

            // insert at front of list
            if (!size || position == 0) {
				newNode->next = head;
				if (head) {
				   head->previous = newNode;
				}
                head = newNode;
                if (size == 0) {
                    tail = head;
                }
            }

            // insert in middle or end of the list
            else {
                pNode = head;
                int currentPosition = 0;
                while (pNode->next && currentPosition < position -1) {
                    pNode = pNode->next;
                    currentPosition++;
                }

                newNode->next = pNode->next;
                pNode->next = temp;
                newNode->previous = pNode;

                if (pNode->next) { // If the next pointer is not null, previous point to newNode
                    pNode->next->prev = newNode;
                }

                pNode->next = newNode;

                // If inserting at the end, tail points to last node
                if (!newNode->next) {
                    tail = newNode;
                }

            }

			// increment list size
            size++;

            // releasing the memory from the two local pointers
            delete pNode;
            delete temp;
        } // insert

        /**
         * Read the payload value at the given position
         * @param position - 0 to size-1
         * @return - value at given position
         */
        Object read(long position) {
            // return an empty payload if position is invalid
            if (position < 0 || position >= size ) {
                return Object{};
            }

            // traverse to position
            Node* pNode = head;
            for (int i=0; i < position; ++i)
                pNode = pNode->next;

            return pNode->value;
        } // read

    private:
        Node* head; // pointer to first element in the list
        long size;   // number of elements in the list
        Node* tail; // pointer to last element in the list


    public:
        /*
         * Big-5 Functions:
         * 1) Destructor: Cleans up resources when an object's lifetime ends.
         * 2) Copy Constructor: Creates a new object as a deep copy (used during initialization).
         * 3) Copy Assignment Operator: Deep copies resources between existing objects.
         * 4) Move Constructor: Transfers resources from a temporary (rvalue) to a new object.
         * 5) Move Assignment Operator: Transfers resources from a temporary (rvalue) to an existing object.
         */


        /**
         * Release residual memory elements at list destruction time.
         */
        ~List() {
#ifdef _DEBUG_CONSTRUCTORS
            std::cout << "fgcu::List - Destructor" << std::endl;
#endif // _DEBUG_CONSTRUCTORS

            // do until the list is empty
            while(head) {
                Node* temp = head; // hold current front node
                head = head->next; // move head to next node
                delete temp;       // release current node
            }
            size = 0;
        }

        /**
         * Copy constructor - make a deep-copy of the
         * right-hand-side (rhs) instance to this instance
         * @param rhs - object to copy to this instance
         */
        List( const List & rhs )
            : head{nullptr}, size{0}, tail{nullptr} {
#ifdef _DEBUG_CONSTRUCTORS
            std::cout << "fgcu::List - Copy constructor" << std::endl;
#endif // _DEBUG_CONSTRUCTORS

            Node* pNode = rhs.head;
            while(pNode) {
                Object value = pNode->value;
                insert(value);
                pNode = pNode->next;
            }
        }

        /**
         * Copy assignment - use the move assignment operator
         * below to do a swap instead of copy
         * @param rhs - object to copy to this instance
         * @return - this instance
         */
        List & operator= ( const List & rhs ) {
#ifdef _DEBUG_CONSTRUCTORS
            std::cout << "fgcu::List - Copy assignment operator" << std::endl;
#endif // _DEBUG_CONSTRUCTORS

            // handle self-assignment
            if (rhs == *this)
                return *this;

           List copy = rhs; // call move assignment operator

           // swap memory for copy and this instance
           std::swap( *this, rhs );

            // return this instance
            return *this;
        }

        /**
         * Move constructor - make this instance point to
         * the right-hand-side (rhs) memory and clear rhs.
         * instance to this instance
         * @param rhs - object to move to this instance
         */
        List( List && rhs )
            : head{ rhs.head }, size{ rhs.size }, tail{rhs.tail} {
#ifdef _DEBUG_CONSTRUCTORS
            std::cout << "fgcu::List - Move constructor" << std::endl;
#endif // _DEBUG_CONSTRUCTORS
            rhs.head = nullptr;
            rhs.size = 0;
            rhs.tail = nullptr;
        }

        /**
         * Copy assignment - make a deep-copy of the
         * right-hand-side (rhs) instance to this instance
         * @param rhs - object to copy to this instance
         * @return - this instance
         */
        List & operator= ( List && rhs ) {
#ifdef _DEBUG_CONSTRUCTORS
            std::cout << "fgcu::List - Move assignment operator" << std::endl;
#endif // _DEBUG_CONSTRUCTORS

            // swap memory values between instances
            std::swap(head, rhs.head);
            std::swap(size, rhs.size);
            std::swap(tail, rhs.tail);
        }


    }; // List


} // fgcu namespace



#endif //FGCU_LIST_H
