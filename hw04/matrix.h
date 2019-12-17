#ifndef __hw04__matrix__
#define __hw04__matrix__

#include <iostream>
#include <vector>
#include <cstdlib>

typedef std::vector<double> row_t;
typedef std::vector<row_t> matrix_t;

class Matrix
{
public:
    /**
     * @brief Creates matrix 0x0.
     */
    Matrix();

    /**
     * @brief Creates matrix rxc filled with zeros.
     * @param r number of rows
     * @param c number of columns
     */
    Matrix(int r, int c);

    /**
     * @brief Creates matrix rxc filled with val.
     * @param r number of rows
     * @param c number of columns
     * @param val value to fill with
     */
    Matrix(int r, int c, double val);

    /**
     * @brief Creates matrix as copy of m.
     * @param m matrix to copy
     */
    Matrix(const Matrix &m);
    
    /**
     * @brief Prints matrix to std::cout
     */
    void   print() const;

    /**
     * @brief Returns trasposed matrix.
     * @return trasposed matrix
     */
    Matrix transpose() const;
    
    /**
     * @brief Returns element at position [r][c].
     * @param r row of element
     * @param c column of element
     * @return element at position
     */
    double getElement(int r, int c) const;

    /**
     * @brief Sets element at position [r][c] to value.
     * @param r row of element
     * @param c column of element
     * @param value value to set
     */
    void   setElement(int r, int c, double value);

    /**
     * @brief Returns number of rows.
     * @return number of rows
     */
    int    getNumRows() const { return m_rows; }

    /**
     * @brief Returns number of columns.
     * @return number of columns
     */
    int    getNumCols() const { return m_cols; }
    
    /**
     * @brief Copies matrix m to this matrix
     * @param m matrix to copy
     */
    void   operator= (const Matrix &m);

    /**
     * @brief Returns sum of matrix m and this matrix. They must be the same dimensions.
     * @param m matrix to add to this matrix
     * @return sum of m and this
     */
    Matrix operator+ (const Matrix &m) const;

    /**
     * @brief Returns difference of this matrix and matrix m. They must be the same dimensions.
     * @param m matrix to substract from this matrix
     * @return difference of this and m
     */
    Matrix operator- (const Matrix &m) const;

    /**
     * @brief Returns this matrix multiplied by -1.
     * @return this matrix multiplied by -1
     */
    Matrix operator- () const;
    
    /**
     * @brief Returns matrix m multiplied by val.
     * @param m matrix to multiply
     * @param val value to multiply by
     * @return m multiplied by val
     */
    friend Matrix operator* (const Matrix &m, const double &val);

    /**
     * @brief Returns matrix m multiplied by val.
     * @param val value to multiply by
     * @param m matrix to multiply
     * @return m multiplied by val
     */
    friend Matrix operator* (const double &val, const Matrix &m);

    /**
     * @brief Returns matrix m1 multiplied by m2. Number of columns of m1 must equal number of row of m2.
     * @param m1 matrix 1
     * @param m2 matrix 2
     * @return m1 multiplied by m2
     */
    friend Matrix operator* (const Matrix &m1, const Matrix &m2);

    /**
     * @brief Resizes this matrix and fills it with val.
     * @param r number of rows
     * @param c number of columns
     * @param val value to fill matrix with
     */
    void   initWithValue(int r, int c, double val);

    /**
     * @brief Resizes this matrix as a copy of m.
     * @param m matrix to copy
     */
    void   initWithMatrix(const Matrix &m);

private:
    int m_rows;
    int m_cols;
    matrix_t m_mat;
};

#endif /* defined(__hw04__matrix__) */
