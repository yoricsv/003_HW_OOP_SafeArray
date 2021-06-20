#include "safearray.h"

// DEFAULT CONSTRUCTOR //
SafeArray::SafeArray()                                    : length (0)
{
    mem_alloc(length);
}

// CONSTRUCTOR //
SafeArray::SafeArray(const size_t       size) noexcept    : length (size)
{
    mem_alloc(size);
}

// COPY CONSTRUCTOR //
SafeArray::SafeArray(const SafeArray &  copyObj) noexcept : length (copyObj.length)
{
    mem_alloc(copyObj.length);
    for(size_t i = 0; i < get_size(); i++)
        this -> ptrDynArray[i]  = copyObj.ptrDynArray[i];
}

// MOVE CONSTRUCTOR //
SafeArray::SafeArray(      SafeArray && moveObj) noexcept : length (moveObj.length)
{
    this -> length = moveObj.length;

    for(size_t i = 0; i < length; i++)
        this -> ptrDynArray[i]  = moveObj.ptrDynArray[i];

    moveObj.length      = 0;
    moveObj.ptrDynArray = nullptr;
}

// COPY ASSIGNMENT OPERATOR (OVERLOAD = ) //
SafeArray& SafeArray::operator = (const SafeArray & copyObj) noexcept
{
    if (this != &copyObj)
    {
        if(this -> ptrDynArray != nullptr)
            delete[] this -> ptrDynArray;

        mem_alloc(copyObj.length);

        for(size_t i = 0; i < length; i++)
            this -> ptrDynArray[i]  = copyObj.ptrDynArray[i];
    }
    return *this;
}

// MOVE ASSIGNMENT OPERATOR (OVERLOAD = ) //
SafeArray& SafeArray::operator = (      SafeArray && moveObj) noexcept
{
    if (this != &moveObj)
    {
        if(this -> ptrDynArray != nullptr)
            delete[] this -> ptrDynArray;

        this -> length      = moveObj.length;

        for(size_t i = 0; i < length; i++)
            this -> ptrDynArray[i]  = moveObj.ptrDynArray[i];

        moveObj.length      = 0;
        moveObj.ptrDynArray = nullptr;
    }
    return *this;
}

// SQUARE BRACKETS (OVERLOAD [] ) //
int& SafeArray::operator [](size_t index)
{
    //    assert(!check_boundaries(index));
        if (check_boundaries(index))
            return ptrDynArray[index];
        else
        {
            std::cerr << "Out of range! ";
            std::cerr << "Maximum size of your array is ";
            std::cerr << get_size() << std::endl;
            return ptrDynArray[0];
        }
}

// VARIOUS PUSH METHODS //
void SafeArray::push_front (      int    value)
{
    if(!get_size())
    {
        mem_alloc(1);
        this -> ptrDynArray[0] = value;
    }
    else
    {
        if(capacity < (this -> length += 1))
            mem_alloc(capacity);

        for(size_t i = get_size() - 1 ; get_size() - 1 > 0; i--)
           this -> ptrDynArray[i] = ptrDynArray[i - 1];
    }
}
void SafeArray::push_at    (const size_t index, int    value)
{
    if (check_boundaries(index))
        ptrDynArray[index] = value;
    else
    {
        std::cerr << "WARRNING! The PUSH function can't do this.\n";
        std::cerr << "\tOut of range! \n";
        std::cerr << "Maximum size of your array is " << get_size() << std::endl;
    }
}
void SafeArray::push_into  (      size_t begin, size_t end)
{
    if (check_boundaries(begin) && check_boundaries(end))
    {
        if(end < begin)
            std::swap(begin, end);

        size_t gap = end - begin;

        if(capacity < (this -> length += gap))
            mem_alloc(capacity);

        for(size_t i = get_size() - 1 ; i <= begin; i--)
            this -> ptrDynArray[i] = ptrDynArray[i - gap];

        int value = 0;
        for(size_t i = begin; i < end; i++)
        {
            std::cout << "You need to fill in " << gap << "position." << std::endl;
            std::cout << "Type value (Press Enter to type next)." << std::endl;
            std::cout << "To left - " << gap-- << std::endl;

            std::cin >> value;

            ptrDynArray[i] = value;
        }
    }
    else
    {
        std::cerr << "WARRNING! The PUSH function can't do this.\n";
        std::cerr << "\tOut of range! \n";
        std::cerr << "Maximum size of your array is " << get_size() << std::endl;
    }
}
void SafeArray::push_back  (      int    value)
{
    if(!get_size())
    {
        mem_alloc(1);
        this -> ptrDynArray[0] = value;
    }
    else
    {
        if(capacity < (this -> length += 1))
            mem_alloc(capacity);

        ptrDynArray[get_size()] = value;
    }
}

