#include <iostream>
#include <vector>
#include <utility>
#include <tuple>



template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> _Numbers;

public:
    Matrix(std::vector<std::vector<T>> numbers) {
        _Numbers = numbers;
    }

    std::pair<size_t, size_t> size() const {
        std::pair<size_t, size_t> res;
        if (_Numbers.size() > 0) {
            res.first = _Numbers.size();
            res.second = _Numbers[0].size();
        } else {
            res.first = 0;
            res.second = 0;
        }
        return res;
    }

    Matrix& transpose() {
        std::vector<std::vector<T>> res;
        for (size_t i = 0; i < _Numbers[0].size(); i++) {
            std::vector<T> str;
            for (size_t j = 0; j < _Numbers.size(); j++) {
                str.push_back(_Numbers[j][i]);
            }
            res.push_back(str);
        }
        _Numbers = res;
        return *this;
    }

    Matrix transposed() const {
        auto temp = *this;
        temp.transpose();
        return temp;
    }

    Matrix& operator += (const Matrix& other) {
        for (size_t i = 0; i < _Numbers.size(); i++) {
            for (size_t j = 0; j < _Numbers[0].size(); j++) {
                _Numbers[i][j] = _Numbers[i][j] + other._Numbers[i][j];
            }
        }
        return *this;
    }

    Matrix operator + (const Matrix& other) const {
        auto temp = *this;
        temp += other;
        return temp;
    }

    Matrix& operator -= (const Matrix& other) {
        for (size_t i = 0; i < _Numbers.size(); i++) {
            for (size_t j = 0; j < _Numbers[0].size(); j++) {
                _Numbers[i][j] = _Numbers[i][j] - other._Numbers[i][j];
            }
        }
        return *this;
    }

    Matrix operator - (const Matrix& other) const {
        auto temp = *this;
        temp -= other;
        return temp;
    }

    Matrix operator * (const Matrix& other) const {
        std::vector<std::vector<T>> res;
        for (size_t i = 0; i < _Numbers.size(); i++) {
            std::vector<T> str;
            for (size_t j = 0; j < other._Numbers[0].size(); j++) {
                T elem = T(0);
                for (size_t k = 0; k < _Numbers[0].size(); k++) {
                    elem = elem + _Numbers[i][k] * other._Numbers[k][j];
                }
                str.push_back(elem);
            }
            res.push_back(str);
        }
        return res;
    }

    Matrix& operator *= (const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    Matrix& operator *= (const T& scalar) {
        for (size_t i = 0; i < _Numbers.size(); i++) {
            for (size_t j = 0; j < _Numbers[0].size(); j++) {
                _Numbers[i][j] = _Numbers[i][j] * scalar;
            }
        }
        return *this;
    }

    Matrix operator * (const T& scalar) const {
        auto temp = *this;
        temp *= scalar;
        return temp;
    }

    friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix) {
        for (size_t i = 0; i < matrix._Numbers.size(); i++) {
            for (size_t j = 0; j < matrix._Numbers[0].size(); j++) {
                out << matrix._Numbers[i][j];
                if (j < matrix._Numbers[0].size() - 1) {
                    out << "\t";
                }
            }
            if (i < matrix._Numbers.size() - 1) {
                out << "\n";
            }
        }
        return out;
    }
};
