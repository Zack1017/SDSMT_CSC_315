
#ifndef SET_H
#define SET_H

#include <vector>
#include <string>
#include <initializer_list>
#include <iosfwd>
#include <algorithm>
#include <ostream>
#include <sstream>
template<typename T>
class Set
{
    public: 
        Set(); 
        Set(const Set& other); 
        ~Set();

        Set& operator =(const Set& other);

        Set(std::initializer_list<T> init);

        int size() const; 
        bool empty() const
        {
            return size() ==0; 
        }
        bool contains(const T& value) const; 

        bool insert(const T& value);
        bool remove(const T& value);
        void clear(); 

        bool subsetOf(const Set& other) const;
        bool equals(const Set& other) const; 

        Set unionWith(const Set& other) const; 
        Set intersectionWith(const Set& other) const; 
        Set differenceWith(const Set& other) const; 
        Set symmetricDifferebceWith(const Set& other) const; 

        void display(std::ostream& os) const; 
        std::string toString() const;

        Set operator|(const Set& other) const; 
        Set operator&(const Set& other) const; 
        Set operator-(const Set& other) const; 
        Set operator/(const Set& other) const; 
        
        bool operator<=(const Set& other) const; 
        bool operator==(const Set& other) const; 
        bool operator!=(const Set& other) const; 

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const Set<U>& s);

    private: 
    std:: vector<T> data;

    typename std::vector<T>::const_iterator cfind(const T& value) const; 
    typename std::vector<T>::iterator findMutale(const T& value);

    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    iterator begin() { return data.begin(); }
    iterator end()   { return data.end();   }
    const_iterator begin() const { return data.begin(); }
    const_iterator end()   const { return data.end();   }

};
#endif