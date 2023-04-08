//	Copyright 2023 Kevin Daniel Taylor (frixtaylor1)
//	Contact: kevinmusic123@gmail.com
//	For more information about the license, see the end of the file.

#ifndef STATIC_MATRIX
#define STATIC_MATRIX

#include "../IMatrix.hpp"

#include <iostream>
#include <assert.h>
#include <array>

template <typename ItemType, const std::size_t nbItems>
using Array = std::array<ItemType, nbItems>;

template <typename ItemType, const std::size_t Rows, const std::size_t Columns>
class Matrix : public IMatrix
{
public:
    Matrix() noexcept = default;
    Matrix(const Array < Array<ItemType, Columns>, Rows >& items) noexcept
        : m_items(items)
    {}

    constexpr const std::size_t getnbRows() const noexcept
    {
        return m_rows;
    }

    constexpr const std::size_t getnbColumns() const noexcept
    {
        return m_columns;
    }

    constexpr const Array< Array<ItemType, Columns>, Rows >& getElements() const noexcept
    {
        return m_items;
    }
    
    constexpr const bool operator == (Matrix const& rhs) const noexcept
    {
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                if (m_items[i][j] != rhs.getElements()[i][j])
                    return false;
        return true;
    }

    constexpr const bool operator != (Matrix const& rhs) const noexcept
    {
        return !( *this == rhs );
    }

    constexpr const Matrix operator + (Matrix const& rhs) const noexcept
    {
        Matrix<ItemType, Rows, Columns> result;
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                result[i][j] = m_items[i][j] + rhs.getElements()[i][j];

        return result;
    }

    constexpr const Matrix operator - (Matrix const& rhs) const noexcept
    {
        Matrix<ItemType, Rows, Columns> result;
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                result[i][j] = m_items[i][j] - rhs.getElements()[i][j];

        return result;
    }

    /*
        A template argument is required if the rhs Matrix is different in the length of the columns. 
        @Arg is type: std::size_t called as rhsColumns
    */
    template <std::size_t rhsColumns = Columns>
    constexpr const Matrix<ItemType, Rows, rhsColumns> multiply(Matrix<ItemType, Rows, rhsColumns> const& rhs)
    {
        assert(Columns == rhs.getnbRows());
        Matrix<ItemType, Rows, rhsColumns> result;

        for(int i = 0; i <= Rows - 1; ++i)
        {
            for(int j = 0; j <= rhsColumns - 1; ++j)
            {
                result[i][j] = 0;
                for(int k = 0; k <= Rows - 1; ++k)
                    result[i][j] += (m_items[i][k] * rhs.getElements()[k][j]);
            }
        }
        return result;
    }

    constexpr const Matrix operator * (ItemType scalar) const noexcept
    {
        Matrix<ItemType, Rows, Columns> result;
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                result[i][j] = m_items[i][j] * scalar;
        return result;
    }

    constexpr const Array<ItemType, Columns>& operator [](int idx) const noexcept
    {
        return m_items[idx];
    }

    constexpr Array<ItemType, Columns>& operator [](int idx) noexcept
    {
        return m_items[idx];
    }

private:
    std::size_t m_rows = Rows, m_columns = Columns;
    Array< Array<ItemType, Columns>, Rows > m_items;
};

template <typename ItemType, std::size_t rows, std::size_t columns>
constexpr const Matrix<ItemType, rows, columns> operator * (ItemType scalar, Matrix<ItemType, rows, columns> const& rhs) noexcept
{
    return rhs * scalar;
}

template <typename ItemType, std::size_t rows, std::size_t columns>
constexpr std::ostream& operator << ( std::ostream& stream, const Matrix<ItemType, rows, columns>& matrix ) noexcept
{
    for(int i = 0; i < matrix.getnbRows(); i++)
    {
        for(int j = 0; j < matrix.getnbColumns(); j++)
        {
            stream << matrix.getElements()[i][j] << " ";
        }
        stream << "\n";
    }
    return stream;
}

#endif // STATIC_MATRIX

// MIT License
// 
// Copyright (c) 2023 Kevin Daniel Taylor frixtaylor1
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.