#ifndef BITCOIN_H
#define BITCOIN_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

class Input {
public:
    /**
     * @brief Input creator.
     * @param prev hash of previous transaction
     * @param index index of output in the transaction
     */
    Input(std::string prev, int index);

    /**
     * @brief Returns index of output in the transaction.
     * @return index of output in the transaction
     */
    int getIndex() const;

    /**
     * @brief Returns hash of previous transaction.
     * @return hash of previous transaction
     */
    std::string getPreviousTx() const;

    /**
     * @brief Writes info about this input to stream.
     * @param stream stream to write to
     */
    void dump(std::ostream& stream) const;
private:
    std::string m_prev;
    int m_index;
};

class Output {
public:
    /**
     * @brief Output constructor.
     * @param value amount of bitcoins
     * @param script control script
     */
    Output(double value, std::string script);

    /**
     * @brief Returns amount of bitcoins.
     * @return amount of bitcoins
     */
    double getValue() const;

    /**
     * @brief Returns control script.
     * @return control script
     */
    std::string getScript() const;

    /**
     * @brief Decodes hiden data in script.
     * @return decoded data
     * @throws not_printable_error when data are not printable
     * @throws missing_word_error when data is missing
     */
    std::string decode() const;

    /**
     * @brief Write info about this output to stream.
     * @param stream stream to write to
     */
    void dump(std::ostream& stream) const;
private:
    double m_value;
    std::string m_script;
};

class Transaction {
public:
    /**
     * @brief Transaction constructor.
     * @param hash hash of transaction
     */
    Transaction(std::string hash);

    /**
     * @brief Adds input to transaction.
     * @param inp input to add
     */
    void addInput(Input inp);

    /**
     * @brief Adds output to transaction.
     * @param out output to add
     */
    void addOutput(Output out);

    /**
     * @brief Returns hash of transaction.
     * @return hash of transaction
     */
    std::string getHash() const;

    /**
     * @brief Returns input at index idx.
     * @param idx index of input
     * @return input at index
     */
    const Input& getNthInput(unsigned int idx) const;

    /**
     * @brief Returns output at index idx.
     * @param idx index of output
     * @return output at index
     */
    const Output& getNthOutput(unsigned int idx) const;

    /**
     * @brief Returns number of inputs.
     * @return number of inputs
     */
    unsigned int getNumInputs() const;

    /**
     * @brief Returns number of outputs.
     * @return number of outputs
     */
    unsigned int getNumOutputs() const;

    /**
     * @brief Decodes printable outputs.
     * @param stream stream to write to
     */
    void decode(std::ostream& stream) const;

    /**
     * @brief Writes info about this transaction to stream.
     * @param stream stream to write to
     */
    void dump(std::ostream& stream) const;
private:
    std::string m_hash;
    std::vector<Input> m_inputs;
    std::vector<Output> m_outputs;
};

class Block {
public:
    /**
     * @brief Block constructor.
     * @param filename filename to create block from
     */
    Block(const char *filename);

    /**
     * @brief Adds transaction to block.
     * @param tx transaction to add
     */
    void addTransaction(Transaction tx);

    /**
     * @brief Returns transaction with given hash
     * @param hash hash of transaction
     * @return transaction with given hash
     */
    const Transaction& getTransaction(std::string hash) const;

    /**
     * @brief Returns hash of block
     * @return hash of block
     */
    std::string getHash() const;

    /**
     * @brief Return hash of previous block.
     * @return hash of previous block
     */
    std::string getPreviousBlock() const;

    /**
     * @brief Writes info about this block to stream.
     * @param stream stream to write to
     */
    void dump(std::ostream& stream) const;
private:
    void loadBlock(std::istream& in);
    void loadTransactions(std::istream& in, std::string& line);
    Transaction loadTransaction(std::istream& in, std::string& line);
    Input loadInput(std::istream& in, std::string& line);
    Output loadOutput(std::istream& in, std::string& line);
    std::string nextAttributeName(std::string line);
    std::string nextStrAttributeValue(std::string line);
    int nextIntAttributeValue(std::string line);
    double nextDoubleAttributeValue(std::string line);
    void handleLongAttName(std::istream& in);

    std::string m_hash;
    std::string m_prev_block;
    std::map<std::string, Transaction> m_txs;
};

class decoding_error : public std::runtime_error {
public:
    decoding_error(const char* what) : std::runtime_error(what) { };
};
class not_printable_error : public decoding_error { 
public:
    not_printable_error() : decoding_error("not decodable as printable ASCII") { };
};
class missing_word_error : public decoding_error {
public:
    missing_word_error() : decoding_error("no possible code") { };
};

#endif /* end of include guard: BITCOIN_H */
