#include "pagerank.h"

void   PageRank::iterate()
{
    const int n = m_TransitionMatrix.getNumRows();
    m_rank.initWithValue(1, n, 1.0 / n);

    for (int i = 0; i < iter; i++)
    {
        m_rank = m_rank * m_RSIMatrix;
    }
}

void   PageRank::createTransitionMatrix(ParserRawTopology prt)
{
    const int n = prt.size();

    m_TransitionMatrix.initWithValue(n, n, 0);

    for (int i = 0; i < n; i++)
    {
        if (prt[i].empty())
        {
            for (int j = 0; j < n; j++)
            {
                m_TransitionMatrix.setElement(i, j, 1.0 / n);
            }
        }
        else
        {
            const int nLinks = prt[i].size();
            for (int j = 0; j < nLinks; j++)
            {
                m_TransitionMatrix.setElement(i, prt[i][j], 1.0 / nLinks);
            }
        }
    }
}

void   PageRank::createRSIMatrix()
{
    const double alfa = 0.85;
    const int n = m_TransitionMatrix.getNumRows();
    Matrix e(n, 1, 1);

    m_RSIMatrix = alfa * m_TransitionMatrix + ((1 - alfa) / n) * e * e.transpose();
}

Matrix PageRank::getTransitionMatrix() const
{
    return m_TransitionMatrix;
}

Matrix PageRank::getRSIMatrix() const
{
    return m_RSIMatrix;
}

Matrix PageRank::getRank() const
{
    return m_rank;
}

void   PageRank::printRank() const
{
    m_rank.print();
}
