#include "Set.h"


template <typename T>
typename std::vector<T>::const_iterator Set<T>::cfind(const T& value) const 
{
    return std::find(data.begin(), data.end(), value);
}

template <typename T>
typename std::vector<T>::iterator Set<T>::findMutale(const T& value) {
    return std::find(data.begin(), data.end(), value);
}

template <typename T>
Set<T>::Set()
{}

template <typename T>
Set<T>::Set(const Set& other) : data(other.data)
{}

template <typename T>
Set<T>::~Set()
{}

template <typename T>
Set<T>& Set<T>::operator=(const Set& other)
{
    if (this != &other)
    {
        data = other.data;
    }
    return *this;
}

template <typename T>
Set<T>::Set(std::initializer_list<T> init)
{
    for(const T& v : init)
    {
        insert(v);
    }
}

template <typename T>
int Set<T>::size() const
{
    return static_cast<int>(data.size());
}

template <typename T>
bool Set<T>::contains(const T& value) const
{
    return cfind(value) != data.end(); 
}

template <typename T>
bool Set<T>::insert(const T& value)
{
    if(contains(value))
    {
        return false;
    }
    data.push_back(value);
    return true; 
}

template <typename T>
bool Set<T>::remove(const T& value)
{
    auto it = findMutale(value);
    if(it == data.end()) 
    {
        return false;
    }
    data.erase(it);
    return true;
}
template <typename T>
void Set<T>::clear()
{
    data.clear();
}

template <typename T>
bool Set<T>::subsetOf(const Set& other) const{
    for (const T& v: data)
    {
        if (!other.contains(v))
        {
            return false; 
        }
    }
    return true; 
}

template <typename T>
bool Set<T>::equals(const Set& other) const
{
    return (size() == other.size()) && subsetOf(other);
}

template <typename T>
Set<T> Set<T>::unionWith(const Set& other) const
{
    Set out = *this;
    for(const T& v: other.data)
    {
        out.insert(v);
    }
    return out;
}

template <typename T>
Set<T> Set<T>::intersectionWith(const Set& other ) const 
{
    Set out; 
    for(const T& v: data)
    {
        if (other.contains(v)) 
        {
            out.insert(v);
        }
    }
    return out; 
}

template <typename T>
Set<T> Set<T>::differenceWith(const Set& other) const
{
    Set out;
    for(const T& v: data)
    {
        if(!other.contains(v))
        {
            out.insert(v);
        }
    }
    return out; 
}

template <typename T>
Set<T> Set<T>::symmetricDifferebceWith(const Set& other) const
{
    return differenceWith(other).unionWith(other.differenceWith(*this));
}

template <typename T>
void Set<T>::display(std::ostream& os ) const 
{
    os << "{";
    for(size_t i =0; i < data.size(); i++)
    {
        os << data[i];
        if (i + 1 < data.size())
        {
            os << ",";
        } 
    }
    os << "}";
}

template <typename T>
std::string Set<T>::toString() const
{
    std::ostringstream oss; 
    display(oss);
    return oss.str();
}

template <typename T>
Set<T> Set<T>::operator|(const Set& other) const 
{
    return unionWith(other);
}

template <typename T>
Set<T> Set<T>::operator&(const Set& other) const 
{
    return intersectionWith(other);
}

template <typename T>
Set<T> Set<T>::operator-(const Set& other) const 
{
    return differenceWith(other);
}

template <typename T>
Set<T> Set<T>::operator/(const Set& other) const
{
    return symmetricDifferebceWith(other);
}

template <typename T>
bool Set<T>::operator<=(const Set& other) const 
{
    return subsetOf(other);
}

template <typename T>
bool Set<T>::operator==(const Set& other) const 
{
    return equals(other);
}

template <typename T>
bool Set<T>:: operator!=(const Set& other) const 
{
    return !(*this == other);
}

template <typename U>
std::ostream& operator<< (std::ostream& os, const Set<U>& s)
{
    s.display(os);
    return os; 
}
// Explicit template instantiation for all of the data types.
template class Set<int>;

template class Set<double>;

template class Set<std::string>;

template std::ostream& operator<< <int>(std::ostream&, const Set<int>&);
template std::ostream& operator<< <std::string>(std::ostream&, const Set<std::string>&);