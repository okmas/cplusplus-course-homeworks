#include "bitcoin.h"

// ---Help functions-------------------------------

char toHex(char c1, char c2)
{
    c1 = toupper(c1);
    c2 = toupper(c2);
    if (c1 >= 'A') c1 -= 'A' - 10;
    else if (c1 >= '0') c1 -= '0';
    if (c2 >= 'A') c2 -= 'A' - 10;
    else if (c2 >= '0') c2 -= '0';

    return c1 * 16 + c2;
}

// ---Input implementation-------------------------

Input::Input(std::string prev, int index)
{
    m_prev = prev;
    m_index = index;
}

int Input::getIndex() const
{
    return m_index;
}

std::string Input::getPreviousTx() const
{
    return m_prev;
}

void Input::dump(std::ostream& stream) const
{
    stream << "  Input from " << m_prev << ", index " << m_index << std::endl;
}

// ---Output implementation-------------------------

Output::Output(double value, std::string script)
{
    m_value = value;
    m_script = script;
}

double Output::getValue() const
{
    return m_value;
}

std::string Output::getScript() const
{
    return m_script;
}

std::string Output::decode() const
{
    std::stringstream s;
    std::string hash;
    s << getScript();
    do s >> hash; while (hash != "" && hash.length() != 40);

    if (hash == "")
    {
        throw missing_word_error();
    }

    char help;
    s.str(std::string());
    s.clear();
    for (int i = 0; i < 40; i += 2)
    {
        help = toHex(hash[i], hash[i + 1]);
        if (! isprint(help))
        {
            throw not_printable_error();
        }

        s << help;
    }

    return s.str();
}

void Output::dump(std::ostream& stream) const
{
    stream << "  Output " << m_value << ", script " << m_script << std::endl;
}

// ---Transaction implementation--------------------

Transaction::Transaction(std::string hash)
{
    m_hash = hash;
}

void Transaction::addInput(Input inp)
{
    m_inputs.push_back(inp);
}

void Transaction::addOutput(Output out)
{
    m_outputs.push_back(out);
}

std::string Transaction::getHash() const
{
    return m_hash;
}

const Input& Transaction::getNthInput(unsigned int idx) const
{
    if (idx >= getNumInputs())
    {
        throw std::out_of_range("Ìnput index higher than number of inputs");
    }

    return m_inputs[idx];
}

const Output& Transaction::getNthOutput(unsigned int idx) const
{
    if (idx >= getNumOutputs())
    {
        throw std::out_of_range("Output index higher than number of outputs");
    }

    return m_outputs[idx];
}

unsigned int Transaction::getNumInputs() const
{
    return m_inputs.size();
}

unsigned int Transaction::getNumOutputs() const
{
    return m_outputs.size();
}

void Transaction::decode(std::ostream& stream) const
{
    for (unsigned int i = 0; i < getNumOutputs(); i++)
    {
        try
        {
            stream << getNthOutput(i).decode() << std::endl;
        }
        catch (missing_word_error e)
        {

        }
        catch (not_printable_error e)
        {
            stream << "not decodable as printable ASCII" << std::endl;
        }
    }
}

void Transaction::dump(std::ostream& stream) const
{
    stream << "Transaction " << m_hash << std::endl;
    for (unsigned int i = 0; i < getNumInputs(); i++) m_inputs[i].dump(stream);
    for (unsigned int i = 0; i < getNumOutputs(); i++) m_outputs[i].dump(stream);
}

// ---Block implementation--------------------------

Block::Block(const char *filename)
{
    std::ifstream in(filename);

    if (! in.good())
    {
        throw std::runtime_error("Cannot open input file.");
    }

    if (! in.eof())
    {
        loadBlock(in);
    }
}

void Block::loadBlock(std::istream &in)
{
    std::string attName;
    std::string line;

    in >> line;
    do
    {
        in >> line;
        attName = nextAttributeName(line);
        if (attName == "hash")
        {
            m_hash = nextStrAttributeValue(line);
        }
        else if (attName == "prev_block")
        {
            m_prev_block = nextStrAttributeValue(line);
        }
        else if (attName == "tx")
        {
            loadTransactions(in, line);
        }
        else if (line[line.length() - 1] == '[')
        {
            handleLongAttName(in);
        }
    } while (attName != "");
}

void Block::loadTransactions(std::istream &in, std::string &line)
{
    in >> line;
    do
    {
        addTransaction(loadTransaction(in, line));
        in >> line;
    } while (line[0] != ']');
}

