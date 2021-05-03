#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

class C{
private:
    double x;
    double y;
public:

    C(double real, double imaginary)
        : x(real), y(imaginary) {}

    C(const C& rhs)
        : x(rhs.x), y(rhs.y) {}

    C(double real): x(real), y(0) {}
    C(int real): x(real), y(0) {}

    C(): x(0),y(0) {}

    C& operator=(const double& rhs){
        this->x = rhs;
        this->y = 0;
        return *this;
    }

    C& operator=(const C& rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        return *this;
    }

    C& operator+(const C& rhs){
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    C& operator+=(const C& rhs){
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    C& operator-(const C& rhs){
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    C& operator-=(const C& rhs){
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    C& operator*(const C& rhs){
        double prev_x = this->x;
        this->x = this->x*rhs.x-this->y*rhs.y;
        this->y = prev_x*rhs.y+this->y*rhs.x;
        return *this;
    }
    C& operator*(const double& rhs){
        this->x *= rhs;
        this->y *= rhs;
        return *this;
    }
    C& operator*(const int& rhs){
        this->x *= rhs;
        this->y *= rhs;
        return *this;
    }
    C& operator*=(const C& rhs){
        this->x = this->x*rhs.x-this->y*rhs.y;
        this->y = this->x*rhs.y+this->y*rhs.x;
        return *this;
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
        }
        else {
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
    // os<<std::setprecision(1);
    // if (c.Im() == 0){
    //     os << c.Re();
    // } else if (c.Re() == 0){
    //     if (c.Im() < 0) os << '-';
    //     os << std::abs(c.Im()) << 'i';
    // } else {
    //     os << c.Re() << (c.Im() > 0 ? "+": "-") << std::abs(c.Im()) << 'i';
    // }
    // return os; 
    return os;
}