#ifndef _POLYNOMIAL_HPP_
#define _POLYNOMIAL_HPP_

#include <initializer_list>
#include <algorithm>
#include <iostream>

/**
 * @brief Polynomial class P_Order[CoefType].
 * 
 * @tparam Order Order >= 0
 * @tparam CoefType 
 */
template<int Order, typename CoefType>
class Polynomial {
private:
    CoefType a[Order + 1];
public:

    Polynomial() {
        std::fill(a, a + Order + 1, CoefType{});
    }

    Polynomial(std::initializer_list<CoefType> l) {
        auto it = l.begin();
        int i = 0;
        for (; i <= Order && it != l.end(); ++i, ++it) {
            a[i] = *it;
        }
        for (; i <= Order; ++i) a[i] = CoefType{};
    }

    bool operator==(const Polynomial &p) const {
        for (int i = 0; i <= Order; ++i) {
            if (a[i] != p.a[i]) return false;
        }
        return true;
    }

#define ELMWISE_BINARY_OP(OpName, Op, OpNameEq, OpEq) \
    Polynomial OpName (const Polynomial &p) const { \
        Polynomial ret; \
        for (int i = 0; i <= Order; ++i) { \
            ret.a[i] = a[i] Op p.a[i]; \
        } \
        return ret; \
    } \
\
    Polynomial& OpNameEq (const Polynomial &p) { \
        for (int i = 0; i <= Order; ++i) { \
            a[i] OpEq p.a[i]; \
        } \
        return *this; \
    } \

    ELMWISE_BINARY_OP(operator+, +, operator+=, +=)
    ELMWISE_BINARY_OP(operator-, -, operator-=, -=)
#undef ELMWISE_BINARY_OP

#define RIGHT_BROADCAST_OP(OpName, Op, OpNameEq, OpEq) \
    template<typename T> \
    Polynomial OpName (const T &u) const { \
        Polynomial ret; \
        for (int i = 0; i <= Order; ++i) { \
            ret.a[i] = a[i] Op u; \
        } \
        return ret; \
    } \
\
    template<typename T> \
    Polynomial& OpNameEq (const T &u) { \
        for (int i = 0; i <= Order; ++i) { \
            a[i] OpEq u; \
        } \
        return *this; \
    }
    
    RIGHT_BROADCAST_OP(operator*, *, operator*=, *=)
    RIGHT_BROADCAST_OP(operator/, /, operator/=, /=)

#undef RIGHT_BROADCAST_OP

    /**
     * @brief This multiplication is modulo-x^(Order+1).
     * That is, higher order terms in the result will be 
     * discarded. You should use it when you are sure
     * the result is still in P_Order.
     * 
     */
    Polynomial operator*(const Polynomial &p) const {
        Polynomial res;
        for (int i = 0; i <= Order; ++i) {
            for (int j = 0; j <= i; ++j) res.a[i] += a[j] * p.a[i - j];
        }
        return res;
    }

    template<typename T>
    CoefType eval(const T &x) const {
        CoefType ret = a[Order];
        for (int i = Order - 1; i >= 0; --i) {
            ret = ret * x + a[i];
        }
        return ret;
    }

    Polynomial derivative() const {
        Polynomial ret;
        for (int i = 1; i <= Order; ++i) {
            ret.a[i - 1] = a[i] * i;
        }
        return ret;
    }

    friend std::ostream& operator<<(std::ostream &os, const Polynomial &p) {
        os << 0 << '[' << p.a[0];
        for (int i = 1; i <= Order; ++i) {
            os << ", " << p.a[i];
        }
        os << ']' << Order;
        return os;
    }

    CoefType& operator[](size_t i) {
        return a[i];
    }

    const CoefType & operator[](size_t i) const {
        return a[i];
    }

};

#endif
