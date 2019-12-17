#include "parser.h"

//---Public methods-----------------------------------------------------

void Parser::queueFile(const char *filename)
{
    queueFile(std::string(filename));
}

void Parser::queueFile(const std::string filename)
{
    if (! isFileQueued(filename))
    {
        m_files.push(filename);
        m_file_keys[filename] = m_files_count;
        m_files_count++;
        m_topology[m_file_keys[filename]] = std::vector<int>(0);
    }
}

bool Parser::isQueueEmpty() const
{
    return m_files.empty();
}

void Parser::process()
{
    while (! isQueueEmpty())
    {
        processFile(nextFile());
    }
}

ParserRawTopology Parser::getMapping() const
{
    return m_topology;
}

//---Private methods----------------------------------------------------

const std::string Parser::nextFile()
{
    const std::string rval = m_files.front();
    m_files.pop();
    return rval;
}

void Parser::processFile(const std::string filename)
{
    std::ifstream is(filename.c_str());
    
    if (! is.good())
    {
        std::cerr << "Unable to open file " << filename << std::endl;
        exit(1);
    }
/*
    std::string str;
    do
    {
        is >> str;
        if (str != "")
        {
            queueFile(str);
            addToTopology(filename, str);
        }
    } while (is.good());*/

    std::string str;
    std::vector<std::string> splitVec;
    do
    {
        is >> str;
        if (boost::to_upper_copy(str) == "<A")
        {
            do
            {
                is >> str;
                splitVec.clear();
                boost::split(splitVec, str, boost::is_any_of("\""));
            } while  (boost::to_upper_copy(splitVec[0]) != "HREF=" || splitVec.size() <= 1);

            queueFile(splitVec[1]);
            addToTopology(filename, splitVec[1]);
        }
    } while (is.good());

    is.close();
}

void Parser::addToTopology(const std::string file, const std::string ref)
{
    for (unsigned int i = 0; i < m_topology[m_file_keys[file]].size(); i++)
    {
        if (m_topology[m_file_keys[file]][i] == m_file_keys[ref])
        {
            return;
        }
    }

    m_topology[m_file_keys[file]].push_back(m_file_keys[ref]);
}

bool Parser::isFileQueued(std::string filename)
{
    return (m_file_keys.find(filename) != m_file_keys.end());
}
