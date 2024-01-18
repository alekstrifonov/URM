#include "URM.hpp"

void URM::updateJump(std::string& input, size_t increment) const {
    std::istringstream iss(input);
    Tokenizer::Token t;
    iss >> t;
    std::ostringstream oss;

    if (t.type == Tokenizer::JUMP)
    {
        t.value[0] += increment;
        oss << t.keyword << " " << t.value[0];
    }
    else {
        t.value[2] += increment;
        oss << t.keyword << " " << t.value[0] << " " << t.value[1] << " " << t.value[2];

    }
    input = oss.str();
}

URM::URM() {
    tempFileName = "instructions.urm";
    numberOfInstructions = 0;
    jumpIncrement = 0;
    clearTempFile();
}

URM::~URM() {
    if (outFile.is_open())
        outFile.close();
    if (inFile.is_open())
        inFile.close();

    if (std::remove(tempFileName.c_str()) != 0) {
        std::cerr << "Error deleting the file: " << tempFileName << '\n';
    }
}

void URM::clearTempFile() {
    std::ofstream clearFile(tempFileName, std::ios::trunc);
    if (clearFile.is_open()) {
        clearFile.close();
    }
}

void URM::refreshFile(std::streampos position)
{
    assert(inFile.is_open());
    inFile.close();
    inFile.open(tempFileName);
    inFile.clear();
    inFile.seekg(0, std::ios::beg);
    inFile.seekg(position);
}

Tokenizer::Token URM::getCurrentInstruction(std::istream& is) {
    is >> currentInstruction;
    return currentInstruction;
}

void URM::getInstructions() {
    std::ofstream code("CODE.urm");
    inFile.open(tempFileName, std::ios::in);

    std::string line;

    if (code && inFile) {
        while (std::getline(inFile, line)) {
            code << line << "\n";
        }
    }

    code.close();
}

bool URM::isInstruction() const
{
    return currentInstruction.type >= 0 && currentInstruction.type < 5;
}

void URM::updateNumInstrucitons(const std::string& line)
{
    Tokenizer::Token token;
    std::istringstream lineStream(line);
    lineStream >> token;

    if (token.type >= 0 && token.type < 5) {
        ++numberOfInstructions;
    }

}

//-------------------------------------------------------------------------------------------------------------------------------------------

void URM::loadFromFile(const std::string& fileName) {
    clearTempFile();
    memory.clear();

    outFile.open(tempFileName);

    std::ifstream fileToAdd(fileName);

    if (!fileToAdd) {
        std::cerr << "Unable to open input file: " << fileName;
        return;
    }

    std::string line;

    while (std::getline(fileToAdd, line)) {
        if (outFile.tellp() != 0) {
            outFile << "\n"; // Add a newline before appending the instruction
        }

        outFile << line;

        updateNumInstrucitons(line);

    }
    outFile.close();
}

void URM::dialogue() {
    std::string prompt;
    std::cout << "Program is running - Type exit to escape\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, prompt);

        if (prompt == "exit") {
            break;
        }

        std::stringstream ss(prompt);
        ss >> currentInstruction;
        evaluate();
    }

    std::cout << "Bye!";
}

void URM::IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z) {
    if (memory.equal(x, y)) {
        JUMP(z);
    }
}

void URM::JUMP(const std::size_t instructionNumber) {
    inFile.seekg(0, std::ios::beg);

    if (!inFile) {
        std::cerr << "Error: Unable to seek in the input file." << std::endl;
        return;
    }

    std::size_t counter = 0;

    while (counter < numberOfInstructions) {
        inFile >> currentInstruction;
        if (isInstruction()) {
            counter++;
        }
    }
}


void URM::run() {
    inFile.open(tempFileName);

    while (inFile >> currentInstruction) {
        evaluate();
    }

    inFile.close();
}


void URM::add(const std::string& fileName) {
    outFile.open(tempFileName, std::ios::app);

    jumpIncrement = numberOfInstructions;

    std::ifstream fileToAdd(fileName);

    if (!fileToAdd) {
        std::cerr << "Unable to open input file: " << fileName;
        return;
    }

    std::string line;
    while (std::getline(fileToAdd, line)) {
        if (!line.empty()) {
            if (!line.find("JUMP")) { //Increment jump depending on the number of previously loaded instructions
                updateJump(line, jumpIncrement);
            }

            if (outFile.tellp() != 0) {
                outFile << "\n"; // Add a newline before appending the instruction
            }

            outFile << line;

            updateNumInstrucitons(line);
        }
    }
    outFile.close();
    refreshFile(inFile.tellg()); //reload the file for the /command
}

void URM::quote(const std::string& line) {
    outFile.open(tempFileName, std::ios::app);

    if (!line.empty()) {
        if (outFile.tellp() != 0) {
            outFile << "\n";
        }

        outFile << line;

        updateNumInstrucitons(line);
    }

    outFile.close();
    refreshFile(inFile.tellg());
}

void URM::evaluate() {
    switch (currentInstruction.type) {
    case Tokenizer::ZERO:
        memory.ZERO(currentInstruction.value[0]);
        break;

    case Tokenizer::INC:
        memory.INC(currentInstruction.value[0]);
        break;

    case Tokenizer::MOVE:
        memory.MOVE(currentInstruction.value[0], currentInstruction.value[1]);
        break;

    case Tokenizer::JUMP:
        JUMP(currentInstruction.value[0]);
        break;

    case Tokenizer::IF_JUMP:
        IF_JUMP(currentInstruction.value[0], currentInstruction.value[1], currentInstruction.value[2]);
        break;

    case Tokenizer::RANGE_ZERO:
        memory.zero(currentInstruction.value[0], currentInstruction.value[1]);
        break;

    case Tokenizer::SET:
        memory.set(currentInstruction.value[0], currentInstruction.value[1]);
        break;

    case Tokenizer::COPY:
        memory.copy(currentInstruction.value[0], currentInstruction.value[1], currentInstruction.value[2]);
        break;

    case Tokenizer::MEM:
        memory.mem(currentInstruction.value[0], currentInstruction.value[1]);
        break;

    case Tokenizer::LOAD:
        loadFromFile(currentInstruction.keyword);
        break;

    case Tokenizer::RUN:
        run();
        break;
    case Tokenizer::ADD:
        add(currentInstruction.keyword);
        break;

    case Tokenizer::QUOTE:
        quote(currentInstruction.keyword);
        break;
    case Tokenizer::CODE:
        getInstructions();
        break;

    case Tokenizer::COMMENT:
        break;

    default:
        break;
    }
}