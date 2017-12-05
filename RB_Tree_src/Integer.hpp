#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <string>

template<class T>
class intWrapperImpl {
    T value;
public:
    typedef T value_type;
    intWrapperImpl() :value() {}
    explicit intWrapperImpl(T v) :value(v) {}
    template<class U> explicit intWrapperImpl(const intWrapperImpl<U>& rhs) : value(static_cast<U>(rhs)) {}
    operator T() const {return value;}
    //modifiers
    intWrapperImpl& operator=(std::nullptr_t) {*this=-1; return *this;}
    template<class U> intWrapperImpl& operator=(U v) {value=v; return *this;}
    template<class U> intWrapperImpl& operator+=(U v) {value+=v; return *this;}
    template<class U> intWrapperImpl& operator-=(U v) {value-=v; return *this;}
    template<class U> intWrapperImpl& operator*=(U v) {value*=value; return *this;}
    template<class U> intWrapperImpl& operator/=(U v) {value/=value; return *this;}
    template<class U> intWrapperImpl& operator%=(U v) {value%=value; return *this;}
    intWrapperImpl& operator++() {++value; return *this;}
    intWrapperImpl& operator--() {--value; return *this;}
    intWrapperImpl operator++(int) {return intWrapperImpl(value++);}
    intWrapperImpl operator--(int) {return intWrapperImpl(value--);}
    intWrapperImpl& operator&=(T v) {value&=v; return *this;}
    intWrapperImpl& operator|=(T v) {value|=v; return *this;}
    intWrapperImpl& operator^=(T v) {value^=v; return *this;}
    template<class U> intWrapperImpl& operator<<=(U v) {value<<=v; return *this;}
    template<class U> intWrapperImpl& operator>>=(U v) {value>>=v; return *this;}
    //accessors
    intWrapperImpl operator+() const {return intWrapperImpl(+value);}
    intWrapperImpl operator-() const {return intWrapperImpl(-value);}
    intWrapperImpl operator!() const {return intWrapperImpl(!value);}
    intWrapperImpl operator~() const {return intWrapperImpl(~value);}
    //friends
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator+(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)+=v;}
    friend intWrapperImpl operator+(T v, intWrapperImpl iw) {return intWrapperImpl(v)+=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator-(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)-=v;}
    friend intWrapperImpl operator-(T v, intWrapperImpl iw) {return intWrapperImpl(v)-=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator*(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)*=v;}
    friend intWrapperImpl operator*(T v, intWrapperImpl iw) {return intWrapperImpl(v)*=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator/(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)/=v;}
    friend intWrapperImpl operator/(T v, intWrapperImpl iw) {return intWrapperImpl(v)/=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator%(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)%=v;}
    friend intWrapperImpl operator%(T v, intWrapperImpl iw) {return intWrapperImpl(v)%=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator&(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)&=v;}
    friend intWrapperImpl operator&(T v, intWrapperImpl iw) {return intWrapperImpl(v)&=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator|(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)|=v;}
    friend intWrapperImpl operator|(T v, intWrapperImpl iw) {return intWrapperImpl(v)|=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator^(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)^=v;}
    friend intWrapperImpl operator^(T v, intWrapperImpl iw) {return intWrapperImpl(v)^=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator<<(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)<<=v;}
    friend intWrapperImpl operator<<(T v, intWrapperImpl iw) {return intWrapperImpl(v)<<=iw;}
    template<class U, class R=typename std::common_type<T,U>::type>
    friend intWrapperImpl<R> operator>>(intWrapperImpl iw, intWrapperImpl<U> v) {return intWrapperImpl<R>(iw)>>=v;}
    friend intWrapperImpl operator>>(T v, intWrapperImpl iw) {return intWrapperImpl(v)>>=iw;}
};
typedef intWrapperImpl<int> intWrapper;
typedef intWrapperImpl<unsigned> uintWrapper;
typedef intWrapperImpl<short> shortWrapper;
typedef intWrapperImpl<char> charWrapper;
typedef intWrapperImpl<unsigned long long> ullWrapper;






#endif //INTEGER_H
