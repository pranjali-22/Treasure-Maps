/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    n1 = 0; 
    n2 = -1; 
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
   data.push_back(newItem);
   if (n1 == -1 && n2 == -1) {
    n1 = 0;
    n2 = 0;
   }
   else {
    n2 = data.size() -1;
   }
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T elem = data[n1];
    vector<T> myVector;
    n1 = n1 + 1;
    int data_size = data.size();
    if (n1+1 > data.size()) {
        n1 = -1;
        n2 = -1;
        data = myVector;
    }
    // resizing
    int size_to_fit = n2 - n1 + 1;
    int size_avl = n1;
    if (size_avl >= size_to_fit) {
        // resize data
        // pop elements
        for (int i = 0; (n1+i) <= n2; i++) {
            myVector.push_back(data[n1+i]);
        }
        data = myVector;
        n1 = 0;
        n2 = myVector.size() -1;
    }
    return elem;
}

/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *

 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
   T elem = peekR();
    data.pop_back();
    n2 -= 1;

    if(n2-n1+1 <= n1){
        vector<T> myVector;
        for(int i=n1; i<=n2; i++){
            myVector.push_back(data[i]);
        }
        data.resize(myVector.size());
        for(unsigned long i=0; i<myVector.size(); i++){
            data[i] = myVector[i];
        }
        n1 = 0;
        n2 = myVector.size()-1;
    }

    return elem;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data[n1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
   return data[n2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return data.empty();
}
