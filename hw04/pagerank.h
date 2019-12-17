#ifndef __hw04__pagerank__
#define __hw04__pagerank__

#include <iostream>
#include "matrix.h"
#include "parser.h"

class PageRank
{
private:
    const static int iter = 100;

public:
    /**
     * @brief Constructor of PageRank.
     */
    PageRank() {}

    /**
     * @brief Performs PageRank::iter iterations of page rank calculation.
     */
    void   iterate();

    /**
     * @brief Creates transition matrix.
     * @param prt topology of links
     */
    void   createTransitionMatrix(ParserRawTopology prt);

    /**
     * @brief Creates RSI matrix.
     */
    void   createRSIMatrix();

    /**
     * @brief Returns transition matrix.
     * @return transition matrix
     */
    Matrix getTransitionMatrix() const;

    /**
     * @brief Returns RSI matrix.
     * @return RSI matrix
     */
    Matrix getRSIMatrix() const;

    /**
     * @brief Returns page rank.
     * @return page rank
     */
    Matrix getRank() const;

    /**
     * @brief Prints page rank to std::cout.
     */
    void   printRank() const;

private:
    Matrix m_RSIMatrix;
    Matrix m_TransitionMatrix;
    Matrix m_rank;
};

#endif /* defined(__hw04__pagerank__) */
