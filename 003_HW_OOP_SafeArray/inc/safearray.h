#pragma once
#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#include <iostream>
#include <cassert>
#include <ctime>

//#define USE_RANDOM
#ifndef USE_RANDOM
    #define USE_INCREMENT
#else
    #ifndef _RANDOM_H_
    #define _RANDOM_H_
        #include <random>
    #endif // _RANDOM_H_
#endif

class SafeArray
{
private:
          int    * ptrDynArray;
          size_t   length;
          size_t   capacity = 0;
    const size_t   MIN_CAP  = 2;


    bool check_boundaries(size_t index)
    {
      if (0 <= index && index < get_size())
          return true;
      return false;
    }

    SafeArray& mem_alloc(const size_t size)
    {
        if(!capacity)
        {
            if(size <= 0)
            {
                this -> length      = 0;
                this -> ptrDynArray = nullptr;
            }
            else
            {
                this -> length      = size;
                this -> capacity    = MIN_CAP + (size * size/2);
                this -> ptrDynArray = new int[capacity];
            }
        }
        else
        {
            if(length < capacity * 2)
                capacity *= 2;
            else
                capacity  = capacity * 2 * length / capacity;

            int * ptrTmpResize   = new int[capacity];
            for(size_t i = 0; i < length; i++)
                ptrTmpResize[i]  = ptrDynArray[i];
            this -> ptrDynArray = ptrTmpResize;
        }
        return *this;
    }
public:
             SafeArray();                                                           // DEFAULT CONSTRUCTOR //
    explicit SafeArray(const size_t       size) noexcept;                                   // CONSTRUCTOR //
    explicit SafeArray(const SafeArray &  copyObj) noexcept;                           // COPY CONSTRUCTOR //
    explicit SafeArray(      SafeArray && moveObj) noexcept;                           // MOVE CONSTRUCTOR //

    ~SafeArray(){if(this -> ptrDynArray != nullptr) delete[] ptrDynArray;}                   // DISTRUCTOR //

    SafeArray& operator = (const SafeArray &  copyObj) noexcept; // COPY ASSIGNMENT OPERATOR (OVERLOAD = ) //
    SafeArray& operator = (      SafeArray && moveObj) noexcept; // MOVE ASSIGNMENT OPERATOR (OVERLOAD = ) //

          int& operator [](size_t index);
    const int& operator [](size_t index) const {return ptrDynArray[index];}

          int& operator * () const {return * ptrDynArray;}
          int* operator ->() const {return   ptrDynArray;}

    void   autoFill();
    void   manuallyFill();

    void   push_front (      int    value);
    void   push_at    (const size_t index,  int    value);
    void   push_into  (      size_t begin,  size_t end);
    void   push_back  (      int    value);

    void   pop_front  ();
    void   pop_at     (const size_t index);
    void   pop_into   (      size_t begin,  size_t end);
    void   pop_back   ();

    void   print_front();
    void   print_at   (const size_t index);
    void   print_range(      size_t begin,  size_t end);
    void   print_all  ();
    void   print_back ();

    bool   isEmpty    () const {return ptrDynArray == nullptr;};
    size_t get_size   ();
    void   swap       (      size_t first,  size_t second) noexcept;

    void   erase      ();
};
#endif // SAFEARRAY_H
