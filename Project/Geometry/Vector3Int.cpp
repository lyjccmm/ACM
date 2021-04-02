#ifndef __VECTOR3_INT_H__
#define __VECTOR3_INT_H__
template<typename T = int>
struct Vector3Int {
    T x;
    T y;
    T z;
    Vector3Int(): x(0), y(0), z(0) {}
    Vector3Int(const T _x, const T _y, const T _z): x(_x), y(_y), z(_z) {}
	explicit Vector3Int(const T *a): x(a[0]), y(a[1]), z(a[2]) {}
    // Vector3Int(const Vector3Int& v): x(v.x), y(v.y), z(v.z) {}
    // inline void operator =(const Vector3Int& v) { x = v.x; y = v.y; z = v.z; }
    inline Vector3Int operator -() const { return Vector3Int(-x, -y, -z); }
    inline Vector3Int operator +(const Vector3Int& v) const { return Vector3Int(x+v.x, y+v.y, z+v.z); }
    inline Vector3Int operator -(const Vector3Int& v) const { return Vector3Int(x-v.x, y-v.y, z-v.z); }
    inline Vector3Int operator *(const Vector3Int& v) const { return Vector3Int(x*v.x, y*v.y, z*v.z); }
    inline Vector3Int operator *(T d) const { return Vector3(x*d, y*d, z*d); }
    inline Vector3Int operator /(T d) const { return Vector3(x/d, y/d, z/d); }
    inline bool operator ==(const Vector3Int& v) const { return x==v.x && y==v.y && z==v.z; }
    inline bool operator !=(const Vector3Int& v) const { return x!=v.x || y!=v.y || z!=v.z; }
    inline Vector3Int& operator +=(const Vector3Int& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    inline Vector3Int& operator -=(const Vector3Int& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
    inline Vector3Int& operator *=(const Vector3Int& v) { x*=v.x; y*=v.y; z*=v.z; return *this; }
    inline Vector3Int& operator *=(T d) { x *= d; y *= d; z *= d; return *this; }
    inline Vector3Int& operator /=(T d) { x /= d; y /= d; z /= d; return *this; }
};

#endif //__VECTOR3_INT_H__