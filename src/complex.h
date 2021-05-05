#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

class C{
private:
    double x;
    double y;
public:

    C(const double real, const double imaginary)
        : x(real), y(imaginary) {}

    C(const C& rhs)
        : x(rhs.x), y(rhs.y) {}

    C(const double real = 0): x(real), y(0) {}

    C& operator=(const C& rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        return *this;
    }

    C operator+(const C& rhs){
        return C(this->x+rhs.x, this->y + rhs.y);
    }

    C operator-(const C& rhs){
        return C(this->x - rhs.x, this->y - rhs.y);
    }

    C operator*(const C& rhs){
        return C(this->x*rhs.x-this->y*rhs.y, this->x*rhs.y+this->y*rhs.x);
    }

    C operator/(const double& n){
        return C(this->x/n, this->y/n);
    }

    C operator/(const C& rhs){
        auto real = (x*rhs.x+y*rhs.y)/(rhs.x*rhs.x+rhs.y*rhs.y);
        auto imag = (rhs.x*y-x*rhs.y)/(rhs.x*rhs.x+rhs.y*rhs.y);
        return C(real, imag);
    }

    C& operator+=(const C& rhs){
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    
    C& operator-=(const C& rhs){
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    C& operator*=(const C& rhs){
        double prev_x = this->x;
        this->x = this->x*rhs.x-this->y*rhs.y;
        this->y = prev_x*rhs.y+this->y*rhs.x;
        return *this;
    }
    
    C operator/=(const double& n){
        this->x /= n;
        this->y /= n;
        return *this;
    }

    bool operator==(const C& rhs){
        if (this->x == rhs.x && this->y == rhs.y)
            return true;
        else
            return false;
    }

    bool operator!=(const C& rhs){
        return !(*this==rhs);
    }


    double Re() const {
        return this->x;
    }

    double Im() const {
        return this->y;
    }

    std::string getText() const {
        if (this->y == 0){
            return std::to_string(this->x).substr(0,std::to_string(this->x).length()-5);
        } else if (this->x == 0){
            std::string str = std::to_string(this->y).substr(0,std::to_string(this->y).length()-5);
            str += 'i';
            return str;
        } else {
            bool is_positive = this->y > 0;
            std::string str = std::to_string(this->x).substr(0,std::to_string(this->x).length()-5);
            str+= (is_positive) ? '+': '-';
            str+= std::to_string(std::abs(this->y)).substr(0,std::to_string(std::abs(this->y)).length()-5) + 'i';
            return str;
        }
    }

};

std::ostream& operator<<(std::ostream& os, const C& c)
{   
    os<<std::fixed<<std::setw(10)<<std::left<<c.getText();
    return os;
}