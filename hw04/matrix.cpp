#include "matrix.h"

Matrix::Matrix()
{
    initWithValue(0, 0, 0);
}

Matrix::Matrix(int r, int c)
{
    initWithValue(r, c, 0);
}

Matrix::Matrix(int r, int c, double val)
{
    initWithValue(r, c, val);
}

Matrix::Matrix(const Matrix &m)
{
    initWithMatrix(m);
}

void Matrix::initWithValue(int r, int c, double val)
{
    if (r < 0 || c < 0)
    {
        std::cerr << "Dimensions of a matrix must be non-negative. "
            << "Tried to create matrix " << r << "x" << c << "."
            << std::endl;
        exit(1);
    }
    
    m_rows = r;
    m_cols = c;
    m_mat.resize(m_rows, std::vector<double>(m_cols, val));
}

void Matrix::initWithMatrix(const Matrix &m)
{
    m_rows = m.getNumRows();
    m_cols = m.getNumCols();
    m_mat.resize(m_rows, std::vector<double>(m_cols));
    
    double val;
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            val = m.getElement(r, c);
            if (val >= 0)
            {
                setElement(r, c, val);
            }
            else
            {
                std::cerr << "Cannot initialize matrix with a negative value of "
                << val << " at row " << r << " column " << c << "."
                << std::endl;
                exit(1);
            }
        }
    }
}

void Matrix::print() const
{
    std::cout.setf(std::ios::fixed);
    
    std::cout << "Matrix " << getNumRows() << "x" << getNumCols() << std::endl;
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            std::cout << getElement(r, c) << " ";
        }
        
        std::cout << std::endl;
    }
}

Matrix Matrix::transpose() const
{
    Matrix rval(getNumCols(), getNumRows());
    
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            rval.setElement(c, r, getElement(r, c));
        }
    }
    
    return rval;
}

double Matrix::getElement(int r, int c) const
{
    return m_mat[r][c];
}

void Matrix::setElement(int r, int c, double value)
{
    m_mat[r][c] = value;
}

void Matrix::operator= (const Matrix &m)
{
    initWithMatrix(m);
}

Matrix Matrix::operator+ (const Matrix &m) const
{
    if (getNumRows() != m.getNumRows() || getNumCols() != m.getNumCols())
    {
        std::cerr << "Cannot add up matrices with different dimensions. "
            << "First is " << getNumRows() << "x" << getNumCols()
            << " second is " << m.getNumRows() << "x" << m.getNumCols() << "."
            << std::endl;
        exit(1);
    }
    
    Matrix rval(getNumRows(), getNumCols());
    
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            rval.setElement(r, c, getElement(r, c) + m.getElement(r, c));
        }
    }
    
    return rval;
}

Matrix Matrix::operator- (const Matrix &m) const
{
    if (getNumRows() != m.getNumRows() || getNumCols() != m.getNumCols())
    {
        std::cerr << "Cannot substract matrices with different dimensions. "
        << "First is " << getNumRows() << "x" << getNumCols()
        << " second is " << m.getNumRows() << "x" << m.getNumCols() << "."
        << std::endl;
        exit(1);
    }
    
    Matrix rval(getNumRows(), getNumCols());
    
    for (int r = 0; r < rval.getNumRows(); r++)
    {
        for (int c = 0; c < rval.getNumCols(); c++)
        {
            rval.setElement(r, c, getElement(r, c) - m.getElement(r, c));
        }
    }
    
    return rval;
}

Matrix Matrix::operator- () const
{
    Matrix rval(getNumRows(), getNumCols());
    
    for (int r = 0; r < rval.getNumRows(); r++)
    {
        for (int c = 0; c < rval.getNumCols(); c++)
        {
            rval.setElement(r, c, -getElement(r, c));
        }
    }
    
    return rval;
}

Matrix operator* (const Matrix &m, const double &val)
{
    if (m.getNumRows() <= 0 || m.getNumCols() <= 0)
    {
        std::cerr << "Cannot multiply matrix with dimensions of "
            << m.getNumRows() << "x" << m.getNumCols()
            << ". Dimenstions must be positive."
            << std::endl;
        exit(1);
    }
    
    Matrix rval(m.getNumRows(), m.getNumCols());
    
    for (int r = 0; r < rval.getNumRows(); r++)
    {
        for (int c = 0; c < rval.getNumCols(); c++)
        {
            rval.setElement(r, c, val * m.getElement(r, c));
        }
    }
    
    return rval;
}

Matrix operator* (const double &val, const Matrix &m)
{
    if (m.getNumRows() <= 0 || m.getNumCols() <= 0)
    {
        std::cerr << "Cannot multiply matrix with dimensions of "
        << m.getNumRows() << "x" << m.getNumCols()
        << ". Dimenstions must be positive."
        << std::endl;
        exit(1);
    }
    
    Matrix rval(m.getNumRows(), m.getNumCols());
    
    for (int r = 0; r < rval.getNumRows(); r++)
    {
        for (int c = 0; c < rval.getNumCols(); c++)
        {
            rval.setElement(r, c, val * m.getElement(r, c));
        }
    }
    
    return rval;
}

Matrix operator* (const Matrix &m1, const Matrix &m2)
{
    if (m1.getNumCols() != m2.getNumRows())
    {
        std::cerr << "Cannot multiply matrices with dimensions of "
        << m1.getNumRows() << "x" << m1.getNumCols() << " and "
        << m2.getNumRows() << "x" << m2.getNumCols() << "."
        << std::endl;
        exit(1);
    }
    
    Matrix rval(m1.getNumRows(), m2.getNumCols());
    
    if (rval.getNumRows() > 0 && rval.getNumCols() > 0)
    {
        int common_d = m1.getNumCols();
        double val;
        for (int r = 0; r < rval.getNumRows(); r++)
        {
            for (int c = 0; c < rval.getNumCols(); c++)
            {
                val = 0;
                for (int i = 0; i < common_d; i++)
                {
                    val += m1.getElement(r, i) * m2.getElement(i, c);
                }
                
                rval.setElement(r, c, val);
            }
        }
    }
    
    return rval;
}
