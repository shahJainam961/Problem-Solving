#include <bits/stdc++.h>
using namespace std;

// Structure to represent a row in the table
struct Row {
    std::vector<std::string> values;
};

// Structure to represent a B-tree node
struct BTreeNode {
    std::vector<std::pair<std::string, int>> keys; // pairs of primary key and file offset
    std::vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool leaf) : isLeaf(leaf) {}
};

// Class representing a table in the database
class Table {
private:
    std::string tableName;
    std::vector<std::string> columns;
    std::string primaryColumn;
    std::map<std::string, int> columnIndices;
    std::fstream dataFile;
    BTreeNode* root;

public:
    Table(const std::string& name, const std::vector<std::string>& cols, const std::string& primary)
        : tableName(name), columns(cols), primaryColumn(primary), root(nullptr) {
        // Create a mapping of column names to their indices
        for (int i = 0; i < columns.size(); ++i) {
            columnIndices[columns[i]] = i;
        }

        // Open or create the data file for the table
        dataFile.open(tableName + ".dat", std::ios::out | std::ios::in | std::ios::binary | std::ios::app);

        // Load the B-tree index from file or create a new one if it doesn't exist
        std::fstream indexFile(tableName + ".idx", std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
        if (indexFile) {
            // If the index file exists, load the root node from it
            indexFile.seekg(0, std::ios::beg);
            root = readBTreeNode(indexFile);
        } else {
            // If the index file doesn't exist, create a new empty root node
            root = createBTreeNode(true);
            writeBTreeNode(root, indexFile);
        }
        indexFile.close();
    }

    ~Table() {
        // Save the B-tree index to file
        std::fstream indexFile(tableName + ".idx", std::ios::out | std::ios::binary | std::ios::trunc);
        writeBTreeNode(root, indexFile);
        indexFile.close();

        dataFile.close();
    }

    // Insert a row into the table
    void insertRow(const Row& row) {
        // Write the row values to the data file
        std::streampos offset = dataFile.tellg();
        for (const std::string& value : row.values) {
            dataFile.write(value.c_str(), value.size());
            dataFile.write("|", 1);
        }
        dataFile.write("\n", 1);
        dataFile.flush();

        // Insert the primary key and file offset into the B-tree index
        insertIntoBTree(row.values[columnIndices[primaryColumn]], offset);
    }

    // Perform a SELECT query on the table
    std::vector<Row> selectRows(const std::string& condition = "") {
        std::vector<Row> result;

        if (condition.empty()) {
            // Read all rows
            std::string line;
            dataFile.seekg(0, std::ios::beg);
            while (std::getline(dataFile, line)) {
                std::istringstream iss(line);
                std::string value;
                Row row;

                // Split the line by delimiter '|'
                while (std::getline(iss, value, '|')) {
                    row.values.push_back(value);
                }

                result.push_back(row);
            }
        } else {
            // Perform B-tree search based on the primary key
            std::vector<std::string> primaryKeys = searchBTree(condition);

            // Read rows from data file using the file offsets obtained from the B-tree search
            for (const std::string& primaryKey : primaryKeys) {
                std::streampos offset = std::stol(primaryKey);
                dataFile.seekg(offset, std::ios::beg);
                std::string line;
                std::getline(dataFile, line);
                std::istringstream iss(line);
                std::string value;
                Row row;

                // Split the line by delimiter '|'
                while (std::getline(iss, value, '|')) {
                    row.values.push_back(value);
                }

                result.push_back(row);
            }
        }

        return result;
    }

private:
    // B-tree functions

    BTreeNode* createBTreeNode(bool leaf) {
        BTreeNode* node = new BTreeNode(leaf);
        return node;
    }

    void writeBTreeNode(BTreeNode* node, std::fstream& file) {
        int numKeys = node->keys.size();
        file.write(reinterpret_cast<char*>(&numKeys), sizeof(int));

        for (const auto& key : node->keys) {
            int keyLength = key.first.size();
            file.write(reinterpret_cast<char*>(&keyLength), sizeof(int));
            file.write(key.first.c_str(), keyLength);

            std::streampos offset = key.second;
            file.write(reinterpret_cast<char*>(&offset), sizeof(std::streampos));
        }

        if (!node->isLeaf) {
            for (const auto& child : node->children) {
                writeBTreeNode(child, file);
            }
        }
    }

    BTreeNode* readBTreeNode(std::fstream& file) {
        BTreeNode* node = new BTreeNode(false);

        int numKeys;
        file.read(reinterpret_cast<char*>(&numKeys), sizeof(int));

        for (int i = 0; i < numKeys; ++i) {
            int keyLength;
            file.read(reinterpret_cast<char*>(&keyLength), sizeof(int));
            std::string key(keyLength, '\0');
            file.read(&key[0], keyLength);

            std::streampos offset;
            file.read(reinterpret_cast<char*>(&offset), sizeof(std::streampos));

            node->keys.push_back(std::make_pair(key, offset));
        }

        if (!node->isLeaf) {
            for (int i = 0; i < numKeys + 1; ++i) {
                node->children.push_back(readBTreeNode(file));
            }
        }

        return node;
    }

    void insertIntoBTree(const std::string& key, std::streampos offset) {
        if (root == nullptr) {
            root = createBTreeNode(true);
        }

        BTreeNode* node = root;
        if (node->keys.size() == 2 * degree - 1) {
            BTreeNode* newNode = createBTreeNode(false);
            newNode->children.push_back(node);
            splitChild(newNode, 0, node);
            root = newNode;
            insertNonFull(newNode, key, offset);
        } else {
            insertNonFull(node, key, offset);
        }
    }

    void insertNonFull(BTreeNode* node, const std::string& key, std::streampos offset) {
        int i = node->keys.size() - 1;
        if (node->isLeaf) {
            while (i >= 0 && key < node->keys[i].first) {
                --i;
            }
            node->keys.insert(node->keys.begin() + i + 1, std::make_pair(key, offset));
        } else {
            while (i >= 0 && key < node->keys[i].first) {
                --i;
            }
            ++i;
            if (node->children[i]->keys.size() == 2 * degree - 1) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i].first) {
                    ++i;
                }
            }
            insertNonFull(node->children[i], key, offset);
        }
    }

    void splitChild(BTreeNode* parent, int index, BTreeNode* child) {
        BTreeNode* newNode = createBTreeNode(child->isLeaf);
        parent->keys.insert(parent->keys.begin() + index, child->keys[degree - 1]);
        parent->children.insert(parent->children.begin() + index + 1, newNode);

        for (int i = 0; i < degree - 1; ++i) {
            newNode->keys.push_back(child->keys[i + degree]);
        }
        if (!child->isLeaf) {
            for (int i = 0; i < degree; ++i) {
                newNode->children.push_back(child->children[i + degree]);
            }
        }

        child->keys.resize(degree - 1);
        if (!child->isLeaf) {
            child->children.resize(degree);
        }
    }

    std::vector<std::string> searchBTree(const std::string& key) {
        std::vector<std::string> result;
        searchBTree(root, key, result);
        return result;
    }

    void searchBTree(BTreeNode* node, const std::string& key, std::vector<std::string>& result) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i].first) {
            ++i;
        }
        if (i < node->keys.size() && key == node->keys[i].first) {
            result.push_back(std::to_string(node->keys[i].second));
        }
        if (node->isLeaf) {
            return;
        }
        if (i == node->keys.size() || key < node->keys[i].first) {
            searchBTree(node->children[i], key, result);
        } else {
            searchBTree(node->children[i + 1], key, result);
        }
    }

    // Helper functions

    std::vector<std::string> splitString(const std::string& input, char delimiter) {
        std::vector<std::string> result;
        std::istringstream iss(input);
        std::string token;
        while (std::getline(iss, token, delimiter)) {
            result.push_back(token);
        }
        return result;
    }
};

int main() {
    // Create a table
    std::string tableName = "Employees";
    std::vector<std::string> columns = { "ID", "Name", "Age" };
    std::string primaryColumn = "ID";
    Table employees(tableName, columns, primaryColumn);

    // Insert rows into the table
    Row row1{ { "1", "John Doe", "30" } };
    employees.insertRow(row1);

    Row row2{ { "2", "Jane Smith", "25" } };
    employees.insertRow(row2);

    // Perform SELECT queries
    std::vector<Row> results = employees.selectRows("Age=30");
    for (const Row& row : results) {
        for (const std::string& value : row.values) {
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}