Transaction Block::loadTransaction(std::istream &in, std::string& line)
{
    std::string attName;
    std::string hash;
    std::vector<Input> inputs;
    std::vector<Output> outputs;

    in >> line;
    do
    {
        attName = nextAttributeName(line);
        if (attName == "hash")
        {
            hash = nextStrAttributeValue(line);
        }
        else if (attName == "in")
        {
            in >> line;
            do
            {
                if (! line[0] != ']')
                {
                    inputs.push_back(loadInput(in, line));
                }
                in >> line;
            } while (line[0] != ']');
        }
        else if (attName == "out")
        {
            in >> line;
            do
            {
                if (! line[0] != ']')
                {
                    outputs.push_back(loadOutput(in, line));
                }
                in >> line;
            } while (line[0] != ']');
        }
        in >> line;
    } while (line[0] != '}');

    Transaction t(hash);
    for (unsigned int i = 0; i < inputs.size(); i++)
    {
        t.addInput(inputs[i]);
    }
    for (unsigned int i = 0; i < outputs.size(); i++)
    {
        t.addOutput(outputs[i]);
    }

    return t;
}

Input Block::loadInput(std::istream &in, std::string& line)
{
    std::string attName;
    std::string hash;
    int n;

    in >> line;
    do
    {
        attName = nextAttributeName(line);
        if (attName == "prev_out")
        {
            in >> line;
            do
            {
                attName = nextAttributeName(line);
                if (attName == "hash")
                {
                    hash = nextStrAttributeValue(line);
                }
                else if (attName == "n")
                {
                    n = nextIntAttributeValue(line);
                    if (n == 4294967295)
                    {
                        n = -1;
                    }
                }

                in >> line;
            } while (line[0] != '}');
        }
        in >> line;
    } while (line[0] != '}');

    Input rval(hash, n);
    return rval;
}

Output Block::loadOutput(std::istream &in, std::string& line)
{
    std::string attName;
    double value;
    std::string script;

    in >> line;
    do
    {
        attName = nextAttributeName(line);
        if (attName == "value")
        {
            value = nextDoubleAttributeValue(line);
        }
        else if (attName == "scriptPubKey")
        {
            std::stringstream line2;
            line2 << nextStrAttributeValue(line) << " ";
            char c;
            while ((c = in.get()) != '"') line2 << c;
            script = line2.str();
        }
        in >> line;
    } while (line[0] != '}');

    Output rval(value, script);
    return rval;
}

std::string Block::nextAttributeName(std::string line)
{
    if (line.length() < 5) return "";
    int colon_index = line.find_first_of(':', 0);
    return line.substr(1, colon_index - 2);
}

std::string Block::nextStrAttributeValue(std::string line)
{
    if (line[line.length() - 1] == ',')
    {
        line = line.substr(0, line.length() - 1);
    }
    int colon_index = line.find_first_of(':', 0);
    return line.substr(colon_index + 2, line.length() - colon_index - 3);
}

int Block::nextIntAttributeValue(std::string line)
{
    if (line[line.length() - 1] == ',')
    {
        line = line.substr(0, line.length() - 1);
    }
    int colon_index = line.find_first_of(':', 0);
    return atoi(line.substr(colon_index + 1, line.length() - colon_index - 1).c_str());
}

double Block::nextDoubleAttributeValue(std::string line)
{
    if (line[line.length() - 1] == ',')
    {
        line = line.substr(0, line.length() - 1);
    }
    int colon_index = line.find_first_of(':', 0);
    return strtod(line.substr(colon_index + 2, line.length() - colon_index - 3).c_str(),
                  NULL);
}

void Block::handleLongAttName(std::istream &in)
{
    std::string line;
    do in >> line; while (line[0] != ']');
}

void Block::addTransaction(Transaction tx)
{
    m_txs.insert(std::pair<std::string, Transaction>(tx.getHash(), tx));
}

const Transaction& Block::getTransaction(std::string hash) const
{
    if (m_txs.count(hash) == 0)
    {
        throw std::out_of_range("Transaction with such hash not found.");
    }

    return m_txs.at(hash);
}

std::string Block::getHash() const
{
    return m_hash;
}

std::string Block::getPreviousBlock() const
{
    return m_prev_block;
}

void Block::dump(std::ostream& stream) const
{
    stream << "Block " << getHash() << ", prev " << getPreviousBlock() << std::endl;
    for (std::map<std::string, Transaction>::const_iterator it = m_txs.begin();
         it != m_txs.end(); it++)
    {
        stream << "  Transaction " << it->second.getHash() << " " << it->second.getNumInputs()
               << "/" << it->second.getNumOutputs() << std::endl;
    }
}
