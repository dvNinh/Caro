#pragma once

struct Coordinate {
    int x, y;
    Coordinate operator+(const Coordinate& _other) const {
        return { this->x + _other.x, this->y + _other.y };
    }
    Coordinate operator-(const Coordinate& _other) const {
        return { this->x - _other.x, this->y - _other.y };
    }
    bool operator== (const Coordinate& _other) const {
        if (x == _other.x && y == _other.y) return true;
        else return false;
    }
    bool operator!= (const Coordinate& _other) const {
        if (*this == _other) return false;
        else return true;
    }
};