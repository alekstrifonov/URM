# URM

## Introduction

Creating an unlimited register machine (URM) for a data structures project.

On top of the URM's 5 basic instructions we have 10 additional commands which we'll be listed in SECTION X.

The way a user interacts with the URM is through the console and the input gets evaluated at runtime like an interpreter.

## Instructions

1) ZERO n:     Writes the value 0 in the cell with address n.
2) INC n:      Increments by one the value written in the address cell n.
3) MOVE x y:   Assigns the cell with address y the value of the cell with address x.
4) JUMP z:     Program execution “jumps” and continues from the instruction with sequence number z. If the program has less than z + 1 instructions, execution is terminated.
5) JUMP x y z: If the contents of cells x and y match, JUMP z gets called, else the program continues with the next instruction.

## Commands

1)  /zero x y Reset memory cells with addresses from x to y inclusive.
2)  /set x y: Change the y content of the cell with address x.
3)  /copy x y z: Copies the contents of z consecutive cells, starting starting from address x in payment z consecutive cells starting from address y.
4)  /mem x y: Outputs the contents of cells with addresses from x to y inclusive to standard output.
5)  /load filename: Loads a new URM program from a text file. The current program gets terminated and replaced by <filename>. The new program is not being executed. 
6)  /run: Executes the loaded program, going in order through the instructions (except for JUMP). When the end of the loaded file has been reached, execution is terminated.
7)  /add <filename>: Extends the loaded program by concatenating it with <filename>
8)  /quote <string>: Adds a new instruction/command at the end of the loaded program.
9)  /code: Outputs the loaded program.
10) /comments <string>: A comment that gets ignored

## Structure of the Project

Given the instructions and commands we can divide them into two types:

    - Those that interact with the memory of the URM
        - ZERO
        - INC
        - MOVE
        - /zero
        - /set
        - /copy
        - /mem
    - Those that interact with the flow of the instructions
        - The rest of the listed above commands and instructions


The user starts the URM by creating a URM object and calling it's '.dialogue' method.
The input is read and added to a temporary file that is keeping our loaded program.
The input also gets parsed with the 'Tokenizer' class and is assigned a Token after which it's evaluated.
Depending on the called instruction/command the evaluation either works with the URM's memory or with the loaded program.
Process is finished when the user writes 'exit'.

## Sparse Array Class

### Overview:
The sparse array class is tasked with representing our URM's memory and managing the operetions regarding it.

It's only private member is 'std::map<std::size_t, unsigned int> memory' whose key represents our memory's index and value is our URM's value at that index.

**Public members**

```c++
    - SparseArray() : Default constructor
    - SparseArray(std::vector<unsigned int> x) : Constructor that takes a vector and copies it to memory - **Used for Testing**
    - std::size_t size() const : Returns the size of our memory - **Used for Testing**

    - const std::vector<unsigned int> getValues() const : Returns a vector of all the non-zero values of the memory - **Used for Testing**
    - const std::vector<std::size_t> getIndexes() const : Returns a vector of all the indexes of non-zero values - **Used for Testing**

    - bool equal(const std::size_t x, const std::size_t y): Checks if the values of indices x and y are equal - **Used in JUMP**
    - void clear() : Clears the memory - **Used in /load**
``` 

**The functionality of the following methods was documented in Instructions and Commands**

```c++
    - void ZERO(const std::size_t position)
    - void INC(const std::size_t position)
    - void MOVE(const std::size_t x, const std::size_t y)

    - void zero(const std::size_t begin, const std::size_t end)
    - void set(const std::size_t position, unsigned int newValue)
    - void copy(const std::size_t begin, const std::size_t end, const std::size_t ammountToCopy)
    - void mem(const std::size_t begin, const std::size_t end)
```

## Tokenizer Class

### Overview

The tokenizer class is tasked with taking a stream as an input and returning a token.

The different Token types correspond to our commands and instructions.

***The Token**
```c++
    struct Token {
        Tokens type;
        std::string keyword;
        std::vector<std::size_t> value; 

        bool operator==(const Token&);
    };
```

We use a vector since not all functions are unitary and some don't even take arguments.

The `operator==` is used for testing.

**Public members**
```c++
    std::istream& operator>>(std::istream&, Tokenizer::Token&);
```

We use the operator to read from our temporary file and evaluate the tokens.

## URM Class

### Overview

The URM class is tasked with taking an input stream, tokenizing it and evaluating it - either changing the contents of its memory, or the order of operations.

**Private members**
```c++
    Tokenizer::Token currentInstruction; 
    SparseArray memory;
    std::size_t numberOfInstructions;
    std::string tempFileName;
    std::ofstream outFile;
    std::ifstream inFile;
```

    - numberOfInstructions is used for our file handling and JUMP instructions.
    - we store the given commands and instructions in a temporary file that get's deleted after program
    - we read and write to the tempfile using the fstreams inFile and outFile.

**Public members**
```c++
    URM(); 
    ~URM();

    Tokenizer::Token getCurrentInstruction(std::istream& is);

    void loadFromFile(const std::string& fileName); //used in /add - public for testing purposes

    void dialogue(); //this is how the user interacts with the interpreter.

    void evaluate(); // evaluates the currentInstruction - public for testing

    void getInstructions() //used in  /code - public for testing
```