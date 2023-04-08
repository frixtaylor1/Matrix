//	Copyright 2023 Kevin Daniel Taylor (frixtaylor1)
//	Contact: kevinmusic123@gmail.com
//	For more information about the license, see the end of the file.

#ifndef STATIC_MATRIX
#define STATIC_MATRIX

#include "../IMatrix.hpp"

#include <iostream>
#include <assert.h>
#include <array>


template <typename ItemType, const std::size_t Rows = 0, const std::size_t Columns = 0>
class StaticMatrix : public IMatrix
{
public:

    template <typename Type, const std::size_t nbItems>
    using Array = std::array<Type, nbItems>;

    StaticMatrix() noexcept = default;
    StaticMatrix(const Array < Array<ItemType, Columns>, Rows >& items) noexcept
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
    
    constexpr static const StaticMatrix identityMatrix() noexcept
    {
        assert(Rows == Columns);
        StaticMatrix<ItemType, Rows, Columns> identity;
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                (i == j) ? identity[i][j] = 1 : identity[i][j] = 0;
        return identity;
    }

    constexpr const bool operator == (StaticMatrix const& rhs) const noexcept
    {
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                if (m_items[i][j] != rhs.getElements()[i][j])
                    return false;
        return true;
    }

    constexpr const bool operator != (StaticMatrix const& rhs) const noexcept
    {
        return !( *this == rhs );
    }

    constexpr const StaticMatrix operator + (StaticMatrix const& rhs) const noexcept
    {
        StaticMatrix<ItemType, Rows, Columns> result;
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                result[i][j] = m_items[i][j] + rhs.getElements()[i][j];
        return result;
    }

    constexpr const StaticMatrix operator - (StaticMatrix const& rhs) const noexcept
    {
        StaticMatrix<ItemType, Rows, Columns> result;
        for(int i = 0; i < Rows; i++)
            for(int j = 0; j < Columns; j++)
                result[i][j] = m_items[i][j] - rhs.getElements()[i][j];
        return result;
    }

    /*
        A template argument is required if the rhs StaticMatrix is different in the length of the columns. 
        @Arg is type: std::size_t called as rhsColumns
    */
    template <std::size_t rhsColumns = Columns>
    constexpr const StaticMatrix<ItemType, Rows, rhsColumns> multiply(StaticMatrix<ItemType, Rows, rhsColumns> const& rhs)
    {
        assert(Columns == rhs.getnbRows());
        StaticMatrix<ItemType, Rows, rhsColumns> result;

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

    constexpr const StaticMatrix operator * (ItemType scalar) const noexcept
    {
        StaticMatrix<ItemType, Rows, Columns> result;
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
constexpr const StaticMatrix<ItemType, rows, columns> operator * (ItemType scalar, StaticMatrix<ItemType, rows, columns> const& rhs) noexcept
{
    return rhs * scalar;
}

template <typename ItemType, std::size_t rows, std::size_t columns>
constexpr std::ostream& operator << ( std::ostream& stream, const StaticMatrix<ItemType, rows, columns>& StaticMatrix ) noexcept
{
    for(int i = 0; i < StaticMatrix.getnbRows(); i++)
    {
        for(int j = 0; j < StaticMatrix.getnbColumns(); j++)
        {
            stream << StaticMatrix.getElements()[i][j] << " ";
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