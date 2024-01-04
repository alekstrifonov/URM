#include "URM.hpp"

URM::URM()
{
    JUMP_INCREMENT = 0;
    tempFileName = "instructions.urm";
    numberOfInstructions = 0;
    clearTempFile();
    inFile.open(tempFileName, std::ios::in);
}

URM::~URM()
{
    if (outFile.is_open())
        outFile.close();
    if (inFile.is_open())
        inFile.close();
}

void URM::clearTempFile()
{
    std::ofstream clearFile(tempFileName, std::ios::trunc);
    if (clearFile.is_open())
    {
        clearFile.close();
    }
}

Tokenizer::Token URM::getCurrentInstruction(std::istream &is)
{
    is >> currentInstruction;
    return currentInstruction;
}

void URM::JUMP(const std::size_t instructionNumber, std::istream &is)
{
    for (std::size_t i = 0; i < instructionNumber + JUMP_INCREMENT; i++)
    {
        is >> currentInstruction;
    }
}

void URM::IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z, std::istream &is)
{
    if (memory.equal(x, y))
    {
        JUMP(z, is);
    }
}

void URM::loadFromFile(const std::string &fileName)
{
    memory.clear();
    add(fileName);
}

void URM::run()
{
    assert(inFile.is_open());

    std::streampos lastPosition;


    std::size_t processedInstructions = 0; //keep track of processed instructions

    while (!inFile.eof() && processedInstructions < numberOfInstructions)
    {
        inFile >> currentInstruction;
        std::cout << "CURRENT I: " << currentInstruction.type << std::endl;
        evaluate(inFile);

        ++processedInstructions; 
        lastPosition = inFile.tellg(); //keep track of position in the tempfile
    }

    while(processedInstructions < numberOfInstructions - 1) //check whether the tempfile was changed
    {
        inFile.close();
        inFile.open(tempFileName, std::ios::in); //reopen the tempfile to reload the data
        inFile.seekg(lastPosition); //go to the newest instruction

        for (;processedInstructions < numberOfInstructions - 1; processedInstructions++)
        {

            inFile >> currentInstruction;
            std::cout << "CURRENT I: " << currentInstruction.type << std::endl;
            evaluate(inFile);
        }

        lastPosition = inFile.tellg();
    }

    if (inFile.is_open())
    {
        inFile.close();
    }
}

void URM::add(const std::string &fileName)
{
    outFile.open(tempFileName, std::ios::app);
    assert(outFile.is_open());

    std::ifstream fileToAdd(fileName);

    if (!fileToAdd)
    {
        std::cerr << "Unable to open input file: " << fileName;
        return;
    }

    std::string line;
    while (std::getline(fileToAdd, line))
    {
        outFile << line << "\n";
        ++numberOfInstructions;
    }
 
    outFile.close();
}

void URM::evaluate(std::istream &is)
{
    switch (currentInstruction.type)
    {
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
        JUMP(currentInstruction.value[0], is);
        break;

    case Tokenizer::IF_JUMP:
        IF_JUMP(currentInstruction.value[0], currentInstruction.value[1], currentInstruction.value[2], is);
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
        std::cout << "We've added: " << currentInstruction.keyword << std::endl;
        add(currentInstruction.keyword);
        break;

    case Tokenizer::QUOTE:
        /* code */
        break;
    case Tokenizer::CODE:
        /* code */
        break;

    case Tokenizer::COMMENT: // add exception for empty comments
        break;

    default:
        break;
    }
}