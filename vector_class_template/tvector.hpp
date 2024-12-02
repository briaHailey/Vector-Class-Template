// Function definitions for tvector.h

//Default Constructor
template<typename T>
TVector<T>::TVector() {
    // Create empty array of length SPARECAPACITY
    array = new T[SPARECAPACITY];
    capacity = SPARECAPACITY;
    size = 0;
}

// Creates a vector containing "num" copies of the data element "val",
template<typename T>
TVector<T>::TVector(T val, int num) {
    // Error checking if num is negative
    if (num < 0){
        num = 0;
    }
    capacity = num + SPARECAPACITY;
    // Create the new vector
    array = new T[num+SPARECAPACITY];
    size = num;
    // Inserts num copies of "val" into the newly created vector
    for (int i = 0; i < num; i++){
        array[i] = val;
    }
}

//Destructor
template<typename T>
TVector<T>::~TVector() {
    if (array != 0) {
        delete [] array;
        array = nullptr;
    }
}

//Copy constructor
template<typename T>
TVector<T>::TVector(const TVector<T> &v) {
    // Assign tracking variables
    capacity = v.capacity;
    size = v.size;
    // Create new array
    array = new T [capacity];
    // Assign values to the new array
    for (int i =0; i < size; i++){
        array[i] = v.array[i];
    }
}

//Copy assignment operator
template<typename T>
TVector<T> &TVector<T>::operator=(const TVector<T> &v) {
    // If not a self-assignment
    if (this != &v){
        // Delete the old array
        delete [] array;
        // Assign tracking variables
        capacity = v.capacity;
        size = v.size;
        // Create new array
        array = new T [capacity];
        // Assign values to the new array
        for (int i =0; i < size; i++){
            array[i] = v.array[i];
        }
    }
    // Return the calling object
    return *this;
}

// Move constructor
template<typename T>
TVector<T>::TVector(TVector<T> &&v) {
    // Assign tracking variables
    capacity = v.capacity;
    size = v.size;
    // Use the pointer to take the data
    array = v.array;
    // Null out pointers and trackers
    v.array = nullptr;
    v.size = 0;
    v.capacity = 0;
}

// Move assignment operator
template<typename T>
TVector<T> &TVector<T>::operator=(TVector<T> &&v) {
    // Member by member swap using pointers
    std::swap(capacity, v.capacity);
    std::swap(size, v.size);
    std::swap(array, v.array);

    // Return the calling object
    return *this;
}

// Is empty
template<typename T>
bool TVector<T>::IsEmpty() const {
    if (size == 0){
        return true;
    }
    else {
        return false;
    }
}

// Set the vector to empty
template<typename T>
void TVector<T>::Clear() {
    if (size != 0){
        size = 0;
        capacity = 0;
    }
}

// Get size
template<typename T>
int TVector<T>::GetSize() const {
    return size;
}

// Insert back
template<typename T>
void TVector<T>::InsertBack(const T &d) {
    // If vector full
    if (capacity == size) {
        T * temp = new T [capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = array[i];
        }
        // Double the capacity
        capacity *= 2;
        array = new T [capacity];
        // Copy over old data
        for (int i = 0; i < size; i++) {
            array[i] = temp[i];
        }
    }
    // Insert the value
    array[size] = d;
    // Adjust the size accordingly
    size++;
}

// Remove Back
template<typename T>
void TVector<T>::RemoveBack() {
   // If the array is not already empty
    if (size != 0){
        // Prevents any access to the removed value
        size -= 1;
    }
}

// Get first element of the vector
template<typename T>
T &TVector<T>::GetFirst() const {
    if (size==0)
        return dummy;
    return array[0];
}

// Get last element of the vector
template<typename T>
T &TVector<T>::GetLast() const {
    if (size==0)
        return dummy;
    return array[size-1];
}

// Get iterator
template<typename T>
TVectorIterator<T> TVector<T>::GetIterator() const {
    // Create beginning iterator
    TVectorIterator<T> beginningIterator;
    // If the array is empty
    if (size == 0){
        return beginningIterator;
    }
    else {
        // Assign tracking variables
        beginningIterator.index = 0;
        beginningIterator.ptr = array;
        beginningIterator.vsize = size;
        return beginningIterator;
    }
}

// Get end iterator
template<typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const {
    // Create end iterator
    TVectorIterator<T> endIterator;
    // If the array is empty
    if (size == 0) {
        return endIterator;
    }
    else {
        // Assign tracking variables
        endIterator.index = size-1;
        endIterator.ptr = array + (size-1);
        endIterator.vsize = size;
        return endIterator;
    }
}

// Reset the capacity of the Vector to c and adjust size if c is smaller.
template<typename T>
void TVector<T>::SetCapacity(unsigned int c) {
    // Make items larger than the new size inacessable
    if (c <= size){
        size = c;
        capacity = c;
    }
    else {
        T * temp = new T [capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = array[i];
        }
        // Increase capacity to c
        capacity = c;
        array = new T [capacity];
        // Copy over old data
        for (int i = 0; i < size; i++) {
            array[i] = temp[i];
        }
    }
}