// VARIOUS POP METHODS //
void SafeArray::pop_front  ()
{
    if(!isEmpty())
    {
        for(size_t i = 0; i < get_size(); i++)
            ptrDynArray[i] = ptrDynArray[i + 1];
        this -> length--;
        if(!length)
        {
            this -> ptrDynArray = nullptr;
            this -> capacity    = 0;
        }
    }
    else
        std::cerr << "WARRNING! The POP function can't do this. Array is EMPTY!\n";
}
void SafeArray::pop_at     (const size_t index)
{
    if(!isEmpty())
    {
        if (check_boundaries(index))
        {
            for(size_t i = index; i < get_size(); i++)
                ptrDynArray[i] = ptrDynArray[i + 1];
            this -> length--;
            if(!length)
            {
                this -> ptrDynArray = nullptr;
                this -> capacity    = 0;
            }
        }
        else
        {
            std::cerr << "WARRNING! The POP function can't do this.\n";
            std::cerr << "\tOut of range! \n";
            std::cerr << "Maximum size of your array is " << get_size() << std::endl;
        }
    }
    else
        std::cerr << "WARRNING! The POP function can't do this. Array is EMPTY!\n";
}
void SafeArray::pop_into   (      size_t begin, size_t end)
{
    if(!isEmpty())
    {
        if (check_boundaries(begin) && check_boundaries(end))
        {
            if(begin > end)
                std::swap(begin, end);

            size_t gap = end - begin;

            for(size_t i = begin; i < get_size() - end; i++)
                ptrDynArray[i] = ptrDynArray[i + gap];

            this -> length -= gap;
            if(!length)
            {
                this -> ptrDynArray = nullptr;
                this -> capacity    = 0;
            }
        }
        else
        {
            std::cerr << "WARRNING! The POP function can't do this.\n";
            std::cerr << "\tOut of range! \n";
            std::cerr << "Maximum size of your array is " << get_size() << std::endl;
        }
    }
    else
        std::cerr << "WARRNING! The POP function can't do this. Array is EMPTY!\n";
}
void SafeArray::pop_back   ()
{
    if(!isEmpty())
    {
        this -> length--;
        if(!length)
        {
            this -> ptrDynArray = nullptr;
            this -> capacity    = 0;
        }
    }
    else
        std::cerr << "WARRNING! The POP function can't do this. Array is EMPTY!\n";
}

// VARIOUS DISPLAY METHODS //
void SafeArray::print_front()
{
    if(!isEmpty())
    {
        std::cout << "The first element contains the value is " << ptrDynArray[0] << "  \t";
        std::cout << "Address: "<< this << std::endl;
    }
    else
        std::cerr << "WARRNING! The PRINT function can't do this. Array is EMPTY!\n";
}
void SafeArray::print_at   (const size_t index)
{
    if (check_boundaries(index))
    {
        std::cout << "Element [" << index << "] = " << ptrDynArray[index] << "  \t";
        std::cout << "Address: "<< this + index << std::endl;
    }
    else
    {
        std::cerr << "WARRNING! The PRINT function can't do this.\n";
        std::cerr << "\tOut of range! \n";
        std::cerr << "Maximum size of your array is " << get_size() << std::endl;
    }
}
void SafeArray::print_range(      size_t begin,    size_t end)
{
    if(!isEmpty())
    {
        if (check_boundaries(begin) && check_boundaries(end))
        {
            if(begin > end)
                std::swap(begin, end);

            for(size_t i = begin; i < end; i++)
            {
                std::cout << "Element [" << i << "] = " << ptrDynArray[i] << "  \t";
                std::cout << "Address: "<< this + i << std::endl;
            }
        }
        else
        {
            std::cerr << "WARRNING! The PRINT function can't do this.\n";
            std::cerr << "\tOut of range! \n";
            std::cerr << "Maximum size of your array is " << get_size() << std::endl;
        }
    }
    else
        std::cerr << "WARRNING! The PRINT function can't do this. Array is EMPTY!\n";
}
void SafeArray::print_all  ()
{
    if(!isEmpty())
        for (size_t i = 0; i < get_size(); i++)
        {
            std::cout << "Element [" << i << "] = " << ptrDynArray[i] << "  \t";
            std::cout << "Address: "<< this + i << std::endl;
        }
    else
        std::cerr << "WARRNING! The PRINT function can't do this. Array is EMPTY!\n";
}
void SafeArray::print_back ()
{
    if(!isEmpty())
    {
        std::cout << "Element [" << get_size() - 1 << "] = " << ptrDynArray[get_size() - 1] << "  \t";
        std::cout << "Address: "<< this + get_size() << std::endl;
    }
    else
        std::cerr << "WARRNING! The PRINT function can't do this. Array is EMPTY!\n";
}

// THE SAME AS STD::SIZEOF METHOD //
size_t SafeArray::get_size ()
{
    if(!isEmpty())
        return this -> length;
    else
        std::cerr << "ERROR! Array is EMPTY! Length is Zero.\n";
    return 0;
}

// THE SAME AS STD::SWAP METHOD //
void SafeArray::swap       (      size_t first, size_t second) noexcept
{
    if (check_boundaries(first) && check_boundaries(second))
    {
        int tmp             = ptrDynArray[first];
        ptrDynArray[first]  = ptrDynArray[second];
        ptrDynArray[second] = tmp;
    }
    else
    {
        std::cerr << "WARRNING! The SWAP function can't do this.\n";
        std::cerr << "\tOut of range! \n";
        std::cerr << "Maximum size of your array is " << get_size() << std::endl;
    }
}

// WIPE ARRAY OUT METHOD //
void SafeArray::erase      ()
{
    if(this -> ptrDynArray != nullptr)
        delete[] ptrDynArray;
}


// MANUALLY FILLING METHOD //
void SafeArray::manuallyFill()
{
    for(size_t i = 0; i < get_size(); i++)
    {
        int value = 0;
        std::cout << "To fill array in, enter your value";
        std::cout << " in DynamicArray["<< i <<"]:"<< std::endl;
        std::cin >> value;
        ptrDynArray[i] = value;
    }
    std::cout << "Your array is:\n";

    print_all();
}

// AUTOMATIC FILLING METHOD //
void SafeArray::autoFill()
{
#ifndef USE_INCREMENT
    for(size_t i = 0; i < length; i++)
        ptrDynArray[i] = (32767 * time(0)) % 47;
    printArray();
#else
    srand((int)(time(0)));
    // PSEUDORANDOM GENERATOR //
    for (size_t i = 0; i < get_size(); i++)
        ptrDynArray[i] = rand() % static_cast<int>(get_size());

    print_all();
#endif
}
