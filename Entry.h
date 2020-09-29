#pragma once
template <typename K, typename V>
class Entry
{
private:       // private data
     K _key;   // key
     V _value; // value
public:
     Entry(K k = K(), V v = V()) : _key(k), _value(v) {}    // constructor
     K key() { return _key; }           // get key
     V value() { return _value; }       // get value
     void setKey(K k) { _key = k; }     // set key
     void setValue(V v) { _value = v; } // set value
};