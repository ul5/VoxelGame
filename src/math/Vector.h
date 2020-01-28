#include <stdint.h>
#include <cmath>

namespace math {

    template <int T>
    class Vector {
    private:
        float data[T];

    public:
        Vector() { for(int i = 0; i < T; i++) data[i] = 0; }

        inline void operator[](int index) {return data[index];}
        inline Vector<T> operator+(Vector<T> o) { Vector<T> n; for(int i = 0; i < T; i++) n[i] = data[i] + o[i]; return n; }
        inline Vector<T> operator-(Vector<T> o) { Vector<T> n; for(int i = 0; i < T; i++) n[i] = data[i] - o[i]; return n; }

        inline void operator+=(Vector<T> o) { for(int i = 0; i < T; i++) data[i] += o[i]; }
        inline void operator-=(Vector<T> o) { for(int i = 0; i < T; i++) data[i] -= o[i]; }

    };

    typedef Vector<2> vec2;
    typedef Vector<3> vec3;
    typedef Vector<4> vec4;

}