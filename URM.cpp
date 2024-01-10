#include "URM.hpp"

URM::URM() {
    tempFileName = "instructions.urm";
    numberOfInstructions = 0;
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

void URM::loadFromFile(const std::string& fileName) {
    std::string code = "CODE.urm";

    // if (std::remove(code.c_str()) != 0) {
    //     std::cerr << "Error deleting " << code << "\n";
    // }

    memory.clear();
    add(fileName);
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
        quote(prompt);

        std::stringstream ss(prompt);
        ss >> currentInstruction;
        evaluate();
    }

    std::cout << "Bye!";
}

void URM::JUMP(const std::size_t instructionNumber) {

    std::size_t counter = 0;


    while (counter < instructionNumber)
    {
        if (!inFile.eof())
        {
            inFile >> currentInstruction;
        }
        else
        {
            inFile.tellg(); //jumped reached beyond scope of the file
            return;
        }
        ++counter;
    }

    inFile.tellg();
}

void URM::IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z) {
    if (memory.equal(x, y)) {
        JUMP(z);
    }
}

void URM::run() {
    inFile.open(tempFileName, std::ios::in);

    std::streampos lastPosition;

    std::size_t processedInstructions = 0; // keep track of processed instructions

    while (!inFile.eof() && processedInstructions < numberOfInstructions) {

        if (currentInstruction.type == Tokenizer::JUMP || currentInstruction.type == Tokenizer::IF_JUMP)
        {
            jumpEval(processedInstructions);
        }

        inFile >> currentInstruction;
        evaluate();

        ++processedInstructions;
        lastPosition = inFile.tellg(); // keep track of position in the tempfile
    }

    while (processedInstructions < numberOfInstructions - 1) { // check whether the tempfile was changed
        inFile.close();
        inFile.open(tempFileName, std::ios::in); // reopen the tempfile to reload the data
        inFile.seekg(lastPosition);              // go to the newest instruction


        for (; processedInstructions < numberOfInstructions - 1; processedInstructions++) {
            if (currentInstruction.type == Tokenizer::JUMP || currentInstruction.type == Tokenizer::IF_JUMP)
            {
                jumpEval(processedInstructions);
            }
            inFile >> currentInstruction;
            evaluate();
        }

        lastPosition = inFile.tellg();
    }
    inFile.close();
}

void URM::add(const std::string& fileName) {
    outFile.open(tempFileName, std::ios::app);
    assert(outFile.is_open());

    std::ifstream fileToAdd(fileName);

    if (!fileToAdd) {
        std::cerr << "Unable to open input file: " << fileName;
        return;
    }

    std::string line;
    while (std::getline(fileToAdd, line)) {
        outFile << line << "\n";
        ++numberOfInstructions;
    }

    outFile.close();
}

void URM::quote(const std::string& instruction) {
    outFile.open(tempFileName, std::ios::app);
    assert(outFile.is_open());

    if (outFile.tellp() != 0) {
        outFile << "\n"; // Add a newline before appending the instruction
    }

    outFile << instruction;
    ++numberOfInstructions;

    outFile.close();
}

void URM::jumpEval(std::size_t& processedInstructions)
{
    switch (currentInstruction.type)
    {
    case Tokenizer::JUMP:
        JUMP(currentInstruction.value[0] - processedInstructions);
        processedInstructions += currentInstruction.value[0] + 1;
        break;

    case Tokenizer::IF_JUMP:
        IF_JUMP(currentInstruction.value[0], currentInstruction.value[1], currentInstruction.value[2] - processedInstructions);

    default:
        break;
    }
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
        memory.MOVE(currentInstruction.value[0],
            currentInstruction.value[1]);
        break;

    case Tokenizer::RANGE_ZERO:
        memory.zero(currentInstruction.value[0],
            currentInstruction.value[1]);
        break;

    case Tokenizer::SET:
        memory.set(currentInstruction.value[0],
            currentInstruction.value[1]);
        break;

    case Tokenizer::COPY:
        memory.copy(currentInstruction.value[0],
            currentInstruction.value[1],
            currentInstruction.value[2]);
        break;

    case Tokenizer::MEM:
        memory.mem(currentInstruction.value[0],
            currentInstruction.value[1]);
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