// insert data element d just before item at pos position and return iterator to the new data item
template<typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T &d) {
    TVectorIterator<T> insertIterator;
    // If array is full
    if (capacity == size) {
        T * temp = new T [capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = array[i];
        }
        // Double the capacity
        capacity *= 2;
        array = new T [capacity];
        // Copy over old data
        for (int i = 0; i < size; i++) {
            array[i] = temp[i];
        }
    }

    // If the array is empty
    if (size == 0){
        if (array == nullptr) {
            // Create an empty array of size SPARECAPACITY
            array = new T [SPARECAPACITY];
            // set capacity to sparecapacity
            capacity= SPARECAPACITY;
            // Assign tracking variables
        }
        array[0] = d;
        // Assign tracking variables
        insertIterator.index = ++size;
        insertIterator.ptr = array;
        insertIterator.vsize = 1;
    }
    // If the position does not refer to a valid spot
    else if ((pos.index > size -1) || (pos.index < 0)) {
        // Insert the value at the back of the array
        array[size] = d;
        // Assign tracking variables
        size++;
        insertIterator.index = size - 1;
        insertIterator.ptr = array + (size-1);
        insertIterator.vsize = size;
    }
    else if (pos.ptr == nullptr) {
        InsertBack(d);
    }
    else{
        // Move everything to the right of the pos over
        for (int i = size-1; i >= static_cast<int>(pos.index); i--){
            array[i+1] = array[i];
        }
        // Insert the value
        array[pos.index] = d;
        // Assign tracking variables
        insertIterator.index = pos.index;
        insertIterator.ptr = array+(pos.index);
        insertIterator.vsize = size++;
    }
    return insertIterator;
}

// Remove (singular)
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos) {
    TVectorIterator<T> removeIterator;
    // If the array is empty
    if (size == 0){
        // Return the default iterator
        return removeIterator;
    }
    // If the position does not refer to a valid spot
    else if ( (pos.index > size -1) || (pos.index < 0) ){
        // Return the default iterator
        return removeIterator;
    }
    else if (pos.ptr == nullptr) {
        return removeIterator;
    }
    else{
        // Overwrite all items with the item to their right from the position to the end of the array
        for (int i = pos.index; i < size-1; i++){
            array[i] = array[i+1];
        }
        // Assign tracking variables
        removeIterator.index = pos.index;
        removeIterator.ptr = array+(pos.index);
        removeIterator.vsize = --size;
        // Return the iterator to the data item after the deleted data item
        return removeIterator;
    }
}

// Remove range function
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2) {
    TVectorIterator<T> rangeIterator;
    // If the array is empty
    if (size == 0){
        // Return the default iterator
        return rangeIterator;
    }
    // If the first iterator is after the second iterator (error)
    else if (pos1.index > pos2.index) {
        rangeIterator.index = pos1.index;
        rangeIterator.ptr = array+(pos1.index);
        rangeIterator.vsize = size;
        return rangeIterator;
    }
    else if (pos1.index == pos2.index){
        TVector<T>::Remove(pos1);
    }
    else if (pos1.ptr == nullptr || pos2.ptr == nullptr) {
        return rangeIterator;
    }
    else {
        // Make sure that both positions are valid
        // If position 1 is not valid, do nothing
        if (pos1.index < 0){
            return rangeIterator;
        }
        // If position 2 is not valid, do nothing
        if (pos2.index > size -1){
            return rangeIterator;
        }
        // Overwrite all items within the range
        for (int i = pos1.index; i < size-(pos2.index - pos1.index); i++) {
            array[i] = array[i + (pos2.index - pos1.index)];
        }
        // Assign tracking variables
        rangeIterator.index = pos1.index + 1;
        rangeIterator.ptr = array+(pos1.index+1);
        rangeIterator.vsize = size - (pos2.index - pos1.index);
        size = size - (pos2.index - pos1.index);
        return rangeIterator;
    }
    return rangeIterator;
}

// Print Function
template<typename T>
void TVector<T>::Print(std::ostream &os, char delim) const {
    if (size == 0) {
        os << "Empty vector";
    }
    else {
        // Print each element of the array seperated by the given delimeter
        for (int i =0; i< size -1; i++){
            os << array[i] << delim;
        }
        // Print the last element without the delimeter after it
        os << array[size-1];
    }
}

// Concatenation Function
template<typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2){
    TVector<T> catVector = t1;
    // Add the contents of t2
    TVectorIterator<T>catIterator = catVector.GetIterator();
    // Navigate the iterator to the correct position
    for (int i = 0; i < t1.GetSize()-1; i++) {
        catIterator.Next();
    }
    // Generate t2 iterator
    TVectorIterator<T> t2Iterator;
    t2Iterator = t2.GetIterator();
    for (int i = 0; i < t2.GetSize(); i++){
        T value = t2Iterator.GetData();
        catVector.InsertBack(value);
        t2Iterator.Next();
    }
    return catVector;
}

// Iterator class default constructor
template<typename T>
TVectorIterator<T>::TVectorIterator() {
    index = 0;
    ptr = nullptr;
    vsize = 0;
}

// Has Next? Iterator Function
template<typename T>
bool TVectorIterator<T>::HasNext() const {
    if (index < vsize-1){
        return true;
    }
    else {
        return false;
    }
}

// Has Previous? Iterator Function
template<typename T>
bool TVectorIterator<T>::HasPrevious() const {
    if (index <= 0){
        return false;
    }
    else{
        return true;
    }
}

template<typename T>
TVectorIterator<T> TVectorIterator<T>::Next() {
    // If there is a next value
    if (HasNext()){
        index++;
        ptr++;
    }
    return *this;
}

// Return previous
template<typename T>
TVectorIterator<T> TVectorIterator<T>::Previous() {
    TVectorIterator<T> prevIterator;
    if (HasPrevious()){
        index = index-1;
        ptr = ptr-1;
    }
    return prevIterator;
}

template<typename T>
T &TVectorIterator<T>::GetData() const {
    if (vsize==0 || ptr == nullptr) {
        TVector<T> dummyVect;
        return dummyVect.dummy;
    }
    return *ptr;
}