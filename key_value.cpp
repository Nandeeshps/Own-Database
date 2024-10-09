#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <algorithm> 

void handleKeyValueStorage() {
    std::string filename;
    std::map<std::string, std::string> keyValueStore;
    std::vector<std::pair<std::string, std::string>> keyValueList;
    bool fileOpen = false;

    std::cout << "Command Line Interface for Key-Value Storage\n";
    std::cout << "Commands:\n";
    std::cout << "  file <filename>  - Create or open a file in Key-value directory\n";
    std::cout << "  key=<Keyname> value=<Value>  - Enter a key-value pair\n";
    std::cout << "  read <filename>  - Read operations for a file\n";
    std::cout << "  update key=<Keyname> value=<Value>  - Update the value for a key\n";
    std::cout << "  save  - Save the file\n";
    std::cout << "  exit  - Exit the program\n";

    std::string command;
    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "file") {
            std::cin >> filename;
            std::filesystem::create_directory("Key-value");
            std::ifstream infile("Key-value/" + filename + ".kv");
            keyValueStore.clear();
            keyValueList.clear();
            std::string line;
            while (std::getline(infile, line)) {
                size_t delimiterPos = line.find(" : ");
                if (delimiterPos != std::string::npos) {
                    std::string key = line.substr(0, delimiterPos);
                    std::string value = line.substr(delimiterPos + 3);
                    keyValueStore[key] = value;
                    keyValueList.push_back({key, value});
                }
            }
            infile.close();
            fileOpen = true;
            std::cout << "File 'Key-value/" << filename << ".kv' is open for writing." << std::endl;
        } else if (command.rfind("key=", 0) == 0 && fileOpen) {
            std::string key = command.substr(4);
            std::cin >> command;
            if (command.rfind("value=", 0) == 0) {
                std::string value = command.substr(6);
                keyValueStore[key] = value;
                keyValueList.push_back({key, value});
                std::cout << "Key-Value pair (" << key << " : " << value << ") added/updated." << std::endl;
            } else {
                std::cerr << "Invalid command. Expected 'value=<Value>'." << std::endl;
            }
        } else if (command == "read") {
            std::cin >> filename;
            std::ifstream infile("Key-value/" + filename + ".kv");
            if (!infile.is_open()) {
                std::cerr << "Error opening file!" << std::endl;
                continue;
            }
            keyValueStore.clear();
            keyValueList.clear();
            std::string line;
            while (std::getline(infile, line)) {
                size_t delimiterPos = line.find(" : ");
                if (delimiterPos != std::string::npos) {
                    std::string key = line.substr(0, delimiterPos);
                    std::string value = line.substr(delimiterPos + 3);
                    keyValueStore[key] = value;
                    keyValueList.push_back({key, value});
                }
            }
            infile.close();
            std::string readCommand;
            while (true) {
                std::cout << filename << "> ";
                std::cin >> readCommand;
                if (readCommand == "all") {
                    for (const auto& pair : keyValueList) {
                        std::cout << pair.first << " : " << pair.second << std::endl;
                    }
                } else if (readCommand.find('[') != std::string::npos && readCommand.find(']') != std::string::npos) {
                    size_t start = readCommand.find('[') + 1;
                    size_t end = readCommand.find(']');
                    std::string indexStr = readCommand.substr(start, end - start);
                    try {
                        int index = std::stoi(indexStr);
                        if (index >= 0 && index < keyValueList.size()) {
                            std::cout << keyValueList[index].first << " : " << keyValueList[index].second << std::endl;
                        } else {
                            std::cerr << "Index out of range." << std::endl;
                        }
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Invalid index format." << std::endl;
                    }
                } else if (keyValueStore.find(readCommand) != keyValueStore.end()) {
                    std::cout << "Value for key '" << readCommand << "' is: " << keyValueStore[readCommand] << std::endl;
                } else if (readCommand == "back") {
                    break;
                } else {
                    std::cerr << "Invalid command. Use 'all', '<keyname>', '<filename>[<index>]', or 'back'." << std::endl;
                }
            }
        } else if (command == "update" && fileOpen) {
            std::cin >> command;
            if (command.rfind("key=", 0) == 0) {
                std::string key = command.substr(4);
                std::cin >> command;
                if (command.rfind("value=", 0) == 0) {
                    std::string value = command.substr(6);
                    if (keyValueStore.find(key) != keyValueStore.end()) {
                        keyValueStore[key] = value;
                        for (auto& pair : keyValueList) {
                            if (pair.first == key) {
                                pair.second = value;
                                break;
                            }
                        }
                        std::cout << "Key-Value pair (" << key << " : " << value << ") updated." << std::endl;
                    } else {
                        std::cout << "Key '" << key << "' not found. Use 'key=<Keyname> value=<Value>' to add a new key-value pair." << std::endl;
                    }
                } else {
                    std::cerr << "Invalid command. Expected 'value=<Value>'." << std::endl;
                }
            } else {
                std::cerr << "Invalid command. Expected 'key=<Keyname>'." << std::endl;
            }
        } else if (command == "save" && fileOpen) {
            std::ofstream outfile("Key-value/" + filename + ".kv");
            for (const auto& pair : keyValueList) {
                outfile << pair.first << " : " << pair.second << std::endl;
            }
            outfile.close();
            std::cout << "File 'Key-value/" << filename << ".kv' has been saved." << std::endl;
        } else if (command == "exit") {
            if (fileOpen) {
                std::ofstream outfile("Key-value/" + filename + ".kv");
                for (const auto& pair : keyValueList) {
                    outfile << pair.first << " : " << pair.second << std::endl;
                }
                outfile.close();
                std::cout << "File 'Key-value/" << filename << ".kv' has been saved." << std::endl;
            }
            break;
        } else {
            std::cerr << "Invalid command or no file open. Please follow the command format." << std::endl;
        }
    }
}
