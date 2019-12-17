#ifndef __hw04__parser__
#define __hw04__parser__

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <cstdlib>

typedef std::map <int, std::vector<int> > ParserRawTopology;

class Parser
{
public:
    /**
     * @brief Parser constructor.
     */
    Parser() { m_files_count = 0; }
    
    /**
     * @brief Queues file to queue of files to process.
     * @param filename file to queue
     */
    void queueFile(const char *filename);

    /**
     * @brief Queues file to queue of files to process.
     * @param filename file to queue
     */
    void queueFile(const std::string filename);

    /**
     * @brief Returns true if queue is empty, false otherwise.
     * @return true if queue is empty, false otherwise
     */
    bool isQueueEmpty() const;
    
    /**
     * @brief Starts processing of files in queue.
     */
    void process();

    /**
     * @brief Returns file link topology.
     * @return file link topology
     */
    ParserRawTopology getMapping() const;

private:
    const std::string nextFile();
    bool isFileQueued(std::string filename);
    void processFile(const std::string filename);
    void addToTopology(const std::string file, const std::string ref);

private:
    std::queue<std::string> m_files;
    std::map<std::string, int> m_file_keys;
    ParserRawTopology m_topology;
    int m_files_count;
};

#endif /* defined(__hw04__parser__) */
