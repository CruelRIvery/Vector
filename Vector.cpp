#include "Vector.h"
#include <iostream>
#include <utility>

Vector::Vector(const ValueType* rawArray, const size_t size, float coef):
    _size(size),
    _capacity(size * coef)
{
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < size; i++){
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other){
    *this = other;
}

Vector& Vector::operator=(const Vector& other){
    delete[] _data;

    _size = other._size;
    _capacity = other._capacity;

    _data = new ValueType[_capacity];
    for(size_t i = 0; i < _size; i++){
        _data[i] = other[i];
    }

    return *this;
}

Vector::Vector(Vector&& other) noexcept{
    *this = other;
}

Vector& Vector::operator=(Vector&& other) noexcept{
    delete[] _data;

    _size = std::move(other._size);
    _capacity = std::move(other._capacity);

    _data = new ValueType[_capacity];
    _data = std::move(other._data);

    return *this;
}

Vector::~Vector(){
    delete[] _data;
}

void Vector::pushBack(const ValueType& value){
    if (_size + 1 == _capacity){
        reserve((_size + 1) * _multiplicativeCoef);
    }

    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const ValueType& value){
    if (_size + 1 >= _capacity){
        reserve((_size + 1) * _multiplicativeCoef);
    }

    for (size_t i = _size + 1; i > 0; i--){
        _data[i] = _data[i - 1];
    }
    _data[0] = value;
    _size++;
}

void Vector::insert(const ValueType& value, size_t pos){
    if (_size + 1 >= _capacity){
        reserve((_size + 1) * _multiplicativeCoef);
    }

    for (size_t i = _size + 1; i > pos; i--){
        _data[i] = _data[i - 1];
    }
    _data[pos] = value;
    _size++;
}

void Vector::insert(const ValueType* values, size_t size, size_t pos){
    if (_size + size >= _capacity){
        reserve((_size + size) * _multiplicativeCoef);
    }

    for (size_t i = _size + size; i > pos; i--){
        _data[i] = _data[i - size];
    }

    for (size_t i = 0; i < size; i++){
        _data[pos + i] = values[i];
    }
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos){
    if (_size + vector._size >= _capacity){
        reserve((_size + vector._size) * _multiplicativeCoef);
    }

    for (size_t i = _size + vector._size; i > pos; i--){
        _data[i] = _data[i - vector._size];
    }

    for (size_t i = 0; i < vector._size; i++){
        _data[pos + i] = vector[i];
    }
    _size += vector._size;
}

void Vector::popBack(){
    _size--;
}

void Vector::popFront(){
    for (size_t i = 0; i < _size - 1; i++){
        _data[i] = _data[i + 1];
    }

    _size--;
}

void Vector::erase(size_t pos, size_t count){
    if (pos + count > _size){
        count = _size - pos;
    }

    for (size_t i = pos; i < _size - count; i++){
        _data[i] = _data[i + count];
    }

    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
    erase(beginPos, endPos - beginPos);
}

size_t Vector::size() const{
    return _size;
}

size_t Vector::capacity() const{
    return _capacity;
}

double Vector::loadFactor() const{
    return _size / _capacity;    
}

ValueType& Vector::operator[](size_t idx){
    return _data[idx];
}

const ValueType& Vector::operator[](size_t idx) const{
    return _data[idx];
}

long long Vector::find(const ValueType& value) const{
    size_t idx = -1;
    for (size_t i = 0; i < _size; i++){
        if (_data[i] == value){
            idx = i;
            break;
        }
    }

    return idx;
}

void Vector::reserve(size_t capacity){
    if (capacity > _capacity){
        ValueType* newData = new ValueType[capacity];

        for (size_t i = 0; i < _size; i++){
            newData[i] = _data[i];
        }

        _capacity = capacity;
        delete[] _data;
        _data = newData;
    }
}

void Vector::shrinkToFit(){
    ValueType* newData = new ValueType[_size];

    for (size_t i = 0; i < _size; i++){
        newData[i] = _data[i];
    }

    _capacity = _size;
    delete[] _data;
    _data = newData;
}

Vector::Iterator::Iterator(ValueType* ptr):
    _ptr(ptr)
{}

ValueType& Vector::Iterator::operator*(){
    return *_ptr;
}

const ValueType& Vector::Iterator::operator*() const{
    return *_ptr;
}

ValueType* Vector::Iterator::operator->(){
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++(){
    _ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int){
    _ptr++;
    return *this;
}

bool Vector::Iterator::operator==(const Iterator& other) const{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const{
    return _ptr != other._ptr;
}

Vector::Iterator Vector::begin(){
    return Iterator(_data);
}

Vector::Iterator Vector::end(){
    return Iterator(_data + _size);
}

void Vector::print(){
    for (size_t i = 0; i < _size; i++){
        std:: cout << _data[i] << " ";
    }
    std::cout << std::endl;
}
