#include <iostream>

int main() {
    int choice;

    std::cout << "Choose how to store data:\n"<<
        "1. Table Storage (Rows)\n"<<
        "2. Document Storage (JSON-like)\n"<<
        "3. Key-Value Storage\n"<<
        "4. Manual Storage \n";
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Data will be stored in Table format" << std::endl;
            break;
        case 2:
            std::cout << "Data will be stored in Key-Value Format" << std::endl;
            break;
        case 4:
            std::cout << "Data will be stored in Manual way" << std::endl;
            break;
        case 3:
        std::cout << "Data will be stored in Document format" << std::endl;
        break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
            break;
    }

    return 0;
}
