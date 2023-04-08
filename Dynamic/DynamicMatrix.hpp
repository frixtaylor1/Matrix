//	Copyright 2023 Kevin Daniel Taylor (frixtaylor1)
//	Contact: kevinmusic123@gmail.com
//	For more information about the license, see the end of the file.

#ifndef DYNAMICMATRIX_HPP
#define DYNAMICMATRIX_HPP

#include "../IMatrix.hpp"

#include <iostream>
#include <assert.h>
#include <vector>

template <typename ItemType>
using Vector = std::vector<ItemType>;

template <typename ItemType>
class DynamicMatrix : public IMatrix
{
public:
    DynamicMatrix() noexcept = default;
    DynamicMatrix(const Vector < Vector<ItemType> >& items) noexcept
        : m_items(items)
    {
        m_rows =  m_items.size();
        m_columns = m_items[0].size();
    }

    constexpr const std::size_t getnbRows() const noexcept
    {
        return m_rows;
    }

    constexpr const std::size_t getnbColumns() const noexcept
    {
        return m_columns;
    }

    constexpr const Vector< Vector<ItemType> >& getElements() const noexcept
    {
        return m_items;
    }
    
    constexpr const bool operator == (DynamicMatrix const& rhs) const noexcept
    {
        for(int i = 0; i < m_rows; i++)
            for(int j = 0; j < m_columns; j++)
                if (m_items[i][j] != rhs.getElements()[i][j])
                    return false;
        return true;
    }

    constexpr const bool operator != (DynamicMatrix const& rhs) const noexcept
    {
        return !( *this == rhs );
    }

    constexpr const DynamicMatrix operator + (DynamicMatrix const& rhs) const noexcept
    {
        Vector< Vector<ItemType> > initializer(getnbRows(), Vector<ItemType>(getnbColumns(), 0));
        DynamicMatrix<ItemType> result(initializer);
        for(int i = 0; i < m_rows; i++)
            for(int j = 0; j < m_columns; j++)
                result[i][j] = m_items[i][j] + rhs.getElements()[i][j];

        return result;
    }

    constexpr const DynamicMatrix operator - (DynamicMatrix const& rhs) const noexcept
    {
        Vector< Vector<ItemType> > initializer(getnbRows(), Vector<ItemType>(getnbColumns(), 0));
        DynamicMatrix<ItemType> result(initializer);
        for(int i = 0; i < m_rows; i++)
            for(int j = 0; j < m_columns; j++)
                result[i][j] = m_items[i][j] - rhs.getElements()[i][j];

        return result;
    }

    constexpr const DynamicMatrix<ItemType> multiply(DynamicMatrix<ItemType> const& rhs)
    {
        assert(getnbColumns() == rhs.getnbRows());
        Vector< Vector<ItemType> > initializer(getnbRows(), Vector<ItemType>(rhs.getnbColumns(), 0));
        DynamicMatrix<ItemType> result(initializer);
        for(int i = 0; i <= m_rows - 1; ++i)
        {
            for(int j = 0; j <= rhs.m_columns - 1; ++j)
            {
                for(int k = 0; k <= m_rows - 1; ++k)
                    result[i][j] += (m_items[i][k] * rhs.getElements()[k][j]);
            }
        }
        return result;
    }

    constexpr const DynamicMatrix operator * (DynamicMatrix<ItemType> const& rhs)
    {
        return { multiply(rhs) };
    }

    constexpr const DynamicMatrix operator * (ItemType scalar) const noexcept
    {
        Vector< Vector<ItemType> > initializer(getnbRows(), Vector<ItemType>(getnbColumns(), 0));
        DynamicMatrix<ItemType> result(initializer);
        for(int i = 0; i < m_rows; i++)
            for(int j = 0; j < m_columns; j++)
                result[i][j] = m_items[i][j] * scalar;
        return result;
    }

    constexpr const Vector<ItemType>& operator [](int idx) const noexcept
    {
        return m_items[idx];
    }

    constexpr Vector<ItemType>& operator [](int idx) noexcept
    {
        return m_items[idx];
    }

private:
    std::size_t m_rows, m_columns;
    Vector< Vector<ItemType> > m_items;
};

template <typename ItemType>
constexpr const DynamicMatrix<ItemType> operator * (ItemType scalar, DynamicMatrix<ItemType> const& rhs) noexcept
{
    return rhs * scalar;
}

template <typename ItemType>
constexpr std::ostream& operator << (std::ostream& stream, const DynamicMatrix<ItemType>& DynamicMatrix ) noexcept
{
    for(int i = 0; i < DynamicMatrix.getnbRows(); i++)
    {
        for(int j = 0; j < DynamicMatrix.getnbColumns(); j++)
        {
            stream << DynamicMatrix.getElements()[i][j] << " ";
        }
        stream << "\n";
    }
    return stream;
}

#endif // DYNAMICMATRIX_HPP

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