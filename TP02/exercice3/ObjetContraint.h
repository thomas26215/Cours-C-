#ifndef OBJETCONTRAINT_H
#define OBJETCONTRAINT_H

#include <stdexcept>

template <class T>
class ObjetContraint {
public:
    ObjetContraint(T val, T min, T max) {
        if (min < max) {
            m_min = min;
            m_max = max;
        } else {
            m_min = max;
            m_max = min;
        }
        setVal(val);
    }

    ObjetContraint(const ObjetContraint& autre) 
        : m_val(autre.m_val), m_min(autre.m_min), m_max(autre.m_max) {}

    ~ObjetContraint() {}

    inline const T& getMin() const { return m_min; }
    inline const T& getMax() const { return m_max; }
    inline const T& getVal() const { return m_val; }

    void setVal(const T& val) {
        if (val < m_min) {
            throw ("La valeur est inférieure au minimum");
        } else if (m_max < val) {
            throw ("La valeur est supérieure au maximum");
        } else {
            m_val = val;
        }
    }

    operator T() const { return m_val; }

private:
    T m_val;
    T m_min;
    T m_max;
};

#endif /* OBJETCONTRAINT_H */