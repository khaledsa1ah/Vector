#pragma once
#include <iostream>

template<typename XYVector>
class XYVectorIterator{
public:
    using ValueType = typename XYVector :: ValueType;
    using PointerType = ValueType*;
    using RefrenceType = ValueType&;
private:
    PointerType ptr;
public :
    XYVectorIterator(PointerType ptr){
        this->ptr = ptr;
    }

    XYVectorIterator& operator++(){
        ptr++;
        return *this;
    }

    const XYVectorIterator& operator++(int){
        XYVectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    XYVectorIterator& operator--(){
        ptr--;
        return *this;
    }

    XYVectorIterator& operator--(int){
        XYVectorIterator Iterator = *this;
        --(*this);
        return Iterator;
    }

    XYVectorIterator& operator+(int x){
        this->ptr += x;
        return *this;
    }

    XYVectorIterator& operator+=(int x){
        this->ptr += x;
        return *this;
    }

    XYVectorIterator& operator-(int x){
        this->ptr -= x;
        return *this;
    }

    XYVectorIterator& operator-=(int x){
        this->ptr -= x;
        return *this;
    }

    bool operator==(const XYVectorIterator& anotherIterator){
        if(this->ptr == anotherIterator.ptr)return true;
        return false;
    }

    bool operator!=(const XYVectorIterator& anotherIterator){
        return !(*this == anotherIterator);
    }

    bool operator<(const XYVectorIterator& anotherIterator){
        return (this->ptr < anotherIterator.ptr);
    }
    bool operator>(const XYVectorIterator& anotherIterator){
        return (this->ptr > anotherIterator.ptr);
    }

    bool operator>=(const XYVectorIterator& anotherIterator){
        return (this->ptr >= anotherIterator.ptr);
    }

    bool operator<=(const XYVectorIterator& anotherIterator){
        return (this->ptr <= anotherIterator.ptr);
    }

    RefrenceType operator[](size_t index){
        return *(ptr + index);
    }

    RefrenceType operator*(){
        return *ptr;
    }
    PointerType operator&(){
        return ptr;
    }

    PointerType operator->(){
        return ptr;
    }

};



template <class T>
class XYVector{
private:
    size_t sz = 0;
    size_t capacity = 0;
    T* data = nullptr;

public:
    using ValueType = T;
    using Iterator = XYVectorIterator<XYVector<T>>;

public:
    XYVector();
    ~XYVector();
    XYVector(size_t sz);
    XYVector(T* arr, size_t n);
    XYVector(const XYVector& anotherVector);
    XYVector(XYVector&& anotherVector);
    XYVector<T>& operator=(const XYVector& anotherVector);
    XYVector<T>& operator=(XYVector&& anotherVector);

    // Access Operations
    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    // Comparison Operators
    bool operator==(const XYVector<T>& anotherVector);
    bool operator<(const XYVector<T>& anotherVector);
    bool operator>(const XYVector<T>& anotherVector);

    // Capacity Operations
    size_t Size() const;
    size_t Capacity() const;
    void reAllocate(size_t newCapacity);
    bool empty();

    void push_back(const T& value);
    T pop_back();
    void insert(Iterator& it, T newValue);
    void erase(Iterator& it);
    void erase(Iterator& it1, Iterator& it2);
    void clear();


    Iterator begin(){
        return Iterator(data);
    }

    Iterator end(){
        return Iterator(data + sz);
    }


    template<class U>
    friend std::ostream& operator<<(std::ostream& out, XYVector<U> data);
};
