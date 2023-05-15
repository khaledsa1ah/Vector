#include "Vector.h"

//template<typename XYVector>
//XYVectorIterator<XYVector> :: XYVectorIterator(PointerType ptr){
//    this->ptr = ptr;
//}


//__________________Default Constructor________________________
template<class T>
XYVector<T> :: XYVector(){
    reAllocate(2);
}

//__________________Default DeConstructor________________________
template<class T>
XYVector<T> :: ~XYVector(){
//    for(int i = 0; i < this->sz; ++i){
//        data[i].~T[];
//    }
    //delete[] this->data;
    this->data = nullptr;
    this->sz = 0;
    this->capacity = 0;
}

//__________________Size Constructor________________________

template<class T>
XYVector<T> :: XYVector(size_t sz){
    this->reAllocate(sz+5);
    this->sz = sz;
}

//__________________New value Constructor________________________

template<class T>
XYVector<T> :: XYVector(T* arr, size_t n){
    this->data = arr;
    this->reAllocate(n+5);
    this->sz = n;
}

//_________________Copy Constructor_________________________

template<class T>
XYVector<T> :: XYVector(const XYVector& anotherVector){
    delete[] this->data;
    this->reAllocate(anotherVector.capacity);
    for(int i = 0; i < anotherVector.sz; ++i){
        data[i] = anotherVector.data[i];
    }
    this->sz = anotherVector.sz;


}

//_________________Move Constructor_________________________

template<class T>
XYVector<T> :: XYVector(XYVector&& anotherVector){
    delete[] this->data;

    this->data = std::move(anotherVector.data);
    this->sz = anotherVector.sz;
    this->reAllocate(anotherVector.capacity);

    anotherVector.data = nullptr;
    anotherVector.sz = 0;
    anotherVector.capacity = 0;
}
//__________________________________________


//_________________Copy Assignment_________________________
template<class T>
XYVector<T>& XYVector<T> :: operator=(const XYVector& anotherVector){
    if(anotherVector.data != this->data) {
        delete[] this->data;
        this->reAllocate(anotherVector.capacity);
        for(int i = 0; i < anotherVector.sz; ++i){
            data[i] = anotherVector.data[i];
        }
        this->sz = anotherVector.sz;
    }
    return *this;
}

//__________________________________________


//___________________Move Assignment_______________________
template<class T>
XYVector<T>& XYVector<T> :: operator=(XYVector&& anotherVector) {
    if(anotherVector.data != this->data) {
        delete[] this->data;
        this->data = std::move(anotherVector.data);
        this->sz = anotherVector.sz;
        this->reAllocate(anotherVector.capacity);


        anotherVector.data = nullptr;
        anotherVector.sz = 0;
        anotherVector.capacity = 0;
    }
    return *this;
}

//__________________________________________


//__________________Index Operator________________________

template<class T>
const T& XYVector<T> :: operator[](size_t index) const{
    try{
        if(index >= sz)
            throw std::invalid_argument("OUT of INDEX");
        return data[index];
    }
    catch(std::invalid_argument& error){
        std::cerr << error.what() << std::endl;
    }
//    return data[index];
}


template<class T>
T& XYVector<T> ::operator[](size_t index){
    try{
        if(index >= sz)
            throw std::invalid_argument("OUT of INDEX");
        return data[index];
    }
    catch(std::invalid_argument& error){
        std::cerr << error.what() << std::endl;
    }
//    return data[index];
}
//__________________________________________

//___________________== Operator_______________________
template<class T>
bool XYVector<T> :: operator==(const XYVector<T>& anotherVector){
    if(this->sz == anotherVector.sz){
        for(int i = 0; i < this->sz; ++i){
            if(data[i] == anotherVector.data[i]) continue;
            return false;
        }
        return true;
    }
    return false;
}

//___________________< >Operator_______________________
template<class T>
bool XYVector<T> :: operator<(const XYVector<T>& anotherVector){
    size_t minSize = std::min(this->sz, anotherVector.sz);
    for(int i = 0; i < minSize; ++i){
        if(data[i] < anotherVector.data[i]) return true;
    }
    return false;
}
template<class T>
bool XYVector<T> :: operator>(const XYVector<T>& anotherVector){
    return ((*this != anotherVector) && !(*this < anotherVector));
}






//___________________Size Getter_______________________

