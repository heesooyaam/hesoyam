#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <cstdint>
#include <list>

template<typename T>
class matrix
{
public:
    class Matrix_Error : public std::exception
    {
    public:
        Matrix_Error(const char* message)
                : message(message)
        {}
        const char* what() const throw()
        {
            return message.c_str();
        }
    private:
        std::string message;
    };

    matrix(const std::vector<std::vector<T>>& mat, const std::optional<int64_t>& MOD = std::nullopt)
            : rows_(mat.size())
            , columns_(mat.front().size())
            , MOD(MOD)
            , data_(new T[rows_ * columns_])
    {
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                data_[columns_ * i + j] = mat[i][j];
            }
        }
    }

    matrix(const std::list<T>& mat, size_t rows, size_t cols, const std::optional<int64_t >& MOD = std::nullopt)
            : rows_(rows)
            , columns_(cols)
            , MOD(MOD)
            , data_(new T[rows_ * columns_])
    {
        auto it = mat.begin();
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j, ++it)
            {
                data_[columns_ * i + j] = *it;
            }
        }
    }

    matrix(const matrix<T>& mat, const std::optional<int64_t>& MOD = std::nullopt)
            : rows_(mat.rows())
            , columns_(mat.columns())
            , MOD(MOD.has_value() ? MOD : mat.MOD)
            , data_(new T[rows_ * columns_])
    {
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                this->operator[](i)[j] = mat[i][j];
            }
        }
    }

    explicit matrix()
            : rows_(0)
            , columns_(0)
            , MOD(std::nullopt)
            , data_(nullptr)
    {}

    explicit matrix(size_t rows, size_t cols, T defaultValue = 0, const std::optional<int64_t>& MOD = std::nullopt)
            : rows_(rows)
            , columns_(cols)
            , MOD(MOD)
            , data_(new T[rows_ * columns_])
    {
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                data_[columns_ * i + j] = defaultValue;
            }
        }
    }

    ~matrix()
    {
        delete[] data_;
    }

    operator std::vector<std::vector<T>>() const
    {
        std::vector<std::vector<T>> mat(rows_, std::vector<T>(columns_));
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                mat[i][j] = this->operator[](i)[j];
            }
        }
        return mat;
    }

    T* operator[](size_t row)
    {
        return data_ + columns_ * row;
    }

    const T* operator[](size_t row) const
    {
        return data_ + columns_ * row;
    }

    matrix<T>& operator=(const matrix<T>& mat)
    {
        if(&mat == this)
        {
            throw Matrix_Error("Cannot use copy operator");
        }
        delete[] data_;
        data_ = new T[mat.columns_ * mat.rows_];
        MOD = mat.MOD;
        columns_ = mat.columns_;
        rows_ = mat.rows_;
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                data_[columns_ * i + j] = mat[i][j];
            }
        }
        return *this;
    }

    // +/-
    matrix<T> operator+(const matrix<T>& mat) const
    {
        if(!okToAdd(mat))
        {
            throw Matrix_Error("Cannot add: bad sizes");
        }

        matrix<T> result(*this);

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                result[i][j] = this->operator[](i)[j] + mat[i][j];
                result.takeModulo(i, j);
            }
        }
        return result;
    }

    matrix<T> operator-(const matrix<T>& mat) const
    {
        if(!okToAdd(mat))
        {
            throw Matrix_Error("Cannot add: bad sizes");
        }

        matrix<T> result(*this);

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                result[i][j] = this->operator[](i)[j] - mat[i][j];
                result.takeModulo(i, j);
            }
        }
        return result;
    }

    matrix<T>& operator+=(const matrix<T>& mat)
    {
        if(!okToAdd(mat))
        {
            throw Matrix_Error("Cannot add: bad sizes");
        }

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                data_[columns_ * i + j] += mat[i][j];
                takeModulo(i, j);
            }
        }

        return *this;
    }

    matrix<T>& operator-=(const matrix<T>& mat)
    {
        if(!okToAdd(mat))
        {
            throw Matrix_Error("Cannot add: bad sizes");
        }

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                data_[columns_ * i + j] -= mat[i][j];
                takeModulo(i, j);
            }
        }

        return *this;
    }

    // multiplication on number
    template<typename Integer>
    typename std::enable_if_t<std::is_integral<Integer>::value, matrix<T>>
    operator*(const Integer& k) const
    {
        matrix<T> result(*this);
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                result[i][j] *= k;
                result.takeModulo(i, j);
            }
        }
        return result;
    }

    template<typename Floating>
    typename std::enable_if_t<std::is_floating_point<Floating>::value, matrix<T>>
    operator*(const Floating& k) const
    {
        matrix<T> result(*this);
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                result[i][j] *= k;
            }
        }
        return result;
    }

    template<typename Integer>
    typename std::enable_if_t<std::is_integral<Integer>::value, matrix<T>&>
    operator*=(const Integer& k)
    {
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                this->operator[](i)[j] *= k;
                takeModulo(i, j);
            }
        }
        return *this;
    }

    template<typename Floating>
    typename std::enable_if_t<std::is_floating_point<Floating>::value, matrix<T>&>
    operator*=(const Floating& k)
    {
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                this->operator[](i)[j] *= k;
            }
        }
        return *this;
    }

    // division on number
    template<typename Integer>
    typename std::enable_if_t<std::is_integral<Integer>::value, matrix<T>>
    operator/(const Integer& k) const
    {
        if(k == 0)
        {
            throw Matrix_Error("Cannot divide by zero");
        }

        matrix<T> result(*this);
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                if(result.MOD) result.divideByModulo(i, j, k);
                else result[i][j] /= k;
            }
        }
        return result;
    }

    template<typename Integer>
    typename std::enable_if_t<std::is_integral<Integer>::value, matrix<T>&>
    operator/=(const Integer& k)
    {
        if(k == 0)
        {
            throw Matrix_Error("Cannot divide by zero");
        }

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                if(MOD) this->divideByModulo(i, j, k);
                else this->operator[](i)[j] /= k;
            }
        }
        return *this;
    }

    template<typename Floating>
    typename std::enable_if_t<std::is_floating_point<Floating>::value, matrix<T>>
    operator/(const Floating& k) const
    {
        if(k == 0)
        {
            throw Matrix_Error("Cannot divide by zero");
        }

        matrix<T> result(*this);
        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                result[i][j] /= k;
            }
        }
        return result;
    }

    template<typename Floating>
    typename std::enable_if_t<std::is_floating_point<Floating>::value, matrix<T>&>
    operator/=(const Floating& k)
    {
        if(k == 0)
        {
            throw Matrix_Error("Cannot divide by zero");
        }

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                this->operator[](i)[j] /= k;
            }
        }
        return *this;
    }

    // matrix multiplication
    matrix<T> operator*(const matrix<T>& mat) const
    {
        if(!okToMultiply(mat))
        {
            throw Matrix_Error("Cannot multiply: bad sizes");
        }

        matrix<T> result(rows_, mat.columns(), 0, MOD);

        for(int i = 0; i < result.rows(); ++i)
        {
            for(int j = 0; j < result.columns(); ++j)
            {
                for(int idx = 0; idx < mat.rows(); ++idx)
                {
                    result[i][j] += this->operator[](i)[idx] * mat[idx][j];
                    result.takeModulo(i, j);
                }
            }
        }

        return result;
    }

    matrix<T>& operator*=(const matrix<T>& mat)
    {
        *this = *this * mat;
        return *this;
    }

    // powering matrix
    template<typename Integer>
    typename std::enable_if_t<std::is_integral_v<Integer>, matrix<T>>
    operator^(Integer power) const
    {
        if(!squareMatrix())
        {
            throw Matrix_Error("Cannot power: bad size");
        }

        matrix<T> result(rows_, columns_, 0, MOD);
        for(int i = 0; i < columns_; ++i)
        {
            result[i][i] = 1;
        }

        matrix<T> currentPower(*this);

        while(power)
        {
            if(power & 1) result *= currentPower;

            currentPower *= currentPower;
            power /= 2;
        }

        return result;
    }

    template<typename Integer>
    typename std::enable_if_t<std::is_integral<Integer>::value, matrix<T>&>
    operator^=(Integer power)
    {
        if(!squareMatrix())
        {
            throw Matrix_Error("Cannot power: bad size");
        }

        matrix<T> result(rows_, columns_, 0, MOD);
        for(int i = 0; i < columns_; ++i)
        {
            result[i][i] = 1;
        }

        while(power)
        {
            if(power & 1) result *= *this;

            *this *= *this;
            power /= 2;
        }
        *this = result;

        return *this;
    }

    void print(const std::string& article = "", bool hasEndl = true) const
    {
        if(!article.empty() && hasEndl)
        {
            std::cout << article << "\n";
        }

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                std::cout << this->operator[](i)[j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout.flush();
    }

    static void print(const matrix<T>& mat, const std::string& article = "", bool hasEndl = true)
    {
        mat.print(article, hasEndl);
    }
    T determinante() const
    {
        if(!squareMatrix())
        {
            throw Matrix_Error("Cannot count determinante: matrix is not square");
        }
        if(columns_ > 2)
        {
            throw Matrix_Error("Cannot count determinante: too big size :(");
        }

        T det = this->operator[](0)[0] * this->operator[](1)[1]
                - this->operator[](0)[1] * this->operator[](1)[0];

        if(MOD.has_value())
        {
            return (det + MOD.value()) % MOD.value();
        }
        else
        {
            return det;
        }
    }

    T reverse()
    {
        if(!squareMatrix())
        {
            throw Matrix_Error("Cannot reverse: matrix is not square");
        }
        if(columns_ > 2)
        {
            throw Matrix_Error("Cannot count reverse: too big size :(");
        }
        T det = determinante();
        std::swap(this->operator[](0)[0], this->operator[](1)[1]);
        this->operator[](0)[1] *= -1;
        this->operator[](1)[0] *= -1;
        takeModulo(0, 1);
        takeModulo(1, 0);
        return det;
    }

    // comparation

    bool operator==(const matrix<T>& mat) const
    {
        if(rows_ != mat.rows_ || columns_ != mat.columns_) return false;

        for(int i = 0; i < rows_; ++i)
        {
            for(int j = 0; j < columns_; ++j)
            {
                if(this->operator[](i)[j] != mat[i][j]) return false;
            }
        }

        return true;
    }

    bool operator!=(const matrix<T>& mat) const
    {
        return !(*this == mat);
    }

    void setModulo(const int64_t& mod)
    {
        if(mod <= 0)
        {
            throw Matrix_Error("Bad modulo");
        }

        MOD.emplace(mod);
    }

    bool hasModulo() const
    {
        return MOD.has_value();
    }
    void clear()
    {
        *this = matrix<T>();
    }
    size_t size() const
    {
        return rows_ * columns_;
    }
    size_t columns() const
    {
        return columns_;
    }

    size_t rows() const
    {
        return rows_;
    }
private:
    size_t rows_, columns_;
    std::optional<int64_t> MOD;
    T* data_;

    void takeModulo(int i, int j)
    {
        if(!MOD.has_value()) return;

        this->operator[](i)[j] += MOD.value();
        this->operator[](i)[j] %= MOD.value();
    }

    void divideByModulo(int i, int j, T divisor = 1)
    {
        if(!MOD.has_value())
        {
            this->operator[](i)[j] /= divisor;
            return;
        }

        int64_t power = MOD.value() - 2;
        int64_t result = 1;
        while(power)
        {
            if(power & 1) result = (result * divisor + MOD.value()) % MOD.value();

            divisor = (divisor * divisor + MOD.value()) % MOD.value();
            power >>= 1;
        }

        this->operator[](i)[j] *= result;
        takeModulo(i, j);
    }

    bool okToAdd(const matrix<T>& mat) const
    {
        return this->columns_ == mat.columns() && this->rows_ == mat.rows();
    }

    bool okToMultiply(const matrix<T>& mat) const
    {
        return this->columns_ == mat.rows();
    }

    bool squareMatrix() const
    {
        return columns_ == rows_;
    }
};
template<typename T, typename Number>
typename std::enable_if_t<std::is_floating_point<Number>{} || std::is_integral<Number>{}, matrix<T>>
operator*(const Number& k, const matrix<T>& mat)
{
    return mat * k;
}