template<class T>
size_t XYVector<T> :: Size() const{
    return sz;
}
//__________________________________________

// ___________________Capacity Getter_______________________

template<class T>
size_t XYVector<T> :: Capacity() const{
    return capacity;
}

//__________________________________________

// ___________________Check Empty_______________________

template<class T>
bool XYVector<T> :: empty(){
    return this->sz == 0;
}

//__________________________________________


//________________PushBack__________________________

template<class T>
void XYVector<T> :: push_back(const T& value){
    if(sz >= capacity){
        this->reAllocate(capacity + capacity / 2);
    }
    data[sz++] = value;
}
//__________________________________________


//________________PopBack__________________________
template<class T>
T XYVector<T> :: pop_back(){
    this->sz--;
    return data[this->sz];
}
//__________________________________________

//________________Insert__________________________
template<class T>
void XYVector<T> ::insert(Iterator& it, T newValue) {
    try{
        if(it >= &data[this->sz+1]) {
            throw std::invalid_argument("OUT of INDEX");
        }
        //tmp 100    5 2 3 5
        this->sz += 1;
        for(int i = this->sz-1; i >= 0; --i){
            data[i+1] = data[i];
            if(&data[i] == it){
                data[i] = newValue;
                it -= i;
                return;
            }
        }
    }
    catch (std::invalid_argument& error){
        std::cerr << error.what() << std::endl;
    }
}
//__________________________________________


//________________Clear__________________________
template<class T>
void XYVector<T> :: clear(){
    this->sz = 0;
    this->capacity = 0;
    this->data = nullptr;
}
//__________________________________________

//________________Erase__________________________
template<class T>
void XYVector<T> :: erase(Iterator& it){
    try{
        if(it >= &data[this->sz]) {
            throw std::invalid_argument("OUT of INDEX");
        }
        for(int i = 0; i < this->sz; ++i){
            if(&data[i] == it){
                for(int j = i; j < this->sz; ++j){
                    if(j == this->sz-1){
                        it = this->begin();
                        this->pop_back();
                        return;
                    }
                    std::swap(data[j+1], data[j]);
                }

            }
        }
    }
    catch (std::invalid_argument& error){
        std::cerr << error.what() << std::endl;
    }
}
//__________________________________________

// ________________Erase__________________________
template<class T>
void XYVector<T> :: erase(Iterator& it1, Iterator& it2){
    try{
        if(it2 >= &data[this->sz]|| it1 > it2) {
            throw std::invalid_argument("OUT of INDEX");
        }
        int index1, index2;
        for(int i = 0; i < this->sz; ++i){
            if(&data[i] == it1){
                index1 = i;
            }
            if(&data[i] == it2){
                index2 = i;
            }
        }
        for(int i = index2-1; i >= index1; --i){
            std::swap(data[i+1], data[i]);
        }

//        for(int j = 0; j <this->sz; ++j){
//            std::cout << data[j] << " ";
//        }
//        std::cout << std::endl;

        for(int i = this->sz-1; i > index2; --i){
            for(int j = this->sz-2; j > index2 - (index2 - index1); --j){
                std::swap(data[j+1], data[j]);
            }
//            for(int j = 0; j <this->sz; ++j){
//                std::cout << data[j] << " ";
//            }
//            std::cout << std::endl;
        }
        for(int i = 0; i < index2 - index1; ++i){
            this->pop_back();
        }
        it1 -= (index2 - index1 + 1);
        it2 -= (index2 - index1 + 1);
    }
    catch (std::invalid_argument& error){
        std::cerr << error.what() << std::endl;
    }
}
//__________________________________________



//__________________Reallocate Memory________________________

template<class T>
void XYVector<T> :: reAllocate(size_t newCapacity){

    T* newData = new T[newCapacity];
    if(newCapacity < this->sz)
        this->sz = newCapacity;

    for(size_t i = 0; i < this->sz; ++i){
        newData[i] = std::move(data[i]);
    }

    delete[] this->data;
    this->data = newData;
    this->capacity = newCapacity;

    newData = nullptr;
}

//_________________Print Function_________________________

template<class U>
std::ostream& operator<<(std::ostream& out, XYVector<U> data){
    for(size_t i = 0; i < data.Size(); ++i){
        out << data[i] << " ";
    }
    out << std::endl;
    return out;
}
